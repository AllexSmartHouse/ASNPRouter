EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:SmartHouseComponents
LIBS:SmartHousePowerUARTRouter-cache
EELAYER 25 0
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
L CONN_01X04 BUS1
U 1 1 59BC23F6
P 2250 2600
F 0 "BUS1" H 2250 2850 50  0000 C CNN
F 1 "CONN_01X04" V 2350 2600 50  0000 C CNN
F 2 "SmartHouseLib:CONN_4_5mm" H 2250 2600 50  0000 C CNN
F 3 "" H 2250 2600 50  0000 C CNN
	1    2250 2600
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X04 BUS2
U 1 1 59BC2463
P 7550 2600
F 0 "BUS2" H 7550 2850 50  0000 C CNN
F 1 "CONN_01X04" V 7650 2600 50  0000 C CNN
F 2 "SmartHouseLib:CONN_4_5mm" H 7550 2600 50  0000 C CNN
F 3 "" H 7550 2600 50  0000 C CNN
	1    7550 2600
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P1
U 1 1 59BC32F8
P 4200 5900
F 0 "P1" H 4200 6050 50  0000 C CNN
F 1 "CONN_01X02" V 4300 5900 50  0000 C CNN
F 2 "SmartHouseLib:CONN_2_3.5mm" H 4200 5900 50  0000 C CNN
F 3 "" H 4200 5900 50  0000 C CNN
	1    4200 5900
	0    1    1    0   
$EndComp
$Comp
L STM32DISCOVERY U1
U 1 1 59D762A4
P 3600 4200
F 0 "U1" H 4050 3450 60  0000 C CNN
F 1 "STM32DISCOVERY" H 3650 5100 60  0000 C CNN
F 2 "SmartHouseLib:STM32_DISCOVERY" H 4050 3450 60  0001 C CNN
F 3 "" H 4050 3450 60  0001 C CNN
	1    3600 4200
	1    0    0    -1  
$EndComp
$Comp
L LM2596_MOD U2
U 1 1 59D75ABF
P 6150 3850
F 0 "U2" H 6150 3850 60  0000 C CNN
F 1 "LM2596_MOD" H 6150 3850 60  0000 C CNN
F 2 "SmartHouseLib:LM2596_MOD" H 6150 3850 60  0001 C CNN
F 3 "" H 6150 3850 60  0001 C CNN
	1    6150 3850
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 BUS3
U 1 1 59D7695F
P 3700 6850
F 0 "BUS3" H 3700 7100 50  0000 C CNN
F 1 "CONN_01X04" V 3800 6850 50  0000 C CNN
F 2 "SmartHouseLib:CONN_4_5mm" H 3700 6850 50  0000 C CNN
F 3 "" H 3700 6850 50  0000 C CNN
	1    3700 6850
	0    1    1    0   
$EndComp
$Comp
L CONN_01X02 P2
U 1 1 59D7799D
P 5450 3600
F 0 "P2" H 5450 3750 50  0000 C CNN
F 1 "CONN_01X02" V 5550 3600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 5450 3600 50  0000 C CNN
F 3 "" H 5450 3600 50  0000 C CNN
	1    5450 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	2450 2450 7350 2450
Wire Wire Line
	5700 4300 5900 4300
Wire Wire Line
	5700 3300 5700 4300
Wire Wire Line
	5700 3400 5900 3400
Connection ~ 5700 3400
Wire Wire Line
	5550 4400 6350 4400
Wire Wire Line
	6350 4300 6350 5700
Wire Wire Line
	5900 4300 5900 5500
Wire Wire Line
	5900 5500 4150 5500
Wire Wire Line
	4150 5300 4150 5700
Wire Wire Line
	6350 5700 4250 5700
Connection ~ 6350 4400
Wire Wire Line
	3850 6650 7300 6650
Wire Wire Line
	5500 3400 5550 3400
Wire Wire Line
	5400 3400 5200 3400
Wire Wire Line
	7350 2550 2450 2550
Wire Wire Line
	3750 6650 3750 6500
Wire Wire Line
	3750 6500 7150 6500
Wire Wire Line
	2450 2650 2650 2650
Wire Wire Line
	2650 2650 2650 2950
Wire Wire Line
	2650 2950 1750 2950
Wire Wire Line
	1750 2950 1750 3800
Wire Wire Line
	1750 3800 2150 3800
Wire Wire Line
	5200 4600 6900 4600
Wire Wire Line
	6900 4600 6900 2650
Wire Wire Line
	6900 2650 7350 2650
Wire Wire Line
	3650 6650 3650 5550
Wire Wire Line
	3650 5550 1850 5550
Wire Wire Line
	1850 5550 1850 4600
Wire Wire Line
	1850 4600 2150 4600
Wire Wire Line
	3550 5700 3550 6650
Wire Wire Line
	3550 5700 1650 5700
Wire Wire Line
	1650 5700 1650 4700
Wire Wire Line
	1650 4700 2150 4700
Wire Wire Line
	2450 2750 2500 2750
Wire Wire Line
	2500 2750 2500 2850
Wire Wire Line
	2500 2850 1450 2850
Wire Wire Line
	1450 2850 1450 3900
Wire Wire Line
	1450 3900 2150 3900
Wire Wire Line
	5200 4500 6800 4500
Wire Wire Line
	6800 4500 6800 2750
Wire Wire Line
	6800 2750 7350 2750
Wire Wire Line
	5900 3400 5900 2550
Connection ~ 5900 2550
Connection ~ 7300 2450
Wire Wire Line
	7300 6650 7300 2450
Wire Wire Line
	7150 6500 7150 2550
Connection ~ 7150 2550
Wire Wire Line
	6350 3400 6350 2450
Connection ~ 6350 2450
Wire Wire Line
	5550 3400 5550 4400
$Comp
L CONN_01X01 P3
U 1 1 59D7B665
P 5050 2800
F 0 "P3" H 5050 2900 50  0000 C CNN
F 1 "CONN_01X01" V 5150 2800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 5050 2800 50  0000 C CNN
F 3 "" H 5050 2800 50  0000 C CNN
	1    5050 2800
	-1   0    0    1   
$EndComp
Wire Wire Line
	4150 5300 2150 5300
Wire Wire Line
	2150 5300 2150 5100
Connection ~ 4150 5500
Wire Wire Line
	5250 2800 5250 3200
Wire Wire Line
	5250 3200 5200 3200
$EndSCHEMATC