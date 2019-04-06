#pragma once


#include "ofMain.h"
#include "ofxSerial.h"
#include "ofxOsc.h"


class ofApp : public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;

    void mousePressed(ofMouseEventArgs& mouse);

    int state = 0;

    void onSerialBuffer(const ofxIO::SerialBufferEventArgs& args);
    void onSerialError(const ofxIO::SerialBufferErrorEventArgs& args);

    ofxIO::SLIPPacketSerialDevice device;

private:
    void appendMessage( ofxOscMessage& message, osc::OutboundPacketStream& p );

};
