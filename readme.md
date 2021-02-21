# 燒錄

[ATmega328p data sheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
[Design consideration](http://ww1.microchip.com/downloads/en/Appnotes/AN2519-AVR-Microcontroller-Hardware-Design-Considerations-00002519B.pdf)
[TSX-3225 data sheet](https://support.epson.biz/td/api/doc_check.php?dl=brief_TSX-3225&lang=en): C~L~ = 9 pF

## To-Do
- [ ] calculate appropriate capacitance for TSX-3225

## Testing Log
- 02/19
    1. 完整片: invalid device signature = 0x000000
    2. MCU+Crystal+reset pull-up: 可燒錄arduino duemilanove, nano, m328p on board bootloader
        - ISP pin 2 to 5V wiring soldered
    4. 僅有MCU: 可燒錄m328p on board bootloader

- 02/20 (Crystal behave strangely)
    1. invalid device signature = 0x000000
        - ISP pin 2 to 5V wiring soldered
        - ~~PB6, PB7 啥都沒有~~
    3. invalid device signature = 0x000000
        - ~~PB6, PB7 有不穩定的怪異週期波~~
    5. 可燒錄arduino duemilanove, nano bootloader (需要先燒due再燒nano)
        - ISP pin 2 to 5V wiring soldered
        - 加上Crystal, reset pull-up, decouple 1, decouple 2, aref decouple, avcc decouple 
        - ~~PB6,PB7 有穩定但怪異的週期波~~
- 02/21 (resources read: [wiring](https://www.avrfreaks.net/forum/does-device-signature-0x000000-mean-atmega-bad)、[fuses&cmd](https://forum.arduino.cc/index.php?topic=407511.0)、[bit clock delay](https://forum.arduino.cc/index.php?topic=25385.0))
    1. invalid device signature = 0x000000
    2. invalid device signature = 0x000000
    3. invalid device signature = 0x000000 &Rarr; remove analogdecouple2 inductor to get it working again &Rarr; after two success burning and re-connect, it stop working
        - **AREF must be connected to GND with a capacitor of 0.1 uf**
    4. new board: MCU + alternate Crystal &rArr; invalid device signature = 0x000000


## MCU
1. Use Arduino to burn bootloader into MCU
2. Write program
    - Arduino language + Arduino as burner **or**
    - Preferred language + `.hex` + avrdudess

## XBee
[XCTU](https://www.digi.com/products/embedded-systems/digi-xbee/digi-xbee-tools/xctu) + Specific mini-USB converter

## Circuit 
1. 加上一個LED給MCU測試用
2. 加上一個可以接出來的GND做為檢測用
3. 燒錄ICSP畫成可以直接插在UNO上