//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    // 1. Upload the SLIPPacketSerialReverseEcho.ino sketch (in this example's
    //    Arduino/ folder) to an Arduino board.  This sketch requires
    //    the Arduino PacketSerial library https://github.com/bakercp/PacketSerial.
    // 2. Check the "listDevices" call below to make sure the correct serial
    //    device is connected.
    // 3. Run this app.

    ofEnableAlphaBlending();

    std::vector<ofxIO::SerialDeviceInfo> devicesInfo = ofxIO::SerialDeviceUtils::listDevices();

    ofLogNotice("ofApp::setup") << "Connected Devices: ";

    for (std::size_t i = 0; i < devicesInfo.size(); ++i)
    {
        ofLogNotice("ofApp::setup") << "\t" << devicesInfo[i];
    }

    if (!devicesInfo.empty())
    {
        // Connect to the first matching device.
        bool success = device.setup(devicesInfo[0], 115200);

        if(success)
        {
            device.registerAllEvents(this);
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

void ofApp::exit()
{
    device.unregisterAllEvents(this);
}


void ofApp::update()
{
    // Create a byte buffer.
    ofxIO::ByteBuffer buffer("Frame Number: " + ofToString(ofGetFrameNum()));

    // Send the byte buffer.
    // ofxIO::PacketSerialDevice will encode the buffer, send it to the
    // receiver, and send a packet marker.
    device.send(buffer);

    // ofLogNotice("update") << "sending : " << buffer;
}


void ofApp::draw()
{
    ofBackground(0);

    ofSetColor(255);

    std::stringstream ss;

    ss << "         FPS: " << ofGetFrameRate() << std::endl;
    ss << "Connected to: " << device.port();

    ofDrawBitmapString(ss.str(), ofVec2f(20, 20));

    std::vector<SerialMessage>::iterator iter = serialMessages.begin();

    int x = 20;
    int y = 50;
    int height = 20;

    while (iter != serialMessages.end())
    {
        iter->fade -= 20;

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
    // Decoded serial packets will show up here.
    SerialMessage message;
    message.message = args.buffer().toString();
    serialMessages.push_back(message);

    // ofLogNotice("onSerialBuffer") << "got serial buffer : " << message.message;
}


void ofApp::onSerialError(const ofxIO::SerialBufferErrorEventArgs& args)
{
    // Errors and their corresponding buffer (if any) will show up here.
    SerialMessage message;
    message.message = args.buffer().toString();
    message.exception = args.exception().displayText();
    message.fade = 500;
    serialMessages.push_back(message);

    ofLogNotice("onSerialError") << "got serial error : " << message.exception;
}
