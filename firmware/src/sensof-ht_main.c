/**
 * htu21_main.c - htu21 sensor main
 *
 * Copyright (c) 2014, David Imhoff <dimhoff_devel@xs4all.nl>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the author nor the names of its contributors may
 *       be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "si4010.h"
#include "si4010_api_rom.h"

#include "htu21.h"
#include "rf.h"

// Config
/**
 * Select where the encryption key is stored
 *
 * If set the MTP will hold the encryption key. The key has to be programmed
 * into MTP using the programmer. This means the key can be changed at any 
 * time. Downside is that the key will occupy all available MTP memory.
 *
 * If not set the encryption key will be hard coded into the NVRAM image. 
 * The key is read form a file called 'key.cinc' at compile time. Having the 
 * key in NVRAM means it can not be zeroized, and is hard to change. But it
 * does leave MTP ram for other purposes.
 */
//#define KEY_IN_MTP 1

/**
 * If set don't call shutdown between frames
 *
 * Normally the chip will shutdown between sending frames to conserve energy.
 * However this requires that the program is stored in NVRAM. When developing
 * the firmware is loaded through the C2 interface into RAM and will be lost 
 * when going into shutdown.
 *
 * Setting this define prevents the firmware from shutting down and instead 
 * enters a short wait loop.
 */
//#define NO_SHUTDOWN 1
#undef NO_SHUTDOWN

/**
 * Store packet counter in MTP
 *
 * Store part of the packet counter to MTP to guarantee that counter is always
 * higher then previous time. Else the receiver will think the packet is 
 * replayed.
 *
 * To be able to use this the key can not be stored in MTP.
 */
#define PKT_CNT_IN_MTP 1

#if defined(PKT_CNT_IN_MTP) && defined(KEY_IN_MTP)
#error "Options KEY_IN_MTP and PKT_CNT_IN_MTP are mutually exclusive"
#endif

// Defines
#define AES_BLOCK_SIZE 16	 /**< Size of a AES encryption block */
#define KEY_128_BIT_SIZE (128/8) /**< Size of 128-bit key in bytes */
#define MTP_CTR_24BIT 4		 /**< Magic value to indicate MTP counter is 24-bit */

/**
 * Sensof-HT encrypted payload structure
 *
 * This structure defines the fields of the encrypted payload.
 */
//#pragma pack(1)
struct frame_t {
	// Encrypted Header
	uint32_t id;  /**< Node ID, also provides integrity check */
	uint32_t cnt; /**< Replay protection counter */

	// Data
	uint16_t temp;
	uint16_t hum;
	uint32_t _reserved2;
};
//#pragma pack()
// static_assert(sizeof(struct frame_t) == AES_BLOCK_LEN);

#ifdef KEY_IN_MTP
uint8_t *key = NULL;
#else
const uint8_t xdata key[KEY_128_BIT_SIZE] = {
#include "key.cinc"
};
#endif

//-----------------------------------------------------------------------------
//-- ISR
//-----------------------------------------------------------------------------
/**
 * Temperature Sensor Demodulator ISR
 *
 * Interrupt generated when a temperature sample is ready. This function only 
 * calls the correct SI4010 API functions to process the sample.
 */
void vIsr_Dmd(void) interrupt INTERRUPT_DMD using 2
{

	vDmdTs_ClearDmdIntFlag();
	vDmdTs_IsrCall();
}

//-----------------------------------------------------------------------------
//-- Main
//-----------------------------------------------------------------------------
void main()
{
	struct frame_t fbuf;
	unsigned char htu_failures=0;
	unsigned char htu_measurements=0;
	union {
		// Uses union to be able to access the value as byte array without casting.
		// This saves ~200 bytes code memory...
		uint32_t val;
		uint8_t bytes[4];
	} pkt_cnt;

	// Init various components
	htu21_init();
	rf_setup();

	// NOTE: we don't use vSys_FirstPowerUp() since it automatically calls
	// vSys_Shutdown(). But apparantely it isn't needed:
	// http://community.silabs.com/t5/Wireless/SI4010-demo-with-wakeup-transmit-sleep/m-p/120710/highlight/true#M818


	// Load Config/State
	if ((SYSGEN & M_POWER_1ST_TIME)) {
#ifdef PKT_CNT_IN_MTP
		pbMtp_Read();
		vMtp_IncCount(0, MTP_CTR_24BIT);
		pkt_cnt.val = lMtp_GetDecCount(0, MTP_CTR_24BIT) << 8;
		bMtp_Write(40); // ignore result since we cant do anything about it.
#else
		pkt_cnt.val = 0;
#endif
		vHvram_Write(4, pkt_cnt.bytes[0]);
		vHvram_Write(5, pkt_cnt.bytes[1]);
		vHvram_Write(6, pkt_cnt.bytes[2]);
		vHvram_Write(7, pkt_cnt.bytes[3]);
	} else {
		pkt_cnt.bytes[0] = bHvram_Read(4);
		pkt_cnt.bytes[1] = bHvram_Read(5);
		pkt_cnt.bytes[2] = bHvram_Read(6);
		pkt_cnt.bytes[3] = bHvram_Read(7);
	}
#ifdef KEY_IN_MTP
	key = pbMtp_Read();
#endif

	// Main loop
	while ( 1 )
	{
		htu_measurements++;
		if (htu21_read(&fbuf.temp, &fbuf.hum) == 0) {
			BYTE key_buf[KEY_128_BIT_SIZE];

			fbuf._reserved2 = 0;
			fbuf.id = lSys_GetProdId();

			// Increase packet counter and store to HVRam
			fbuf.cnt = pkt_cnt.val++;
			vHvram_Write(4, pkt_cnt.bytes[0]);
			vHvram_Write(5, pkt_cnt.bytes[1]);
			vHvram_Write(6, pkt_cnt.bytes[2]);
			vHvram_Write(7, pkt_cnt.bytes[3]);
#ifdef PKT_CNT_IN_MTP

			if (pkt_cnt.bytes[3] == 0) {
				pbMtp_Read();
				vMtp_IncCount(0, MTP_CTR_24BIT);
				bMtp_Write(40); // ignore result since we cant do anything about it.
			}
#endif // PKT_CNT_IN_MTP

//TODO: Currently we overwrite fbuf with encrypted data because we haven't got enough DATA ram.
//      It would be better to have fbuf in XDATA. But then the code size becomes to big....
//			BYTE enc_buf[AES_BLOCK_SIZE];
//			memcpy(enc_buf, &fbuf, sizeof(fbuf));

			memcpy(key_buf, key, KEY_128_BIT_SIZE);
			vAes_Cipher((BYTE *) &fbuf, key_buf);

			ezradiopro_send_frame((uint8_t *) &fbuf, sizeof(fbuf));
		} else {
			htu_failures++;
		}

		// Sleep a bit
		{
//  Sleep about 1 min.
#ifdef NO_SHUTDOWN
		unsigned char i = 0;
		i = 0;
		TMR2H = 0;
		TMR2L = 0;

		SYSGEN = 0x07; // lower clock rate to 24MHz/128
		TMR2L_RUN = 1;
//		while (i < 172) {
//		while (i < 86) {
		while (i < 20) {
			while (! TMR2INTH) ;
			TMR2INTH = 0;
			i++;
		}
		TMR2L_RUN = 0;
		SYSGEN = 0x00; // Reset clock rate
#else
#define SLEEP_TIM_POWER_UP 0x01000000
#define SLEEP_TIME_HOUR_SHIFT 4 // 1 hour >> 4 = 225 sec = 3.75 min.
		vSleepTim_SetCount(
			(lSleepTim_GetOneHourValue() >> SLEEP_TIME_HOUR_SHIFT) | 
				SLEEP_TIM_POWER_UP
			);
		vSys_Shutdown();
#endif
		}
	}
}
