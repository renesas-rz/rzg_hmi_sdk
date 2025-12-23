## Step 5: Run the HMI Demo Applications

The HMI SDK supports the following demo applications. Follow the steps below to use them.

* LVGL Benchmark Demo
* LVGL Home Panel Demo
* Chromium Home Panel Demo

<br>
Follow the steps below to use them.

1. Prepare the necessary equipment and connect it to your EVK board by following the instructions in [Hardware Setup](../hmi_applications/#hardware-setup).

2.  Set up the DIP switch for ***eSD boot mode***.

    === "RZ/G2L"

        Set up DIP switch SW1 and SW11 as follows.

        * SW1

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

                ![](images/smarc-rzg2l-board-SW1.png){ align=left .switch-icon }

                |      SW1-1     |      SW1-2     |
                |:--------------:|:--------------:|
                | ON {: .green } | ON {: .green } |

        * SW11

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

                ![](images/smarc-carrier-board-SW11.png){ align=left .switch-icon }

                |     SW11-1     |     SW11-2     |    SW11-3    |     SW11-4     |
                |:--------------:|:--------------:|:------------:|:--------------:|
                | ON {: .green } | ON {: .green } | OFF {: .red} | ON {: .green } |

    === "RZ/G2LC"

        Set up DIP switch SW1 and SW11 as follows.

        * SW1

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

                ![](images/smarc-rzg2lc-board-SW1.png){ align=left .switch-icon }

                |      SW1-1     |      SW1-2     |       SW1-3     |     SW1-4     |      SW1-5      |      SW1-6     |
                |:--------------:|:--------------:|:---------------:|:-------------:|:---------------:|:--------------:|
                | ON {: .green } | ON {: .green } | ON* {: .green } | OFF* {: .red} | ON* {: .green } | Not used       |

                *These switches are not related to the settings required for this boot mode.

        * SW11

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

                ![](images/smarc-carrier-board-SW11.png){ align=left .switch-icon }

                |     SW11-1     |     SW11-2     |    SW11-3    |     SW11-4     |
                |:--------------:|:--------------:|:------------:|:--------------:|
                | ON {: .green } | ON {: .green } | OFF {: .red} | ON {: .green } |

    === "RZ/G2UL"

        Set up DIP switch SW1 and SW11 as follows.

        * SW1

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

                ![](images/smarc-rzg2ul-board-SW1.png){ align=left .switch-icon }

                |      SW1-1     |      SW1-2     |      SW1-3      |
                |:--------------:|:--------------:|:---------------:|
                | ON {: .green } | ON {: .green } | ON* {: .green } |

                *This switch is not related to the settings required for this boot mode.

        * SW11

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

                ![](images/smarc-carrier-board-SW11.png){ align=left .switch-icon }

                |     SW11-1     |     SW11-2     |    SW11-3    |     SW11-4     |
                |:--------------:|:--------------:|:------------:|:--------------:|
                | ON {: .green } | ON {: .green } | OFF {: .red} | ON {: .green } |


3.  Insert the bootable microSD card created in [Step 4](../getting_started/#step-4-create-sd-cards-with-the-prebuilt-image) into the microSD card slot for eSD boot mode (*sd ChC CN3 port* on Module Board), and then power on the EVK board.

    !!! success "Tip"
        *  Please refer to the [EVK Peripheral Setup](../hmi_applications/#evk-peripheral-setup) for the location of the microSD card slot.
        *  Press and hold the power button (red button, SW9) for 1 second to turn on the EVK board, and for 2 seconds to turn it off.

4.  The HMI SDK Demo Launcher launches **automatically** once the device is fully booted.<br> 

    Right after boot, you will see the launch window as shown below.

    ![](images/demo_launching.png){: width="40%"} 

    After a few seconds, the HMI SDK Demo Launcher will appear.<br>
    Click the corresponding button to try each demo application we provide.

    ![](images/demo_launcher.png){: width="40%"}


This concludes the Getting Started guide.
<br><br>
For detailed information about each demo application, see [Demo Applications](../hmi_applications/#demo-applications).<br>
For further development of sample applications, see [Sample Applications](../hmi_applications/#sample-applications).<br>
For additional customizations, see [Wiki](../wiki/).

