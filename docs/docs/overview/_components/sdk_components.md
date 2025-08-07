## SDK Components

HMI SDK provides the following packages:

* eSD boot image and toolchain installer package

    This package is the heart of HMI SDK.
    You can create a bootable microSD card, set up Linux environment on the EVK, and build sample applications.

* Yocto recipe and pre-built binary image package

    This is an optional package.
    If you would like to build the HMI SDK from scratch, or you would like to try QSPI boot or eMMC boot (other than eSD boot mode), get this package.

* Source code package

    When you build the HMI SDK from scratch, you can use source code in this package for offline building.

Except for the source code package, the packages are available for each EVK.

### File Contents

The contents of the packages are as follows:

!!! content-wrapper no-indent table-no-sort table-no-hover ""

    +---------------------------------------------------------+---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    | Package                                                 | File Name                                         | Details                                                                                                             |
    +=========================================================+===================================================+=====================================================================================================================+
    | eSD boot image and                                      | image-file_<*dev*\>_hmi-sdk_v2.3.1.0.zip          | Bootable SD card images in WIC format                                                                               |
    | toolchain installer package                             +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    | (RTK0EF0195F02310SJ_<*dev*\>)                           | licenses_rzg2_hmi-sdk_v2.3.1.0.zip                | License files for open-source software used in HMI SDK                                                              |
    |                                                         +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                         | r01an7976ej0100-rzg-hmi-sdk.pdf                   | Release note that contains RZ/G HMI SDK release information                                                         |
    |                                                         +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                         | README.txt                                        | README that contains information about the package                                                                  |
    |                                                         +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                         | toolchain-installer_<*dev*\>_hmi-sdk_v2.3.1.0.zip | Installer for pre-built cross-toolchain used for building sample applications                                       |
    +---------------------------------------------------------+---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    | Yocto recipe and                                        | licenses_rzg2_hmi-sdk_v2.3.1.0.zip                | License files for open-source software used in HMI SDK                                                              |
    | pre-built binary image package                          +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    | (RTK0EF0195F02310SJ_<*dev*\>_yocto-and-pre-built-image) | pre-built-binary_<*dev*\>_hmi-sdk_v2.3.1.0.zip    | Pre-built binaries (boot loader, Linux kernel image and root filesystem, flash writer) for SPI boot mode (option)   |
    |                                                         +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                         | r01an7976ej0100-rzg-hmi-sdk.pdf                   | Release note that contains RZ/G HMI SDK release information                                                         |
    |                                                         +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                         | README.txt                                        | README that contains information about the package                                                                  |
    |                                                         +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                         | yocto_recipe_rzg2_hmi-sdk_v2.3.1.0.tar.gz         | Yocto meta layers used for building HMI SDK                                                                         |
    +---------------------------------------------------------+---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    | Source code package                                     | licenses_rzg2_hmi-sdk_v2.3.1.0.zip                | License files for open-source software used in HMI SDK                                                              |
    | (RTK0EF0195F02310SJ_linux-src)                          +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                         | oss-souce-code-pkg_rzg2_hmi-sdk_v2.3.1.0.7z       | Source code package of open-source software used for building HMI SDK                                               |
    |                                                         +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                         | r01an7976ej0100-rzg-hmi-sdk.pdf                   | Release note that contains RZ/G HMI SDK release information                                                         |
    |                                                         +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                         | README.txt                                        | README that contains information about the package                                                                  |
    +---------------------------------------------------------+---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+

    <*dev*\> in the above table stands for a device name, such as rzg2l, rzg2lc, or rzg2ul.

### HMI Applications

HMI SDK provides HMI demos and sample applications. <br>
These are available as both source code and prebuilt binaries, allowing you to run them on the board immediately and customize them as needed.

!!! content-wrapper center ""

    | Sample Application Name                                                        | Description                                                                                                                             | Pre-installed <br>in SD Card Image | Target Device            | Source Code URL   |
    | ------------------------------------------------------------------------------ | --------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------- | ------------------------ | ----------------- |
    | **LVGL** Sample Program for **Image Display**<br> `#!bash lvgl_sample_img_disp` | This program is implemented using [LVGL](https://lvgl.io/){: target=_blank }, and it can display image files in bmp/jpg/png/gif format. | No                                | RZ/G2L, RZ/G2LC, RZ/G2UL | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_sample_img_disp){: target=_blank } |
    | **LVGL** Sample Program for **Audio Playback**<br> `#!bash lvgl_sample_audio_playback` | This program is implemented using [LVGL](https://lvgl.io/){: target=_blank }, and it can play audio files in mp3/aac/wav format. | No                                | RZ/G2L, RZ/G2LC          | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_sample_audio_playback){: target=_blank } |
    | **LVGL** Sample Program for **Video Playback**<br> `#!bash lvgl_sample_video_playback` | This program is implemented using [LVGL](https://lvgl.io/){: target=_blank }, and it can play a movie file in mp4 format.       | No                                 | RZ/G2L                   | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_sample_video_playback){: target=_blank } |
    | **LVGL** RZ Linux **Benchmark** Demo<br> `#!bash rz_benchmark_demo`            | RZ Linux Benchmark Demo is implemented using [LVGL](https://lvgl.io/){: target=_blank }, and some benchmarks can be run on the demo.    | Yes                                | RZ/G2L, RZ/G2LC, RZ/G2UL | [Link to GitHub](https://github.com/renesas-rz/rz_benchmark_demo){: target=_blank } |
    | **Chromium Home Panel** Demo                                                   | Chromium Home Panel Demo is an HTML5 Single Page Web Application, and it is a demo for home panel.<br>Please click the browser's refresh button before using the seek bar of the 'Video Player'. | Yes                                | RZ/G2L, RZ/G2LC          | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/chromium/home_panel_demo){: target=_blank } |
    | **LVGL Home Panel** Demo                                                       | LVGL Home Panel Demo is implemented using [LVGL](https://lvgl.io/){: target=_blank }, and it is a demo for home panel.                  | Yes                                | RZ/G2L, RZ/G2LC, RZ/G2UL | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_home_panel_demo){: target=_blank } |


The pre-installed applications can be run from a launcher program that starts automatically when the HMI SDK Linux launches.
To run other applications, see [Step 8](../getting_started/#step-8-run-sample-application) at [Getting Started](../getting_started/index.md).


