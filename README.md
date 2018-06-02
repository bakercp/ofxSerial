ofxSerial
=========

Description
-----------

A cross-platform serial addon for openFrameworks wrapping the [Serial Communication Library](https://github.com/wjwwood/serial).

Features
--------

-   Full Port configuration via [SerialDevice](https://github.com/bakercp/ofxSerial/blob/master/libs/ofxSerial/include/ofx/IO/SerialDevice.h)
    -   baud rate
    -   data bits
    -   parity
    -   stop bits
-   Full Flow Control
    -   CTS get / set
    -   DSR get / set
    -   RI get / set
    -   CD get / set
-   Read/write blocking control via custom timeouts.
-   Event-driven serial via [BufferedSerial](https://github.com/bakercp/ofxSerial/blob/master/libs/ofxSerial/include/ofx/IO/BufferedSerialDevice.h) class.
-   Packet-based serial system with byte stuffing via [PacketSerialDevice](https://github.com/bakercp/ofxSerial/blob/master/libs/ofxSerial/include/ofx/IO/PacketSerialDevice.h)
    -   SLIP, COBS and others packet encoding supported.
-   Cross-platform compatibility.
    -   Tested on:
        -   OSX
        -   Windows Visual Studio
        -   Windows Codeblocks / MinGW / MSYS
        -   Linux
-   Robust Cross-platform port listing.

-   Arduino Examples for sanity testing.
Required Addons
---------------

-   ofxPoco (included in openFrameworks)
-   [ofxIO](https://github.com/bakercp/ofxIO)

Getting Started
---------------

To get started, generate the example project files using the openFrameworks [Project Generator](http://openframeworks.cc/learning/01_basics/how_to_add_addon_to_project/).

Documentation
-------------

API documentation can be found here.

Build Status
------------

Linux, macOS [![Build Status](https://travis-ci.org/bakercp/ofxSerial.svg?branch=master)](https://travis-ci.org/bakercp/ofxSerial)

Visual Studio, MSYS [![Build status](https://ci.appveyor.com/api/projects/status/6ekkxmpkinwtv9j4/branch/master?svg=true)](https://ci.appveyor.com/project/bakercp/ofxserial/branch/master)

Compatibility
-------------

The `stable` branch of this repository is meant to be compatible with the openFrameworks [stable branch](https://github.com/openframeworks/openFrameworks/tree/stable), which corresponds to the latest official openFrameworks release.

The `master` branch of this repository is meant to be compatible with the openFrameworks [master branch](https://github.com/openframeworks/openFrameworks/tree/master).

Some past openFrameworks releases are supported via tagged versions, but only `stable` and `master` branches are actively supported.

Versioning
----------

This project uses Semantic Versioning, although strict adherence will only come into effect at version 1.0.0.

Licensing
---------

See [LICENSE.md](LICENSE.md).

Contributing
------------

Check out the [Help Wanted](https://github.com/bakercp/ofxSerial/issues?q=is%3Aissue+is%3Aopen+label%3A%22help+wanted%22) tag in the issues section for specific ideas or propose your own new ideas.

Pull Requests are always welcome, so if you make any improvements please feel free to float them back upstream :)

1.  Fork this repository.
2.  Create your feature branch (`git checkout -b my-new-feature`).
3.  Commit your changes (`git commit -am 'Add some feature'`).
4.  Push to the branch (`git push origin my-new-feature`).
5.  Create new Pull Request.
