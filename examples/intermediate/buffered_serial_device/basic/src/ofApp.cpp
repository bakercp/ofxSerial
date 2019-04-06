//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//

#include "ofApp.h"


void ofApp::setup()
{
    // 1. Upload the HaikuGenerator.ino sketch (in this example's Arduino/
    //    folder) to an Arduino board.
    // 2. Check the "getDevices" call below to make sure the correct serial
    //    device is connected. This works with OSX but may require a different
    //    port name for Linux or Windows.
    // 3. Run this app.

    ofEnableAlphaBlending();

    auto deviceDescriptors = ofx::IO::SerialDeviceUtils::listDevices();

    if (!deviceDescriptors.empty())
    {
        ofLogNotice("ofApp::setup") << "Connected Devices: ";
        for (auto deviceDescriptor: deviceDescriptors)
        {
            ofLogNotice("ofApp::setup") << "\t" << deviceDescriptor;
        }

        // Choose a device.
        auto deviceDescriptor = deviceDescriptors[0];
        
        // Connect to the first matching device.
        bool success = device.setup(deviceDescriptor, 115200);

        if (success)
        {
            device.registerAllEvents(this);
            ofLogNotice("ofApp::setup") << "Successfully setup " << deviceDescriptor;
        }
        else
        {
            ofLogNotice("ofApp::setup") << "Unable to setup " << deviceDescriptor;
        }
    }
    else
    {
        ofLogNotice("ofApp::setup") << "No devices connected.";
    }
}

void ofApp::exit()
{
    device.unregisterAllEvents(this);
}


void ofApp::draw()
{
    ofBackground(0);

    ofSetColor(255);

    std::stringstream ss;

    ss << "         FPS: " << ofGetFrameRate() << std::endl;
    ss << "Connected to: " << device.port();

    ofDrawBitmapString(ss.str(), ofVec2f(20, 20));

    int x = 20;
    int y = 50;
    int height = 20;

    auto iter = serialMessages.begin();

    // Cycle through each of our messages and delete those that have expired.
    while (iter != serialMessages.end())
    {
        iter->fade -= 1;

        if (iter->fade < 0)
        {
            iter = serialMessages.erase(iter);
        }
        else
        {
            ofSetColor(255, ofClamp(iter->fade, 0, 255));
            ofDrawBitmapString(iter->message, ofVec2f(x, y));

            y += height;

            if (!iter->exception.empty())
            {
                ofSetColor(255, 0, 0, ofClamp(iter->fade, 0, 255));
                ofDrawBitmapString(iter->exception, ofVec2f(x + height, y));
                y += height;
            }

            ++iter;
        }
    }
}


void ofApp::onSerialBuffer(const ofxIO::SerialBufferEventArgs& args)
{
    // Buffers will show up here when the marker character is found.
    SerialMessage message(args.buffer().toString(), "", 500);
    serialMessages.push_back(message);
}

void ofApp::onSerialError(const ofxIO::SerialBufferErrorEventArgs& args)
{
    // Errors and their corresponding buffer (if any) will show up here.
    SerialMessage message(args.buffer().toString(),
                          args.exception().displayText(),
                          500);
    serialMessages.push_back(message);
}
