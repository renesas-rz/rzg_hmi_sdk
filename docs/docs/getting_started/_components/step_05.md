## Step 5: Run the HMI Demo Applications

The HMI SDK supports the following demo applications. Follow the steps below to use them.

* LVGL Benchmark Demo
* LVGL Home Panel Demo
* Chromium Home Panel Demo
* Flutter Samples

<br>
Follow the steps below to use them.

1. Prepare the necessary equipment and connect it to your EVK board by following the instructions in [Hardware Setup](../hmi_applications/#hardware-setup).

2.  Set up the DIP switch for ***eSD boot mode***.

    === "RZ/G3E"

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
        *  Press and hold the power button (red button) for 1 second to turn on the EVK board, and for 2 seconds to turn it off.

4.  The HMI SDK Demo Launcher launches **automatically** once the device is fully booted.<br> 

    Right after boot, you will see the launch window as shown below.

    ![](../hmi_applications/images/demo/demo_launching.png){: width="40%"} 

    After a few seconds, the HMI SDK Demo Launcher will appear.<br>
    Click the corresponding button to try each demo application we provide.

    ![](../hmi_applications/images/demo/demo_launcher.png){: width="40%"}
    ![](../hmi_applications/images/demo/demo_launcher_2.png){: width="40%"}


This concludes the Getting Started guide.
<br><br>
For detailed information about each demo application, see [Demo Applications](../hmi_applications/#demo-applications).<br>
For further development of sample applications, see [Sample Applications](../hmi_applications/#sample-applications).<br>
For additional customizations, see [Wiki](../wiki/).

