# Pixel-Star
PCB star with RGB LEDs, xmas decoration

![alt text](https://github.com/drzacek/Pixel-Star/blob/master/render_01.png "Kicad PCB 3D-render")



With this project you can make a simple yet nice star-shaped PCB with a bunch of addressable LEDs.

It has STM32 microcontroller on board and this project provides software for it to drive the LEDs.
<br/><br/><br/>


In order to make it:

1. Download KiCAD 6, STM32CubeIDE, clone/download this project
2. Generate Gerber files according to your manufarcturer rules (for example [JLCPCB](https://support.jlcpcb.com/article/194-how-to-generate-gerber-and-drill-files-in-kicad-6))
3. Order the PCB
4. Order the parts (Kicad project contains links to all parts on lcsc)
5. Solder everything
6. Compile the STM32 project
7. Flash the firmware using ST-Link


A cable with 4-pin molex picoblade connector is needed to flash the board. 
[Like this one here](https://www.ebay.de/itm/174533296900)
<br/><br/><br/>


A quick test of the board:

[![Pixel-Star on Youtube](https://img.youtube.com/vi/iGwG598rLek/0.jpg)](https://www.youtube.com/watch?v=iGwG598rLek)


<br/><br/><br/>

### Bill of Materials

|  Pos. | Name  | Link  | Amount  |
| ------------ | ------------ | ------------ | ------------ |
| 1.  | Capacitor 10µF 1206  | [Link](https://www.lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_Samsung-Electro-Mechanics-CL31B106KAHNNNE_C14860.html)  |  2  |
| 2.  | Capacitor 100nf 0805  | [Link](https://www.lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_CCTC-TCC0805X7R104K500DT_C282732.html)  | 17  |
| 3.  | Capacitor 4.7µF 1206  | [Link](https://www.lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_Samwha-Capacitor-CS3216X7R475K160NRI_C5189824.html)  | 1  |
| 4.  | WS2813E RGB LED  | [Link](https://www.lcsc.com/product-detail/Light-Emitting-Diodes-LED_Worldsemi-WS2813E_C160214.html)  | 11  |
| 5.  | LED 1206 Emerald  | [Link](https://www.lcsc.com/product-detail/Light-Emitting-Diodes-LED_XINGLIGHT-XL-3216UGC_C965825.html)  | 5  |
| 6.  | USB-C Connector  | [Link](https://www.lcsc.com/product-detail/USB-Connectors_SHOU-HAN-TYPE-C-16PIN-2MD-073_C2765186.html)  | 1  |
| 7.  | Picoblade 1x4 Connector  | [Link](https://www.lcsc.com/product-detail/Wire-To-Board-Wire-To-Wire-Connector_MOLEX-532610471_C240847.html)  | 1  |
| 8.  | Resistor 5.11k 0805  | [Link](https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_UNI-ROYAL-Uniroyal-Elec-0805W8F5111T5E_C46039.html)  | 2  |
| 9.  | Resistor 1k 0805  | [Link](https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_FOJAN-FRC0805F1001TS_C2907232.html)  | 2  |
| 10.  | Resistor 10k 0805  | [Link](https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_UNI-ROYAL-Uniroyal-Elec-0805W8F1002T5E_C17414.html)  | 2  |
| 11.  | Resistor 47 Ohm 0805  | [Link](https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_Walsin-Tech-Corp-WR08X47R0FTL_C168456.html)  | 5  |
| 12.  | Button  | [Link](https://www.lcsc.com/product-detail/Tactile-Switches_Korean-Hroparts-Elec-K2-1107ST-A4DW-06_C118141.html)  | 3  |
| 13.  | Voltage regulator 3.3V  | [Link](https://www.lcsc.com/product-detail/Linear-Voltage-Regulators-LDO_HEERMICR-AMS1117-3-3_C5199435.html)  | 1  |
| 14.  | MCU STM32G030  | [Link](https://www.lcsc.com/product-detail/Microcontroller-Units-MCUs-MPUs-SOCs_STMicroelectronics-STM32G030F6P6TR_C529330.html)  | 1  |
| 15.  | Level shifter  | [Link](https://www.lcsc.com/product-detail/Buffers-Drivers_Texas-Instruments-SN74LV1T34DBVR_C100024.html)  | 1  |
