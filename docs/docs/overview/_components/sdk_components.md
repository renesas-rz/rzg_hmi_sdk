## SDK Components

### File Contents

HMI SDK provides following files:

!!! content-wrapper no-indent table-no-sort table-no-hover ""

    +-------------------------------+------------------------------------------+------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    | Package                       | Items                                    | File Name                                      | Details                                                                                                             |
    +===============================+==========================================+================================================+=====================================================================================================================+
    | HMI SDK <br>                  | Release Note                             | r01an7643ej0100-rzg-hmi-sdk.pdf                | PDF documentation that contains RZ/G HMI SDK release information                                                    |
    | (RTK0EF0195F02300SJ)          +------------------------------------------+------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                               | README                                   | README.txt                                     | Information of HMI SDK package                                                                                      |
    |                               +------------------------------------------+------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                               | SD card image for eSD boot               | image-file_rzg2*_hmi-sdk_v2.3.0.0.zip          | Bootable SD card images in WIC format for RZ/G2L, RZ/G2LC, and RZ/G2UL                                              |
    |                               +------------------------------------------+------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                               | Installer for pre-built cross-toolchain  | toolchain-installer_rzg2*_hmi-sdk_v2.3.0.0.zip | Cross-toolchain is used for building sample applications.                                                           |
    |                               +------------------------------------------+------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                               | Pre-built binaries                       | pre-built-binary_rzg2*_hmi-sdk_v2.3.0.0.zip    | Pre-built binaries (boot loader, Linux kernel image and root filesystem, flash writer) for SPI boot mode (option)   |
    |                               +------------------------------------------+------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                               | OSS license files                        | licenses_rzg2_hmi-sdk_v2.3.0.0.zip             | License files for open-source software used in HMI SDK                                                              |
    +-------------------------------+------------------------------------------+------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    | HMI SDK Source Code <br>      | README                                   | README.txt                                     | Information of HMI SDK Source Code package                                                                          |
    | (RTK0EF0195F02300SJ_linux-src)+------------------------------------------+------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                               | Yocto Recipe                             | yocto_recipe_rzg2_hmi-sdk_v2.3.0.0.tar.gz      | Yocto meta layers used for building HMI SDK                                                                         |
    |                               +------------------------------------------+------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                               | Source Code                              | oss-souce-code-pkg_rzg2_hmi-sdk_v2.3.0.0.7z    | Source code package of open-source software used for building HMI SDK                                               |
    +-------------------------------+------------------------------------------+------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+

### HMI Applications

HMI SDK provides HMI demos and sample applications. <br>
These are available as both source code and prebuilt binaries, allowing you to run them on the board immediately and customize them as needed.

!!! content-wrapper center ""

    | Sample Application Name                                                        | Description                                                                                                                             | Pre-installed <br>in SD Card Image | Source Code URL   |
    | ------------------------------------------------------------------------------ | --------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------- | ----------------- |
    | **LVGL** Sample Program for **Image Display**<br> `#!bash lvgl_sample_img_disp`        | This program is implemented using [LVGL](https://lvgl.io/){: target=_blank }, and it can display image files in bmp/jpg/png/gif format. | No                                 | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_sample_img_disp){: target=_blank } |
    | **LVGL** Sample Program for **Audio Playback**<br> `#!bash lvgl_sample_audio_playback` | This program is implemented using [LVGL](https://lvgl.io/){: target=_blank }, and it can play audio files in mp3/aac/wav format.        | No                                 | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_sample_audio_playback){: target=_blank } |
    | **LVGL** Sample Program for **Video Playback**<br> `#!bash lvgl_sample_video_playback` | This program is implemented using [LVGL](https://lvgl.io/){: target=_blank }, and it can play a movie file in mp4 format.               | No                                 | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/lvgl/lvgl_sample_video_playback){: target=_blank } |
    | **LVGL** RZ Linux **Benchmark** Demo<br> `#!bash rz_benchmark_demo`                         | RZ Linux Benchmark Demo is implemented using [LVGL](https://lvgl.io/){: target=_blank }, and some benchmarks can be run on the demo.    | Yes                                | [Link to GitHub](https://github.com/renesas-rz/rz_benchmark_demo){: target=_blank } |
    | **Chromium Home Panel** Demo                                                       | Chromium Home Panel Demo is an HTML5 Single Page Web Application, and it is a demo for home panel. It is available only for RZ/G2L EVK.     | Yes                                | [Link to GitHub](https://github.com/renesas-rz/rzg_hmi_sdk/tree/main/sample_app/chromium/home_panel_demo){: target=_blank } |


The pre-installed applications can be run from a launcher program that starts automatically when the HMI SDK Linux launches.
To run other applications, see [Step 8](../getting_started/#step-8-run-sample-application) at [Getting Started](../getting_started/index.md).


