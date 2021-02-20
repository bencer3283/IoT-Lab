# 燒錄

## Testing Log
- 02/19
    1. 完整片: invalid device signature = 0x000000
    2. MCU+Crystal+reset pull-up: 可燒錄arduino duelinanove, nano, m328p on board bootloader
        - ISP pin 2 to 5V wiring soldered
    4. 僅有MCU: 可燒錄m328p on board bootloader

- 02/20
    1. invalid device signature = 0x000000
        - ISP pin 2 to 5V wiring soldered
    3. invalid device signature = 0x000000
    4. 可燒錄arduino duelinanove bootloader
        - ISP pin 2 to 5V wiring soldered
        - 加上Crystal

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