# RZ Linux Demo Application Launcher

## Overview

RZ Linux Demo Application Launcher runs on RZ Evaluation Board Kit (EVK).

## Notes

- A maximum of 8 buttons can be created. Any buttons configured beyond the 8th will not be generated.
- Each button can display up to 28 characters. If more characters are entered, only the first 28 will be displayed, and the rest will be omitted.
- The app will not function if the line break code in the configuration file is not set to LF.
- For RZ/G2UL, operation is limited to either the touchpad or the mouse. Both cannot be used simultaneously.
- For the RZ/G2UL, only a mouse should be connected to the USB port. Connecting devices other than a mouse may result in the device becoming inoperable. (Ensure the mouse is assigned to event0.)

### Target Board

Currently, RZ Linux '_demo-launcher_' supports the following EVK.

- [RZ/G2L Evaluation Board Kit](https://www.renesas.com/us/en/products/microcontrollers-microprocessors/rz-mpus/rzg2l-evkit-evaluation-board-kit-rzg2l-mpu)
- [RZ/G2LC Evaluation Board Kit](https://www.renesas.com/en/products/microcontrollers-microprocessors/rz-mpus/rzg2lc-evkit-evaluation-board-kit-rzg2lc-mpu)
- [RZ/G2UL Evaluation Board Kit](https://www.renesas.com/en/products/microcontrollers-microprocessors/rz-mpus/rzg2ul-evkit-evaluation-board-kit-rzg2ul-mpu)

## License

This project is licensed under the [MIT License](LICENSE.txt). You are free to modify and customize it as you wish.
