//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofMain.h"
#include "ofxSerial.h"


struct SerialMessage
{
    std::string message;
    std::string exception;
    int fade = 255;
};


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void exit();

    void onSerialBuffer(const ofxIO::SerialBufferEventArgs& args);
    void onSerialError(const ofxIO::SerialBufferErrorEventArgs& args);

    ofxIO::PacketSerialDevice device;

    std::vector<SerialMessage> serialMessages;

};
