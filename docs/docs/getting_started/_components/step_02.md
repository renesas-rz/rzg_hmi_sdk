## Step 2: Obtain necessary environment

### 1. Necessary Equipment

Please prepare the following equipment for your EVK.

=== "RZ/G2L"

    +-------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------------------------+
    |    Equipment                                          |    Purpose                                                        |    Remarks                                                       |
    +=======================================================+===================================================================+==================================================================+
    | RZ/G2L Module Board (SMARC2.1) + Common Carrier Board | It is used to evaluate not only Linux but also demo programs or   | Included with RZ/G2L Evaluation Board Kit (EVK).                 |
    |                                                       | applications that run on Linux in the Linux operating environment |                                                                  |
    | (P/N: RTK9744L23S01000BE)                             | provided by HMI SDK.                                              |                                                                  |
    |                                                       |                                                                   |                                                                  |
    |                                                       | * 4GB or more ROM (SPI or eMMC or SD)                             |                                                                  |
    |                                                       | * 2GB or more RAM (DDR4/DDR3L 16bit x 1.6/1.3Gbps)                |                                                                  |
    +-------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------------------------+
    | USB serial cable                                      | It is used to connect the PC and the EVK and get the console      | Included   with RZ/G2L Evaluation Board Kit (EVK).               |
    |                                                       | output of Linux running on the EVK.                               |                                                                  |
    |                                                       |                                                                   |                                                                  |
    |                                                       | * Connect to micro USB type-B (2.0) port of EVK                   |                                                                  |
    +-------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------------------------+
    | USB Power Delivery (PD) AC adapter + USB C PD cable   | Use for power supply.                                             | 　                                                                |
    | for power supply                                      |                                                                   |                                                                  |
    |                                                       | * Connect to USB type-C port of EVK                               |                                                                  |
    +-------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------------------------+
    | PC                                                    | It can be used to operate the demo environment from a terminal    | The OS of the PC is as follows. However, Windows PCs are for     |
    |                                                       | on a PC, rebuild HMI SDK Linux, or use it as a development device | debugging using a serial connection and cannot be used for       |
    |                                                       | for applications.                                                 | development such as building software.                           |
    |                                                       |                                                                   |                                                                  |
    |                                                       | * At least 100GB or more free space of HDD/SDD                    | * Ubuntu 20.04 LTS, 64-bit version                               |
    |                                                       | * 8GB or more RAM                                                 | * Windows 10 or 11                                               |
    |                                                       | * 4-core or more CPU                                              |                                                                  |
    +-------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------------------------+
    | HDMI display monitor + HDMI cable                     | Used to display demo programs or applications provided by HMI     | If you need a touch panel function, you need a panel that        |
    |                                                       | SDK.                                                              | supports USB connection.                                         |
    |                                                       |                                                                   |                                                                  |
    |                                                       | * Connect to micro HDMI port of EVK                               | The HMI SDK supports the display of resolutions supported by the |
    |                                                       |                                                                   | Extended Display Identification Data (EDID) information obtained |
    |                                                       |                                                                   | from this HDMI display monitor.                                  |
    +-------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------------------------+
    | USB mouse                                             | Used to operate demo programs and applications provided by        | 　                                                                |
    |                                                       | HMI SDK.                                                          |                                                                  |
    |                                                       |                                                                   |                                                                  |
    |                                                       | * USB HID Compliant                                               |                                                                  |
    +-------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------------------------+
    | USB hub                                               | Used when multiple USB devices are required for the demo          | 　                                                                |
    |                                                       | program or applications provided by HMI SDK.                      |                                                                  |
    +-------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------------------------+
    | USB keyboard                                          | Used to operate demo programs and applications provided by        | 　                                                                |
    |                                                       | HMI SDK.                                                          |                                                                  |
    |                                                       |                                                                   |                                                                  |
    |                                                       | * USB HID Compliant                                               |                                                                  |
    +-------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------------------------+
    | USB touch screen                                      | Used to operate demo programs and applications provided by        | 　                                                                |
    |                                                       | HMI SDK.                                                          |                                                                  |
    |                                                       |                                                                   |                                                                  |
    |                                                       | * USB HID Compliant                                               |                                                                  |
    +-------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------------------------+
    | Audio speaker                                         | Used to evaluate the audio output demo programs or applications   | 　                                                                |
    |                                                       | provided by HMI SDK.                                              |                                                                  |
    |                                                       |                                                                   |                                                                  |
    |                                                       | * 3.5mm mini plug connector required                              |                                                                  |
    +-------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------------------------+
    | micro SD card                                         | Linux and demo images provided by the HMI SDK are written and     | Linux on the RZ/G2L EVK is booted from a micro SD card by eSD    |
    |                                                       | used as a Linux boot device.                                      | boot.                                                            |
    |                                                       |                                                                   |                                                                  |
    |                                                       | * Type: SDHC                                                      |                                                                  |
    |                                                       | * Speed class: UHI-Class 10                                       |                                                                  |
    |                                                       | * Capacity: Minimum 4GB, recommended 8GB                          |                                                                  |
    +-------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------------------------+

### 2. Necessary Software

Please install following software **on Linux PC**.

* git
