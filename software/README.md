# Tracker M8 Keyboard Software

# Overview
This is source code for RP2040 keyboard HID implementation. You wouldn't need to build this source file yourself. Pre-built firmware is available for easy flashing.


# Steps for flashing M8 tracker keyboard firmware:
## For Most Users:
- Download single firmware `pico-m8-keyboard.uf2` file from the `Release` Folder
- "Press and Hold" the `Boot` button on the RP2040 board, and connect the usb to your PC, then release `Boot` button.
- A disk will showup or mounted. It means you RP2040 is in boot-loader mode and ready to load firmware.
- Simply drag and drop the `pico-m8-keyboard.urf` firmware file to the mounted disk.
- RP2040 will then unmount and reboot itself to new firmware

That simple!


## Developer:
- Follow quick start guide from Raspberry PI RP2040 documentation. 
- Install Pico SDK base on your system environment.
  
```shell
git submodule update

# make sure PICO_SDK is installed and sourced in your environment
cd src && mkdir ./build && cd build
cmake ..
ninja # builds elf/bin/uf2 firmware into same folder
```


## Q&A
### How is it different than MicroPython version?
- This is implemented in C++. Compare to MicroPython's interrupt language This offers even lower input latency!
- One firmware file only, simple upload
- No more annoying disk pop-up everytime  when the device is connected 