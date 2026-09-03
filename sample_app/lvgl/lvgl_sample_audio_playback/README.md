# HMI SDK / RZ/G Linux LVGL sample program for audio playback

## Overview

This program runs on RZ/G2L Evaluation Board Kit (EVK).

## How to Build

Befor you build this program, you need to install the HMI SDK toolchain into your PC.

    $ source /opt/poky/3.1.31/environment-setup-aarch64-poky-linux
    $ make

## How to Use

The sample program needs sample audio files stored in /usr/share/sounds/sample.

First, create /usr/share/sounds/sample directory in the root filesystem on the EVK.

    # mkdir -p /usr/share/sounds/sample

Copy lvgl_sample_audio_playback and sample audio files.
If you use scp command for the copy, you may copy the files as follows.

    $ scp lvgl_sample_audio_playback root@<your-EVK-IP>:/home/root/
    $ scp -r sample/* root@<your-EVK-IP>:/usr/share/sounds/sample/

Then, run the sample program as follows.

    # ./lvgl_sample_audio_playback

## License

This program is distributed under MIT license. And all sample audio files are licensed [CC0 1.0 Universal Public Domain Dedication](https://creativecommons.org/publicdomain/zero/1.0/legalcode).

## Known Issues

### v2.01

* When this program is run on the RZ/G HMI SDK v3.5.0.0 with LVGL v9.5, the following issue is known:
    * A segmentation fault occurs when the program is terminated by clicking the **Quit** button.

