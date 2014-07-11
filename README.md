ofxSerial
=========

A serial addon for openFrameworks.

## Features
- Full Port configuration via [SerialDevice](https://github.com/bakercp/ofxSerial/blob/master/libs/ofxSerial/include/ofx/IO/SerialDevice.h)
  - baud rate
  - data bits
  - parity
  - stop bits
- Full Flow Control
  - CTS get / set
  - DSR get / set
  - RI get / set
  - CD get / set
- Read/write blocking control via custom timeouts.
- Event-driven serial via [BufferedSerial](https://github.com/bakercp/ofxSerial/blob/master/libs/ofxSerial/include/ofx/IO/BufferedSerialDevice.h) class.
- Packet-based serial system with byte stuffing via [PacketSerialDevice](https://github.com/bakercp/ofxSerial/blob/master/libs/ofxSerial/include/ofx/IO/PacketSerialDevice.h)
- Cross-platform compatibility.
  - Tested on: 
    - OSX
    - Windows Visual Studio
    - Windows Codeblocks / MinGW
    - Linux
- Robust Cross-platform port listing.

- Arduino Examples for sanity testing.

## Requirements
- https://github.com/bakercp/ofxIO

## Built With
- https://github.com/wjwwood/serial
