## Specification

RZ/G HMI SDK includes the following software modules:

* RZ/G3L Board Support Package Version 1.0.0
* RZ MPU Graphics Library v5.1.3.2
* RZ MPU Video Codec Library v5.1.5.0

!!! note
    Please refer to [Renesas RZ Linux BSP Plus](https://renesas-rz.github.io/rz_linux_bsp_plus/){: target="_blank" } for more details on the software modules.

### Component Information

For detailed component information, please refer to the table below:

!!! content-wrapper no-indent table-no-sort ""

    | Components        | Version                          | Details |
    |-------------------|----------------------------------|---------|
    | Linux Kernel      | kernel-6.12.46-cip8              | SLTS (Super Long Term Support) kernel |
    | Yocto             | 5.0.9 (scarthgap)                | Distribution for embedded Linux |
    | GCC               | 13.4.0                           | Compiler |
    | glibc             | 2.39                             | |
    | busybox           | 1.36.1                           | |
    | OpenSSL           | 3.2.6                            | |
    | GStreamer 1.0     | 1.22.12                          | [GStreamer Software Manual](https://www.renesas.com/document/mas/rzg3l-group-linux-interface-specification-gstreamer-software-manual){: target="_blank" }<br>[GStreamer Sample Applications](https://github.com/renesas-rz/rz_gstreamer_sample_code/){: target=_blank } |
    | Wayland           | 1.22.0                           | |
    | Weston            | 13.0.1                           | |
    | Python            | 3.12.12                          | |
    | Chromium          | 132.0.6834.83                    | chromium-ozone-wayland |
    | Flutter           | 3.38.3                           | |
    | LVGL              | 9.5.0                            | |
    | FiraCode          | 6.2                              | |
    | Tomlc99           | *^[1](#tf:1)^{: #tfref:1 }       | |
    | OpenCL            | 2.0 Full Profile                 | [OpenCL Overview](https://www.khronos.org/opencl/){: target="_blank" } |
    | OpenGL ES         | 1.1, 2.0, 3.0, 3.1 and 3.2       | [OpenGL ES Overview](https://www.khronos.org/opengles/){: target="_blank" } |
    | OpenMAX IL        | 1.1                              | [OpenMAX IL Overview](https://www.khronos.org/api/openmax/il){: target="_blank" } |  

    1. Commit ID [5221b3d](https://github.com/cktan/tomlc99/commit/5221b3d3d66c25a1dc6f0372b4f824f1202fe398){: target="_blank" }. [↩](#tfref:2){: .tf-backref }
    {: #tf:1 }

{% include "./license_information.md" %}

