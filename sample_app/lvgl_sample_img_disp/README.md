# HMI SDK / RZ/G Linux LVGL sample program for iamge display

## Overview

This program runs on RZ/G2L Evaluation Board Kit (EVK).

## How to Build

Befor you build this program, you need to install the HMI SDK toolchain into your PC.

    $ source /opt/poky/3.1.31/environment-setup-aarch64-poky-linux
    $ make

## How to Use

The sample program needs sample image files stored in /usr/share/images.

First, create /usr/share/images directory in the root filesystem on the EVK.

    # mkdir -p /usr/share/images

Copy lvgl_sample_img_disp and sample images.
If you use scp command for the copy, you may copy the files as follows.

    $ scp lvgl_sample_img_disp root@<your-EVK-IP>:/home/root/
    $ scp -r sample/* root@<your-EVK-IP>:/usr/share/images/

Then, run the sample program as follows.

    # ./lvgl_sample_img_disp

## License

This program is distributed under MIT license. And all sample image files are public domain.
