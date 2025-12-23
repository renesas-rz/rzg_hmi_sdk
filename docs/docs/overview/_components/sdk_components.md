## SDK Components

HMI SDK provides the following packages:

* **HMI SDK Package**
    *-eSD Boot Image & Toolchain Installer* 

    This package lets you get started right away. You can create a bootable microSD card for the EVK, set up the Linux environment, run the prebuilt demo applications, and build sample HMI applications using the included toolchain installer. <br> 
    <br>
    Please go to [Getting Started](../getting_started/) to get started with this HMI SDK Package.

    <br>

* **HMI SDK Yocto Build Package** 
    *-Yocto Recipes & Pre-built Binary for QSPI Boot*

    This package is for when you want more flexibility. You can build and customize the entire HMI SDK from source. You can also try other boot modes such as QSPI or eMMC, in addition to eSD.    

    *  **Source Code** *-Supplementary for HMI SDK Yocto Build Package*  
            Note that this is optional; the supplementary source code used in the Yocto build is provided for offline builds or as a backup if online fetching fails.
    
    <br>
    Please go to [Building the HMI SDK with Yocto](../building_the_hmi_sdk_with_yocto/) to get started with this HMI SDK Yocto Build Package (and Source Code).        

The packages are designed for specific board models, while the source code is universal and can be used across all boards.



### File Contents

The contents of the packages are as follows:

!!! content-wrapper no-indent table-no-sort table-no-hover ""

    +---------------------------------------------------------------+---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    | Packages                                                      | Content File                                      | Details                                                                                                             |
    +===============================================================+===================================================+=====================================================================================================================+
    |**HMI SDK Package**                                            | *image-file_<*dev*\>_hmi-sdk_v2.3.1.0.zip*        | Bootable SD card images in WIC format                                                                               |
    | *-eSD Boot Image & Toolchain Installer*                       +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                               | *licenses_rzg2_hmi-sdk_v2.3.1.0.zip*              | License files for open-source software used in HMI SDK                                                              |
    | *(RTK0EF0195F02310SJ_***<dev\>***)*                           +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                               | *r01an7976ej0100-rzg-hmi-sdk.pdf*                 | Release notes with RZ/G HMI SDK information                                                                         |
    |                                                               +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                               | *README.txt*                                      | README with package details                                                                                         |
    |                                                               +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                               |*toolchain-installer_<*dev*\>_hmi-sdk_v2.3.1.0.zip*| Cross-toolchain installer for building sample applications                                                          |
    +---------------------------------------------------------------+---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |**HMI SDK Yocto Build Package**                                | *licenses_rzg2_hmi-sdk_v2.3.1.0.zip*              | License files for open-source components used in HMI SDK                                                            |
    | *-Yocto Recipes & Pre-built Binary for QSPI Boot*             +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                               | *pre-built-binary_<*dev*\>_hmi-sdk_v2.3.1.0.zip*  | Pre-built binaries (bootloader, Linux kernel, root filesystem, flash writer) for SPI boot mode                      |
    | *(RTK0EF0195F02310SJ_***<dev\>***_yocto-and-pre-built-image)* +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                               | *r01an7976ej0100-rzg-hmi-sdk.pdf*                 | Release notes with RZ/G HMI SDK information                                                                         |
    |                                                               +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                               | *README.txt*                                      | README with package details                                                                                         |
    |                                                               +---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                               | *yocto_recipe_rzg2_hmi-sdk_v2.3.1.0.tar.gz*       | Yocto meta layers for building HMI SDK                                                                              |
    +---------------------------------------------------------------+---------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    !!! success "Tip"   
        ***<dev\>*** in the table represents a device name, such as *rzg2l* for RZ/G2L, *rzg2lc* RZ/G2LC, or *rzg2ul* for RZ/G2UL.<br>
        The angle brackets `<` and `>` should not be included when you enter the text.



The contents of the source code are as follows:

!!! content-wrapper no-indent table-no-sort table-no-hover ""

    +---------------------------------------------------------------+-----------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    | Supplements                                                   | Content File                                        | Details                                                                                                             |
    +===============================================================+=====================================================+=====================================================================================================================+
    |**Source Code**                                                | *licenses_rzg2_hmi-sdk_v2.3.1.0.zip*                | License files for open-source components used in HMI SDK                                                            |
    | *-Supplementary for HMI SDK Yocto Build Package*              +-----------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                               | *oss-souce-code-pkg_rzg2_hmi-sdk_v2.3.1.0.7z*       | Source code package of open-source components for building HMI SDK                                                  |
    | *(RTK0EF0195F02310SJ_linux-src)*                              +-----------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                               | *r01an7976ej0100-rzg-hmi-sdk.pdf*                   | Release notes with RZ/G HMI SDK information                                                                         |
    |                                                               +-----------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+
    |                                                               | *README.txt*                                        | README with package details                                                                                         |
    +---------------------------------------------------------------+-----------------------------------------------------+---------------------------------------------------------------------------------------------------------------------+


### HMI Application Contents


**HMI Demo Applications**

When the HMI SDK Linux system boots, the Demo Application Launcher starts automatically. The pre-installed demo applications can then be launched from the Demo Application Launcher—for example, the Chromium Home Panel Demo shown below.
![](images/demo_chromium.png){: width="40%"} 

Follow the instructions under [Demo Applications](../hmi_applications/#demo-applications) in the [HMI Applications](../hmi_applications/index.md) section to view these demos. They come as pre-built binaries, with source code also provided in the table below:


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


**HMI Sample Applications**

The sample applications are not pre-built and require additional building and deployment. Follow the instructions under [Sample Applications](../hmi_applications/#sample-applications) in the [HMI Applications](../hmi_applications/index.md) section to try them, with source code also provided in the table below:

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

