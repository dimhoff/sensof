EESchema Schematic File Version 4
LIBS:sensof_ht-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Sensof HT v2"
Date "2018-09-16"
Rev "01"
Comp "Copyright (c) 2018, David Imhoff <dimhoff.devel@gmail.com>"
Comment1 "License: BSD-3-Clause"
Comment2 "Project: 0003"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:C C1
U 1 1 5B335AB5
P 3300 3700
F 0 "C1" H 3100 3650 50  0000 L CNN
F 1 "2.7pF" H 3000 3750 50  0000 L CNN
F 2 "silabs_0402:C_0402" H 3338 3550 50  0001 C CNN
F 3 "" H 3300 3700 50  0001 C CNN
F 4 "Murata" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "GJM1555C1H2R7BB01D" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "81-GJM1555C1H2R7BB01" H 0   0   50  0001 C CNN "Mouser No"
	1    3300 3700
	-1   0    0    1   
$EndComp
$Comp
L Device:L L1
U 1 1 5B335F3C
P 3300 3300
F 0 "L1" H 3400 3350 50  0000 C CNN
F 1 "220nH" H 3450 3250 50  0000 C CNN
F 2 "silabs_0402:C_0402" H 3300 3300 50  0001 C CNN
F 3 "" H 3300 3300 50  0001 C CNN
F 4 "Murata" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "LQW15CNR22J10D" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "81-LQW15CNR22J10D" H 0   0   50  0001 C CNN "Mouser No"
	1    3300 3300
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR01
U 1 1 5B336350
P 3300 3150
F 0 "#PWR01" H 3300 3000 50  0001 C CNN
F 1 "VDD" H 3300 3300 50  0000 C CNN
F 2 "" H 3300 3150 50  0001 C CNN
F 3 "" H 3300 3150 50  0001 C CNN
	1    3300 3150
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR03
U 1 1 5B337212
P 5750 2100
F 0 "#PWR03" H 5750 1950 50  0001 C CNN
F 1 "VDD" H 5750 2250 50  0000 C CNN
F 2 "" H 5750 2100 50  0001 C CNN
F 3 "" H 5750 2100 50  0001 C CNN
	1    5750 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5B33724A
P 5500 2350
F 0 "C3" H 5525 2450 50  0000 L CNN
F 1 "2.2uF" H 5525 2250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5538 2200 50  0001 C CNN
F 3 "" H 5500 2350 50  0001 C CNN
F 4 "Taiyo Yuden" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "LMK107BJ225KAHT" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "963-LMK107BJ225KAHT" H 0   0   50  0001 C CNN "Mouser No"
	1    5500 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5B3372D2
P 5750 2350
F 0 "C4" H 5775 2450 50  0000 L CNN
F 1 "1nF" H 5775 2250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5788 2200 50  0001 C CNN
F 3 "" H 5750 2350 50  0001 C CNN
F 4 "KEMET" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "C0603C102J5RACTU" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "80-C0603C102J5R" H 0   0   50  0001 C CNN "Mouser No"
	1    5750 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5B337541
P 5750 2650
F 0 "#PWR04" H 5750 2400 50  0001 C CNN
F 1 "GND" H 5750 2500 50  0000 C CNN
F 2 "" H 5750 2650 50  0001 C CNN
F 3 "" H 5750 2650 50  0001 C CNN
	1    5750 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5B33736F
P 6000 2350
F 0 "C5" H 6025 2450 50  0000 L CNN
F 1 "270pF" H 6025 2250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 6038 2200 50  0001 C CNN
F 3 "" H 6000 2350 50  0001 C CNN
F 4 "Yageo" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "CC0603JRX7R9BB271" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "603-CC603JRX7R9BB271" H 0   0   50  0001 C CNN "Mouser No"
	1    6000 2350
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Humidity:Si7020-A20 U2
U 1 1 5B338116
P 8050 3400
F 0 "U2" H 8050 3650 60  0000 C CNN
F 1 "HTU21D/Si7020" H 8600 3150 60  0000 C CNN
F 2 "Housings_DFN_QFN:DFN-6-1EP_3x3mm_Pitch0.95mm" H 8050 3400 60  0001 C CNN
F 3 "" H 8050 3400 60  0001 C CNN
F 4 "TE Connectivity" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "HTU21DF" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "824-HPP845E131R5" H 0   0   50  0001 C CNN "Mouser No"
	1    8050 3400
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR05
U 1 1 5B338266
P 8200 2600
F 0 "#PWR05" H 8200 2450 50  0001 C CNN
F 1 "VDD" H 8200 2750 50  0000 C CNN
F 2 "" H 8200 2600 50  0001 C CNN
F 3 "" H 8200 2600 50  0001 C CNN
	1    8200 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5B33829C
P 8350 2900
F 0 "#PWR06" H 8350 2650 50  0001 C CNN
F 1 "GND" H 8350 2750 50  0000 C CNN
F 2 "" H 8350 2900 50  0001 C CNN
F 3 "" H 8350 2900 50  0001 C CNN
	1    8350 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5B33839F
P 7000 3050
F 0 "R2" H 7150 3000 50  0000 C CNN
F 1 "10k" H 7150 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 6930 3050 50  0001 C CNN
F 3 "" H 7000 3050 50  0001 C CNN
F 4 "Yageo" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "RE0603FRE0710KL" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "603-RE0603FRE0710KL" H 0   0   50  0001 C CNN "Mouser No"
	1    7000 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5B338562
P 6700 3050
F 0 "R1" H 6850 3000 50  0000 C CNN
F 1 "10k" H 6850 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 6630 3050 50  0001 C CNN
F 3 "" H 6700 3050 50  0001 C CNN
F 4 "Yageo" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "RE0603FRE0710KL" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "603-RE0603FRE0710KL" H 0   0   50  0001 C CNN "Mouser No"
	1    6700 3050
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR07
U 1 1 5B338644
P 6850 2800
F 0 "#PWR07" H 6850 2650 50  0001 C CNN
F 1 "VDD" H 6850 2950 50  0000 C CNN
F 2 "" H 6850 2800 50  0001 C CNN
F 3 "" H 6850 2800 50  0001 C CNN
	1    6850 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 5B33A3DE
P 3750 4900
F 0 "BT1" H 3850 5000 50  0000 L CNN
F 1 "CR2032" H 3850 4900 50  0000 L CNN
F 2 "silabs_cr2032:silabs_cr2032" V 3750 4960 50  0001 C CNN
F 3 "" V 3750 4960 50  0001 C CNN
F 4 "Linx Technologies" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "BAT-HLD-001" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "712-BAT-HLD-001" H 0   0   50  0001 C CNN "Mouser No"
	1    3750 4900
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR08
U 1 1 5B33A490
P 3750 4700
F 0 "#PWR08" H 3750 4550 50  0001 C CNN
F 1 "VDD" H 3750 4850 50  0000 C CNN
F 2 "" H 3750 4700 50  0001 C CNN
F 3 "" H 3750 4700 50  0001 C CNN
	1    3750 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5B33A4CE
P 3750 5000
F 0 "#PWR09" H 3750 4750 50  0001 C CNN
F 1 "GND" H 3750 4850 50  0000 C CNN
F 2 "" H 3750 5000 50  0001 C CNN
F 3 "" H 3750 5000 50  0001 C CNN
	1    3750 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5B363426
P 8350 2750
F 0 "C6" H 8375 2850 50  0000 L CNN
F 1 "100nF" H 8375 2650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 8388 2600 50  0001 C CNN
F 3 "" H 8350 2750 50  0001 C CNN
F 4 "Yageo" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "CC0603KRX7R6BB104" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "603-CC603KRX7R6BB104" H 0   0   50  0001 C CNN "Mouser No"
	1    8350 2750
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG010
U 1 1 5B364865
P 3450 5000
F 0 "#FLG010" H 3450 5075 50  0001 C CNN
F 1 "PWR_FLAG" H 3450 5150 50  0000 C CNN
F 2 "" H 3450 5000 50  0001 C CNN
F 3 "" H 3450 5000 50  0001 C CNN
	1    3450 5000
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG011
U 1 1 5B364A5A
P 3450 4700
F 0 "#FLG011" H 3450 4775 50  0001 C CNN
F 1 "PWR_FLAG" H 3450 4850 50  0000 C CNN
F 2 "" H 3450 4700 50  0001 C CNN
F 3 "" H 3450 4700 50  0001 C CNN
	1    3450 4700
	1    0    0    -1  
$EndComp
$Comp
L Graphic:Logo_Open_Hardware_Small #LOGO1
U 1 1 5B37440A
P 10850 6850
F 0 "#LOGO1" H 10850 7125 50  0001 C CNN
F 1 "Logo_Open_Hardware_Small" H 10850 6625 50  0001 C CNN
F 2 "" H 10850 6850 50  0001 C CNN
F 3 "" H 10850 6850 50  0001 C CNN
	1    10850 6850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5B67FED2
P 4000 3500
F 0 "C2" H 3800 3450 50  0000 L CNN
F 1 "N.F." H 3700 3550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4038 3350 50  0001 C CNN
F 3 "" H 4000 3500 50  0001 C CNN
F 4 "-" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "-" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "-" H 0   0   50  0001 C CNN "Mouser No"
	1    4000 3500
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5B6800F1
P 3300 3850
F 0 "#PWR012" H 3300 3600 50  0001 C CNN
F 1 "GND" H 3300 3700 50  0000 C CNN
F 2 "" H 3300 3850 50  0001 C CNN
F 3 "" H 3300 3850 50  0001 C CNN
	1    3300 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2500 5500 2650
Wire Wire Line
	5500 2650 5750 2650
Wire Wire Line
	6000 2650 6000 2500
Connection ~ 5750 2650
Wire Wire Line
	5750 2650 5750 2500
Wire Wire Line
	6000 2100 6000 2200
Wire Wire Line
	5500 2100 5750 2100
Wire Wire Line
	5750 2100 5750 2200
Connection ~ 5500 2100
Connection ~ 5750 2100
Wire Wire Line
	6700 3200 6700 3500
Connection ~ 6700 3500
Wire Wire Line
	7000 3200 7000 3300
Connection ~ 7000 3300
Wire Wire Line
	6700 2800 6850 2800
Wire Wire Line
	6700 2800 6700 2900
Wire Wire Line
	7000 2800 7000 2900
Connection ~ 6850 2800
Wire Wire Line
	3450 4700 3750 4700
Wire Wire Line
	3450 5000 3750 5000
Wire Wire Line
	6450 3500 6700 3500
Wire Wire Line
	6450 3300 7000 3300
Wire Wire Line
	4000 3650 4350 3650
Wire Wire Line
	4350 3350 4000 3350
Wire Wire Line
	4000 3350 4000 2900
Wire Wire Line
	3650 2900 3650 3500
Wire Wire Line
	4000 4100 4000 3650
Connection ~ 3650 2900
Connection ~ 3650 4100
Wire Wire Line
	2850 3700 2850 3350
Wire Wire Line
	2800 3300 2800 3650
Wire Wire Line
	2750 3350 2750 3700
Connection ~ 2750 3700
Wire Wire Line
	2700 3650 2700 3300
Connection ~ 2700 3300
Wire Wire Line
	2650 3350 2650 3700
Connection ~ 2650 3700
Wire Wire Line
	2550 3700 2550 3350
Connection ~ 2550 3700
Wire Wire Line
	2500 2900 2500 3300
Connection ~ 2500 3300
Wire Wire Line
	2600 3650 2600 3300
Connection ~ 2600 3300
Wire Wire Line
	2500 3700 2500 4100
Wire Wire Line
	2500 3700 2550 3700
Wire Wire Line
	2500 3300 2600 3300
Wire Wire Line
	3300 3450 3300 3500
Wire Wire Line
	3300 3500 3650 3500
Connection ~ 3650 3500
Connection ~ 3300 3500
$Comp
L power:VDD #PWR013
U 1 1 5B6840DE
P 7600 4150
F 0 "#PWR013" H 7600 4000 50  0001 C CNN
F 1 "VDD" H 7600 4300 50  0000 C CNN
F 2 "" H 7600 4150 50  0001 C CNN
F 3 "" H 7600 4150 50  0001 C CNN
	1    7600 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 5B684125
P 7600 5200
F 0 "#PWR014" H 7600 4950 50  0001 C CNN
F 1 "GND" H 7600 5050 50  0000 C CNN
F 2 "" H 7600 5200 50  0001 C CNN
F 3 "" H 7600 5200 50  0001 C CNN
	1    7600 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 5050 7600 5050
Wire Wire Line
	6350 4900 7600 4900
Wire Wire Line
	6450 4750 7600 4750
Wire Wire Line
	6550 4600 7600 4600
Wire Wire Line
	7600 4450 7200 4450
Wire Wire Line
	7200 4450 7200 3500
Connection ~ 7200 3500
Wire Wire Line
	7300 4300 7600 4300
Wire Wire Line
	7300 4300 7300 3300
Connection ~ 7300 3300
Wire Wire Line
	2500 4100 3650 4100
Wire Wire Line
	4000 2900 3650 2900
Text Notes 2000 3600 0    60   ~ 0
Printed\nCapacitor
$Comp
L Connector:TestPoint TP1
U 1 1 5B684EAC
P 7600 4150
F 0 "TP1" V 7600 4350 50  0001 L CNN
F 1 "VCC" V 7600 4350 50  0000 L CNN
F 2 "Measurement_Point_Round-SMD-Pad_Small-Labeled:Measurement_Point_Round-SMD-Pad_Small-Labeled" H 7800 4150 50  0001 C CNN
F 3 "" H 7800 4150 50  0001 C CNN
F 4 "-" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "-" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "-" H 0   0   50  0001 C CNN "Mouser No"
	1    7600 4150
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP2
U 1 1 5B684E7D
P 7600 4300
F 0 "TP2" V 7600 4500 50  0001 L CNN
F 1 "SDA" V 7600 4500 50  0000 L CNN
F 2 "Measurement_Point_Round-SMD-Pad_Small-Labeled:Measurement_Point_Round-SMD-Pad_Small-Labeled" H 7800 4300 50  0001 C CNN
F 3 "" H 7800 4300 50  0001 C CNN
F 4 "-" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "-" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "-" H 0   0   50  0001 C CNN "Mouser No"
	1    7600 4300
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP3
U 1 1 5B684E4E
P 7600 4450
F 0 "TP3" V 7600 4650 50  0001 L CNN
F 1 "SCL" V 7600 4650 50  0000 L CNN
F 2 "Measurement_Point_Round-SMD-Pad_Small-Labeled:Measurement_Point_Round-SMD-Pad_Small-Labeled" H 7800 4450 50  0001 C CNN
F 3 "" H 7800 4450 50  0001 C CNN
F 4 "-" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "-" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "-" H 0   0   50  0001 C CNN "Mouser No"
	1    7600 4450
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP4
U 1 1 5B684E1F
P 7600 4600
F 0 "TP4" V 7600 4800 50  0001 L CNN
F 1 "GPIO0" V 7600 4800 50  0000 L CNN
F 2 "Measurement_Point_Round-SMD-Pad_Small-Labeled:Measurement_Point_Round-SMD-Pad_Small-Labeled" H 7800 4600 50  0001 C CNN
F 3 "" H 7800 4600 50  0001 C CNN
F 4 "-" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "-" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "-" H 0   0   50  0001 C CNN "Mouser No"
	1    7600 4600
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP5
U 1 1 5B684DF0
P 7600 4750
F 0 "TP5" V 7600 4950 50  0001 L CNN
F 1 "GPIO3" V 7600 4950 50  0000 L CNN
F 2 "Measurement_Point_Round-SMD-Pad_Small-Labeled:Measurement_Point_Round-SMD-Pad_Small-Labeled" H 7800 4750 50  0001 C CNN
F 3 "" H 7800 4750 50  0001 C CNN
F 4 "-" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "-" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "-" H 0   0   50  0001 C CNN "Mouser No"
	1    7600 4750
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP6
U 1 1 5B684DC1
P 7600 4900
F 0 "TP6" V 7600 5100 50  0001 L CNN
F 1 "C2D" V 7600 5100 50  0000 L CNN
F 2 "Measurement_Point_Round-SMD-Pad_Small-Labeled:Measurement_Point_Round-SMD-Pad_Small-Labeled" H 7800 4900 50  0001 C CNN
F 3 "" H 7800 4900 50  0001 C CNN
F 4 "-" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "-" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "-" H 0   0   50  0001 C CNN "Mouser No"
	1    7600 4900
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP7
U 1 1 5B684D92
P 7600 5050
F 0 "TP7" V 7600 5250 50  0001 L CNN
F 1 "C2CK" V 7600 5250 50  0000 L CNN
F 2 "Measurement_Point_Round-SMD-Pad_Small-Labeled:Measurement_Point_Round-SMD-Pad_Small-Labeled" H 7800 5050 50  0001 C CNN
F 3 "" H 7800 5050 50  0001 C CNN
F 4 "-" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "-" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "-" H 0   0   50  0001 C CNN "Mouser No"
	1    7600 5050
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP8
U 1 1 5B684D63
P 7600 5200
F 0 "TP8" V 7600 5400 50  0001 L CNN
F 1 "GND" V 7600 5400 50  0000 L CNN
F 2 "Measurement_Point_Round-SMD-Pad_Small-Labeled:Measurement_Point_Round-SMD-Pad_Small-Labeled" H 7800 5200 50  0001 C CNN
F 3 "" H 7800 5200 50  0001 C CNN
F 4 "-" H 0   0   50  0001 C CNN "Manufacturer"
F 5 "-" H 0   0   50  0001 C CNN "Mfr. No"
F 6 "-" H 0   0   50  0001 C CNN "Mouser No"
	1    7600 5200
	0    1    1    0   
$EndComp
NoConn ~ 6100 3950
NoConn ~ 6100 3850
NoConn ~ 6100 3150
NoConn ~ 6100 3050
Wire Wire Line
	5750 2650 6000 2650
Wire Wire Line
	5500 2100 5500 2200
Wire Wire Line
	5750 2100 6000 2100
Wire Wire Line
	6700 3500 7200 3500
Wire Wire Line
	7000 3300 7300 3300
Wire Wire Line
	6850 2800 7000 2800
Wire Wire Line
	3650 2900 2500 2900
Wire Wire Line
	3650 4100 4000 4100
Wire Wire Line
	2750 3700 2850 3700
Wire Wire Line
	2700 3300 2800 3300
Wire Wire Line
	2650 3700 2750 3700
Wire Wire Line
	2550 3700 2650 3700
Wire Wire Line
	2500 3300 2500 3650
Wire Wire Line
	2600 3300 2700 3300
Wire Wire Line
	3650 3500 3650 4100
Wire Wire Line
	3300 3500 3300 3550
Wire Wire Line
	7200 3500 7550 3500
Wire Wire Line
	7300 3300 7550 3300
Wire Wire Line
	8050 3100 8050 2600
Connection ~ 8200 2600
Wire Wire Line
	8200 2600 8050 2600
Wire Wire Line
	8200 2600 8350 2600
$Comp
L power:GND #PWR0101
U 1 1 5B9B6AE8
P 7950 3700
F 0 "#PWR0101" H 7950 3450 50  0001 C CNN
F 1 "GND" H 7950 3550 50  0000 C CNN
F 2 "" H 7950 3700 50  0001 C CNN
F 3 "" H 7950 3700 50  0001 C CNN
	1    7950 3700
	1    0    0    -1  
$EndComp
NoConn ~ 8150 3700
$Comp
L si4010:Si4010-GS U1
U 1 1 5B3260C4
P 5350 3550
F 0 "U1" H 5350 4300 60  0000 C CNN
F 1 "Si4010-GS" H 5700 2900 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" H 5400 3000 60  0001 C CNN
F 3 "" H 5400 3000 60  0001 C CNN
F 4 "Silicon Labs" H 5350 3550 50  0001 C CNN "Manufacturer"
F 5 "SI4010-C2-GS" H 5350 3550 50  0001 C CNN "Mfr. No"
F 6 "634-SI4010-C2-GS" H 5350 3550 50  0001 C CNN "Mouser No"
	1    5350 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5B33700F
P 5350 4250
F 0 "#PWR02" H 5350 4000 50  0001 C CNN
F 1 "GND" H 5350 4100 50  0000 C CNN
F 2 "" H 5350 4250 50  0001 C CNN
F 3 "" H 5350 4250 50  0001 C CNN
	1    5350 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 3450 4600 3450
Wire Wire Line
	4350 3350 4350 3450
Wire Wire Line
	4600 3550 4350 3550
Wire Wire Line
	4350 3550 4350 3650
Wire Wire Line
	6100 3450 6300 3450
Wire Wire Line
	6300 3450 6450 3300
Wire Wire Line
	6100 3350 6300 3350
Wire Wire Line
	6300 3350 6450 3500
Wire Wire Line
	6100 3250 6550 3250
Wire Wire Line
	6550 3250 6550 4600
Wire Wire Line
	6100 3550 6450 3550
Wire Wire Line
	6450 3550 6450 4750
Wire Wire Line
	6100 3650 6350 3650
Wire Wire Line
	6350 3650 6350 4900
Wire Wire Line
	6100 3750 6250 3750
Wire Wire Line
	6250 3750 6250 5050
Wire Wire Line
	5350 2750 5350 2100
Wire Wire Line
	5350 2100 5500 2100
$EndSCHEMATC
