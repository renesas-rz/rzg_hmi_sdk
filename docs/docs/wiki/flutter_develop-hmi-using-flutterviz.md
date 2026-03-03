# How to Develop Flutter HMI Applications Using FlutterViz

!!! abstract "Page Information"
    The information provided on this page has been verified using the following SDK versions and evaluation kits (EVKs):

    - ***HMI SDK v3.4.0.0 (Yocto 5.0.9 (scarthgap), kernel 6.1) using RZ/G3E EVK***
    - ***HMI SDK v3.4.1.0 (Yocto 5.0.9 (scarthgap), kernel 6.1) using RZ/G2L and RZ/G2LC EVK***

    Last updated: ***March 03, 2026***

[FlutterViz](https://flutterviz.com/) is easy to use interface with Flutter Drag and Drop UI builder to quickly kick-start your project. This open-source project aims to empower developers by providing a free and extensible visual Flutter UI builder. For more information about FlutterViz, see the [FlutterViz GitHub repository](https://github.com/iqonic-design/flutter_viz).  

This guide describes how to use FlutterViz, a web-based visual UI builder, to develop Flutter HMI applications. You will complete the following steps:  

[Step 1: Create a Flutter Application Using FlutterViz](../flutter_develop-hmi-using-flutterviz/#step-1-create-flutter-applications-using-flutterviz)  
[Step 2: Prepare the Flutter Sample Application Package](../flutter_develop-hmi-using-flutterviz/#step-2-prepare-the-flutter-sample-application-package)  
[Step 3: Update the Flutter Sample Application Package](../flutter_develop-hmi-using-flutterviz/#step-3-update-the-flutter-sample-application-package)   
[Step 4: Build the Flutter Sample Application](../flutter_develop-hmi-using-flutterviz/#step-4-build-the-flutter-sample-application)  
[Step 5: Deploy the Flutter Sample Application](../flutter_develop-hmi-using-flutterviz/#step-5-deploy-the-flutter-sample-application)  
[Step 6: Run the Flutter Sample Application](../flutter_develop-hmi-using-flutterviz/#step-6-run-the-flutter-sample-application)  

!!! success
    [Step 1](../flutter_develop-hmi-using-flutterviz/#step-1-create-flutter-applications-using-flutterviz) demonstrates how to use FlutterViz’s drag-and-drop features to design the UI of your application.  
    [Step 3](../flutter_develop-hmi-using-flutterviz/#step-3-update-the-flutter-sample-application-package) explains how to update the Flutter sample application package. Please note that this step requires a basic understanding of the Dart programming language.  

    If you prefer, you can download the ready-to-use Flutter sample application package by [**clicking here**](../packages/fluttersampleapp_source.zip) and proceed directly to [Step 4](../flutter_develop-hmi-using-flutterviz/#step-4-build-the-flutter-sample-application).  


## Step 1: Create Flutter Applications Using FlutterViz

### 1-1. Create an account and log in

Open [FlutterViz](https://flutterviz.com/) and click *GET INVITE* to obtain the invitation code required to create an account.
![](images/flutter/FlutterViz_02.png){: width="60%"}  

Enter a username and your email address, then click GET INVITE.  
![](images/flutter/FlutterViz_03.png){: width="60%"}  

The invitation code will be sent to the email address you entered.  

!!! success "Tip" 
    Note that it may take up to one week to receive the invitation code.  

Once you receive the code, click *Login*, then select *Click here to Sign Up* to create a new account.  
![](images/flutter/FlutterViz_04.png){: width="60%"}  
![](images/flutter/FlutterViz_05.png){: width="60%"}    
Enter your username, email address, password, and the invitation code you received, then click *Sign Up*.  
![](images/flutter/FlutterViz_06.png){: width="60%"}     


### 1-2. Create a new project

After creating a new account, select *Create New Project*.    
![](images/flutter/FlutterViz_08.png){: width="60%"}  

Select the template to use. This guide uses the *Blank App* template.   
Enter your project name, then click *Create New* to continue.    
![](images/flutter/FlutterViz_09.png){: width="60%"}    


### 1-3. Create screens

In this sample application, 3 screens will be created:  

- [SelectScreen](#selectscreen)  
- [JPGScreen](#jpgscreen)  
- [GIFScreen](#gifscreen)  

<br>
  
#### SelectScreen

1. Create a new screen and choose a template to use. 

    Click *+ New Screen* in the top-right corner to create a new screen.  
    ![](images/flutter/FlutterViz_10.png){: width="60%"}  

    Enter a name for your project, as "SelectScreen".  
    Then, go to the Welcome section and choose *WelcomeScreen#2* as the template to use.  
    ![](images/flutter/FlutterViz_11.png){: width="40%"}  


2. Delete and add widgets.  

    After you successfully create SelectScreen, the screen will appear as shown below.  
    ![](images/flutter/FlutterViz_12.png){: width="60%"}  

    In the left-side panel, select the third option, *Tree View*. You will see the widgets listed as shown below.   
    ![](images/flutter/FlutterViz_13.png){: width="60%"}  

    Right-click a widget to display the available options, as shown below (left).  

    Use these options to add or delete widgets as needed (right). For this example:  
    - Delete the *Row* and *Image* widgets.  
    - Add a *Stack* widget and a *Text Button* widget.  
    - Make sure the *Column* and the newly added *Text Button* are wrapped inside the *Stack* widget.  
    ![](images/flutter/FlutterViz_14.png){: width="60%"}    


3. Modify the properties of each widget.  

    Modify the widgets starting from the top of the Tree View.  

    Click each widget to display its properties in the right-side panel.  
    Only change the settings shown below, and keep all other properties at their default values.  

    - Stack  
        Change the alignment to "Center".  
        ![](images/flutter/FlutterViz_15.png){: width="25%"}  

    - "X" Text Button  
        The newly added *Text button* wrapped inside the *Stack*.  
        Change the following settings.  
        ![](images/flutter/FlutterViz_16.png){: width="50%"}  

    - Column  
        Change the following settings.  
        ![](images/flutter/FlutterViz_17.png){: width="25%"}  

    - Title Text  
        The first Text widget.  
        Change the Text content to "Flutter Sample Application".  
        ![](images/flutter/FlutterViz_18.png){: width="25%"}   

    - Subtitle Text  
        The second Text widget.  
        Change the Text content to "Select the button below to view images in different formats.".  
        ![](images/flutter/FlutterViz_19.png){: width="25%"}  

    - "JPG" Text Button     
        The first Text Button wrapped inside the Column.  
        Change the Text content to "JPG".  
        ![](images/flutter/FlutterViz_20.png){: width="25%"}   

    - "GIF" Text Button  
        The second Text Button wrapped inside the Column.  
        Change the Text content to "GIF".Set the button font style to match the first Text Button.  
        ![](images/flutter/FlutterViz_21.png){: width="50%"}  

    After completing all the modifications, your *SelectScreen* will look like this:  
    ![](images/flutter/FlutterViz_22.png){: width="60%"}  

<br>

#### JPGScreen

1. Create a new screen and choose a template to use. 

    Click *+ New Screen* in the top-right corner to create a new screen.  
    ![](images/flutter/FlutterViz_10.png){: width="60%"}  

    Enter a name for your project, as "JPGScreen".  
    Then, go to the *Detail* section and choose *DetailScreen#2* as the template to use.  
    ![](images/flutter/FlutterViz_23.png){: width="40%"}  


2. Delete widgets.  

    After you successfully create SelectScreen, the screen will appear as shown below.  
    ![](images/flutter/FlutterViz_24.png){: width="60%"}  

    In the left-side panel, select the third option, *Tree View*. You will see the widgets listed as shown below.   
    ![](images/flutter/FlutterViz_25.png){: width="60%"}  

    Right-click a widget to display the available options, as shown below (left).  

    Use these options to delete widgets as needed. For this example:  
    - Delete all other widgets and keep only the ones highlighted in the red box (right).   
    ![](images/flutter/FlutterViz_26.png){: width="60%"}   

    After deleting the widgets, your *JPGScreen* will look like this:  
    ![](images/flutter/FlutterViz_27.png){: width="60%"}  


3. Modify the properties of each widget.  

    Modify the widgets starting from the top of the Tree View.  

    Click each widget to display its properties in the right-side panel.  
    Only change the settings shown below, and keep all other properties at their default values.  

    - Stack  
        Change the alignment to "Center".  
        ![](images/flutter/FlutterViz_15.png){: width="25%"}  

    - Column  
        Change the following settings.  
        ![](images/flutter/FlutterViz_17.png){: width="25%"}  

    - Image  
        Change the following settings.   
        ![](images/flutter/FlutterViz_28.png){: width="25%"}   

    - Row  
        Change the following settings.   
        ![](images/flutter/FlutterViz_29.png){: width="25%"}   

    - "JPG" Text  
        Change the following settings.   
        ![](images/flutter/FlutterViz_30.png){: width="25%"}   

    - "Back to Home" Text Button  
        Change the Text content to "Back to Home".    
        ![](images/flutter/FlutterViz_31.png){: width="50%"}  

    After completing all the modifications, your *JPGScreen* will look like this:  
    ![](images/flutter/FlutterViz_32.png){: width="60%"}  

<br>

#### GIFScreen  

For the GIFScreen, repeat the exact same process used for the [JPGScreen](#jpgscreen) or copy the screen from FlutterViz, but replace "JPG" with "GIF" wherever applicable.  

After completing all the modifications, your *JGIFScreen* will look like this:  
![](images/flutter/FlutterViz_33.png){: width="60%"}  



### 1-4. Export the source files

#### Image File Selection Screen

Select each screen using the ![](images/flutter/FlutterViz_77.png){: width="2%"} button on the right, then click the ![](images/flutter/FlutterViz_76.png){: width="2%"} to view the source code.  
![](images/flutter/FlutterViz_34.png){: width="25%"}  

Click the *Download code* button to download the source file for each Screen. The files will be saved as *SelectScreen.dart*, *JPGScreen.dart*, and *GIFScreen.dart*, respectively.     
![](images/flutter/FlutterViz_35.png){: width="60%"}  

<br>


## Step 2: Prepare the Flutter Sample Application Package

!!! success "Tip"
    A Linux PC is required from this step.

### 2-1. Configure the Flutter development environment   

1. Enable the cross-compilation Environment.  

    Before building the Flutter sample application, ensure that the **cross-compilation toolchain** and **cross compiler** are enabled.  

    !!! success "Tip"
        Refer to the <span style="color: var(--renesas-primary-color-fg-blue">*first 2 steps*</span> in [Step 1: Build Sample Applications](../../hmi_applications/#step-1-build-sample-applications).  


2. Verify the installation of Flutter. 

    ```bash
    $OECORE_NATIVE_SYSROOT/usr/share/flutter/sdk/bin/flutter doctor
    ```
    { .dollar }

    !!! success "Tip"
        - `$OECORE_NATIVE_SYSROOT` is an environment variable exported by the toolchain setup script.  
        - If you encounter a “Permission denied” error, fix the file ownership of the SDK installation directory (from <span style="color: var(--renesas-primary-color-fg-blue">*step 1*</span>) by updating it recursively:  

        ```bash
        sudo chown -R <user>:<user> <path-to-sdk>
        ```
        { .dollar }


    If the setup is correct, you should see output similar to the following, with the first two items checked:

    ```bash
    [v] Flutter (Channel stable, 3.27.1, on Ubuntu 22.04.5 LTS 6.8.0-50-generic, locale en_US.UTF-8)
    [v] Linux toolchain - develop for Linux desktop
    [-] VS Code (version 1.96.2)
    [-] Connected device (1 available)
    [-] Network resources
    ```  
    This confirms that Flutter and the Linux toolchain are properly installed.  

3. Disable analytics and CLI animations (recommended).

    To disable analytics reporting:

    ```bash
    $OECORE_NATIVE_SYSROOT/usr/share/flutter/sdk/bin/flutter config --no-analytics
    ```
    { .dollar }

    You should see:

    ```bash
    Analytics reporting disabled.
    ```

    To disable CLI animations:

    ```bash
    $OECORE_NATIVE_SYSROOT/usr/share/flutter/sdk/bin/flutter config --no-cli-animations
    ```
    { .dollar }  

    Expected output:

    ```bash
    Setting "cli-animations" value to "false".
    ```


### 2-2. Create a new Flutter application  

To create the new flutter sample application package:

```bash
flutter create fluttersampleapp
```
{ .dollar } 

Resulting structure:

```bash
fluttersampleapp/
├─ android/
├─ ios/
├─ linux/
├─ macos/
├─ windows/
├─ web/
├─ lib/
│  └─ main.dart
├─ test/
├─ pubspec.yaml
├─ pubspec.lock
├─ analysis_options.yaml
└─ README.md
```

`main.dart` and `pubspec.yaml` are created by default.

!!! success "Tip"
    Unless otherwise specified, **all following steps are performed in the `fluttersampleapp/` directory**.  
    When using commands such as `cd <path-to>/fluttersampleapp/`, replace `<path-to>` with the actual path on your system.  



## Step 3: Update the Flutter Sample Application Package

### 3-1. Apply the display image to sample application  

1. Create a new `images` directory inside `fluttersampleapp`:

    ```bash
    cd <path-to>/fluttersampleapp
    ```
    { .dollar }

    ```bash
    mkdir images
    ```
    { .dollar }

2. Download and copy the display image to the `images` directory you created.  

    [**Click here**](../packages/Display_Image_File.zip) to download `Display_Image_File.zip`, and extract it.  

    Use `scp` to copy *`Cat.jpg`* and *`Moon.gif`* from the *Display_Image_File* folder into `<path-to>/fluttersampleapp/images`.  


### 3-2. Apply the font to the sample application  

1. Create a new `fonts` directory inside `fluttersampleapp`:

    ```bash
    mkdir fonts
    ```
    { .dollar }

2. Download and copy the font files to the `fonts` directory you created.  

    [Download FiraCode font](https://github.com/tonsky/FiraCode) by clicking Download & Install in README.  

    Extract the downloaded *Fira_Code_v6.2.zip*.

    Use `scp` to copy the following files from the *ttf folder* in *Fira_Code_v6.2* into `<path-to>/fluttersampleapp/fonts`:   

        FiraCode-Bold.ttf  
        FiraCode-Light.ttf  
        FiraCode-Medium.ttf  
        FiraCode-Regular.ttf  
        FiraCode-SemiBold.ttf  

### 3-3. Modify the `pubspec.yaml` File  

The `pubspec.yaml` file is the main configuration file of a Flutter project. It defines the application name, version, dependencies (packages), and asset settings such as images and fonts.

Here, modify the dependencies, assets, and fonts sections of the `pubspec.yaml` file.  
[**Click here**](../packages/pubspec_modified.yaml) to download the modified `pubspec.yaml` file, and update your existing file accordingly.    

### 3-4. Apply the downloaded screen source files to the sample application  

1. Modify the `main.dart` File  

    `main.dart` is the entry point of a Flutter application.   

    We keep main.dart simple so it only initializes the app and loads the first screen. All UI design and application logic should be placed in separate screen Dart files.

    [**Click here**](../packages/main_modified.dart) to download the modified `main.dart` file, and update your existing file accordingly.  


2. Update the UI design anfd the navigation logic in the screen dart files.

    Use `scp` to copy the screen source files created in [Step 1](../../flutter_develop-hmi-using-flutterviz/#step-1-create-flutter-applications-using-flutterviz) into `<path-to>/fluttersampleapp/lib/`.  


    There are two main parts that need to be modified:  

    - Navigation Logic

    `Navigator.push()` to go to JPG and GIF screen  
    `Navigator.pop()` to return  
    `SystemNavigator.pop()` to exit application  

    - Wide Screen UI Adjustment  

    Increased font size to 40  
    Increased button size to 400 × 150  
    Centralized all sizes in a new `style.dart`  


    [**Click here**](../packages/screen_dart_files_modified.zip) to download the modified screen dart files, and update your existing file accordingly.   



## Step 4: Build the Flutter Sample Application  

!!! success
    Please make sure you have completed [Step 2-1  Configure the Flutter development environment](../flutter_develop-hmi-using-flutterviz/#2-1-configure-the-flutter-development-environment) before starting the following steps.


1. Upgrade and resolve Flutter packages.

    ```bash
    $OECORE_NATIVE_SYSROOT/usr/share/flutter/sdk/bin/flutter pub upgrade
    ```
    { .dollar }

    The process completes when messages similar to the following appear:

    ```bash
    Changed 47 dependencies!
    27 packages have newer versions incompatible with dependency constraints.
    ```

    Next, enforce the dependency versions defined in the lockfile:

    ```bash
    $OECORE_NATIVE_SYSROOT/usr/share/flutter/sdk/bin/flutter pub get --enforce-lockfile --offline
    ```
    { .dollar }

    Expected output:

    ```bash
    Resolving dependencies...
    Downloading packages...
    Got dependencies!
    ```

2. Clean the Flutter build environment.

    ```bash
    $OECORE_NATIVE_SYSROOT/usr/share/flutter/sdk/bin/flutter clean -v
    ```
    { .dollar }

    When completed successfully, you should see:

    ```bash
    [   +1 ms] Running 1 shutdown hook
    [        ] Shutdown hooks complete
    [        ] exiting with code 0
    ```

3. Build the Flutter assets (fonts, images, and other bundles).

    ```bash
    $OECORE_NATIVE_SYSROOT/usr/share/flutter/sdk/bin/flutter build bundle -v
    ```
    { .dollar }

    A successful build will show messages similar to:

    ```bash
    [ +637 ms] copy_flutter_bundle: Complete
    [ +384 ms] Persisting file store
    [ +3 ms] Done persisting file store
    [ +10 ms] "flutter bundle" took 5,897ms.
    [ +1 ms] Running 1 shutdown hook
    [ ] Shutdown hooks complete
    [ ] exiting with code 0
    ```

4. Build the Flutter sample application (AOT).

    Use the command below to locate your build hash`<Hash>`:

    ```bash
    cd <path-to>/fluttersampleapp
    ```
    { .dollar }

    ```bash
    ls .dart_tool/flutter_build/
    ```
    { .dollar }

    You will see result similar to:  
    ```bash
    bab3a9eb030968554b57b1276c135ddb
    ```

    Run the following command to build the Flutter sample application:

    !!! success "Tip"  
        Replace `bab3a9eb030968554b57b1276c135ddb` with your own build hash.

    ```bash
    $OECORE_NATIVE_SYSROOT/usr/share/flutter/sdk/bin/cache/dart-sdk/bin/dartaotruntime \
    --disable-analytics \
    --disable-dart-dev \
    $OECORE_NATIVE_SYSROOT/usr/share/flutter/sdk/bin/cache/artifacts/engine/linux-x64/frontend_server_aot.dart.snapshot \
    --sdk-root $OECORE_NATIVE_SYSROOT/usr/share/flutter/sdk/bin/cache/artifacts/engine/common/flutter_patched_sdk_product/ \
    --target=flutter \
    -Ddart.vm.profile=false \
    -Ddart.vm.product=true \
    --aot \
    --tfa \
    --target-os linux \
    --packages .dart_tool/package_config.json \
    --output-dill .dart_tool/flutter_build/bab3a9eb030968554b57b1276c135ddb/app.dill \
    --depfile .dart_tool/flutter_build/bab3a9eb030968554b57b1276c135ddb/kernel_snapshot_program.d \
    --source file://$PWD/.dart_tool/flutter_build/dart_plugin_registrant.dart \
    --source package:flutter/src/dart_plugin_registrant.dart \
    -Dflutter.dart_plugin_registrant=file://$PWD/.dart_tool/flutter_build/dart_plugin_registrant.dart \
    --native-assets .dart_tool/flutter_build/bab3a9eb030968554b57b1276c135ddb/native_assets.yaml \
    --verbosity=error \
    package:fluttersampleapp/main.dart
    ```
    { .dollar }

    Once the build completes successfully, the Flutter build configuration is applied, and the following file is generated:

    ```bash
    .dart_tool/flutter_build/bab3a9eb030968554b57b1276c135ddb/app.dill 0
    ```  

5. Update kernel nlob timestamp.

    ```bash
    touch build/flutter_assets/kernel_blob.bin
    ```
    { .dollar }

6. Generate AOT shared library (libapp.so).

    Download `engine_sdk.tar.bz2` from the [Renesas Wiki-Flutter-Deliverables](https://renesas-wiki.atlassian.net/wiki/spaces/REN/pages/77103109/Flutter#Deliverables).    
    Decompress `engine_sdk.tar.bz2`, then unzip `engine_sdk_release.zip` inside it. This will generate the `sdk` directory.  
<br>
    Use `gen_snapshot` from extracted `sdk` to generate the AOT shared library:

    !!! success "Tip"
        - Replace `<path-to>` with your local download path.  
        - Replace `bab3a9eb030968554b57b1276c135ddb` with your own build hash.      

    ```bash
    <path-to>/sdk/clang_x64/gen_snapshot \
    --deterministic \
    --snapshot_kind=app-aot-elf \
    --elf=libapp.so \
    --strip \
    .dart_tool/flutter_build/bab3a9eb030968554b57b1276c135ddb/app.dill

    ```
    { .dollar }

    You will see messages similar to:  

    ```bash
    Warning: Generating ELF library without DWARF debugging information.
    ```  

7. Verify the output architecture.

    Confirm that the generated library targets ARM (aarch64):

    ```bash
    file libapp.so
    ```
    { .dollar }

    Expected output:

    ```bash
    libapp.so: ELF 64-bit LSB shared object, ARM aarch64,version 1 (SYSV), dynamically linked,stripped
    ```

    !!! warning "Notice"
        If the output does not indicate **ARM aarch64** (for example, it shows x86_64), stop here.  
        This means the cross-compilation environment is not correctly applied.    

    !!! success "Tip"
        To recover:

        - Reconfirm that the cross-compilation toolchain is enabled.
        - Verify that the environment is correctly set up and sourced.
        - Clean the Flutter build artifacts and restart from <span style="color: var(--renesas-primary-color-fg-blue">*5. Clean up the build folder of the Flutter project*</span>:  

        ```bash
        rm -rf .dart_tool/flutter_build
        $OECORE_NATIVE_SYSROOT/usr/share/flutter/sdk/bin/flutter clean -v
        ```
        { .dollar }

        - Resume the [Step 4: Build the Flutter Sample Application](../flutter_develop-hmi-using-flutterviz/#step-4-build-the-flutter-sample-application) till <span style="color: var(--renesas-primary-color-fg-blue">*7. Verify the output architecture*</span>.

        

8. Prepare the release directory structure

    Move to the Flutter sample app directory:  

    ```bash
    cd <path-to>/fluttersampleapp
    ```
    { .dollar }

    Create the required release directories:

    ```bash
    install -d my_release/usr/share/flutter/flutter-samples-app/3.27.1/release/data/flutter_assets
    ```
    { .dollar }

    ```bash
    install -d my_release/usr/share/flutter/flutter-samples-app/3.27.1/release/lib
    ```
    { .dollar }

9. Copy the flutter sample application files 

    Next, copy the Flutter sample application files into the directories you created. 

    ```bash
    cd <path-to>/fluttersampleapp
    ```
    { .dollar } 

    Copy the Flutter asset files:

    ```bash
    cp -r build/flutter_assets/* my_release/usr/share/flutter/flutter-samples-app/3.27.1/release/data/flutter_assets
    ```
    { .dollar }

    Copy the generated application library:

    ```bash
    cp libapp.so my_release/usr/share/flutter/flutter-samples-app/3.27.1/release/lib
    ```
    { .dollar }

    Create a symbolic link to the ICU data file:

    ```bash
    ln -sfr my_release/usr/share/flutter/3.27.1/release/data/icudtl.dat my_release/usr/share/flutter/flutter-samples-app/3.27.1/release/data/icudtl.dat
    ```
    { .dollar }

    Create a symbolic link to the Flutter engine library:

    ```bash
    ln -sfr my_release/usr/share/flutter/3.27.1/release/lib/libflutter_engine.so my_release/usr/share/flutter/flutter-samples-app/3.27.1/release/lib/libflutter_engine.so
    ```
    { .dollar }

    After completing the setup, the directory structure under `fluttersampleapp/my_release/usr/share/flutter/flutter-samples-app/3.27.1/release/` should look like the following:  

    ```bash
    .
    ├── data
    │   ├── flutter_assets
    │   │   ├── AssetManifest.bin
    │   │   ├── AssetManifest.json
    │   │   ├── FontManifest.json
    │   │   ├── fonts
    │   │   ├── images
    │   │   ├── isolate_snapshot_data
    │   │   ├── kernel_blob.bin
    │   │   ├── NOTICES.Z
    │   │   ├── packages
    │   │   ├── shaders
    │   │   └── vm_snapshot_data
    │   └── icudtl.dat -> ../../../../3.27.1/release/data/icudtl.dat
    └── lib
        ├── libapp.so
        └── libflutter_engine.so -> ../../../../3.27.1/release/lib/libflutter_engine.so
    ```


    
## Step 5. Deploy the Flutter Sample Application

1.  Insert your SD card into the Linux PC and mount it.

    !!! warning "Notice"
        Make sure to turn off your EVK board before ejecting the SD card.  
        
        To power off the board, execute the `shutdown -h now` command in the terminal. Once the screen turns black, press and hold the power button (red button) for approximately 2 seconds to complete the shutdown process.
        

2.  Copy the executable binary files and resource files to your SD card.
    
    !!! success "Tip"
        - On your Linux PC, the Flutter sample applications are now located at:  
        `<path-to>/fluttersampleapp/my_release/usr/share/flutter/flutter-samples-app/`  
        - We recommend deploying the application to the following directory on your EVK board:   
        `/usr/share/flutter/my-flutter-samples-app/`
        - Follow the instructions in [Step 4 in Option 2](../getting_started/#option-2-for-linux-pc-ubuntu) to check where your SD card is mounted using the `#!bash lsblk` command.  

    Copy the Flutter sample application files:

    ```bash
    cd <path-to>/fluttersampleapp
    ```
    { .dollar }

    ```bash
    sudo cp -r my_release/usr/share/flutter/flutter-samples-app/3.27.1 <sdcard-mount-point>/usr/share/flutter/my-flutter-samples-app/
    ```
    { .dollar }

    !!! warning "Notice"
        - Please make sure the `#!bash /usr/share/flutter/flutter-samples-app` exists on your EVK board or SD card before copying.<br>
        - If it does not exist, create it using:  

        ```bash
        sudo mkdir -p <sdcard-mount-point>/usr/share/flutter/my-flutter-samples-app/
        ```
        { .dollar }

Please refer to [Step 2: Deploy Sample Applications](../../hmi_applications/#step-2-deploy-sample-applications) if you want to deploy over ethernet (using SCP).


## Step 6. Run the Flutter Sample Application

1.  Prepare the necessary equipment and configure the EVK DIP switches by following the instructions in [Hardware Setup](../../hmi_applications/#hardware-setup).

2.  Insert the bootable microSD card created in [Step 4](../flutter_develop-hmi-using-flutterviz/#step-4-deploy-the-flutter-sample-application) into the microSD card slot, and then power on the EVK board.

    !!! success "Tip"
        *  Please refer to the [EVK Peripheral Setup](../../hmi_applications/#evk-peripheral-setup) to locate the microSD card slot based on your selected boot mode.
        *  Press and hold the power button (red button) for 1 second to turn on the EVK board.

3. Use the following command on your EVK board to run the Flutter sample application.

```bash
export LD_PRELOAD=/usr/share/flutter/my-flutter-samples-app/3.27.1/release/lib/libflutter_engine.so
```
{: .hash }  


```bash
flutter-client -f -b /usr/share/flutter/my-flutter-samples-app/3.27.1/release/
```
{: .hash }

The launched sample application is shown below.  
Image File Selection Screen  
![](images/flutter/Selection.png){: width="60%"}  

Click the JPEG button, you will get:
Image File Display Screen-JPG display
![](images/flutter/JPG_Display.png){: width="60%"}  

Click the GIF button, you will get:
Image File Display Screen-GIF display
![](images/flutter/GIF_Display.png){: width="60%"}  

<br>

Once you have successfully tried this simple Flutter sample application, you’re ready to start designing your own Flutter applications.
