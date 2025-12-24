## Specification

RZ/G HMI SDK includes the following software modules:

* RZ/G Verified Linux Package Version 3.0.7
* RZ MPU Graphics Library V3.1.2.3 for RZ/G2L and RZ/G2LC
* RZ MPU Video Codec Library V3.1.3.0 for RZ/G2L

!!! note
    Please refer to [RZ/G Verified Linux Package (5.10-CIP)](https://www.renesas.com/en/software-tool/rzg-verified-linux-package-cip) for more details on the software modules.
!!! warning "Notice"
    Several updated OSS components, released to address security vulnerabilities and enhance driver performance, are now available on Renesas' GitHub. Please refer to [How to Update Linux Packages in the HMI SDK](../wiki/common_update-linux-package/) in [Wiki](../wiki) for instructions on how to replace them.

### Component Information

For detailed component information, please refer to the table below:

!!! content-wrapper no-indent table-no-sort ""

    | Components   | Version                          | Details |
    |-------------|----------------------------------|---------|
    | Linux Kernel | 5.10.229-cip54                   | SLTS (Super Long Term Support) kernel |
    | Yocto       | 3.1.31 (dunfell)                 | Distribution for embedded Linux |
    | GCC         | 8.3.0 (Arm GCC 8.3-2019.03)      | Compiler |
    | glibc       | 2.28                             | |
    | busybox     | 1.30.1                           | |
    | OpenSSL     | 1.1.1n                           | |
    | GStreamer 1.0 | 1.16.3                        | [GStreamer UM for RZ/G2L](https://www.renesas.com/us/en/document/mas/rzg2l-group-and-rzv2l-group-linux-interface-specification-gstreamer-users-manual-software){: target="_blank" }<br>[GStreamer Sample Applications](https://github.com/renesas-rz/rz_gstreamer_sample_code/) |
    | Wayland     | 1.18.0                           | |
    | Weston      | 8.0.0                            | |
    | Python      | 3.8.18                           | |
    | LVGL        | 8.3.11                           | |
    | lv-drivers  | 8.3.0                            | |
    | FiraCode    | 6.2                              | |
    | Tomlc99     | *^[1](#tf:2)^{: #tfref:2 }       | |
    | OpenCL      |                                  | [OpenCL Overview](https://www.khronos.org/opencl/){: target="_blank" } |
    | OpenGL ES   |                                  | [OpenGL ES Overview](https://www.khronos.org/opengles/){: target="_blank" } |
    | OpenMAX IL  | 1.1                              | [OpenMAX IL Overview](https://www.khronos.org/api/openmax/il){: target="_blank" } |  

    1. Commit ID [5221b3d](https://github.com/cktan/tomlc99/commit/5221b3d3d66c25a1dc6f0372b4f824f1202fe398){: target="_blank" }. [↩](#tfref:2){: .tf-backref }
    {: #tf:1 }

<br>

