## Sample Applications

This section explains how to build, deploy, and run the HMI sample applications, as well as provides detailed introductions for each one.

We have prepared the following sample applications. <br>
Their source code can be downloaded from the GitHub links listed in the table below.

!!! content-wrapper no-indent table-no-sort table-no-hover ""

    +--------------+------------------------------------------+---------------------------+-------------------------------------------------------------------------------------------------------------------------------------+
    | Type         | Sample Applications                      | Target Device             | Source Code URL                                                                                                                     |
    +==============+==========================================+===========================+=====================================================================================================================================+
    |              |  LVGL Sample Program for Image Display   | RZ/G3E                    | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_sample_img_disp){: target=_blank }        |
    |              +------------------------------------------+---------------------------+-------------------------------------------------------------------------------------------------------------------------------------+
    | LVGL         |  LVGL Sample Program for Audio Playback  | RZ/G3E                    | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_sample_audio_playback){: target=_blank }  |
    |              +------------------------------------------+---------------------------+-------------------------------------------------------------------------------------------------------------------------------------+
    |              |  LVGL Sample Program for Video Playback  | RZ/G3E                    | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_sample_video_playback){: target=_blank }  |
    +--------------+------------------------------------------+---------------------------+-------------------------------------------------------------------------------------------------------------------------------------+

The executable binaries are also available in the `bin` directory of each sample application, so you can run the samples without building them yourself.
If you choose to use the binaries, simply download them, skip Step 1, and start from [Step 2: Deploy Sample Applications](../hmi_applications/#step-2-deploy-sample-applications).


### Step 1: Build Sample Applications

!!! success "Tip"
    This step requires a Linux PC (Ubuntu).

1. Install cross-compilation toolchain.

    *  When Using the **HMI SDK Package**
        
        If you download the HMI SDK Package and follow the [Getting Started](../getting_started/) setup instructions, you will find the toolchain installer script included in the package. Follow the steps below to install the toolchain for your board. <br>

        === "RZ/G3E"

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

            +------------+---------------------------------------------------------------------------------+--------------------------------------------------+
            |Target Board| Toolchain Installer Script                                                      | Location                                         |
            +============+=================================================================================+==================================================+
            | RZ/G3E     |*rz-vlp-glibc-x86_64-core-image-weston-cortexa55-smarc-rzg3e-toolchain-5.0.8.sh* |*toolchain-installer_rzg3e_hmi-sdk_v3.4.0.0.zip*  |
            +------------+---------------------------------------------------------------------------------+--------------------------------------------------+

            Unzip the package, and extract the installer.

            Navigate to the directory where the HMI SDK Package was extracted.

            ```bash
            cd RTK0EF0195F03400SJ_rzg3e/
            unzip toolchain-installer_rzg3e_hmi-sdk_v3.4.0.0.zip
            ```
            { .dollar }

            Then, install the toolchain.

            ```bash
            cd toolchain-installer_rzg3e_hmi-sdk_v3.4.0.0/
            sudo sh rz-vlp-glibc-x86_64-core-image-weston-cortexa55-smarc-rzg3e-toolchain-5.0.8.sh
            ```
            { .dollar }

        !!! success "Tip"
            Please set the directory for installing the toolchain.<br>

            The default `<path-to-toolchain>` is `#!bash /opt/rz-vlp/5.0.8`, which is used in the instructions below.<br>
            If you set the target directory manually, please remember to update the path accordingly in the next step.
        <br>

    *  When Using the **HMI SDK Yocto Build Package**

        If you download the HMI SDK Yocto Build Package, please ensure that you have completed <span style="color: var(--renesas-secondary-color-fg-blue-teal">*Step 2-10: Create the SDK toolchain*</span> in [Building the HMI SDK with Yocto](../building_the_hmi_sdk_with_yocto/#step-2-build-hmi-sdk-with-yocto). Then follow the steps below to install the toolchain for your board.

        !!! success "Tip"
            `#!bash ${WORK}` refers to the directory you set in <span style="color: var(--renesas-secondary-color-fg-blue-teal">*Step 2-3. Set environment variables*</span> in [Building the HMI SDK with Yocto](../building_the_hmi_sdk_with_yocto/#step-2-build-hmi-sdk-with-yocto).

        === "RZ/G3E"

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

            +------------+---------------------------------------------------------------------------------+--------------------------------------------------+
            |Target Board| Toolchain Installer Script                                                      | Location                                         |
            +============+=================================================================================+==================================================+
            | RZ/G3E     |*rz-vlp-glibc-x86_64-core-image-weston-cortexa55-smarc-rzg3e-toolchain-5.0.8.sh* | *${WORK}/build/tmp/deploy/sdk/*                  |
            +------------+---------------------------------------------------------------------------------+--------------------------------------------------+

            Install the toolchain.

            ```bash
            cd ${WORK}/build/tmp/deploy/sdk/
            sudo sh rz-vlp-glibc-x86_64-core-image-weston-cortexa55-smarc-rzg3e-toolchain-5.0.8.sh
            ```
            { .dollar }

        !!! success "Tip"
            Please set the directory for installing the toolchain.<br>

            The default `<path-to-toolchain>` is `#!bash /opt/rz-vlp/5.0.8`, which is used in the instructions below.<br>
            If you set the target directory manually, please remember to update the path accordingly in the next step.


2. Enable cross compiler.

    ```bash
    source <path-to-toolchain>/environment-setup-cortexa55-poky-linux 
    ```
    { .dollar }

    By default:

    ```bash
    source /opt/rz-vlp/5.0.8/environment-setup-cortexa55-poky-linux 
    ```
    { .dollar }

3. Get the sample application source code.

    Navigate to the directory where you want to store the source code.

    ```bash
    git clone https://github.com/renesas-rz/rzg_hmi_sdk
    ```
    { .dollar }

4.  Go to the source code working directory.

    ```bash
    cd <path-to>/rzg_hmi_sdk/sample_app/<sample-application-directory>
    ```
    { .dollar }

    !!! success "Tip"
        Existing `#!bash <sample-application-directory>`entries are listed in the table below.

        | `#!bash <sample-application-directory>`     | Description                                |
        | ------------------------------------------- | ------------------------------------------ |
        | `#!bash lvgl/lvgl_sample_img_disp`          | LVGL Sample Application for Image Display  |
        | `#!bash lvgl/lvgl_sample_audio_playback`    | LVGL Sample Application for Audio Playback |
        | `#!bash lvgl/lvgl_sample_video_playback`    | LVGL Sample Application for Video Playback |

5.  Build sample applications.

    ```bash
    MACHINE=smarc-rzg3e make
    ```
    { .dollar }
    
    The executable binaries for the sample applications are built as follows:<br>
    `#!bash rzg_hmi_sdk/sample_app/<sample-application-directory>/<sample-application-binary>`.

    !!! success "Tip"
        The executable binaries file name (`#!bash <sample-application-binary>`) is the same as its directory name.

        For example, for `#!bash lvgl_sample_img_disp`, the path to the built executable is:
        ```bash
        <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_img_disp/lvgl_sample_img_disp
        ```
        {: .dollar }


### Step 2: Deploy Sample Applications

!!! success "Tip"
    *  This step requires a Linux PC (Ubuntu).<br>
    *  For operations that require entering commands on the EVK board, you can use the on-screen terminal at the top-left corner of the display, or connect remotely using an terminal emulator such as [Tera Term](https://github.com/TeraTermProject/teraterm/releases).

#### Option 1. Over Ethernet (using `SCP`)

1.  Connect the EVK board to your Linux PC and boot it.

    Connect an Ethernet cable between the EVK’s port and your Linux PC.

    !!! note
        Refer to [EVK Peripheral Setup](../hmi_applications/#evk-peripheral-setup) for details.

    === "RZ/G3E"
        Ethernet 0 and Ethernet 1 are available; either port can be used.

    Press and hold the power button (red button) for 1 second to turn on the EVK board.  
<br>
    
2.  Check your EVK board’s IP address.
    
    Run the `#!bash ip` command on your EVK board as follows.

    ```bash
    ip a
    ```
    {: .hash }

    !!! success "Tip"
        For example, if the RZ/G3E board is connected to the local network through the Ethernet 0 port:

        ```console
        root@smarc-rzg3e:~# ip a | grep end
        5: end0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq state UP group default qlen 1000
            inet 192.168.20.99/24 brd 192.168.20.255 scope global end0
        6: end1: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc mq state DOWN group default qlen 1000
        ```

        RZ/G3E board's IP address is `#!console 192.168.20.99` (at `#!console end0`).

3.  Copy the executable binary files and resource files to your EVK board (external SD card storage).

    Copy the executable binary files from your Linux PC (Ubuntu) using `#!bash scp` command.

    === "LVGL Sample Application for Image Display"

        ```bash
        scp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_img_disp/lvgl_sample_img_disp root@<your-EVK-IP>:/home/root/
        ```
        {: .dollar }

    === "LVGL Sample Application for Audio Playback"

        ```bash
        scp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_audio_playback/lvgl_sample_audio_playback root@<your-EVK-IP>:/home/root/
        ```
        {: .dollar }

    === "LVGL Sample Application for Video Playback"

        ```bash
        scp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_video_playback/lvgl_sample_video_playback root@<your-EVK-IP>:/home/root/
        ```
        {: .dollar }

    !!! success "Tip"
        *  We recommend copying the file to the `#!bash /home/root` directory.<br>
        *  Don’t forget to replace `#!bash <your-EVK-IP>` with your EVK's IP address.

    <br>
    Copy resource files from your Linux PC (Ubuntu) using `#!bash scp` command.

    === "LVGL Sample Application for Image Display"

        !!! warning "Notice"
            Please make sure the `#!bash /usr/share/images/` exists on your EVK before using scp.<br>
            If it does not exist, create it using the following command:
            ```bash
            mkdir -p /usr/share/images/
            ```
            {: .hash }    

        ```bash
        scp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_img_disp/sample/* root@<your-EVK-IP>:/usr/share/images/
        ```
        {: .dollar }
        

    === "LVGL Sample Application for Audio Playback"

        !!! warning "Notice"
            Please make sure the `#!bash /usr/share/sounds/sample/` exists on your EVK board before using scp.<br>
            If it does not exist, create it using the following command:
            ```bash
            mkdir -p /usr/share/sounds/sample/
            ```
            {: .hash }

        ```bash
        scp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_audio_playback/sample/* root@<your-EVK-IP>:/usr/share/sounds/sample/
        ```
        {: .dollar }


    === "LVGL Sample Application for Video Playback"

        !!! warning "Notice"
            Please make sure the `#!bash /usr/share/movies/` exists on your EVK board before using scp.<br>
            If it does not exist, create it using the following command:
            ```bash
            mkdir -p /usr/share/movies/
            ```
            {: .hash }

        ```bash
        scp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_video_playback/sample/* root@<your-EVK-IP>:/usr/share/movies/
        ```
        {: .dollar }

    !!! success "Tip"
        Don’t forget to replace `#!bash <your-EVK-IP>` with your EVK's IP address.


        

#### Option 2. Over SD Card

1.  Insert your SD card into the Linux PC and mount it.

    !!! warning "Notice"
        Make sure to turn off your EVK board before ejecting the SD card.<BR>
        Press and hold the power button for 2 seconds to turn it off.

2.  Copy the executable binary files and resource files to your SD card.
    
    !!!success "Tip"
        Follow the instructions in [Step 4 in Option 2](../getting_started/#option-2-for-linux-pc-ubuntu) to check where your SD card is mounted using the `#!bash lsblk` command.

    For example, if the SD card is mounted at `#!bash /media/user/rootfs`.

    Copy the executable binary files.

    === "LVGL Sample Application for Image Display"

        ```bash
        cp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_img_disp/lvgl_sample_img_disp /media/user/rootfs/home/root/
        ```
        {: .dollar }

    === "LVGL Sample Application for Audio Playback"

        ```bash
        cp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_audio_playback/lvgl_sample_audio_playback /media/user/rootfs/home/root/
        ```
        {: .dollar }

    === "LVGL Sample Application for Video Playback"

        ```bash
        cp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_video_playback/lvgl_sample_video_playback /media/user/rootfs/home/root/
        ```
        {: .dollar }

    !!! success "Tip"
        We recommend copying the file to the `#!bash /home/root` directory.

    <br>
    Copy resource files.

    === "LVGL Sample Application for Image Display"

        !!! warning "Notice"
            Please make sure the `#!bash /usr/share/images/` exists on your SD card before copying.<br>
            If it does not exist, create it using the following command:
            ```bash
            mkdir -p /media/user/rootfs/usr/share/images/
            ```
            {: .dollar }    

        ```bash
        cp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_img_disp/sample/* /media/user/rootfs/usr/share/images/
        ```
        {: .dollar }


    === "LVGL Sample Application for Audio Playback"

        !!! warning "Notice"
            Please make sure the `#!bash /usr/share/sounds/sample/` exists on your SD card before using scp.<br>
            If it does not exist, create it using the following command:
            ```bash
            mkdir -p /media/user/rootfs/usr/share/sounds/sample/
            ```
            {: .dollar }

        ```bash
        cp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_audio_playback/sample/* /media/user/rootfs/usr/share/sounds/sample/
        ```
        {: .dollar }


    === "LVGL Sample Application for Video Playback"

        !!! warning "Notice"
            Please make sure the `#!bash /usr/share/movies/` exists on your SD card before using scp.<br>
            If it does not exist, create it using the following command:
            ```bash
            mkdir -p /media/user/rootfs/usr/share/movies/
            ```
            {: .dollar }

        ```bash
        cp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_video_playback/sample/* /media/user/rootfs/usr/share/movies/
        ```
        {: .dollar }

### Step 3: Run the HMI Sample Applications

1.  Prepare the necessary equipment and configure the EVK DIP switches by following the instructions in [Hardware Setup](../hmi_applications/#hardware-setup).

2.  Insert the bootable microSD card created in [Step 2](../hmi_applications/#step-2-deploy-sample-applications) into the microSD card slot, and then power on the EVK board.

    !!! success "Tip"
        *  Please refer to the [EVK Peripheral Setup](../hmi_applications/#evk-peripheral-setup) to locate the microSD card slot based on your selected boot mode.
        *  Press and hold the power button (red button, SW9) for 1 second to turn on the EVK board, and for 2 seconds to turn it off.

3.  Set execute permission and run the sample applications on your EVK board.  
    <br>

    *  ***LVGL Sample Applications***

    === "LVGL Sample Application for Image Display"

        Grant execute permission to the binary files.

        ```bash
        cd /home/root
        ```
        {: .hash }

        ```bash
        chmod +x lvgl_sample_img_disp
        ```
        {: .hash }
        
        Run the executable binary files.

        ```bash
        ./lvgl_sample_img_disp
        ```
        {: .hash }

        The launched sample application is shown below.<br>
        This sample application is implemented using LVGL and can display image files in BMP, JPG, PNG, and GIF formats.

        ![](images/sample/sample_img_disp_1.png){: width="40%"} 

        Click the button to display the image from the source file.

        ![](images/sample/sample_img_disp_2.png){: width="40%"} 

        To exit, simply close the window or press Ctrl+C in the EVK board terminal.


    === "LVGL Sample Application for Audio Playback"

        Grant execute permission to the binary files.

        ```bash
        cd /home/root
        ```
        {: .hash }

        ```bash
        chmod +x lvgl_sample_audio_playback
        ```
        {: .hash }

        Run the executable binary files.

        ```bash
        ./lvgl_sample_audio_playback
        ```
        {: .hash }

        The launched sample application is shown below.<br>
        This sample application is implemented using LVGL and can play audio files in mp3, AAC, and WAV formats.

        ![](images/sample/sample_audio_playback.png){: width="40%"}

        Click the button to start, stop, or pause the audio from the source file.

        To exit, simply close the window or press Ctrl+C in the EVK board terminal.


    === "LVGL Sample Application for Video Playback"

        Grant execute permission to the binary files.

        ```bash
        cd /home/root
        ```
        {: .hash }

        ```bash
        chmod +x lvgl_sample_video_playback
        ```
        {: .hash }

        Run the executable binary files.

        ```bash
        ./lvgl_sample_video_playback -i /usr/share/movies/sample_video_with_audio.mp4
        ```
        {: .hash }

        The launched sample application is shown below.<br>
        This sample application is implemented using LVGL, and it can play movie files in MP4 format.

        ![](images/sample/sample_video_playback_1.png){: width="40%"} 

        Click the button to start, stop, or pause the video from the source file.

        ![](images/sample/sample_video_playback_2.png){: width="40%"} 

        To exit, simply close the window or press Ctrl+C in the EVK board terminal.



