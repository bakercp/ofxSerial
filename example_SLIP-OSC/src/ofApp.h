#pragma once

#include "ofMain.h"
#include "ofxSerial.h"
#include "ofxOsc.h"

class SerialMessage
{
public:
    SerialMessage(): fade(0)
    {
    }

    SerialMessage(const std::string& _message,
                  const std::string& _exception,
                  int _fade):
        message(_message),
        exception(_exception),
        fade(_fade)
    {
    }

    std::string message;
    std::string exception;
    int fade;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

        void mousePressed(ofMouseEventArgs& mouse);
        int state;

        void onSerialBuffer(const ofx::IO::SerialBufferEventArgs& args);
        void onSerialError(const ofx::IO::SerialBufferErrorEventArgs& args);

        ofx::IO::SLIPPacketSerialDevice device;

        std::vector<SerialMessage> serialMessages;
    private:
        void appendMessage( ofxOscMessage& message, osc::OutboundPacketStream& p );
};
