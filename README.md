# cangaroo hardware filtering demo

![](doc/screenshot.jpg) 

This is a demo of adding [hardware filtering](https://github.com/koendv/canfilter) to cangaroo on linux. Requires candlelight [usb-to-can adapters with support for hardware filtering](https://github.com/marckleinebudde/candleLight_fw/tree/can-hw-filter).

To build:
```
mkdir build
cd build
qmake ..
make
./bin/cangaroo
```
