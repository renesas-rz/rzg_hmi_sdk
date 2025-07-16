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

## Functional description of the config files under the config directory

1. Setting details

   Configure the UI settings for the buttons that are displayed when demo-launcher is opened.

2. File name (The application to be displayed depends on the evaluation board used.)
   - lvgl_launcher_smarc-rzg2l.json : configuration file for RZ/G2L

      Benchmark demo, showing the CHROMIUM app.

   - lvgl_launcher_smarc-rzg2lc.json : configuration file for RZ/G2LC

	   A benchmark demo will be displayed.

   - lvgl_launcher_smarc-rzg2ul.json : configuration file for RZ/G2UL

	   A benchmark demo will be displayed.

3. Setup Method

   Up to 8 buttons can be added to be displayed when demo-launcher is opened.

EXAMPLE . How to set up the first button (after the second button, duplicate the following source code according to the number of buttons you want to set up.)

    {
      exe_cmd : " aaa/bb/e ",     Benchmark demo, startup command to execute chromium app startup file path
      icon_image : " xxx.png ",   Path to demo-launcher button icon image
      description : " **\*** "    Button description string for demo-launcher (max. 28 characters)
    {

Path to the demo-launcher configuration file installed on the evaluation board
- /usr/share/demo-launcher/

## When building the demo-launcher source code, the following command is used to specify the machine name.

Execution command(Enter the name of the evaluation board to be used in smarc-rzg2l,smarc-rzg2lc,smarc-rzg2ul in "MACHINE NAME".)
```
$export MACHINE=<MACHINE NAME>
$make
```
