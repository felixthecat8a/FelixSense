# FelixSense

<!-- ![GitHub Release](https://img.shields.io/github/v/release/felixthecat8a/FelixSense?color=00878F&logo=arduino&logoColor=00878F) -->
[![License: MIT](https://img.shields.io/github/license/felixthecat8a/FelixSense)](https://opensource.org/licenses/MIT)
![GitHub repo size](https://img.shields.io/github/repo-size/felixthecat8a/FelixSense)
![GitHub repo file or directory count](https://img.shields.io/github/directory-file-count/felixthecat8a/FelixSense)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/felixthecat8a/FelixSense?color=00599C)
![GitHub top language](https://img.shields.io/github/languages/top/felixthecat8a/FelixSense?color=00599C&logo=cplusplus&logoColor=00599C)

<!-- Workflows -->
![Check Arduino](https://github.com/felixthecat8a/FelixSense/actions/workflows/check-arduino.yml/badge.svg)
![Compile Examples](https://github.com/felixthecat8a/FelixSense/actions/workflows/compile-examples.yml/badge.svg)
![Spell Check](https://github.com/felixthecat8a/FelixSense/actions/workflows/spell-check.yml/badge.svg)

<!-- GitHub Activity -->
![GitHub Created At](https://img.shields.io/github/created-at/felixthecat8a/FelixSense)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/felixthecat8a/FelixSense)
![GitHub last commit](https://img.shields.io/github/last-commit/felixthecat8a/FelixSense)
<!-- ![GitHub Release Date](https://img.shields.io/github/release-date/felixthecat8a/FelixSense) -->
<!-- ![GitHub commits since latest release](https://img.shields.io/github/commits-since/felixthecat8a/FelixSense/latest) -->


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
