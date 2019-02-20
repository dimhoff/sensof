;-------------------------------------------------------------------------------
;                           Silicon Laboratories, Inc.
;                            http://www.silabs.com
;                                Copyright 2010
;-------------------------------------------------------------------------------
;
;     FILE:       fstep_startup.a51 .. startup for fstep_demo project
;     TARGET:     Si4010
;     TOOLCHAIN:  Keil
;     DATE:       May 18, 2010, Tuesday
;     RELEASE:    2.0 (JimG, MPech), ROM version 02.00, trim 3
;
;---------------------------------------------------------------------------
;
;       DESCRIPTION:
;         The original file is part of the C51 Compiler package.
;         Part of the file are Copyright (c) 1988-2005 Keil Elektronik GmbH
;         and Keil Software, Inc.
;         Version 8.01
;
;         This is a startup file for the fstep_demo project.
;         The only difference from the
;
;           ..\common\src\startup.a51
;
;         is that is reserves a stack space other then 1.
;
;         Startup file for Si4010 project for the Keil C. It must
;         be included in any of the C projects and compiled and linked
;         with the main() file. Only needed for the main() application
;         build.
;
;         All the conditionals were removed from the original Keil
;         file and only those needed are kept. What this code does:
;
;           1. Sets P2 for possible PDATA use for XREG
;           2. Sets SP after the last used data in IDATA
;
;         All DATA/IDATA and XDATA variable initializations were removed.
;         If user application relies on the zero initial values
;         of variables then the code should be return there.
;
;         Note that CODE/XDATA share the same RAM space. Also note that
;         the XDATA memory can be cleared only up to the address value
;         (not inclusive) specified in the WORD (2 byte, big endian)
;         variable wBoot_DpramTrimBeg at address 0x11F3. The XDATA
;         area clearing code must read this variable to get the first
;         occupied address of XDATA which must not be touched.
;         User usable CODE/XDATA RAM is in a range, limits inclusive:
;
;           0x0000 .. (wBoot_DpramTrimBeg) - 1
;
;---------------------------------------------------------------------------
;
;       DATA DECLARATIONS:
;

$NOMOD51

;------------------------------------------------------------------------------
;  This file is part of the C51 Compiler package
;  Copyright (c) 1988-2005 Keil Elektronik GmbH and Keil Software, Inc.
;  Version 8.01
;------------------------------------------------------------------------------
;  STARTUP.A51:  This code is executed after processor reset.
;
;  To translate this file use A51 with the following invocation:
;
;     A51 STARTUP.A51
;
;  To link the modified STARTUP.OBJ file to your application use the following
;  Lx51 invocation:
;
;     Lx51 your object file list, STARTUP.OBJ  controls
;
;------------------------------------------------------------------------------
;
;  User-defined Power-On Initialization of Memory
;  SiLabs: Removed, we don't do any power on memory clearing.
;  See the description above.
;

; PDATASTART: PDATA memory start address <0x0-0xFFFF>
; The absolute start address of PDATA memory
; SiLabs: Set to XREG space, but it is up to the use to initialize this.
PDATASTART      EQU     04000H

;------------------------------------------------------------------------------
;
; Memory Page for Using the Compact Model with 64 KByte XDATA RAM
; Compact Model Page Definition
;
; Define the XDATA page used for PDATA variables.
; PPAGE must conform with the PPAGE set in the linker invocation.
; MPech: Even if we are not using the compact mode, the P2 can be
; set to XREG page for faster access by default.

; Enable PDATA memory page initialization
PPAGEENABLE     EQU     1       ; Set to 1 if pdata object are used.

; PPAGE number <0x0-0xFF>
; Uppermost 256-byte address of the page used for PDATA variables.
PPAGE           EQU     HIGH(PDATASTART)

; FR address which supplies uppermost address byte <0x0-0xFF>
; Most 8051 variants use P2 as uppermost address byte. The P2 SFR address
; is 0xA0
PPAGE_SFR       DATA    0A0H    ; P2

;---------------------------------------------------------------------------
;
;       SYMBOLS:
;

; -- Standard SFR Symbols
ACC     DATA    0E0H
B       DATA    0F0H
SP      DATA    81H
DPL     DATA    82H
DPH     DATA    83H

;---------------------------------------------------------------------------
;
;       CODE:
;

                NAME    ?C_STARTUP

?C_C51STARTUP   SEGMENT   CODE
?STACK          SEGMENT   IDATA

; -- Nominally the DS 1 is used for the STACK segment. However, if we want
; to reserve a desired space and make sure that we are not overflowing
; sizes we should allocated desired amount here.
                RSEG    ?STACK
                DS      40        ; 40 bytes of stack reserved

; -- Start code and startup entry .. CPU reset entry
                EXTRN CODE (?C_START)
                PUBLIC  ?C_STARTUP

; -- Entry point of the code .. CPU starts here
                CSEG    AT      0

?C_STARTUP:     ljmp    STARTUP1  ; Long jump to startup code


; -- Startup code. The relocatable segment name must be ?C_C51STARTUP
                RSEG    ?C_C51STARTUP
STARTUP1:
IF PPAGEENABLE <> 0
                mov     PPAGE_SFR, #PPAGE  ; Get the PDATA ready
ENDIF

                mov     SP, #?STACK-1   ; Set stack pointer
                ljmp    ?C_START        ; Go to C main()

                END

;
;------------------------------------------------------------------------------
;
