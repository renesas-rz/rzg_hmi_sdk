# HMI SDK / RZ/G Linux LVGL sample program for iamge display

## Overview

This program runs on RZ/G2L, RZ/G2LC, and RZ/G2UL Evaluation Board Kit (EVK).

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

### How to identify an input event device file

When you run this sample program without weston, you need to specify an input event device file with '-i' or '--input' option.
The device file for an input device (such as mice and touchpads) appears as '_/dev/input/eventN_' (where _N_ is a number).
When there are multiple device files such as event0, event1, ..., run the following commnad to check the device file.

    # cat /dev/input/event0

Then, operate your input device (move a mouse, or tap a touchpad).
If you see something output on the console, '_/dev/input/event0_' is the right file for the device.
You can run this prgram, as follows:

    # ./lvgl_sample_img_disp -i /dev/input/event0

If you see nothing, check the next file (event1, event2, ...) in the same way as above.

## Notice
* LVGL v8.3 library uses [TJpgDec (Tiny JPEG Decompressor)](http://elm-chan.org/fsw/tjpgd/) for JPEG decompression. Since the library does not support progressive JPEG, this sample app cannot display a progressive JPEG image.
* LVGL v8.3 library supports 24-bit RGB888 and 32-bit ARGB8888 bitmap. Please note that it does not support 32-bit XRGB8888 bitmap. When you use a 32-bit bitmap image, you need to set appropriate alpha values.
* Information about image files used in this program (such as file path and image size) is hard-coded. If you would like to change displayed image files, edit '_create_buttons_' function in '_src/sample-app.c_'.

## License

This program is distributed under MIT license. And all sample image files are public domain.

