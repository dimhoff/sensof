#include "rf.h"

#include <stdlib.h>
#include <string.h>

#include "si4010.h"
#include "si4010_api_rom.h"
#include "crc.h"

#ifndef BOARD_VERSION
#define BOARD_VERSION 2
#endif

// Transmission parameters

// Values are calculated with si4010_calc_regs_110107.ods. Used input data:
// Package: v1: 10-pin MSOP; v2: 14-pin SOIC
//
// Antenna:
// - Alpha: 0 (we don't mind radiant power fluctuation over temperature)
// - Approx. Eff:
//   - v1: 35 % (from ACAG1204-433-T-1314083.pdf datasheet) 
//   - v2: 12.5 % (default)
// - Reactance change: 15 % (default)
// - Manual Impedance: no
//
// Power Amplifier Setup:
// - Total PA Power: 10.5 dBm (Above this sheet starts to complain)
// - Max Radiant Power
// - Center Freq: 433.92 MHz (Center of 433/434 ISM band)
// - Nom. Cap Word: 
//   - v1: 23 (from AN369: SI4010 Antenna Interface and Matching Network Guide")
//   - v2: 80 (from AN369: SI4010 Antenna Interface and Matching Network Guide")
// - External diff Cap: 0
//
// Serializer Setup:
// - Data rate: 9.6 kbits/s
// - Encoding: NRZ Only (eg. no encoding)
// - Modulation: FSK
// - FSK Deviation: 59 kHz
//
// Calculated Values:
// - Actual symbol rate: 9.59 kbit/s
// - Expected deviation: 59.05 kHz

const tPa_Setup code rPaSetup = {
#if BOARD_VERSION==1 // Sensof v1 - Ceramic antenna
	/*.fAlpha      =*/ 0,
	/*.fBeta       =*/ 0.2455, // Calculated: 0.2455 (MSOP-10), 0.2499 (SOIC-14)
	/*.bLevel      =*/ 76, // Max according to sheet is: 76 @ max. drv.
	/*.bMaxDrv     =*/ 1,
	/*.wNominalCap =*/ 23,
#elif BOARD_VERSION==2 // Sensof v2 - PCB antenna
	/*.fAlpha      =*/ 0,
	/*.fBeta       =*/ 0.1755, // Calculated: 0.1674 (MSOP-10), 0.1755 (SOIC-14)
	/*.bLevel      =*/ 76, // Max according to sheet is: 76 @ max. drv.
	/*.bMaxDrv     =*/ 1,
	/*.wNominalCap =*/ 80,
#else
#error "BOARD_VERSION incorrect or not defined"
#endif
};

/**
 * PaSetup structure pointer.
 *
 * Since code and xdata memory are the same it is possible to directly access 
 * constant structures in code memory. Normally the compiler would copy the 
 * structure from the code memory into xdata memory, causing two identical 
 * copies to exist.
 */
const tPa_Setup xdata  *prPaSetup = (const tPa_Setup xdata  *) &rPaSetup; 

const tOds_Setup code rOdsSetup = {
	/*.bModulationType =*/ 1,  // Use FSK
	/*.bClkDiv     =*/ 5,
	/*.bEdgeRate   =*/ 0,
	/*.bGroupWidth =*/ 7,
	/*.wBitRate    =*/ 417,   // Bit width in seconds = (ods_datarate*(ods_ck_div+1))/24MHz
	/*.bLcWarmInt  =*/ 0,
	/*.bDivWarmInt =*/ 5,
	/*.bPaWarmInt  =*/ 4,
};
/**
 * OdsSetup structure pointer.
 *
 * Since code and xdata memory are the same it is possible to directly access 
 * constant structures in code memory. Normally the compiler would copy the 
 * structure from the code memory into xdata memory, causing two identical 
 * copies to exist.
 */
const tOds_Setup xdata *prOdsSetup = (const tOds_Setup xdata *) &rOdsSetup;

const float fFreq = 433979050.0;
const float fFdiv = 102; // 59 KHz @ 433.92 MHz

// Frame data
/**
 * Frame data buffer
 *
 * Sensof frames as send through the air. These frames are compatible with
 * the Si4430/EZRadioPro receiver. The following settings differ from the 
 * default Si4430 configuration:
 *
 * - Header Length = 0
 * - Fixed packet length = True
 * - Packet length = 16
 */
const uint8_t code frame_data[] = {
	//reg 0x35[7:3] (number is amount of 4-bit nibbles!!!), reg 0x70[3]
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, // preamble
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 			// preamble
	//reg 0x33[2:1], reg 0x36-0x39
	0x2d, 0xd4,                             // sync word 3 & 2
	//reg 0x33[6:4], reg 0x43-0x4a
	//0x11, 0x22,                             // Header 3 & 2
	//reg 0x33[3]
	//0x10,                                   // packet len
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Data
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Data
	//reg 0x30[5,2,1:0]
	0x00, 0x00                              // CRC-16-IBM
};
#define LEN_PREAMBLE	(13)
#define LEN_SYNC_WORD	(2)
#define	LEN_HEADER	(0)
#define	LEN_PLEN	(0)
#define LEN_PAYLOAD	(16)
#define LEN_CRC		(2)

#define OFFSET_SYNC_WORD (LEN_PREAMBLE)
#define OFFSET_HEADER	(OFFSET_SYNC_WORD + LEN_SYNC_WORD)
#define OFFSET_PLEN	(OFFSET_HEADER + LEN_HEADER)
#define OFFSET_PAYLOAD	(OFFSET_PLEN + LEN_PLEN)
#define OFFSET_CRC	(OFFSET_PAYLOAD + LEN_PAYLOAD)

#define LEN_FRAME	(OFFSET_CRC + LEN_CRC)

void rf_setup()
{

	// Set DMD interrupt to high priority,
	// any other interrupts have to stay low priority
	PDMD=1;

	// Call the system setup. This just for initialization.
	// Argument of 1 just configures the SYS module such that the
	// bandgap can be turned off if needed.  
	vSys_Setup( 1 );

	// Setup the bandgap for working with the temperature sensor here.
	// bSys_FirstBatteryInsertWaitTime set to non zero value. 
	vSys_BandGapLdo( 1 );

	// Required bPA_TRIM clearing before calling vPa_Setup() 
	vPa_Setup( prPaSetup );

	// ODS setup 
	vOds_Setup( prOdsSetup );

	// Setup the STL encoding for none.
	vStl_EncodeSetup( bEnc_NoneNrz_c, NULL );

	// Setup and run the frequency casting. 
	vFCast_Setup();

	// Disable Bandgap and LDO till needed
	vSys_BandGapLdo(0);
}

static void rf_transmit_frame(float freq, float fdiv, BYTE xdata *pbFrameHead, BYTE bLen, BYTE cnt)
{
	// Enable the Bandgap and LDO
	vSys_BandGapLdo(1);

	// Tune to the right frequency and set FSK ferquency adjust
	vFCast_Tune(freq);
	vFCast_FskAdj(fdiv);

	// Wait for a temperature sample and adjust oscilator with it
	while ( 0 == bDmdTs_GetSamplesTaken() ) {}
	vPa_Tune( iDmdTs_GetLatestTemp() );

	// Run a single TX loop 
	vStl_PreLoop();
	while (cnt != 0) {
		vStl_SingleTxLoop(pbFrameHead, bLen);
		cnt--;
	}
	vStl_PostLoop();

	// Disable Bandgap and LDO to save power
	vSys_BandGapLdo(0);
}

static uint8_t reverse_bits(uint8_t b)
{
	// reverse bit order
        b = ((b & 0xaa) >> 1) | ((b & 0x55) << 1);
        b = ((b & 0xcc) >> 2) | ((b & 0x33) << 2);
        b = ((b & 0xf0) >> 4) | ((b & 0x0f) << 4);

	return b;
}

void ezradiopro_send_frame(uint8_t *payload, uint8_t len)
{
	int i;

	uint16_t crc;
	uint8_t xdata *buf = (uint8_t xdata *) frame_data;

	if (len > 16) len = 16;
	memcpy(&buf[OFFSET_PAYLOAD], payload, len);

	// Calculate CRC-16
	crc = 0;
	for (i=OFFSET_HEADER; i < OFFSET_CRC; i++) {
		crc = crc16(crc, buf[i]);
	}
	buf[OFFSET_CRC] = (crc >> 8) & 0xff;
	buf[OFFSET_CRC + 1] = crc & 0xff;


#if 0 // only needed for encoding that changes frame length(ie. manchester)
	{
		BYTE xdata abFrameArray[LEN_FRAME * 2];
		uint8_t *pbFrameHead;           // Pointer to frame Head 

		for (i=0; i < LEN_FRAME; i++) {
			buf[i] ^= 0xff;
			pbFrameHead = encode_manchester(pbFrameHead, buf[i]);
		}

		rf_transmit_frame(fFreq, fFdiv, abFrameArray, pbFrameHead - abFrameArray, 1);
	}
#else
	for (i=0; i < LEN_FRAME; i++) {
		// Invert bits, by default Si4430 has different notion of '1' and '0'
		//TODO: can't we just fix this on receiver?
		buf[i] ^= 0xff;
		// Revert bits since Si4010 sends out LSB first
		buf[i] = reverse_bits(buf[i]);
	}


	// Transmit
	rf_transmit_frame(fFreq, fFdiv, buf, LEN_FRAME, 1);
#endif
}
