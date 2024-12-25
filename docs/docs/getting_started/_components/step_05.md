## Step 5: Run HMI SDK demo

### 1. Setup EVK's peripheral

Please setup following below diagram.

=== "RZ/G2L"

    ![](images/hardware-requirements.png)

### 2. Setup EVK's DIP switch

=== "RZ/G2L"

    Set up DIP switch SW1 and SW11 as follows.

    * SW1

        !!! content-wrapper no-indent table-no-sort table-no-hover ""

            ![](images/smarc-carrier-board-SW1.png){ align=left .switch-icon }

            |      SW1-1     |      SW1-2     |
            |:--------------:|:--------------:|
            | ON {: .green } | ON {: .green } |

    * SW11

        !!! content-wrapper no-indent table-no-sort table-no-hover ""

            ![](images/smarc-carrier-board-SW11.png){ align=left .switch-icon }

            |     SW11-1     |     SW11-2     |    SW11-3    |     SW11-4     |
            |:--------------:|:--------------:|:------------:|:--------------:|
            | ON {: .green } | ON {: .green } | OFF {: .red} | ON {: .green } |

### 3. Turn on EVK and run demo

=== "RZ/G2L"

    1.  Insert the bootable SD card created at [Step 4](#step-4-prepare-hmi-sdk-sd-card-image-for-demo) into the microSD card slot on SMARC module board as illustrated in the figure at ["1. Setup EVK's peripheral"](#1-setup-evks-peripheral).
    2.  Connect a USB cable to CN6 for power supply.
    3.  Press and hold power button (SW9) for 1 second to turn on the EVK.

        !!! note
            Press and hold the button for 2 seconds when you turn off the EVK.
