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
    |                       +--------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    |                       | *Parallel to HDMI Conversion Board   | *Only for RZ/G2UL                                                                                                         |
    |                       |                                      |                                                                                                                           | 
    |                       |                                      | Used to convert an FFC/FPC connector to a micro HDMI connector.                                                           |
    +-----------------------+--------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | USB Power Delivery (PD) AC Adapter &                         | *Port*: Connect to the USB Type-C port on the board                                                                       |
    | USB Type-C PD Cable                                          |                                                                                                                           |
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | PC                                                           | *Storage*: 100GB or more free space on HDD/SSD                                                                            |
    |                                                              | *Memory*: 8GB or more RAM                                                                                                 | 
    |                                                              | *CPU*: 4-core or more CPU                                                                                                 |
    |                                                              |                                                                                                                           |
    |                                                              | ***OS***:                                                                                                                 |
    |                                                              |    **Linux: Ubuntu 22.04 LTS, 64-bit version**                                                                            |
    |                                                              |    **Windows: Windows 10 or 11**                                                                                          |
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
    | *USB Camera                                                  | *Only for RZ/G2L and RZ/G2LC.                                                                                             |
    |                                                              |                                                                                                                           |
    |                                                              | *Standard*: USB HID Compliant                                                                                             |
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | Audio Speaker                                                | *Port*: 3.5mm mini plug connector                                                                                         |
    |                                                              |                                                                                                                           |
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
    | *Ethernet Cable                                              |  Used to connect the board to your host PC or network.                                                                    |
    |                                                              |                                                                                                                           |
    |                                                              |  *Optional, only needed when developing using methods such as:                                                            |
    |                                                              |    File transfer (binaries, logs, images)                                                                                 |
    |                                                              |    SSH access (remote login)                                                                                              |
    |                                                              |    Network access (internet or communication with other devices)                                                          |
    +--------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------+
!!! success "Tip"
    A Windows PC can be used for flashing an SD card and debugging via a serial connection.<br> 
    For further development and deployment, use a Linux PC.



### EVK Peripheral Setup

Please set up the necessary equipment referring to the EVK peripheral diagram below.

=== "RZ/G2L"

    ![](images/hardware-requirements_rzg2l.png){: width="80%"}

=== "RZ/G2LC"

    ![](images/hardware-requirements_rzg2lc.png){: width="80%"}

=== "RZ/G2UL"

    ![](images/hardware-requirements_rzg2ul.png){: width="70%"}

!!! success "Tip"
    *  For *eSD boot mode*, insert the microSD card into the **sd ChC slot (CN3)** on the module board; for *QSPI boot mode*, insert the microSD card into the **micro SD slot (CN10)** on the common carrier board.
    *  If you use a touch-panel HDMI display, in addition to the HDMI cable, a USB cable connected to **USB 1 (CN12)** is required to enable touch functionality.
    *  For Ethernet connection, RZ/G2L and RZ/G2UL support **Ethernet 0 (CN9) and Ethernet 1 (CN8)**, while RZ/G2LC supports only **Ethernet 0 (CN9)**.


### EVK DIP Switch Setup

*  ***eSD Boot Mode***

=== "RZ/G2L"

    Set DIP switch SW1 and SW11 as follows.

    * SW1 (on Module Board)

        !!! content-wrapper no-indent table-no-sort table-no-hover ""

            ![](images/smarc-rzg2l-board-SW1.png){ align=left .switch-icon }

            |      SW1-1     |      SW1-2     |
            |:--------------:|:--------------:|
            | ON {: .green } | ON {: .green } |

    * SW11 (on Common Carrier Board)

        !!! content-wrapper no-indent table-no-sort table-no-hover ""

            ![](images/smarc-carrier-board-SW11.png){ align=left .switch-icon }

            |     SW11-1     |     SW11-2     |    SW11-3    |     SW11-4     |
            |:--------------:|:--------------:|:------------:|:--------------:|
            | ON {: .green } | ON {: .green } | OFF {: .red} | ON {: .green } |

=== "RZ/G2LC"

    Set DIP switch SW1 and SW11 as follows.

    * SW1 (on Module Board)

        !!! content-wrapper no-indent table-no-sort table-no-hover ""

            ![](images/smarc-rzg2lc-board-SW1.png){ align=left .switch-icon }

            |      SW1-1     |      SW1-2     |       SW1-3     |     SW1-4     |      SW1-5      |      SW1-6     |
            |:--------------:|:--------------:|:---------------:|:-------------:|:---------------:|:--------------:|
            | ON {: .green } | ON {: .green } | ON* {: .green } | OFF* {: .red} | ON* {: .green } | Not used       |

            *These switches are not related to the settings required for this boot mode.

    * SW11 (on Common Carrier Board)

        !!! content-wrapper no-indent table-no-sort table-no-hover ""

            ![](images/smarc-carrier-board-SW11.png){ align=left .switch-icon }

            |     SW11-1     |     SW11-2     |    SW11-3    |     SW11-4     |
            |:--------------:|:--------------:|:------------:|:--------------:|
            | ON {: .green } | ON {: .green } | OFF {: .red} | ON {: .green } |

=== "RZ/G2UL"

    Set DIP switch SW1 and SW11 as follows.

    * SW1 (on Module Board)

        !!! content-wrapper no-indent table-no-sort table-no-hover ""

            ![](images/smarc-rzg2ul-board-SW1.png){ align=left .switch-icon }

            |      SW1-1     |      SW1-2     |      SW1-3      |
            |:--------------:|:--------------:|:---------------:|
            | ON {: .green } | ON {: .green } | ON* {: .green } |

            *This switch is not related to the settings required for this boot mode.

    * SW11 (on Common Carrier Board)

        !!! content-wrapper no-indent table-no-sort table-no-hover ""

            ![](images/smarc-carrier-board-SW11.png){ align=left .switch-icon }

            |     SW11-1     |     SW11-2     |    SW11-3    |     SW11-4     |
            |:--------------:|:--------------:|:------------:|:--------------:|
            | ON {: .green } | ON {: .green } | OFF {: .red} | ON {: .green } |


*  ***QSPI Boot Mode***
    
Set DIP switch SW11 as follows for all boards.

!!! content-wrapper no-indent table-no-sort table-no-hover ""
    ![](images/smarc-carrier-board-SW11_QSPI.png){ align=left .switch-icon }

    |     SW11-1     |     SW11-2     |    SW11-3    |     SW11-4     |
    |:--------------:|:--------------:|:------------:|:--------------:|
    | OFF {: .red }  | OFF {: .red }  | OFF {: .red} | ON {: .green } |

    !!! warning "Notice"
        Firmware (bootloader) updates are required for QSPI boot modes. Please follow the steps provided in [How to Update Firmware (Flash Writer and Bootloaders)](../wiki/common_update-firmware/).
    !!! note
        Please refer to [How to Boot from a microSD Card in QSPI Boot Mode](../wiki/common_qspi-boot-mode/) for details.

    