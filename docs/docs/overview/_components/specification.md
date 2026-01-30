## Specification

RZ/G HMI SDK includes the following software modules:

* RZ/G3E Board Support Package Version 1.0.0
* RZ MPU Graphics Library v4.2.0.2
* RZ MPU Video Codec Library v4.4.0.0

!!! note
    Please refer to [RZ/G3E Board Support Package](https://www.renesas.com/en/software-tool/rzg3e-board-support-package) for more details on the software modules.

### Component Information

For detailed component information, please refer to the table below:

!!! content-wrapper no-indent table-no-sort ""

    | Components   | Version                          | Details |
    |-------------|----------------------------------|---------|
    | Linux Kernel | 6.1.107-cip28                   | SLTS (Super Long Term Support) kernel |
    | Yocto       | 3.1.31 (dunfell)                 | Distribution for embedded Linux |
    | GCC         | 13.3.0                           | Compiler |
    | glibc       | 2.39                             | |
    | busybox     | 1.36.1                           | |
    | OpenSSL     | 3.2.4                            | |
    | GStreamer 1.0 | 1.22.12                        | [GStreamer UM for RZ/G3E](https://www.renesas.com/en/document/mas/rzg3e-group-linux-interface-specification-gstreamer-users-manual-software){: target="_blank" }<br>[GStreamer Sample Applications](https://github.com/renesas-rz/rz_gstreamer_sample_code/) |
    | Wayland     | 1.22.0                           | |
    | Weston      | 13.0.1                           | |
    | Python      | 3.12.9                           | |
    | Chromium    | 132.0.6834.83                    | chromium-ozone-wayland |
    | Flutter     | 3.27.1                           | |
    | LVGL        | 9.2.2                            | |
    | FiraCode    | 6.2                              | |
    | Tomlc99     | *^[1](#tf:2)^{: #tfref:2 }       | |
    | OpenCL      |                                  | [OpenCL Overview](https://www.khronos.org/opencl/){: target="_blank" } |
    | OpenGL ES   |                                  | [OpenGL ES Overview](https://www.khronos.org/opengles/){: target="_blank" } |
    | OpenMAX IL  | 1.1                              | [OpenMAX IL Overview](https://www.khronos.org/api/openmax/il){: target="_blank" } |  

    1. Commit ID [5221b3d](https://github.com/cktan/tomlc99/commit/5221b3d3d66c25a1dc6f0372b4f824f1202fe398){: target="_blank" }. [↩](#tfref:2){: .tf-backref }
    {: #tf:1 }

<br>

