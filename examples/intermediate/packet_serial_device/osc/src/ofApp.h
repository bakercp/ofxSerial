#pragma once


#include "ofMain.h"
#include "ofxSerial.h"
#include "ofxOsc.h"


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void draw() override;

    void keyPressed(int key) override;

    void onOscMessage(const ofxOscMessage& message);
    void onSerialError(const ofxIO::SerialBufferErrorEventArgs& error);

    bool state = false;

    ofxIO::OSCSerialDevice device;

    ofEventListener onOscMessageListener;
    ofEventListener onSerialErrorListener;

};
