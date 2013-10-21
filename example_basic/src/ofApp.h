#pragma once


#include "ofMain.h"
#include "Poco/Platform.h"
#include "Poco/DeviceIO/Serial/SerialChannel.h"


using Poco::DeviceIO::Serial::SerialConfig;
using Poco::DeviceIO::Serial::SerialChannel;


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    

    std::shared_ptr<SerialChannel> channel;

};
