# ASNPRouter
Allex Serial Network Protocol router device based on stm32 board(blue pill) and arduino libs(STM32GENERIC)

# Hardware  
STM32 board - blue pill(or another with simillar pinout)  
![Blue pill](https://revspace.nl/images/thumb/f/fb/Bluepill_pinout.png/800px-Bluepill_pinout.png)  

DC-DC converter(default PCB based on LM2596)
![DC-DC converter](http://roboshop.spb.ru/image/cache/catalog/demo/product/LM2596-down/LM2596-down-800x800.jpg)  

PCB designed to use with cheap plastic case:  
![cheap plastic case](https://ae01.alicdn.com/kf/HTB1mlf3LVXXXXaaXXXXq6xXFXXXK/1Pcs-New-font-b-Plastic-b-font-Electronic-Project-Box-100x60x25mm-Black-font-b-DIY-b.jpg)

# Software  
Arduino Libs:  
https://github.com/AllexSmartHouse/STM32GENERIC  

Use ST-Link  
Settings:  
Board: Blue pill  
USB: Disabled, No usb  
Serial communication: SerialUART1  
JTAG/SWD debugging: SWD
Upload method: ST-Link
