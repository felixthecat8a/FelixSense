# FelixSense

A lightweight Arduino library for analog sensors with photoresistors, thermistors, and potentiometers.

## Installation

### Install via ZIP file

1. ~~Download the *.zip* file of the [latest release](https://github.com/felixthecat8a/FelixSense/releases/latest/).~~

1. Click the `<>Code` button and select *Download ZIP* to  download the *.zip* file.
2. In the **Arduino IDE**, go to ***Sketch > Include Library > Add .ZIP Library...***.
3. Select the downloaded *.zip* file.

### Updating the Library

To update the library:
1. Go to ***Documents > Arduino > libraries > FelixSense*** to and delete the existing ***FelixSense*** folder from your *libraries* directory.
2. Follow the installation steps above to install the latest version.

### Add to PlatformIO Project

Add the following to the project's `platformio.ini` file:
```
lib_deps =
    https://github.com/felixthecat8a/FelixSense.git
```
