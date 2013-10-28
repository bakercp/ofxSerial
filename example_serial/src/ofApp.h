#pragma once


#include "ofMain.h"
#include "ofxSerial.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

    ofx::IO::SerialDevice device;

};
