#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{


    // port, baudrate, timeout in milliseconds
    serial = std::shared_ptr<serial::Serial>(new serial::Serial("/dev/tty.PL2303-0030121A",
                                                                9600));//
//                          serial::Timeout::simpleTimeout(10),
//                            serial::eightbits,
//                          serial::parity_none,
//                          serial::stopbits_one,
//                          serial::flowcontrol_hardware)
//                                             );



//    serial->setFlowcontrol(serial::flowcontrol_software);
    serial->setDTR(); 
    serial->setRTS();


}

//------------------------------------------------------------------------------
void ofApp::update()
{
    while(serial->available() > 0)
    {
        uint8_t array[1024];

        std::size_t n = serial->read(array, 1024);

        for(std::size_t i = 0; i < n; ++i)
        {
            cout << array[i];
        }


    }
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    stringstream ss;

    ss << "DSR: " << serial->getDSR() << endl;
    ss << "CTS: " << serial->getCTS() << endl;
    ss << " CD: " << serial->getCD() << endl;
    ss << " RI: " << serial->getRI() << endl;

    ofDrawBitmapStringHighlight(ss.str(), ofPoint(20,20));



}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{


    if('h' == key)
    {
        cout << "h" << endl;
        serial->write("Hello world\n\n\n\n\n");
    }

    if(' ' == key)
    {

        cout << "SPB" << endl;
//        uint8_t command[3] = { 29 , 73 , 1 };
//        std::size_t numBytesWritten = serial->write(command,3);
//        cout << "BW = " << numBytesWritten << endl;

        uint8_t command[3] = { 0x1d, 0x49, 0x44 };
        std::size_t numBytesWritten = serial->write(command,3);
        cout << "BW = " << numBytesWritten << endl;



    }


}

//------------------------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//------------------------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//------------------------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
