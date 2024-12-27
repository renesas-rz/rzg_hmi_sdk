## Step 6: Build sample application

This step explains how to build HMI SDK sample application. <br>
To see the overview about HMI Applications, please refer to [HMI Applications](../index.md#hmi-applications).

!!! Note
    This step requires a Linux PC (Ubuntu).

    The prebuilt binary of executable files are also provided, and you can run them without building.

1.  Install cross compiler to you Linux PC (Ubuntu)

    !!! note
        This step is optional, as prebuilt binaries was prepared.

    === "RZ/G2L"

        ```bash
        sudo sh poky-glibc-x86_64-core-image-weston-aarch64-smarc-rzg2l-toolchain-3.1.31.sh
        ```
        { .dollar }

    === "RZ/G2LC"

        ```bash
        sudo sh poky-glibc-x86_64-core-image-weston-aarch64-smarc-rzg2lc-toolchain-3.1.31.sh
        ```
        { .dollar }

    === "RZ/G2UL"

        ```bash
        sudo sh poky-glibc-x86_64-core-image-bsp-aarch64-smarc-rzg2ul-toolchain-3.1.31.sh
        ```
        { .dollar }

    !!! Note
        Please set target directory (default: `#!bash /opt/poky/3.1.31`).

2.  Enable cross compiler

    !!! note
        This step is optional, as prebuilt binaries was prepared.

    ```bash
    source /opt/poky/3.1.31/environment-setup-aarch64-poky-linux
    ```
    { .dollar }

    !!! Note
        Please make sure where cross compiler is installed (default: `#!bash /opt/poky/3.1.31`).

3.  Clone sample application source code

    ```bash
    git clone https://github.com/renesas-rz/rzg_hmi_sdk
    ```
    { .dollar }

4.  Go to source code working directory

    ```bash
    cd rzg_hmi_sdk/sample_app/<sample-application-directory>
    ```
    { .dollar }

    !!! note
        Existing `#!bash <sample-application-directory>`(s) are listed on below table.

        | `#!bash <sample-application-directory>`     | Description                            |
        | ------------------------------------------- | -------------------------------------- |
        | `#!bash lvgl/lvgl_sample_img_disp`          | LVGL Sample Program for Image Display  |
        | `#!bash lvgl/lvgl_sample_audio_playback`    | LVGL Sample Program for Audio Playback |
        | `#!bash lvgl/lvgl_sample_video_playback`    | LVGL Sample Program for Video Playback |

5.  Build sample application

    !!! note
        This step is optional, as prebuilt binaries was prepared.

    ```bash
    make
    ```
    { .dollar }

6.  Executable file of sample application

    Each executable file of sample application built as `#!bash rzg_hmi_sdk/sample_app/<sample-application-directory>/<sample-application-binary>`.

    !!! note
        Executable file name (`#!bash <sample-application-binary>`) are same with the directory name.
        For example in case `#!bash lvgl_sample_img_disp`, path to executable file is:

        ```bash
        <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_img_disp/lvgl_sample_img_disp
        ```
        {: .dollar }

        In addition, prebuilt executable binaries are stored in 'bin' directory.
        For example in case `#!bash lvgl_sample_img_disp`, path to the prebuilt executable file is:

        ```bash
        <path-to>/rzg_hmi_sdk/sample_app/lvgl/lvgl_sample_img_disp/bin/lvgl_sample_img_disp
        ```
        {: .dollar }

