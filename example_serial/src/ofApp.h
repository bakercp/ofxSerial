#pragma once


#include "ofMain.h"
#include "ofxSerial.h"


using ofx::IO::SerialDevice;


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

    SerialDevice device;

};
