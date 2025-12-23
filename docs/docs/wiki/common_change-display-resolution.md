# How to Change the Display Resolution


This page describes how to change display resolution for weston (window manager).

## 1. Edit weston configuration file to change display resolution

Weston has a configuration file '/etc/xdg/weston/weston.ini' in the root filesystem.
You can change the display resolution by editing the file.

You can use a text editor 'vi' to change the configuration file. To open and edit the file, execute 'vi' in the terminal for Linux running on the EVK as follows.
```bash
vi /etc/xdg/weston/weston.ini
```
{: .hash }

For information about 'vi', see [Linux manual page](https://man7.org/linux/man-pages/man1/vi.1p.html).
And you can find much more information about how to use 'vi' on the internet.

If you want to edit the configuration file on your PC, insert your microSD card into your PC.
You can edit the file in your microSD card directly. It may need root privileges.

The configuration file consists of some sections, and the section has combinations of a key and a value.
```
[section]
key1=<value1>
key2=<value2>
```

The display resolution is configured in 'output' section, and it is set with 'name' key and 'mode' key as follows.
```
[output]
name=<connector>
mode=<width>x<height>
```

You can also set display resolution with a refresh rate in the 'mode' key as follows.
```
[output]
name=<connector>
mode=<width>x<height>@<refresh rate>
```

When you use Linux in the HMI SDK, set '**HDMI-A-1**' to 'name'.
For example, if you want to set a display resolution of 1920x1080 and a refresh rate of 60Hz, add the following text to the configuration file.
```bash title="/etc/xdg/weston/weston.ini"
[output]
name=HDMI-A-1
mode=1920x1080@60
```

To apply the change, you need to restart weston.
Execute the following command in the terminal for Linux running on the EVK.
```bash
systemctl restart weston@root
```
{: .hash }


## 2. Check available display resolutions

A display monitor can support several display resolutions.
You can get a list of display resolutions supported by the display monitor that you are using.

To get a list of display resolutions, execute 'weston-info' or 'modetest'.

### 1. weston-info

Execute 'weston-info' in the terminal for Linux running on the EVK as follows.
```bash
weston-info
```
{: .hash }

This command outputs many messages related to weston, but you need to check only information of 'wl_output'. For example:
```
interface: 'wl_output', version: 3, name: 17
        x: 0, y: 0, scale: 1,
        physical_width: 260 mm, physical_height: 150 mm,
        make: 'GEC', model: 'Onlap1102I',
        subpixel_orientation: unknown, output_transform: normal,
        mode:
                width: 1920 px, height: 1080 px, refresh: 60.000 Hz,
                flags: current preferred
        mode:
                width: 1920 px, height: 1080 px, refresh: 60.000 Hz,
                flags:
        mode:
                width: 1920 px, height: 1080 px, refresh: 59.940 Hz,
                flags:

...

        mode:
                width: 640 px, height: 480 px, refresh: 60.000 Hz,
                flags:
        mode:
                width: 640 px, height: 480 px, refresh: 59.940 Hz,
                flags:
        mode:
                width: 640 px, height: 480 px, refresh: 59.940 Hz,
                flags:
```

In the information of 'wl_output', all available display resolution are listed.
The mode with the flags 'current' is the currently used mode.


### 2. modetest

Execute 'modetest' in the terminal for Linux running on the EVK as follows.
```bash
modetest -M rzg2l-du -c
```
{: .hash }

This command output information about connectors, and it includes a list of modes (display resolution and refresh rate).
For example:
```
Connectors:
id      encoder status          name            size (mm)       modes   encoders
39      38      connected       HDMI-A-1        260x150         24      38
  modes:
        index name refresh (Hz) hdisp hss hse htot vdisp vss vse vtot)
  #0 1920x1080 60.00 1920 2008 2052 2200 1080 1084 1089 1125 148500 flags: phsync, pvsync; type: preferred, driver
  #1 1920x1080 60.00 1920 2008 2052 2200 1080 1084 1089 1125 148500 flags: phsync, pvsync; type: driver
  #2 1920x1080 59.94 1920 2008 2052 2200 1080 1084 1089 1125 148352 flags: phsync, pvsync; type: driver
  #3 1920x1080 50.00 1920 2448 2492 2640 1080 1084 1089 1125 148500 flags: phsync, pvsync; type: driver
  #4 1920x1080 50.00 1920 2448 2492 2640 1080 1084 1089 1125 148500 flags: phsync, pvsync; type: driver
  #5 1680x1050 59.88 1680 1728 1760 1840 1050 1053 1059 1080 119000 flags: phsync, nvsync; type: driver
  #6 1600x900 60.00 1600 1624 1704 1800 900 901 904 1000 108000 flags: phsync, pvsync; type: driver
  #7 1280x1024 60.02 1280 1328 1440 1688 1024 1025 1028 1066 108000 flags: phsync, pvsync; type: driver
  #8 1440x900 59.90 1440 1488 1520 1600 900 903 909 926 88750 flags: phsync, nvsync; type: driver
  #9 1280x800 59.91 1280 1328 1360 1440 800 803 809 823 71000 flags: phsync, nvsync; type: driver
  #10 1280x720 60.00 1280 1390 1430 1650 720 725 730 750 74250 flags: phsync, pvsync; type: driver
  #11 1280x720 60.00 1280 1390 1430 1650 720 725 730 750 74250 flags: phsync, pvsync; type: driver
  #12 1280x720 59.94 1280 1390 1430 1650 720 725 730 750 74176 flags: phsync, pvsync; type: driver
  #13 1280x720 50.00 1280 1720 1760 1980 720 725 730 750 74250 flags: phsync, pvsync; type: driver
  #14 1024x768 60.00 1024 1048 1184 1344 768 771 777 806 65000 flags: nhsync, nvsync; type: driver
  #15 800x600 60.32 800 840 968 1056 600 601 605 628 40000 flags: phsync, pvsync; type: driver
  #16 720x576 50.00 720 732 796 864 576 581 586 625 27000 flags: nhsync, nvsync; type: driver
  #17 720x480 60.00 720 736 798 858 480 489 495 525 27027 flags: nhsync, nvsync; type: driver
  #18 720x480 60.00 720 736 798 858 480 489 495 525 27027 flags: nhsync, nvsync; type: driver
  #19 720x480 59.94 720 736 798 858 480 489 495 525 27000 flags: nhsync, nvsync; type: driver
  #20 720x480 59.94 720 736 798 858 480 489 495 525 27000 flags: nhsync, nvsync; type: driver
  #21 640x480 60.00 640 656 752 800 480 490 492 525 25200 flags: nhsync, nvsync; type: driver
  #22 640x480 59.94 640 656 752 800 480 490 492 525 25175 flags: nhsync, nvsync; type: driver
  #23 640x480 59.94 640 656 752 800 480 490 492 525 25175 flags: nhsync, nvsync; type: driver
  props:
        1 EDID:

...

```

You can choose one of the modes and set it to the weston configuration file.






