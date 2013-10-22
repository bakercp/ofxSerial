// =============================================================================
//
// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{

   // ofSerial serial;

    pConfig = new SerialConfig("/dev/tty.PL2303-00001014",
                               SerialConfig::BPS_38400);


//    SerialConfig config("/dev/ttyUSB0",SerialConfig::BPS_38400);

    cout << "XXX: " << pConfig->getName() << endl;

    try
    {
        pChannel = new SerialChannel(pConfig);
        pChannel->setBlocking();

//    channel.open();

//    channel.write(1);
        for(int i = 0; i < 1; i++) {
        pChannel->write("Hello world!\n");
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
    pChannel->write("Key Pressed!\n");
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
