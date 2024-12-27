## Specification

RZ/G HMI SDK includes the following software packages:

* RZ/G Verified Linux Package Version 3.0.6-update3
* RZ MPU Graphics Library V1.2.2 Unrestricted Version for Verified Linux Package of RZ/G2L and RZ/G2LC
* RZ MPU Video Codec Library v1.2.2 Unrestricted Version for Verified Linux Package of RZ/G2L

Please refer to the table below for more information.


### Features

!!! content-wrapper no-indent table-no-sort ""

    | Components                            | Version                                 | Detail                                                                                                                                                                              |
    |---------------------------------------|-----------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
    | Linux Kernel                          | 5.10.201-cip41                          | SLTS(Super Long Term Support) Kernel                                                                                                                                                |
    | Yocto                                 | 3.1.31 (dunfell)                        | Distribution for embedded linux                                                                                                                                                     |
    | gcc                                   | 8.3.0 (Arm GCC 8.3-2019.03)             | Compiler                                                                                                                                                                            |
    | glibc                                 | 2.28                                    |                                                                                                                                                                                     |
    | busybox                               | 1.30.1                                  |                                                                                                                                                                                     |
    | openssl                               | 1.1.1n                                  |                                                                                                                                                                                     |
    | GStreamer1.0^[1](#tf:1)^{: #tfref:1 } | 1.16.3                                  | GStreamer UM for [RZ/G2L](https://www.renesas.com/us/en/document/mas/rzg2l-group-and-rzv2l-group-linux-interface-specification-gstreamer-users-manual-software){: target="_blank" } |
    | wayland                               | 1.18.0                                  |                                                                                                                                                                                     |
    | weston                                | 8.0.0                                   |                                                                                                                                                                                     |
    | Python3                               | 3.8.14                                  |                                                                                                                                                                                     |
    | lvgl                                  | 8.3.11                                  |                                                                                                                                                                                     |
    | lv-drivers                            | 8.3.0                                   |                                                                                                                                                                                     |
    | Firacode                              | 6.2                                     |                                                                                                                                                                                     |
    | Tomlc99                               | Latest version^[2](#tf:2)^{: #tfref:2 } |                                                                                                                                                                                     |
    | OpenCL                                |                                         | [OpenCL Overview](https://www.khronos.org/opencl/){: target="_blank" }                                                                                                              |
    | OpenGLES                              |                                         | [OpenGL ES Overview](https://www.khronos.org/opengles/){: target="_blank" }                                                                                                         |
    | OpenMAX IL                            | 1.1                                     | [OpenMAX IL Overview](https://www.khronos.org/api/openmax/il){: target="_blank" }                                                                                                   |

    1. For GStreamer Sample Applications please visit [this repository](https://github.com/renesas-rz/rz_gstreamer_sample_code/){: target="_blank" }. [↩](#tfref:1){: .tf-backref }
    {: #tf:1 }

    2. Commit ID [5221b3d](https://github.com/cktan/tomlc99/commit/5221b3d3d66c25a1dc6f0372b4f824f1202fe398){: target="_blank" }. [↩](#tfref:2){: .tf-backref }
    {: #tf:2 }

### Memory Map

=== "RZ/G2L"

    Please see the memory map at **Linux Interface Specification Kernel Core User’s Manual: Software** for **RZ/G2L Group, RZ/V2L Group, and RZ/Five**.

    `RTK0EF0045Z9006AZJ-v3.0.6.zip` > `r01us0468ej0108-rz-g_Kernel_Core_UME.pdf` page 5-6.

    [:octicons-download-16: Get User's Manual: Software<br><span class="btn-subtext">RZ/G2L Group, RZ/V2L Group, and RZ/Five</span>](https://www.renesas.com/document/mas/rzg2lfivev2l-group-bsp-manual-set-rtk0ef0045z9000azj-v306zip){ .md-button .btn-round target=_blank }
