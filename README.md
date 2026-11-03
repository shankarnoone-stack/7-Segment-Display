"SOKSOKQOKOSKOKOOKOSKOKOKSOKOSKOKSKOKSOKOKOKOKOKOKOKOKOKS"


## TimerSwitch
Starbie is a small basic timer on a PCB with a TM1637 module. It uses a rotary encoder and bult in switch to change the set time and start the timer. The project also has two buttons for changing between timers and 

I designed the schematic and PCB in KiCad, routed the traces, and exported the fabrication files. This is my Week 1 PCB project for Hack Club Half Life.


![7-Segment front render](Screenshot%202026-11-01%20175531.png)
![7-Segment front render](Screenshot%202026-11-01%20175540.png)

## What it is

TimerSwitch is a small timer designed to store 

## How?

I started by following the guide in the half life website. First, I chose to do the TM1637 module, and set up the schematic with the Raspberry Pi Pico, MX buttons, a Rotary Encoder, and a connector for the module. After this, I 
After this, I routed the traces, and checked it using designs rules checker to make sure that it was ok.
I finally exported the fabrication files and BOM.

## Why?
I made it for the week 4 Half Life hackclub challenge, to learn about how to build displays using Arduino and KiCad.

## BOM.csv
I looked towards amazon for my parts, and used JLCPCB for my PCB vendor. For my microcontroller, I first thought of aliexpress, but then I realized it was better to go with Seeed Studio.
| Part | What it is used for | Quantity | Price | Vendor |
|---|---|---:|---:|---|
| [XIAO ESP32-C3](https://www.seeedstudio.com/Seeed-XIAO-ESP32C3-p-5431.html) | Main microcontroller and Wi-Fi | 1 |$5| Seeed Studio |
| [0.96-inch OLED Display](https://www.amazon.com/Display-SSD1306-Self-Luminous-Compatible-Raspberry/dp/B0GBWXTR1Z) | Displays pet status and sensor readings | 1 | $6 | Amazon |
| [10k Resistor](https://www.amazon.com/10K-Resistor-Tolerance-Resistors-Resistance/dp/B0B4JFPHTW) | 6DOF Motion and gyroscope sensor | 1 | $0.05 |Amazon|
| [Keycaps](https://www.amazon.com/dp/B0CQ2VLMVY) | Temperature and humidity monitoring | 1 | $2.40 | Amazon |
| [MPU-6050](https://www.amazon.com/dp/B0943SGP34) | Mechanical user input switches | 1 | $2.29 | Amazon |
| [DHT11](https://www.amazon.com/dp/B0BLG7R99R) | Clear dual-layer customizable keycap shell | 1 | $3.33 | Amazon |
| [MX Switches](https://www.amazon.com//dp/B0FQP8VYX4) | Switches | 4 | $0.72 | Amazon |
| [PCB](https://jlcpcb.com/) | Custom circuit board manufacturing | 1 | $8.40 | JLCPCB |

- **Parts Subtotal:** 28.19
- **Tax & Shipping:** $21.44 (Including PCB manufacturing shipping/taxes)
- **Total Project Cost:** **$49.63**


## Repository contents

- KiCad source files and fabrication exports
- PCB renders
- Arduino
- BOM
