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


//------------------------------------------------------------------------------
void ofApp::setup()
{

    std::vector<SerialDeviceInfo> devicesInfo = SerialDeviceUtils::getDevices("/dev/tty.PL2303.*");

    devices = std::vector<SerialDevice>(devicesInfo.size());

    for(std::size_t i = 0; i < devices.size(); ++i)
    {
        bool success = devices[i].setup(devicesInfo[i],
                                        115200,
                                        SerialDevice::DATA_BITS_EIGHT,
                                        SerialDevice::PAR_NONE,
                                        SerialDevice::STOP_ONE,
                                        SerialDevice::FLOW_CTRL_HARDWARE);

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

//------------------------------------------------------------------------------
void ofApp::update()
{
//    while(device.available() > 0)
//    {
//        uint8_t array[1024];
//
//        std::size_t n = device.readBytes(array, 1024);
//
//        for(std::size_t i = 0; i < n; ++i)
//        {
//            cout << array[i];
//        }
//    }
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    int xOffset = 20;
    int yOffset = 20;

    int tab = 20;

//    for(std::size_t i = 0; i < devices.size(); ++i)
//    {
//        std::stringstream ss;
//
//        ss << std::setw(tab) << "NAME: " << devices[i].getPortName() << endl;
//        ss << std::setw(tab) <<  "DSR: " << devices[i].isDataSetReady() << endl;
//        ss << std::setw(tab) <<  "CTS: " << devices[i].isClearToSend() << endl;
//        ss << std::setw(tab) <<  " CD: " << devices[i].isCarrierDetected() << endl;
//        ss << std::setw(tab) <<  " RI: " << devices[i].isRingIndicated() << endl;
//
//        ofDrawBitmapStringHighlight(ss.str(), ofPoint(xOffset, yOffset));
//
//        if(yOffset > ofGetWidth() - 100)
//        {
//            xOffset = 0;
//            yOffset += 100;
//        }
//    }


}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
//
//    if('d' == key)
//    {
//        dtr = !dtr;
//        device.setDataTerminalReady(dtr);
//
//    }
//    else if('r' == key)
//    {
//        cout << "R IN HERE" << endl;
//        rts = !rts;
//        device.setRequestToSend(rts);
//    }
//
//    if('h' == key)
//    {
//        cout << "h" << endl;
//        device.writeBytes("Hello world\n\n\n\n\n");
//    }
//
//    if(' ' == key)
//    {
//        {
//device.setDataTerminalReady(false);            
//uint8_t command[3] = { 0x1d, 0x49, 0x44 };
//            std::size_t numBytesWritten = device.writeBytes(command,3);
//            cout << "BW = " << numBytesWritten << endl;
//    device.setDataTerminalReady(true);
//       }
//    }
}
