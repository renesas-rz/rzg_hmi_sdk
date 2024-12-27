## Step 7: Deploy sample application

!!! Note
    This step requires a Linux PC (Ubuntu).

### 1. Over ethernet (using `SCP`)

1.  Boot and connect your EVK into your local network

    Connect an ethernet cable to RJ45 port for networking.

    === "RZ/G2L"
        RJ45 ports are CN9 (Ethernet 0) and CN8 (Ethernet 1).

        !!! note
            Just connect 1 ethernet cable to CN9 or CN8.

    === "RZ/G2LC"
        RJ45 ports is CN9 (Ethernet 0).

        !!! note
            Just connect a ethernet cable to CN9.

    === "RZ/G2UL"
        RJ45 ports are CN9 (Ethernet 0) and CN8 (Ethernet 1).

        !!! note
            Just connect 1 ethernet cable to CN9 or CN8.

    !!! note
        Your EVK will run the demo program automatically.

        Please exit the demo by pressing the keyboard keys ++ctrl+c++,
        before proceeding to the next step.

2.  Check your EVK's IP

    Open terminal of your EVK, and check using `#!bash ip` command as below.

    ```bash
    ip a
    ```
    {: .hash }

    !!! note
        For example, when RZ/G2L EVK's CN8 ethernet port connected to local network.

        ```console
        root@smarc-rzg2l:~# ip a | grep eth
        5: eth0: <NO-CARRIER,BROADCAST,MULTICAST,DYNAMIC,UP> mtu 1500 qdisc mq state DOWN group default qlen 1000
            link/ether f2:d6:18:24:f0:6b brd ff:ff:ff:ff:ff:ff
        6: eth1: <BROADCAST,MULTICAST,DYNAMIC,UP,LOWER_UP> mtu 1500 qdisc mq state UP group default qlen 1000
            link/ether 72:26:f0:8b:64:59 brd ff:ff:ff:ff:ff:ff
            inet 192.168.0.32/24 brd 192.168.0.255 scope global dynamic eth1
        ```

        EVK's IP is `#!console 192.168.0.32` (at `#!console eth1`).

3.  Copy executable into your EVK storage (SD card)

    Send executable file from your Linux PC (Ubuntu) using `#!bash scp` command as below.

    ```bash
    scp <path-to>/rzg_hmi_sdk/sample_app/<sample-application-directory>/<sample-application-binary> root@<your-EVK-IP>:/home/root/
    ```
    {: .dollar }

    !!! note
        We recommend you to copy to `#!bash /home/root` directory.

        Don't forget to replace `#!bash <your-EVK-IP>` with your EVK's IP.

4.  Copy resources required by sample application

    === "`#!bash lvgl_sample_img_disp`"

        ```bash
        scp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_img_disp/sample/* root@<your-EVK-IP>:/usr/share/images/
        ```
        {: .dollar }

        !!! danger "Caution"
            Make sure you are copying to `#!bash /usr/share/images/` directory of EVK.

    === "`#!bash lvgl_sample_audio_playback`"

        ```bash
        scp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_audio_playback/sample/* root@<your-EVK-IP>:/usr/share/sounds/sample/
        ```
        {: .dollar }

        !!! danger "Caution"
            Make sure you are copying to `#!bash /usr/share/sounds/sample/` directory of EVK.

    === "`#!bash lvgl_sample_video_playback`"

        ```bash
        scp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_video_playback/sample/* root@<your-EVK-IP>:/usr/share/movies/
        ```
        {: .dollar }

        !!! danger "Caution"
            Make sure you are copying to `#!bash /usr/share/movies/` directory of EVK.

### 2. Directly write into HMI SDK's SD card

1.  Turn off your EVK (if its on)
2.  Insert and mount your SD card into PC
3.  Copy executable into your SD card

    For example, in case mounted on `#!bash /media/user/rootfs`.

    ```bash
    cp <path-to>/rzg_hmi_sdk/sample_app/<sample-application-directory>/<sample-application-binary> /media/user/rootfs/home/root/
    ```
    {: .dollar }

    !!! note
        We recommend you to copy to `#!bash /home/root` directory.

        If you not sure where is your SD card mounted,
        please check it using `#!bash lsblk` command
        (see [Step 4.2](#2-in-case-of-linux-pc-ubuntu).3).

4.  Copy resources required by sample application

    For example, in case mounted on `#!bash /media/user/rootfs`.

    === "`#!bash lvgl_sample_img_disp`"

        ```bash
        cp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_img_disp/sample/* /media/user/rootfs/usr/share/images/
        ```
        {: .dollar }

        !!! danger "Caution"
            Make sure you are copying to `#!bash /usr/share/images/` directory on SD card.

    === "`#!bash lvgl_sample_audio_playback`"

        ```bash
        cp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_audio_playback/sample/* /media/user/rootfs/usr/share/sounds/sample/
        ```
        {: .dollar }

        !!! danger "Caution"
            Make sure you are copying to `#!bash /usr/share/sounds/sample/` directory on SD card.

    === "`#!bash lvgl_sample_video_playback`"

        ```bash
        cp <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_video_playback/sample/* /media/user/rootfs/usr/share/movies/
        ```
        {: .dollar }

        !!! danger "Caution"
            Make sure you are copying to `#!bash /usr/share/movies/` directory on SD card.
