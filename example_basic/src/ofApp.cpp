#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{

    ofSerial serial;

    // SerialConfig config("/dev/tty.PL2303-00002014",SerialConfig::BPS_38400);

    SerialConfig config("/dev/ttyUSB0",SerialConfig::BPS_38400);

    cout << "XXX: " << config.getName() << endl;

    try
    {
        channel = std::shared_ptr<SerialChannel>(new SerialChannel(&config));
        channel->setBlocking();

//    channel.open();

//    channel.write(1);
        for(int i = 0; i < 1; i++) {
        channel->write("Hello world!\n");
//        channel.write("Hello world!\n");
//        channel.write("Hello world!\n");
//        channel.write("Hello world!\n");
//        channel.write("Hello world!\n");
//        channel.write("Hello world!\n");
//        channel.write("Hello world!\n");
//        channel.write("Hello world!\n");
//        channel.write("Hello world!\n");
//        channel.write("Hello world!\n");
//        channel.write("Hello world!\n");
//        channel.write("Hello world!\n");
//        channel.write("Hello world!\n");
//        channel.write("Hello world!\n");
//        channel.write("Hello world!\n");
        }


//    channel.close();
    }
    catch (Poco::Exception& ex)
    {
        cout << ex.what() << endl;

    }


}

//------------------------------------------------------------------------------
void ofApp::update()
{
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    channel->write("Key Pressed!\n");
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
