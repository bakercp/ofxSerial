// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


void ofApp::setup()
{

    std::vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::getDevices("/dev/cu.NoZAP-PL2303.*");

    devices = std::vector<ofx::IO::SerialDevice>(devicesInfo.size());

    for(std::size_t i = 0; i < devices.size(); ++i)
    {
        bool success = devices[i].setup(devicesInfo[i],
                                        38400,
                                        ofx::IO::SerialDevice::DATA_BITS_EIGHT,
                                        ofx::IO::SerialDevice::PAR_NONE,
                                        ofx::IO::SerialDevice::STOP_ONE);

        if(success)
        {
            ofLogNotice("ofApp::setup") << "Successfully setup " << devicesInfo[i];
        }
        else
        {
            ofLogNotice("ofApp::setup") << "Unable to setup " << devicesInfo[i];
        }
    }
}


void ofApp::update()
{
}


void ofApp::draw()
{
    int xOffset = 200;
    int yOffset = 100;

    int x = 20;
    int y = 20;

    int tab = 8;

    if (!devices.empty())
    {
        for(std::size_t i = 0; i < devices.size(); ++i)
        {
            std::stringstream ss;

            ss << std::setw(tab) << "NAME: " << devices[i].getPortName() << endl;
            ss << std::setw(tab) <<  "DSR: " << devices[i].isDataSetReady() << endl;
            ss << std::setw(tab) <<  "CTS: " << devices[i].isClearToSend() << endl;
            ss << std::setw(tab) <<  " CD: " << devices[i].isCarrierDetected() << endl;
            ss << std::setw(tab) <<  " RI: " << devices[i].isRingIndicated();

            ofDrawBitmapStringHighlight(ss.str(), ofVec2f(x, y));

            if(yOffset > ofGetWidth() - 100)
            {
                x = 20;
                y += yOffset;
            }
            else
            {
                x += xOffset;
            }
        }
    }
    else
    {
        ofDrawBitmapStringHighlight("No printers connected.", ofVec2f(x, y));
    }
}


void ofApp::keyPressed(int key)
{
    if (' ' == key)
    {
       for(std::size_t i = 0; i < devices.size(); ++i)
       {    
            std::string message = "Testing device " + ofToString(i) + " " + devices[i].getPortName() + "\n";

            devices[i].writeBytes((const uint8_t*)message.c_str(), message.length());
       }
    }
}
