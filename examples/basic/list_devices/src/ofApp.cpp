//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofLogNotice("ofApp::setup") << "Connected Devices: ";

    for (auto& device: ofxIO::SerialDeviceUtils::listDevices())
    {
        ofLogNotice("ofApp::setup") << "\t" << device;
    }
}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("See Console.", glm::vec2(70, 30));
}
