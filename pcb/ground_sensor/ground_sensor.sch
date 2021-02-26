EESchema Schematic File Version 4
LIBS:ground_sensor-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:Battery_Cell BT?
U 1 1 601EF6B9
P 1300 3700
F 0 "BT?" H 1418 3796 50  0000 L CNN
F 1 "Battery_Cell" H 1418 3705 50  0000 L CNN
F 2 "" V 1300 3760 50  0001 C CNN
F 3 "~" V 1300 3760 50  0001 C CNN
	1    1300 3700
	1    0    0    -1  
$EndComp
$Comp
L RF:NRF24L01_Breakout U?
U 1 1 601EFA4A
P 7250 1800
F 0 "U?" H 7728 1778 50  0000 L CNN
F 1 "NRF24L01_Breakout" H 7728 1687 50  0000 L CNN
F 2 "RF_Module:nRF24L01_Breakout" H 7400 2400 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 7250 1700 50  0001 C CNN
	1    7250 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 1650 4850 1650
Wire Wire Line
	4750 1550 4850 1550
Text GLabel 4850 1550 2    50   Input ~ 0
MOSI
Text GLabel 4850 1650 2    50   Input ~ 0
MISO
Wire Wire Line
	4750 1750 4850 1750
Text GLabel 4850 1750 2    50   Input ~ 0
SCK
Wire Wire Line
	4800 2350 4900 2350
Text GLabel 4900 2350 2    50   Input ~ 0
C_SENS
Wire Wire Line
	4750 1950 4850 1950
Text GLabel 4850 1950 2    50   Input ~ 0
Enable
$Comp
L ROCCI:NMOS_BSS138 Q?
U 1 1 601F9F50
P 7250 2800
F 0 "Q?" H 7358 2853 60  0000 L CNN
F 1 "NMOS_BSS138" H 7358 2747 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 7450 3000 60  0001 L CNN
F 3 "" H 7450 3100 60  0001 L CNN
F 4 "BSS138CT-ND" H 7450 3200 60  0001 L CNN "Digi-Key_PN"
F 5 "BSS138" H 7450 3300 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 7450 3400 60  0001 L CNN "Category"
F 7 "Transistors - FETs, MOSFETs - Single" H 7450 3500 60  0001 L CNN "Family"
F 8 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 7450 3600 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/on-semiconductor/BSS138/BSS138CT-ND/244294" H 7450 3700 60  0001 L CNN "DK_Detail_Page"
F 10 "MOSFET N-CH 50V 220MA SOT-23" H 7450 3800 60  0001 L CNN "Description"
F 11 "ON Semiconductor" H 7450 3900 60  0001 L CNN "Manufacturer"
F 12 "Active" H 7450 4000 60  0001 L CNN "Status"
	1    7250 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 2400 7250 2500
Wire Wire Line
	7250 2500 6550 2500
Wire Wire Line
	6550 2500 6550 1800
Wire Wire Line
	6550 1800 6750 1800
Connection ~ 7250 2500
Wire Wire Line
	7250 2500 7250 2600
Wire Wire Line
	6950 2900 6600 2900
Text GLabel 6600 2900 0    50   Input ~ 0
Enable
$Comp
L power:GND #PWR?
U 1 1 601FA2CC
P 7250 3050
F 0 "#PWR?" H 7250 2800 50  0001 C CNN
F 1 "GND" H 7255 2877 50  0000 C CNN
F 2 "" H 7250 3050 50  0001 C CNN
F 3 "" H 7250 3050 50  0001 C CNN
	1    7250 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3050 7250 3000
Text GLabel 6550 1500 0    50   Input ~ 0
MOSI
Text GLabel 6550 1600 0    50   Input ~ 0
MISO
Text GLabel 6550 1700 0    50   Input ~ 0
SCK
Wire Wire Line
	6550 1700 6750 1700
Wire Wire Line
	6550 1600 6750 1600
Wire Wire Line
	6550 1500 6750 1500
$Comp
L power:VCC #PWR?
U 1 1 601FA6CF
P 7250 1000
F 0 "#PWR?" H 7250 850 50  0001 C CNN
F 1 "VCC" H 7267 1173 50  0000 C CNN
F 2 "" H 7250 1000 50  0001 C CNN
F 3 "" H 7250 1000 50  0001 C CNN
	1    7250 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 1000 7250 1200
$Comp
L power:VCC #PWR?
U 1 1 601FAC00
P 3900 1100
F 0 "#PWR?" H 3900 950 50  0001 C CNN
F 1 "VCC" H 3917 1273 50  0000 C CNN
F 2 "" H 3900 1100 50  0001 C CNN
F 3 "" H 3900 1100 50  0001 C CNN
	1    3900 1100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 601FAC2F
P 3800 4200
F 0 "#PWR?" H 3800 3950 50  0001 C CNN
F 1 "GND" H 3805 4027 50  0000 C CNN
F 2 "" H 3800 4200 50  0001 C CNN
F 3 "" H 3800 4200 50  0001 C CNN
	1    3800 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4100 3800 4150
Wire Wire Line
	3900 1300 3900 1200
Wire Wire Line
	3200 1600 3100 1600
Text GLabel 3100 1600 0    50   Input ~ 0
RESET
$Comp
L Connector:AVR-ISP-6 J?
U 1 1 601FB0FA
P 1400 1800
F 0 "J?" H 1120 1896 50  0000 R CNN
F 1 "AVR-ISP-6" H 1120 1805 50  0000 R CNN
F 2 "" V 1150 1850 50  0001 C CNN
F 3 " ~" H 125 1250 50  0001 C CNN
	1    1400 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1700 1900 1700
Wire Wire Line
	1800 1600 1900 1600
Text GLabel 1900 1700 2    50   Input ~ 0
MOSI
Text GLabel 1900 1600 2    50   Input ~ 0
MISO_Charge
Wire Wire Line
	1800 1800 1900 1800
Text GLabel 1900 1800 2    50   Input ~ 0
SCK
Wire Wire Line
	1800 1900 1900 1900
Text GLabel 1900 1900 2    50   Input ~ 0
RESET
$Comp
L power:VCC #PWR?
U 1 1 601FC117
P 1300 1100
F 0 "#PWR?" H 1300 950 50  0001 C CNN
F 1 "VCC" H 1317 1273 50  0000 C CNN
F 2 "" H 1300 1100 50  0001 C CNN
F 3 "" H 1300 1100 50  0001 C CNN
	1    1300 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1300 1300 1100
$Comp
L power:GND #PWR?
U 1 1 601FC3FE
P 1300 2300
F 0 "#PWR?" H 1300 2050 50  0001 C CNN
F 1 "GND" H 1305 2127 50  0000 C CNN
F 2 "" H 1300 2300 50  0001 C CNN
F 3 "" H 1300 2300 50  0001 C CNN
	1    1300 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 2200 1300 2300
$Comp
L power:VCC #PWR?
U 1 1 601FC829
P 1300 3300
F 0 "#PWR?" H 1300 3150 50  0001 C CNN
F 1 "VCC" H 1317 3473 50  0000 C CNN
F 2 "" H 1300 3300 50  0001 C CNN
F 3 "" H 1300 3300 50  0001 C CNN
	1    1300 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 3500 1300 3300
$Comp
L power:GND #PWR?
U 1 1 601FCB86
P 1300 3900
F 0 "#PWR?" H 1300 3650 50  0001 C CNN
F 1 "GND" H 1305 3727 50  0000 C CNN
F 2 "" H 1300 3900 50  0001 C CNN
F 3 "" H 1300 3900 50  0001 C CNN
	1    1300 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 3800 1300 3900
$Comp
L MCU_Microchip_ATmega:ATmega8-16AU U?
U 1 1 60201A44
P 3800 2700
F 0 "U?" H 3800 4278 50  0000 C CNN
F 1 "ATmega8-16AU" H 3800 4187 50  0000 C CNN
F 2 "Package_QFP:TQFP-32_7x7mm_P0.8mm" H 3800 2700 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2486-8-bit-avr-microcontroller-atmega8_l_datasheet.pdf" H 3800 2700 50  0001 C CNN
	1    3800 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 1300 3800 1200
Wire Wire Line
	3800 1200 3900 1200
Connection ~ 3900 1200
Wire Wire Line
	3900 1200 3900 1100
Wire Wire Line
	3800 4150 3900 4150
Wire Wire Line
	3900 4150 3900 4100
Connection ~ 3800 4150
Wire Wire Line
	3800 4150 3800 4200
Text GLabel 6450 2000 0    50   Input ~ 0
CE
Text GLabel 6450 2100 0    50   Input ~ 0
IRQ
Wire Wire Line
	6450 2000 6750 2000
Wire Wire Line
	6450 2100 6750 2100
$Comp
L Device:R R?
U 1 1 60205E6E
P 9700 1550
F 0 "R?" V 9493 1550 50  0000 C CNN
F 1 "R" V 9584 1550 50  0000 C CNN
F 2 "" V 9630 1550 50  0001 C CNN
F 3 "~" H 9700 1550 50  0001 C CNN
	1    9700 1550
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 60206017
P 10200 1800
F 0 "C?" H 10315 1846 50  0000 L CNN
F 1 "C" H 10315 1755 50  0000 L CNN
F 2 "" H 10238 1650 50  0001 C CNN
F 3 "~" H 10200 1800 50  0001 C CNN
	1    10200 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 1550 10200 1550
Wire Wire Line
	10200 1550 10200 1650
$Comp
L power:GND #PWR?
U 1 1 6020669B
P 10200 2050
F 0 "#PWR?" H 10200 1800 50  0001 C CNN
F 1 "GND" H 10205 1877 50  0000 C CNN
F 2 "" H 10200 2050 50  0001 C CNN
F 3 "" H 10200 2050 50  0001 C CNN
	1    10200 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 2050 10200 1950
Text GLabel 4900 2500 2    50   Input ~ 0
C_LOAD
Wire Wire Line
	4900 2500 4800 2500
Text GLabel 9400 1550 0    50   Input ~ 0
C_LOAD
Wire Wire Line
	9400 1550 9550 1550
Text GLabel 10500 1550 2    50   Input ~ 0
C_SENS
Wire Wire Line
	10500 1550 10200 1550
Connection ~ 10200 1550
$EndSCHEMATC
