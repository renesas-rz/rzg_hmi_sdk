## Demo Applications

This section explains how to run the HMI demo applications and provides detailed introductions for each one.

The HMI SDK Demo Launcher starts automatically when the EVK boots. Currently, it includes the following prebuilt demo applications.
If you want to customize them, their source code can be downloaded from the GitHub links listed in the table below.


!!! content-wrapper no-indent table-no-sort table-no-hover ""

    +--------------+----------------------------+---------------------------------------+-------------------------------------------------------------------------------------------------------------------------------+
    | Type         | Demo Applications          | Target Device                         | Source Code URL                                                                                                               |
    +==============+============================+=======================================+===============================================================================================================================+      
    | LVGL         | LVGL Home Panel Demo       | RZ/G3L                                | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_home_panel_demo){: target=_blank }  |
    +--------------+----------------------------+---------------------------------------+-------------------------------------------------------------------------------------------------------------------------------+
    | Chromium     | Chromium Home Panel Demo   | RZ/G3L                                | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/chromium/home_panel_demo){: target=_blank }   |
    +--------------+----------------------------+---------------------------------------+-------------------------------------------------------------------------------------------------------------------------------+
    | Flutter      | Flutter Samples            | RZ/G3L                                | [Link to GitHub](https://github.com/flutter/samples){: target=_blank }                                                        |
    +--------------+----------------------------+---------------------------------------+-------------------------------------------------------------------------------------------------------------------------------+

Please follow the steps below to run the demo applications.

1.  Prepare the necessary equipment and configure the EVK DIP switches by following the instructions in [Hardware Setup](../hmi_applications/#hardware-setup).

2.  Insert the bootable microSD card into the microSD card slot for eSD boot mode, and then power on the EVK board.

    !!! success "Tip"
        *  Please refer to the [EVK Peripheral Setup](../hmi_applications/#evk-peripheral-setup) for the location of the microSD card slot.
        *  Press and hold the power button (red button) for 1 second to turn on the EVK board.

3.  The HMI SDK Demo Launcher launches **automatically** once the device is fully booted.

    Right after boot, you will see the launch window as shown below.

    ![](images/demo/demo_launching.png){: width="40%"} 

    After a few seconds, the HMI SDK Demo Launcher will appear.

    Click the corresponding button to try each demo application we provide.

    ![](images/demo/demo_launcher.png){: width="40%"}

    !!! success "Tip"
        If you want to exit a demo application and return to the HMI SDK Demo Launcher, you can either<br> 
        *  restart your EVK board by press reset button (blue button) or   
        *  run the following command in your board terminal to relaunch it: 
        ```bash 
        demo-launcher
        ```
        {: .hash }
        
        Note that the Demo Launcher does not support maximizing/minimizing window.


    <br>


    You can then try the following types of demo applications:  
    - [LVGL](#lvgl-demo-applications)  
    - [Chromium](#chromium-demo-applications)  
    - [Flutter](#flutter-demo-applications)  
 <br>

    #### LVGL Demo Applications
    ![](images/demo/demo_launcher_lvgl.png){: width="40%"}  

    
    === "LVGL Home Panel Demo"

        This demo application is implemented using LVGL.<br> 
        Click the buttons or use the sidebar to explore the available functions.

        ![](images/demo/demo_lvgl_homepanel.png){: width="40%"} 

        For example, by clicking the Image Gallery button, you will see the screen shown below.

        ![](images/demo/demo_lvgl_homepanel_imagegallery.png){: width="40%"}

        For example, by clicking the Home Automation button, you will see the screen shown below.

        ![](images/demo/demo_lvgl_homepanel_homeautomation.png){: width="40%"}
    
    <br>

    #### Chromium Demo Applications
    ![](images/demo/demo_launcher_chromium.png){: width="40%"}  

    === "Chromium Home Panel Demo"

        This demo application is implemented using Chromium, and it presents an HTML5 single-page home panel interface.

        Click the buttons or use the sidebar to explore the available functions.

        ![](images/demo/demo_chromium.png){: width="40%"}

        For example, by clicking the Video Player button, you will see the screen shown below.

        ![](images/demo/demo_chromium_videoplayer.png){: width="40%"}

        For example, by clicking the Home Automation button, you will see the screen shown below.

        ![](images/demo/demo_chromium_homepanel.png){: width="40%"}

        The live camera function is also available. The image below is captured using USB Camera.
        Please switch the camera display mode using the control on top.

        ![](images/demo/demo_chromium_livecam.png){: width="40%"}

    <br>  


    #### Flutter Demo Applications
    ![](images/demo/demo_launcher_flutter.png){: width="40%"}    

    === "Flutter Samples"

        You can try three types of Flutter sample applications to see what features are provided.
        These samples are open-source software distributed on [GitHub](https://github.com/flutter/samples).

        ***Material 3 Demo***

        ![](images/demo/demo_flutter_material3.png){: width="40%"}

        ***Animation Demo***

        ![](images/demo/demo_flutter_animation.png){: width="40%"}

        ***Shopping Demo***

        ![](images/demo/demo_flutter_shopping.png){: width="40%"}

!!! success "Tip"
    To power off the board, execute the `shutdown -h now` command in the terminal. Once the screen turns black, press and hold the power button (red button) for approximately 2 seconds to complete the shutdown process.