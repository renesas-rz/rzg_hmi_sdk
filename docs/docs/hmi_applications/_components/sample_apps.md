## Sample Applications

This section explains how to build, deploy, and run the HMI sample applications, as well as provides detailed introductions for each one.

We have prepared the following sample applications. <br>
Their source code can be downloaded from the GitHub links listed in the table below.

!!! content-wrapper no-indent table-no-sort table-no-hover ""

    +--------------+------------------------------------------+---------------------------+-------------------------------------------------------------------------------------------------------------------------------------+
    | Type         | Sample Applications                      | Target Device             | Source Code URL                                                                                                                     |
    +==============+==========================================+===========================+=====================================================================================================================================+
    |              |  LVGL Sample Program for Image Display   | RZ/G2L, RZ/G2LC, RZ/G2UL  | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_sample_img_disp){: target=_blank }        |
    |              +------------------------------------------+---------------------------+-------------------------------------------------------------------------------------------------------------------------------------+
    | LVGL         |  LVGL Sample Program for Audio Playback  | RZ/G2L, RZ/G2LC           | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_sample_audio_playback){: target=_blank }  |
    |              +------------------------------------------+---------------------------+-------------------------------------------------------------------------------------------------------------------------------------+
    |              |  LVGL Sample Program for Video Playback  | RZ/G2L                    | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_sample_video_playback){: target=_blank }  |
    +--------------+------------------------------------------+---------------------------+-------------------------------------------------------------------------------------------------------------------------------------+

The executable binaries are also available in the `bin` directory of each sample application, so you can run the samples without building them yourself.
If you choose to use the binaries, simply download them, skip Step 1, and start from [Step 2: Deploy Sample Applications](../hmi_applications/#step-2-deploy-sample-applications).


### Step 1: Build Sample Applications

!!! success "Tip"
    This step requires a Linux PC (Ubuntu).

1. Install cross-compilation toolchain.

    *  When Using the **HMI SDK Package**
        
        If you download the HMI SDK Package and follow the [Getting Started](../getting_started/) setup instructions, you will find the toolchain installer script included in the package. Follow the steps below to install the toolchain for your board. <br>

        === "RZ/G2L"

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

            +------------+------------------------------------------------------------------------------+--------------------------------------------------+
            |Target Board|Toolchain Installer Script                                                    |Location                                          |
            +============+==============================================================================+==================================================+
            | RZ/G2L     |*poky-glibc-x86_64-core-image-weston-aarch64-smarc-rzg2l-toolchain-3.1.33.sh* |*toolchain-installer_rzg2l_hmi-sdk_v2.3.1.0.zip*  |
            +------------+------------------------------------------------------------------------------+--------------------------------------------------+

            Unzip the package, and extract the installer.

            Navigate to the directory where the HMI SDK Package was extracted.

            ```bash
            cd RTK0EF0195F02310SJ_rzg2l/
            unzip toolchain-installer_rzg2l_hmi-sdk_v2.3.1.0.zip
            ```
            { .dollar }

            Then, install the toolchain.

            ```bash
            cd toolchain-installer_rzg2l_hmi-sdk_v2.3.1.0/
            sudo sh poky-glibc-x86_64-core-image-weston-aarch64-smarc-rzg2l-toolchain-3.1.33.sh
            ```
            { .dollar }

        === "RZ/G2LC"

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

            +------------+-------------------------------------------------------------------------------+--------------------------------------------------+
            |Target Board|Toolchain Installer Script                                                     |Location                                          |
            +============+===============================================================================+==================================================+
            | RZ/G2LC    |*poky-glibc-x86_64-core-image-weston-aarch64-smarc-rzg2lc-toolchain-3.1.33.sh* |*toolchain-installer_rzg2lc_hmi-sdk_v2.3.1.0.zip* |
            +------------+-------------------------------------------------------------------------------+--------------------------------------------------+

            
            Unzip the package, and extract the installer.

            Navigate to the directory where the HMI SDK Package was extracted.

            ```bash
            cd RTK0EF0195F02310SJ_rzg2lc/
            unzip toolchain-installer_rzg2lc_hmi-sdk_v2.3.1.0.zip
            ```
            { .dollar }

            Then, install the toolchain.

            ```bash
            cd toolchain-installer_rzg2lc_hmi-sdk_v2.3.1.0/
            sudo sh poky-glibc-x86_64-core-image-weston-aarch64-smarc-rzg2lc-toolchain-3.1.33.sh
            ```
            { .dollar }

        === "RZ/G2UL"

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

            +------------+-------------------------------------------------------------------------------+--------------------------------------------------+
            |Target Board|Toolchain Installer Script                                                     |Location                                          |
            +============+===============================================================================+==================================================+
            | RZ/G2UL    |*poky-glibc-x86_64-core-image-bsp-aarch64-smarc-rzg2ul-toolchain-3.1.33.sh*    |*toolchain-installer_rzg2ul_hmi-sdk_v2.3.1.0.zip* |
            +------------+-------------------------------------------------------------------------------+--------------------------------------------------+

            Unzip the package, and extract the installer.

            Navigate to the directory where the HMI SDK Package was extracted.

            ```bash
            cd RTK0EF0195F02310SJ_rzg2ul/
            unzip toolchain-installer_rzg2ul_hmi-sdk_v2.3.1.0.zip
            ```
            { .dollar }

            Then, install the toolchain as follows:

            ```bash
            cd toolchain-installer_rzg2ul_hmi-sdk_v2.3.1.0/
            sudo sh poky-glibc-x86_64-core-image-bsp-aarch64-smarc-rzg2ul-toolchain-3.1.33.sh
            ```
            { .dollar }

        !!! success "Tip"
            Please set the directory for installing the toolchain.<br>

            The default `<path-to-toolchain>` is `#!bash /opt/poky/3.1.33`, which is used in the instructions below.<br>
            If you set the target directory manually, please remember to update the path accordingly in the next step.
        <br>

    *  When Using the **HMI SDK Yocto Build Package**

        If you download the HMI SDK Yocto Build Package, please ensure that you have completed <span style="color: var(--renesas-primary-color-fg-blue">*Step 2-10: Create the SDK toolchain*</span> in [Building the HMI SDK with Yocto](../building_the_hmi_sdk_with_yocto/#step-2-build-hmi-sdk-with-yocto). Then follow the steps below to install the toolchain for your board.

        !!! success "Tip"
            `#!bash ${WORK}` refers to the directory you set in <span style="color: var(--renesas-primary-color-fg-blue">*Step 2-3. Set environment variables*</span> in [Building the HMI SDK with Yocto](../building_the_hmi_sdk_with_yocto/#step-2-build-hmi-sdk-with-yocto).

        === "RZ/G2L"

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

            +------------+------------------------------------------------------------------------------+--------------------------------------------------+
            |Target Board|Toolchain Installer Script                                                    |Location                                          |
            +============+==============================================================================+==================================================+
            | RZ/G2L     |*poky-glibc-x86_64-core-image-weston-aarch64-smarc-rzg2l-toolchain-3.1.33.sh* |*${WORK}/build/tmp/deploy/sdk/*                   |
            +------------+------------------------------------------------------------------------------+--------------------------------------------------+

            Install the toolchain.

            ```bash
            cd ${WORK}/build/tmp/deploy/sdk/
            sudo sh poky-glibc-x86_64-core-image-weston-aarch64-smarc-rzg2l-toolchain-3.1.33.sh
            ```
            { .dollar }

        === "RZ/G2LC"

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

            +------------+-------------------------------------------------------------------------------+--------------------------------------------------+
            |Target Board|Toolchain Installer Script                                                     |Location                                          |
            +============+===============================================================================+==================================================+
            | RZ/G2LC    |*poky-glibc-x86_64-core-image-weston-aarch64-smarc-rzg2lc-toolchain-3.1.33.sh* |*${WORK}/build/tmp/deploy/sdk/*                   |
            +------------+-------------------------------------------------------------------------------+--------------------------------------------------+

            Install the toolchain.

            ```bash
            cd ${WORK}/build/tmp/deploy/sdk/
            sudo sh poky-glibc-x86_64-core-image-weston-aarch64-smarc-rzg2lc-toolchain-3.1.33.sh
            ```
            { .dollar }

        === "RZ/G2UL"

            !!! content-wrapper no-indent table-no-sort table-no-hover ""

            +------------+-------------------------------------------------------------------------------+--------------------------------------------------+
            |Target Board|Toolchain Installer Script                                                     |Location                                          |
            +============+===============================================================================+==================================================+
            | RZ/G2UL    |*poky-glibc-x86_64-core-image-bsp-aarch64-smarc-rzg2ul-toolchain-3.1.33.sh*    |*${WORK}/build/tmp/deploy/sdk/*                   |
            +------------+-------------------------------------------------------------------------------+--------------------------------------------------+
            
            Install the toolchain.

            ```bash
            cd ${WORK}/build/tmp/deploy/sdk/
            sudo sh poky-glibc-x86_64-core-image-bsp-aarch64-smarc-rzg2ul-toolchain-3.1.33.sh
            ```
            { .dollar }

        !!! success "Tip"
            Please set the directory for installing the toolchain.<br>

            The default `<path-to-toolchain>` is `#!bash /opt/poky/3.1.33`, which is used in the instructions below.<br>
            If you set the target directory manually, please remember to update the path accordingly in the next step.


2. Enable cross compiler.

    ```bash
    source <path-to-toolchain>/environment-setup-aarch64-poky-linux
    ```
    { .dollar }

    By default:

    ```bash
    source /opt/poky/3.1.33/environment-setup-aarch64-poky-linux
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
    make
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

    Connect an Ethernet cable between the EVK’s *RJ45 port* and your Linux PC.

    !!! note
        Refer to [EVK Peripheral Setup](../hmi_applications/#evk-peripheral-setup) for details.

    === "RZ/G2L"
        *RJ45 ports* Ethernet 0 (CN9) and Ethernet 1 (CN8) are available; either port can be used.

    === "RZ/G2LC"
        RJ45 ports is Ethernet 0 (CN9).


    === "RZ/G2UL"
        *RJ45 ports* Ethernet 0 (CN9) and Ethernet 1 (CN8) are available; either port can be used.

    Press and hold the power button (red button, SW9) for 1 second to turn on the EVK board.  
<br>
    
2.  Check your EVK board’s IP address.
    
    Run the `#!bash ip` command on your EVK board as follows.

    ```bash
    ip a
    ```
    {: .hash }

    !!! success "Tip"
        For example, if the RZ/G2L board is connected to the local network through the CN8 Ethernet port:

        ```console
        root@smarc-rzg2l:~# ip a | grep eth
        5: eth0: <NO-CARRIER,BROADCAST,MULTICAST,DYNAMIC,UP> mtu 1500 qdisc mq state DOWN group default qlen 1000
            link/ether f2:d6:18:24:f0:6b brd ff:ff:ff:ff:ff:ff
        6: eth1: <BROADCAST,MULTICAST,DYNAMIC,UP,LOWER_UP> mtu 1500 qdisc mq state UP group default qlen 1000
            link/ether 72:26:f0:8b:64:59 brd ff:ff:ff:ff:ff:ff
            inet 192.168.0.32/24 brd 192.168.0.255 scope global dynamic eth1
        ```

        RZ/G2L board's IP address is `#!console 192.168.0.32` (at `#!console eth1`).

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
            mkdir /usr/share/images/
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
            mkdir /usr/share/sounds/sample/
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
            mkdir /usr/share/movies/
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
            mkdir /media/user/rootfs/usr/share/images/
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
            mkdir /media/user/rootfs/usr/share/sounds/sample/
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
            mkdir /media/user/rootfs/usr/share/movies/
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
        ./lvgl_sample_video_playback
        ```
        {: .hash }

        The launched sample application is shown below.<br>
        This sample application is implemented using LVGL, and it can play movie files in MP4 format.

        ![](images/sample/sample_video_playback_1.png){: width="40%"} 

        Click the button to start, stop, or pause the video from the source file.

        ![](images/sample/sample_video_playback_2.png){: width="40%"} 

        To exit, simply close the window or press Ctrl+C in the EVK board terminal.



