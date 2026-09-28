## Step 5: Run the HMI Demo Applications

The HMI SDK supports the following demo applications. Follow the steps below to use them.

* LVGL Home Panel Demo
* Chromium Home Panel Demo
* Flutter Samples

<br>
Follow the steps below to use them.

1. Prepare the necessary equipment and connect it to your EVK board by following the instructions in [Hardware Setup](../hmi_applications/#hardware-setup).

2.  Set up the DIP switch for ***eSD boot mode***.

    === "RZ/G3L"

        Set up DIP switch SW_MODE as follows.

        * SW_MODE

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

                ![](images/smarc-carrier-board-II-SW_MODE.png){ align=left .switch-icon }

                |   SW_MODE[1]   |   SW_MODE[2]   |  SW_MODE[3]  |   SW_MODE[4]   |
                |:--------------:|:--------------:|:------------:|:--------------:|
                | ON {: .green } | ON {: .green } | OFF {: .red} | ON {: .green } |


3.  Insert the bootable microSD card created in [Step 4](../getting_started/#step-4-create-sd-cards-with-the-prebuilt-image) into the microSD card slot for eSD boot mode, and then power on the EVK board.

    !!! success "Tip"
        *  Please refer to the [EVK Peripheral Setup](../hmi_applications/#evk-peripheral-setup) for the location of the microSD card slot.
        *  Press and hold the power button (red button) for 1 second to turn on the EVK board.

4.  The HMI SDK Demo Launcher starts **automatically** after the system has fully booted.

    After approximately 30 seconds, the HMI SDK Demo Launcher appears.  
    Click the corresponding button to launch and try each demo application provided by the HMI SDK.

    ![](../hmi_applications/images/demo/demo_launcher.png){: width="40%"}

    !!! success "Tip"
        Please note that the buttons displayed on the Demo Launcher vary depending on the device.
        For information on the demo applications supported on each device, refer to [HMI Application Contents](../overview/#hmi-application-contents).

    !!! success "Tip"
        To power off the board, execute the `shutdown -h now` command in the terminal. Once the screen turns black, press and hold the power button (red button) for approximately 2 seconds to complete the shutdown process.

This concludes the Getting Started guide.  

For detailed information about each demo application, see [Demo Applications](../hmi_applications/#demo-applications).  
For further development of sample applications, see [Sample Applications](../hmi_applications/#sample-applications).  
For additional customizations, see [Wiki](../wiki/).

