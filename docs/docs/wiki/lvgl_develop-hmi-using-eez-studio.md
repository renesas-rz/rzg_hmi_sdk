# How to Develop LVGL HMI Applications Using EEZ Studio

!!! abstract "Page Information"
    The information provided on this page has been verified using the following SDK versions and evaluation kits (EVKs):

    - ***HMI SDK v2.3.1.0 (Yocto 3.1.31 (dunfell), kernel 5.10) using RZ/G2L and RZ/G2LC EVK***

    Last updated: ***January 30, 2026***

[EEZ Studio](https://www.envox.eu/studio/studio-introduction/) is a free and cross-platform tool that can be used for development of LVGL GUIs.
It is an open-source tool licensed under [GPL v3](https://github.com/eez-open/studio/blob/master/LICENSE.TXT).

This guide describes the use of EEZ Studio to develop LVGL GUI applications.
For detailed information about EEZ Studio, see [EEZ Studio documentation](https://www.envox.eu/eez-studio-docs/) because this guide provides only basic information.

## Installation

### In the case of Windows PC

1. Get the EEZ Studio installer 'EEZ-Studio-Setup-x.xx.x.exe' from the [GitHub page](https://github.com/eez-open/studio/releases).
  ![eezinstall3-windows-image](images/eezstudio/eezstudio_installation_windows-1.png)

2. Double-click the downloaded installer and agree to the software license agreement to start installation.

### In the case of Linux PC (Ubuntu)

1. Get the EEZ Studio installer 'eezstudio_x.xx.x_amd64.deb' from the [GitHub page](https://github.com/eez-open/studio/releases).
If you cannot find the installer in the list, click 'Show all xx assets' at the bottom of the list to show all items.
  ![eezinstall4-image](images/eezstudio/eezstudio_installation_linux-1.png)

2. Double-click the downloaded installer and click the Install button.
  ![eezinstall5-image](images/eezstudio/eezstudio_installation_linux-2.png)

3. Enter the login password and click Authenticate to start the installation.
  ![eezinstall6-image](images/eezstudio/eezstudio_installation_linux-3.png)

## Development of GUI

The development flow described in this guide is as follows.

1. Create GUI and generate source code in EEZ Studio on your PC.
2. Build the GUI application from the generated source code on your Linux PC.
3. Copy the built executable file into a microSD card and run it on the EVK.

### 1. Create GUI and Generate source code

You can create LVGL GUI applications using EEZ Studio on your PC.
And it supports generating source code.

#### Creating a project

1. Start EEZ Studio, select "File" on the left tab and choose "New Project".
  ![newproject-image](images/eezstudio/eezstudio_create-project-1.png)

2. Select "LVGL" and enter an arbitrary project name in PROJECT SETTINGS and press Create Project.
  ![createproject-image](images/eezstudio/eezstudio_create-project-2.png)

#### Creating GUI

1. Adding widgets
Drag and drop the necessary widgets (e.g. Arc) from the Components Palettes.
  ![UI-components-image](images/eezstudio/eezstudio_create-gui-1.png)
  ![UI-widgets-image](images/eezstudio/eezstudio_create-gui-2.png)

2. Change the size and display of widgets
You can resize the widgets (e.g. Arc) by expanding the blue frame.
  ![UI-widgetsresize-image](images/eezstudio/eezstudio_create-gui-3.png)
You can also change the size from POSITION AND SIZE in widgets (e.g. Arc).
  ![UI-widgetsposition-image](images/eezstudio/eezstudio_create-gui-4.png)
	- Left - Move widgets left and right.
	- Top - Move widgets up and down.
	- Width - Set the width of widgets.
	- Height - Set the height of widgets.
	<br>
SPECIFIC in WIDGETS (e.g. Arc) to change the way it is displayed.
SPECIFIC has different items that can be changed depending on the widgets displayed.
  ![UI-widgetsposition-image](images/eezstudio/eezstudio_create-gui-5.png)
	- Range min - Minimum value of range
	- Range max - Maximum value of range
	- Value - Length of the blue line (depends on the application.)
	- Bg start angle - Starting point of the blue line
	- Bg end angle - End of the blue line
	- Mode - Select from three types.
	<br>
NORMAL appears at the fixed position of the blue line, SYMMETRICAL at the symmetrical position of the fixed position of the blue line, and REVERSE at the exact opposite position of the fixed position of the blue line.

3. Adding image files
Click on bitmaps on the right and drag and drop image files from Explorer into the red box.
  ![UI-widgetsposition-image](images/eezstudio/eezstudio_create-gui-6.png)

4. Apply image to widgets (image).
Drag and drop the necessary widgets (image) from the Components Palettes.
  ![UI-components-image](images/eezstudio/eezstudio_create-gui-1.png)
  ![UI-widgets-image](images/eezstudio/eezstudio_create-gui-7.png)
Add the image files added in Add Image Files.
  ![UI-gallery-image](images/eezstudio/eezstudio_create-gui-8.png)

5. Apply image to widgets (imagebutton).
Drag and drop the necessary widgets (imagebutton) from the Components Palettes.
  ![UI-components-image](images/eezstudio/eezstudio_create-gui-1.png)
  ![UI-imagebutton-image](images/eezstudio/eezstudio_create-gui-9.png)
Add the image files added in Add Image Files.
  ![UI-imagebutton-image](images/eezstudio/eezstudio_create-gui-10.png)

#### Generating C source code

1. Open the created UI project in EEZ Studio
  ![U1-sample-image](images/eezstudio/eezstudio_generate-code-1.png)

2. Generate source code by following the steps below.

	- 2.1. Preservation

	- 2.2. Check the settings.

	- 2.3. Build and generate source code
	![UI-build-image](images/eezstudio/eezstudio_generate-code-2.png)

3. Source code is generated.
Source files are generated in the source folder in the project within eez-project.
  ![code-generate-image](images/eezstudio/eezstudio_generate-code-3.png)

#### Implementation of events

1. Follow the steps below to set up events using the UI in EEZ Studio.

	1. Press "+" for "event handlers" in the properties of the object for which you want to set events.
	![event-setting-image1](images/eezstudio/eezstudio_implement-event-1.png)

	2. Select "New Action" and set the event name.
	![event-setting-image2](images/eezstudio/eezstudio_implement-event-2.png)

	3. Go to "User Actions", select the event created in the previous step, and copy the generated event callback template to screen.c.
	![event-setting-image3](images/eezstudio/eezstudio_implement-event-3.png)

2. Implement the generated event callback in C language.
In this example, color of the button is changed in the event callback function.

```
void action_push(lv_event_t *e) {
	lv_obj_t btn = lv_event_get_target(e);

	lv_obj_set_style_bg_color(btn, lv_color_hex(0xfff6e01d), LV_PART_MAIN | LV_STATE_DEFAULT);
}
```

#### Implementation of screen transitions

- For screen transitions, a screen ID is assigned to each page in screen.h when a multi-page UI is created in EEZ Studio.
```bash title="screen.h"
enum ScreensEnum {
	SCREEN_ID_MAIN = 1,
	SCREEN_ID_SECOND = 2,
};
```

- To perform screen transitions, implement them in the event callbacks by yourself using the C language.
In this example, screen transition is implemented in an event callback is.
```
void action_push(lv_event_t *e) {
	loadScreen(SCREEN_ID_SECOND);
}
```

### 2. Build LVGL GUI applications

You can build LVGL GUI applications from the generated source code.
Please note that you need to build the applications on a Linux PC.

#### Setting up cross compiler

Install cross compiler to your Linux PC, and enable the compiler.
To install and enable the compiler, see [Step 1: Build Sample Applications](../../hmi_applications/#step-1-build-sample-applications).

#### Building GUI application

1. Add "main.c" to the generated “src/ui folder.
An example of main.c is shown in [Appendix](#appendix).

2. Create a Makefile in the generated "src/ui folder" and execute make command.
An example of MakeFile is shown in [Appendix](#appendix).

### 3. Deploy and run LVGL GUI applications

Copy the built executable file into a microSD card so that you can run it on the EVK.

#### Checking operation of the application on EVK

1. Copy the generated executable file to the root filesystem in an SD card.
For information about how to copy the file, see [Step 2: Deploy Sample Applications](../../hmi_applications/#step-2-deploy-sample-applications).

2. Set execute permission on the file.
```bash
chmod +x <executable file name>
```
{: .hash }

3. Execute the file.
```bash
./<executable file name>
```
{: .hash }

  ![bord-image](images/eezstudio/eezstudio_check-operation-1.png)

## Appendix

### Sample source code

```bash title="main.c"
--8<-- "./docs/wiki/_codes/main.c"
```

```bash title="Makefile"
--8<-- "./docs/wiki/_codes/Makefile"
```
