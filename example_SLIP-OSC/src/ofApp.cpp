// =============================================================================
//
// Copyright (c) 2014 Christopher Baker <http://christopherbaker.net>
// 2016 - Antoine Villeret
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

// example_SLIP-OSC.cpp
// This app send SLIP encoded OSC data over USB to switch an LED on and off.
//
// 1. Upload the SLIP-OSC.ino sketch (in this example's
//    Arduino/ folder) to an Arduino board.  This sketch requires
//    the Arduino PacketSerial library https://github.com/bakercp/PacketSerial.
// 2. Check the "listDevices" call below to make sure the correct serial
//    device is connected.
// 3. Run this app.
// 4. Click on the app window to send OSC

void ofApp::setup()
{
    state=false;
    ofSetLogLevel(OF_LOG_VERBOSE);


    ofEnableAlphaBlending();

    std::vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();

    ofLogNotice("ofApp::setup") << "Connected Devices: ";

    for (std::size_t i = 0; i < devicesInfo.size(); ++i)
    {
        ofLogNotice("ofApp::setup") << "\t" << devicesInfo[i];
    }

    if (!devicesInfo.empty())
    {
        // Connect to the first matching device.
        bool success = device.setup(devicesInfo[0], 115200);

        if(success)
        {
            device.registerAllEvents(this);
            ofLogNotice("ofApp::setup") << "Successfully setup " << devicesInfo[0];
        }
        else
        {
            ofLogNotice("ofApp::setup") << "Unable to setup " << devicesInfo[0];
        }
    }
    else
    {
        ofLogNotice("ofApp::setup") << "No devices connected.";
    }
}

void ofApp::exit()
{
    device.unregisterAllEvents(this);
}


void ofApp::update()
{
    // Create a byte buffer.
    ofx::IO::ByteBuffer buffer("Frame Number: " + ofToString(ofGetFrameNum()));

    // Send the byte buffer.
    // ofx::IO::PacketSerialDevice will encode the buffer, send it to the
    // receiver, and send a packet marker.
    device.send(buffer);

    // ofLogNotice("update") << "sending : " << buffer;

    // ofxOsc::OscBunble bundle;
}


void ofApp::draw()
{
    ofBackground(state*255);

    ofSetColor(255);

    std::stringstream ss;

    ss << "         FPS: " << ofGetFrameRate() << std::endl;
    ss << "Connected to: " << device.getPortName();

    ofDrawBitmapString(ss.str(), ofVec2f(20, 20));

    std::vector<SerialMessage>::iterator iter = serialMessages.begin();

    int x = 20;
    int y = 50;
    int height = 20;

    while (iter != serialMessages.end())
    {
        iter->fade -= 20;

        if (iter->fade < 0)
        {
            iter = serialMessages.erase(iter);
        }
        else
        {
            ofSetColor(255, ofClamp(iter->fade, 0, 255));
            ofDrawBitmapString(iter->message, ofVec2f(x, y));

            y += height;

            if (!iter->exception.empty())
            {
                ofSetColor(255, 0, 0, ofClamp(iter->fade, 0, 255));
                ofDrawBitmapString(iter->exception, ofVec2f(x + height, y));
                y += height;
            }

            ++iter;
        }
    }
}

void ofApp::mousePressed(ofMouseEventArgs& mouse){
    // invert state flag on mouseClick;
    state = 1-state;

    ofxOscMessage m;
    m.setAddress("/led");
    m.addInt32Arg(state);

    // sender.sendMessage(m);
    // this code come from ofxOscSender::sendMessage in ofxOscSender.cpp
    static const int OUTPUT_BUFFER_SIZE = 8192;
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );

    // serialise the message
    bool wrapInBundle = true;
    if(wrapInBundle) p << osc::BeginBundleImmediate;
    appendMessage( m, p );
    if(wrapInBundle) p << osc::EndBundle;

    ofx::IO::SLIPEncoding slip;
    ofx::IO::ByteBuffer original(p.Data(),p.Size());

    device.send(original);

    ofx::IO::ByteBuffer encoded;
    slip.encode(original, encoded);
}


void ofApp::onSerialBuffer(const ofx::IO::SerialBufferEventArgs& args)
{
    // Decoded serial packets will show up here.
    SerialMessage message(args.getBuffer().toString(), "", 255);
    serialMessages.push_back(message);

    // ofLogNotice("onSerialBuffer") << "got serial buffer : " << message.message;
}


void ofApp::onSerialError(const ofx::IO::SerialBufferErrorEventArgs& args)
{
    // Errors and their corresponding buffer (if any) will show up here.
    SerialMessage message(args.getBuffer().toString(),
                          args.getException().displayText(),
                          500);

    serialMessages.push_back(message);
    ofLogNotice("onSerialError") << "got serial error : " << message.exception;
}

void ofApp::appendMessage( ofxOscMessage& message, osc::OutboundPacketStream& p )
{
    p << osc::BeginMessage( message.getAddress().c_str() );
    for ( int i=0; i< message.getNumArgs(); ++i )
    {
        if ( message.getArgType(i) == OFXOSC_TYPE_INT32 )
            p << message.getArgAsInt32( i );
        else if ( message.getArgType(i) == OFXOSC_TYPE_INT64 )
            p << (osc::int64)message.getArgAsInt64( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_FLOAT )
            p << message.getArgAsFloat( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_DOUBLE )
            p << message.getArgAsDouble( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_STRING || message.getArgType( i ) == OFXOSC_TYPE_SYMBOL)
            p << message.getArgAsString( i ).c_str();
        else if ( message.getArgType( i ) == OFXOSC_TYPE_CHAR )
            p << message.getArgAsChar( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_MIDI_MESSAGE )
            p << message.getArgAsMidiMessage( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_TRUE || message.getArgType( i ) == OFXOSC_TYPE_FALSE )
            p << message.getArgAsBool( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_TRIGGER )
            p << message.getArgAsTrigger( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_TIMETAG )
            p << (osc::int64)message.getArgAsTimetag( i );
        //else if ( message.getArgType( i ) == OFXOSC_TYPE_RGBA_COLOR )
        //	p << message.getArgAsRgbaColor( i );
        else if ( message.getArgType( i ) == OFXOSC_TYPE_BLOB ){
            ofBuffer buff = message.getArgAsBlob(i);
            osc::Blob b(buff.getData(), (unsigned long)buff.size());
            p << b;
        }else
        {
            ofLogError("ofxOscSender") << "appendMessage(): bad argument type " << message.getArgType( i );
            assert( false );
        }
    }
    p << osc::EndMessage;
}
