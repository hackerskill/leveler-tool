# leveler-tool
&#x09;

### A interactive leveler tool based on rp 2040 with acceleration sensor and led matrix.
---
Used to measure angle of displacement for a horizontal or a vertical surface, based on RP2040 with acceleration sensor and led matrix. Modules plug in into the custom PCB, allowing for measuring angle of displacement for a horizontal or a vertical surface.

## Features
- XIAO RP2040 acts as the main microcontroller
- Real time tilt measurement using an ADXL345
- MAX7219 LED matrix for visual feedback
- Active buzzer for audio feedback
- Cherry MX switch for user input
- USB-C connectivity through the XIAO RP2040 for Power
- Compact custom PCB

---

# Schematics-
<img width="822" height="396" alt="leveler-tool-schematics" src="https://github.com/user-attachments/assets/e9b3a43d-c00b-4f78-a8f8-e6cc07fc817a" />

# PCB-
<img width="770" height="749" alt="leveler-tool" src="https://github.com/user-attachments/assets/9abca95c-7428-49c4-af3f-86e4f862a1dd" />

## How It Works

1. The ADXL345 continuously measures acceleration along its three axes.

2. The RP2040 processes these measurements and converts them to angle. The resulting angle is used to determine which leds should be turned on using the LED matrix.

3. The Buzzer turns on when the device is exactly parallel to the surface.

4. The Cherry MX switch is used for user interaction such as changing modes or temporary turning off.


# BOM-
| Component Name | Description | Quantity |
| :--- | :--- | :---: |
| **Seeed Studio Xiao RP2040** | Devboard for RP2040 Chipset | 1 |
| **MAX7219** | 8x8 LED Display Matrix | 1 |
| **ADXL345** | 3-Axis Digital Accelerometer Module | 1 |
| **Active Buzzer** | 3V3 Active Buzzer | 1 |
| **Custom PCB** | Custom PCB | 1 |

---

**Made by hackerskill**

