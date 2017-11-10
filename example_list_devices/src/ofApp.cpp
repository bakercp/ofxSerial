//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//

#include "ofApp.h"


void ofApp::setup()
{
    ofLogNotice("ofApp::setup") << "Connected Devices: ";

    for (auto& device : ofx::IO::SerialDeviceUtils::listDevices())
    {
        ofLogNotice("ofApp::setup") << "\t" << device;
    }
}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("See Console.", ofVec2f(70, 30));
}
