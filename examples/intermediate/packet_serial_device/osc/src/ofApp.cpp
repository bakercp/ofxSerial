//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
// Copyright (c) 2016 Antoine Villeret
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"

// example_SLIP-OSC.cpp
// This app send SLIP encoded OSC data over USB to switch an LED on and off.
//
// 1. Upload the SLIP-OSC.ino sketch (in this example's
//    Arduino/ folder) to an Arduino board.  This sketch requires
//    the Arduino PacketSerial library https://github.com/bakercp/PacketSerial.
// 2. Check the "listDevices" call below to make sure the correct serial
//    device is connected.
// 3. Run this app.
// 4. Click on the app window to send OSC.

void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);

    ofEnableAlphaBlending();

    auto devicesInfo = ofxIO::SerialDeviceUtils::listDevices();

    ofLogNotice("ofApp::setup") << "Connected Devices: ";

    for (auto& device: devicesInfo) ofLogNotice("ofApp::setup") << "\t" << device;

    if (!devicesInfo.empty())
    {
        // Connect to the first matching device.
        bool success = device.setup(devicesInfo[0], 115200);

        if(success)
        {
            device.onOscMessage.newListener(this, &ofApp::onOscMessage);
            device.onSerialError.newListener(this, &ofApp::onSerialError);

            ofLogNotice("ofApp::setup") << "Successfully setup " << devicesInfo[0];
        }
        else
        {
            ofLogNotice("ofApp::setup") << "Unable to setup " << devicesInfo[0];
        }
    }
    else
    {
        ofLogNotice("ofApp::setup") << "No devices connected.";
    }
}


void ofApp::draw()
{
    ofBackground(state ? 255 : 0, state ? 255 : 0, 0);
}


void ofApp::keyPressed(int key)
{
    state = !state;

    ofxOscMessage m;
    m.setAddress("/led");
    m.addInt32Arg(state);

    device.send(m);
}


void ofApp::onOscMessage(const ofxOscMessage& message)
{
    ofLog() << "Got OSC Message: " << message;
}

void ofApp::onSerialError(const ofxIO::SerialBufferErrorEventArgs& error)
{
    ofLogError() << "Got OSC Error: " << error.exception().displayText();
}
