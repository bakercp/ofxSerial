#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    SerialConfig config("/dev/tty.PL2303-00002014",SerialConfig::BPS_38400);

    cout << "XXX: " << config.getName() << endl;

    try
    {
    SerialChannel channel(&config);

//    channel.open();

    channel.write("Hello world!\n");
    channel.write("Hello world!\n");
    channel.write("Hello world!\n");
    channel.write("Hello world!\n");
    channel.write("Hello world!\n");
    channel.write("Hello world!\n");


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
