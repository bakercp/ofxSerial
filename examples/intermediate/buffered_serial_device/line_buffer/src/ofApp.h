//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofMain.h"
#include "ofxSerial.h"


class SerialMessage
{
public:
    SerialMessage(): fade(0)
    {
    }

    SerialMessage(const std::string& _message,
                  const std::string& _exception,
                  int _fade):
        message(_message),
        exception(_exception),
        fade(_fade)
    {
    }

    std::string message;
    std::string exception;
    int fade;
};


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void draw() override;
    void exit() override;

    void onSerialBuffer(const ofxIO::SerialBufferEventArgs& args);
    void onSerialError(const ofxIO::SerialBufferErrorEventArgs& args);

    ofxIO::BufferedSerialDevice device;

    std::vector<SerialMessage> serialMessages;

};
