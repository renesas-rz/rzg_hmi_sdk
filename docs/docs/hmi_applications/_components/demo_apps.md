## Demo Applications

This section explains how to run the HMI demo applications and provides detailed introductions for each one.

The HMI SDK Demo Launcher starts automatically when the EVK boots. Currently, it includes the following prebuilt demo applications.
If you want to customize them, their source code can be downloaded from the GitHub links listed in the table below.

!!! content-wrapper no-indent table-no-sort table-no-hover ""

    +--------------+----------------------------------------+---------------------------+------------------------------------------------------------------------------------------------------------------------------------+
    | Type         | Demo Applications                      | Target Device             | Source Code URL                                                                                                                    |
    +==============+========================================+===========================+====================================================================================================================================+
    | LVGL         | LVGL Benchmark Demo                    | RZ/G2L, RZ/G2LC, RZ/G2UL  | [Link to GitHub](https://github.com/renesas-rz/rz_benchmark_demo){: target=_blank }                                                |
    |              +----------------------------------------+---------------------------+------------------------------------------------------------------------------------------------------------------------------------+
    |              | LVGL Home Panel Demo                   | RZ/G2L, RZ/G2LC, RZ/G2UL  | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_home_panel_demo){: target=_blank }       |
    +--------------+----------------------------------------+---------------------------+------------------------------------------------------------------------------------------------------------------------------------+
    | Chromium     | Chromium Home Panel Demo               | RZ/G2L, RZ/G2LC           | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/chromium/home_panel_demo){: target=_blank }        |
    +--------------+----------------------------------------+---------------------------+------------------------------------------------------------------------------------------------------------------------------------+
<br>
Please follow the steps below to run the demo applications.

1.  Prepare the necessary equipment and configure the EVK DIP switches by following the instructions in [Hardware Setup](../hmi_applications/#hardware-setup).

2.  Insert the bootable microSD card into the microSD card slot for eSD boot mode (*sd ChC CN3 port* on Module Board), and then power on the EVK board.

    !!! success "Tip"
        *  Please refer to the [EVK Peripheral Setup](../hmi_applications/#evk-peripheral-setup) for the location of the microSD card slot.
        *  Press and hold the power button (red button, SW9) for 1 second to turn on the EVK board, and for 2 seconds to turn it off.

3.  The HMI SDK Demo Launcher launches **automatically** once the device is fully booted.<br> 

    Right after boot, you will see the launch window as shown below.

    ![](images/demo/demo_launching.png){: width="40%"} 

    After a few seconds, the HMI SDK Demo Launcher will appear.<br>
    Click the corresponding button to try each demo application we provide.

    ![](images/demo/demo_launcher.png){: width="40%"}

    !!! success "Tip"
        If you want to exit a demo application and return to the HMI SDK Demo Launcher, you can either<br> 
        *  restart your EVK board by press reset button (blue button, SW10) or<br> 
        *  run the following command in your board terminal to relaunch it: 
        ```bash 
        /usr/share/demo-launcher/start_demo.sh 
        ```
        {: .hash }
        
        Note that this is temporary behavior, and we will improve it in future releases.
    <br>

    *  ***LVGL Demo Applications***

    === "LVGL Benchmark Demo"

        This demo application is implemented using LVGL, and it includes the following tools for performance testing.

        ![](images/demo/demo_lvgl_benchmark.png){: width="40%"}

        Please click each tool and follow the detailed instructions to try them.<br>
        After you finish trying the tools, click the Quit button at the top-right corner to exit.

        ![](images/demo/demo_lvgl_benchmark_quit.png){: width="40%"}

    
    === "LVGL Home Panel Demo"

        This demo application is implemented using LVGL.<br> 
        Click the buttons or use the sidebar to explore the available functions.

        ![](images/demo/demo_lvgl_homepanel.png){: width="40%"} 

        For example, by clicking the Image Gallery button, you will see the screen shown below.

        ![](images/demo/demo_lvgl_homepanel_imagegallery.png){: width="40%"}

        For example, by clicking the Home Automation button, you will see the screen shown below.

        ![](images/demo/demo_lvgl_homepanel_homeautomation.png){: width="40%"}
    
    <br>

    *  ***Chromium Demo Applications***

    === "Chromium Home Panel Demo"

        This demo application is implemented using Chromium, and it presents an HTML5 single-page home panel interface.<br>
        Click the buttons or use the sidebar to explore the available functions.

        ![](images/demo/demo_chromium.png){: width="40%"}

        For example, by clicking the Video Player button, you will see the screen shown below.

        ![](images/demo/demo_chromium_videoplayer.png){: width="40%"}

        !!! success "Tip"
            Please refresh the browser before using the seek bar in the Video Player.        
        
        For example, by clicking the Home Automation button, you will see the screen shown below.

        ![](images/demo/demo_chromium_homepanel.png){: width="40%"}

        For RZ/G2L and RZ/G2LC, the live camera function is also available.The image below is captured using USB Camera.  
        Please switch the camera display mode using the control on top.

        ![](images/demo/demo_chromium_livecam.png){: width="40%"}
