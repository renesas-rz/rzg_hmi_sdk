## Hardware Setup

### Necessary Equipment

*  Please prepare the following required equipment.

!!! content-wrapper no-indent table-no-sort table-no-hover ""

    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    |    Equipment                                                 |    Requirements                                                                                                           |
    +=======================+======================================+===========================================================================================================================+
    |                       | Target RZ/G EVK Board                |                                                                                                                           |
    |                       |                                      |                                                                                                                           |
    |Included with RZ/G EVK +--------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    |                       | USB Cable (for serial communication) | *Port*: Connect to micro USB Type-B (2.0) port on the board                                                               |
    |                       |                                      |                                                                                                                           |
    +-----------------------+--------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | USB Power Delivery (PD) AC Adapter &                         | *Port*: Connect to the USB Type-C port on the board                                                                       |
    | USB Type-C PD Cable                                          |                                                                                                                           |
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | PC                                                           | *Storage*: a maximum of 450GB of free space on HDD/SSD                                                                    |
    |                                                              | *Memory*: 8GB or more RAM                                                                                                 | 
    |                                                              | *CPU*: 4-core or more CPU                                                                                                 |
    |                                                              |                                                                                                                           |
    |                                                              | ***OS***:                                                                                                                 |
    |                                                              |    **Linux: Ubuntu 22.04 LTS, 64-bit version**                                                                            |
    |                                                              |    **Windows: Windows 11**                                                                                                |
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | Micro SD Card & Reader                                       | *Type*: SDHC                                                                                                              |  
    |                                                              | *Speed Class*: UHI-Class 10                                                                                               |
    |                                                              | ***Capacity*: Minimum 4GB, recommended 8GB**                                                                              |
    |                                                              |                                                                                                                           |
    |                                                              | A micro SD card is used to store the Linux system and prebuilt demo images from the HMI SDK.                              | 
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | HDMI Display & HDMI Cable                                    | *Port*: Connect to the micro HDMI on the board                                                                            |
    |                                                              |                                                                                                                           |
    |                                                              | For touch displays, both HDMI and USB cables are required.                                                                |
    |                                                              | *Standard*: USB HID Compliant                                                                                             |
    |                                                              |                                                                                                                           |
    |                                                              | No specific resolution is required.                                                                                       |
    |                                                              | The board automatically uses the resolutions supported by your HDMI display.                                              |
    |                                                              | See [How to Change the Display Resolution](../wiki/common_change-display-resolution/) for more information.               |
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | USB Hub                                                      | Used when multiple USB devices are needed.                                                                                |
    |                                                              |                                                                                                                           | 
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | USB Keyboard                                                 | *Standard*: USB HID Compliant                                                                                             |
    |                                                              |                                                                                                                           |
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | USB Mouse                                                    | *Standard*: USB HID Compliant                                                                                             |
    |                                                              |                                                                                                                           |
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | USB Camera                                                   | *Standard*: USB HID Compliant                                                                                             |
    |                                                              |                                                                                                                           |
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | Audio Speaker                                                | *Port*: 3.5mm mini plug connector                                                                                         |
    |                                                              |                                                                                                                           |
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | Ethernet Cable                                               |  Used to connect the board to your host PC or network.                                                                    |
    |                                                              |                                                                                                                           |
    |                                                              |  * Optional, only needed when developing using methods such as:                                                           |
    |                                                              |    File transfer (binaries, logs, images)                                                                                 |
    |                                                              |    SSH access (remote login)                                                                                              |
    |                                                              |    Network access (internet or communication with other devices)                                                          |
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
!!! success "Tip"
    A Windows PC can be used for flashing an SD card and debugging via a serial connection.<br> 
    For further development and deployment, use a Linux PC.



### EVK Peripheral Setup

Please set up the necessary equipment referring to the EVK peripheral diagram below.

=== "RZ/G3E"

    ![](images/hardware-requirements_rzg3e.png){: width="80%"}

!!! success "Tip"
    *  For *eSD boot mode*, insert the microSD card into the **microSD0** on the module board; for *QSPI boot mode*, insert the microSD card into the **microSD1** on the common carrier board.
    *  If you use a touch-panel HDMI display, in addition to the HDMI cable, a USB cable connected to **USB** is required to enable touch functionality.
    *  For Ethernet connection, RZ/G3E support **Ethernet 0 and Ethernet 1 **.


### EVK DIP Switch Setup

*  ***eSD Boot Mode***

=== "RZ/G3E"

    Set DIP switch SW_MODE as follows.

    * SW_MODE (on Common Carrier Board II)

        !!! content-wrapper no-indent table-no-sort table-no-hover ""

            ![](images/smarc-carrier-board-II-SW_MODE.png){ align=left .switch-icon }

            |   SW_MODE[1]   |   SW_MODE[2]   |  SW_MODE[3]  |   SW_MODE[4]   |
            |:--------------:|:--------------:|:------------:|:--------------:|
            | ON {: .green } | ON {: .green } | OFF {: .red} | ON {: .green } |

*  ***QSPI Boot Mode***

=== "RZ/G3E"

    Set DIP switch SW_MODE as follows.

    * SW_MODE (on Common Carrier Board II)

        !!! content-wrapper no-indent table-no-sort table-no-hover ""

            ![](images/smarc-carrier-board-II-SW_MODE_QSPI.png){ align=left .switch-icon }

            |   SW_MODE[1]   |   SW_MODE[2]   |  SW_MODE[3]  |   SW_MODE[4]   |
            |:--------------:|:--------------:|:------------:|:--------------:|
            | OFF {: .red }  | OFF {: .red }  | OFF {: .red} | ON {: .green } |

    !!! warning "Notice"
        Firmware (bootloader) updates are required for QSPI boot modes. Please follow the steps provided in [How to Update Firmware (Flash Writer and Bootloaders)](../wiki/common_update-firmware/).
    !!! note
        Please refer to [How to Boot from a microSD Card in QSPI Boot Mode](../wiki/common_qspi-boot-mode/) for details.

    
