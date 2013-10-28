#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{


    string name = "/dev/tty.PL2303-00002014";

    device.setup(name, 9600);
    device.setDataTerminalReady(true);
    device.setRequestToSend(true);
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    while(device.available() > 0)
    {
        uint8_t array[1024];

        std::size_t n = device.readBytes(array, 1024);

        for(std::size_t i = 0; i < n; ++i)
        {
            cout << array[i];
        }
    }
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    std::stringstream ss;

    ss << "DSR: " << device.isDataSetReady() << endl;
    ss << "CTS: " << device.isClearToSend() << endl;
    ss << " CD: " << device.isCarrierDetected() << endl;
    ss << " RI: " << device.isRingIndicated() << endl;

    ofDrawBitmapStringHighlight(ss.str(), ofPoint(20,20));
}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{


    if('h' == key)
    {
        cout << "h" << endl;
        device.writeBytes("Hello world\n\n\n\n\n");
    }

    if(' ' == key)
    {
        {
            cout << "SPB" << endl;
            uint8_t command[3] = { 29 , 73 , 1 };
            std::size_t numBytesWritten = device.writeBytes(command,3);
            cout << "BW = " << numBytesWritten << endl;
        }
        {
            uint8_t command[3] = { 0x1d, 0x49, 0x44 };
            std::size_t numBytesWritten = device.writeBytes(command,3);
            cout << "BW = " << numBytesWritten << endl;
        }
    }
}
