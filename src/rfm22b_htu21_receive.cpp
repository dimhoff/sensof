/**
 * sensof_rfm22b_receive.cpp - Receive Sensof-HT frames using a RFM22B receiver
 *
 * Copyright (c) 2015, David Imhoff <dimhoff.devel@gmail.com>
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
#include "rfm22b.h"
#include <endian.h>
#include <openssl/aes.h>

//#define DEBUG 1
//#define DISABLE_CRC 1
//#define USE_OOK 1
#define USE_ENCRYPTION 1

#pragma pack(1)
struct frame_t {
	// Encrypted Header
	uint32_t  id;
	uint16_t  cnt;
	uint16_t  _reserved1;

	// Data
	uint16_t  temp;
	uint16_t  hum;
	uint32_t  _reserved2;
};
#pragma pack()

int main() {
	// Initialise encryption parameters
#ifdef USE_ENCRYPTION
	AES_KEY kobj;
	uint8_t key[128/8] = {
#include "key.cinc"
	};
	if (AES_set_decrypt_key(key, 128, &kobj) != 0) {
		fprintf(stderr, "Failed to set decryption key\n");
		exit(EXIT_FAILURE);
	}
#endif // USE_ENCRYPTION

	// Initialise the radio
	RFM22B *myRadio = new RFM22B("/dev/spidev0.0");
	
	// Set the bus speed
	myRadio->setMaxSpeedHz(50000);
	
	// Radio configuration
	myRadio->reset();
	myRadio->setCarrierFrequency(434.0e6);
	myRadio->setModulationType(RFM22B::OOK);
	myRadio->setModulationDataSource(RFM22B::FIFO);
	
#ifdef DISABLE_CRC
	myRadio->setCRCMode(RFM22B::CRC_DISABLED);
#else
	myRadio->setCRCMode(RFM22B::CRC_NORMAL);
#endif

	// Magic numbers from 'Si443x-Register-Settings_RevB1.xls' calculator
	// sheet.
#ifdef USE_OOK
	// 9600 bps OOK
	myRadio->setDataRate(9600);
	myRadio->setRegister(0x58, 0x80);
	myRadio->setRegister(0x1c, 0xa1);
	myRadio->setRegister(0x20, 0x39);
	myRadio->setRegister(0x21, 0x20);
	myRadio->setRegister(0x22, 0x68);
	myRadio->setRegister(0x23, 0xdc);
	myRadio->setRegister(0x24, 0x10);
	myRadio->setRegister(0x25, 0x6B);
	myRadio->setRegister(0x2C, 0x28);
	myRadio->setRegister(0x2d, 0x82);
	myRadio->setRegister(0x2e, 0x2a);
	myRadio->setRegister(0x1F, 0x00);
	myRadio->setRegister(0x69, 0x60);
#else // USE_OOK
	// 9600 bps FSK (AFC)
	myRadio->setRegister(0x1C, 0x06);
	myRadio->setRegister(0x1D, 0x44);
	myRadio->setRegister(0x1E, 0x0A);
	myRadio->setRegister(0x1F, 0x00);
	myRadio->setRegister(0x20, 0xA1);
	myRadio->setRegister(0x21, 0x20);
	myRadio->setRegister(0x22, 0x4E);
	myRadio->setRegister(0x23, 0xA5);
	myRadio->setRegister(0x24, 0x10);
	myRadio->setRegister(0x25, 0x1C);
	myRadio->setRegister(0x2A, 0x28);
	myRadio->setRegister(0x2C, 0x28);
	myRadio->setRegister(0x2D, 0x82);
	myRadio->setRegister(0x2E, 0x2A);
	
	myRadio->setRegister(0x30, 0xA9);
	myRadio->setRegister(0x32, 0x0C);
	myRadio->setRegister(0x33, 0x22);
	myRadio->setRegister(0x34, 0x1A);
	myRadio->setRegister(0x35, 0x2A);
	myRadio->setRegister(0x36, 0x2D);
	myRadio->setRegister(0x37, 0xD4);
	myRadio->setRegister(0x38, 0x00);
	myRadio->setRegister(0x39, 0x00);
	myRadio->setRegister(0x3A, 0x00);
	myRadio->setRegister(0x3B, 0x00);
	myRadio->setRegister(0x3C, 0x00);
	myRadio->setRegister(0x3D, 0x00);
	myRadio->setRegister(0x3E, 0x09);
	myRadio->setRegister(0x3F, 0x00);
	myRadio->setRegister(0x40, 0x00);
	myRadio->setRegister(0x41, 0x00);
	myRadio->setRegister(0x42, 0x00);
	myRadio->setRegister(0x43, 0xFF);
	myRadio->setRegister(0x44, 0xFF);
	myRadio->setRegister(0x45, 0xFF);
	myRadio->setRegister(0x46, 0xFF);
	
	myRadio->setRegister(0x58, 0x80);
	myRadio->setRegister(0x69, 0x60);
	myRadio->setRegister(0x6E, 0x4E);
	myRadio->setRegister(0x6F, 0xA5);
	
	myRadio->setRegister(0x70, 0x2C);
	myRadio->setRegister(0x71, 0x22);
	myRadio->setRegister(0x72, 0x5E);
	
	myRadio->setRegister(0x75, 0x53);
	myRadio->setRegister(0x76, 0x62);
	myRadio->setRegister(0x77, 0x00);
#endif // USE_OOK

	// What header do we want?
	myRadio->setCheckHeader(0x11223344);
	
	// Listen for a packet
	printf("Listening for frames...\n");
	
	while (true) {
		uint8_t buf[RFM22B::MAX_PACKET_LENGTH];
		int len;
		len = myRadio->receive(buf, RFM22B::MAX_PACKET_LENGTH);
		if (len == sizeof(struct frame_t)) {
			struct frame_t *fbuf = (struct frame_t *) buf;

#ifdef USE_ENCRYPTION
			uint8_t outbuf[AES_BLOCK_SIZE];
			AES_decrypt(buf, outbuf, &kobj);
			fbuf = (struct frame_t *) outbuf;

			fprintf(stderr, "Raw decrypted data(len=%d):\n", len);
			for (int i(0); i < len; i++) {
				printf("%.2x ", outbuf[i]);
			}
			putchar('\n');
#endif // USE_ENCRYPTION

			double temp = be16toh(fbuf->temp);
			double hum = be16toh(fbuf->hum);

			temp = -46.85 + 175.72 * temp / 65536;
			hum = -6.0 + 125.0 * hum / 65536;
			printf("%08x#%04x Temperature = %.2f, Humidity = %.2f\n",
				be32toh(fbuf->id), be16toh(fbuf->cnt),
				temp, hum);
		}
#ifdef DEBUG
		if (len > 0) {
			fprintf(stderr, "Raw data(len=%d):\n", len);
			for (int i(0); i < len; i++) {
				printf("%.2x ", buf[i]);
			}
			putchar('\n');
		}
#endif
	}
		
	myRadio->close();

	return EXIT_SUCCESS;
}
