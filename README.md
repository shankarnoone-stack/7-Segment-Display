

## TimerSwitch
Starbie is a small basic timer on a PCB with a TM1637 module. It uses a rotary encoder and bult in switch to change the set time and start the timer. The project also has two buttons for changing between timers and 

I designed the schematic and PCB in KiCad, routed the traces, and built the firmware in Arduino IDE.


![7-Segment front render](Screenshot%202026-11-01%20175531.png)
![7-Segment front render](Screenshot%202026-11-01%20175540.png)

## What it is

TimerSwitch is a small timer designed to store multiple timers inside it. It's features include changing the smount of time you want to set, alternating between timers, and keeping track of how much time is passing.

## How?

I started by following the guide in the half life website. First, I chose to do the TM1637 module, and set up the schematic with the Raspberry Pi Pico, MX buttons, a Rotary Encoder, and a connector for the module. After this, I converted the schematic into a PCB, routed the traces, and checked it using designs rules checker to make sure that it was ok.
I finally wrote the firmware for the Timer.

## Why?
I made it for the week 4 Half Life hackclub challenge, to learn about how to build displays using Arduino and KiCad.

## BOM.csv
I looked towards amazon for my parts, and used JLCPCB for my PCB vendor. For my microcontroller, I resorted to go with Adafruit.
| Part| Quantity | Price | Vendor |
|---|---:|---:|---|
| [Raspberry Pi Pico](https://www.adafruit.com/product/4883)| 1 |$5| AdaFruit |
| [Rotary Encoder](https://www.amazon.com/gp/product/B07D3DF8TK)| 1 | $0.99 | Amazon |
| [Keycaps](https://www.amazon.com/dp/B0CQ2VLMVY)| 1 | $2.40 | Amazon |
| [TM1637]([https://www.amazon.com/dp/B0BLG7R99R](https://www.amazon.com/dp/B0F4PSNH94)) | 1 | $7.49 | Amazon |
| [MX Switches](https://www.amazon.com//dp/B0FQP8VYX4)| 2 | $0.72 | Amazon |
| [PCB](https://jlcpcb.com/)| 1 | $4 | JLCPCB |
| [Female Header](https://www.amazon.com/gp/product/B0F3CZVSPJ)| 1 | $0.05 | Amazon |

- **Parts Subtotal:** $21.37
- **Tax & Shipping:** $7.75 (Including PCB manufacturing shipping/taxes)


## Repository contents

- KiCad source files
- PCB renders
- Arduino
