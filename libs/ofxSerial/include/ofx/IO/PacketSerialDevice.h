// =============================================================================
//
// Copyright (c) 2010-2016 Christopher Baker <http://christopherbaker.net>
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


#pragma once


#include "ofx/IO/SerialEvents.h"
#include "ofx/IO/BufferedSerialDevice.h"
#include "ofx/IO/COBSEncoding.h"
#include "ofx/IO/SLIPEncoding.h"


namespace ofx {
namespace IO {


template<typename Encoder, uint8_t PacketMarker = 0, std::size_t BufferSize = 8192>
class PacketSerialDevice_: protected BufferedSerialDevice
{
public:
    PacketSerialDevice_(): BufferedSerialDevice(PacketMarker, BufferSize)
    {
        BufferedSerialDevice::registerAllEvents(this);
    }

    /// \Brief destroy the PacketSerialDevice.
    virtual ~PacketSerialDevice_()
    {
        BufferedSerialDevice::unregisterAllEvents(this);
    }

    using BufferedSerialDevice::setup;

    void send(const ByteBuffer& buffer)
    {
        ByteBuffer encoded;
        _encoder.encode(buffer, encoded);
        BufferedSerialDevice::writeBytes(encoded);
        BufferedSerialDevice::writeByte(PacketMarker);
    }

    using BufferedSerialDevice::port;
    using BufferedSerialDevice::baudRate;
    using BufferedSerialDevice::dataBits;
    using BufferedSerialDevice::stopBits;
    using BufferedSerialDevice::timeout;
    using BufferedSerialDevice::isClearToSend;
    using BufferedSerialDevice::isDataSetReady;
    using BufferedSerialDevice::isRingIndicated;
    using BufferedSerialDevice::isCarrierDetected;
    using BufferedSerialDevice::isOpen;

    /// \brief Register a class to receive notifications for all events.
    /// \param listener a pointer to the listener class.
    /// \param order the event order.
    template<class ListenerClass>
    void registerAllEvents(ListenerClass* listener, int order = OF_EVENT_ORDER_AFTER_APP)
    {
        ofAddListener(packetEvents.onSerialBuffer, listener, &ListenerClass::onSerialBuffer, order);
        ofAddListener(packetEvents.onSerialError, listener, &ListenerClass::onSerialError, order);
    }

    /// \brief Unregister a class to receive notifications for all events.
    /// \param listener a pointer to the listener class.
    template<class ListenerClass>
    void unregisterAllEvents(ListenerClass* listener, int order = OF_EVENT_ORDER_AFTER_APP)
    {
        ofRemoveListener(packetEvents.onSerialBuffer, listener, &ListenerClass::onSerialBuffer, order);
        ofRemoveListener(packetEvents.onSerialError, listener, &ListenerClass::onSerialError, order);
    }

    /// \brief The SerialEvents that the user can subscribe to.
    SerialEvents packetEvents;

    void onSerialBuffer(const SerialBufferEventArgs& args)
    {
        ByteBuffer decoded;

        std::size_t size = _encoder.decode(args.buffer(), decoded);

        if (size > 0)
        {
            SerialBufferEventArgs evt(args.device(), decoded);
            ofNotifyEvent(packetEvents.onSerialBuffer, evt, this);
        }
    }

    void onSerialError(const SerialBufferErrorEventArgs& args)
    {
        // Pass it along.
        ofNotifyEvent(packetEvents.onSerialError, args, this);
    }

private:
    /// \brief The encoder used to encode and decode byte buffers.
    Encoder _encoder;

};


typedef PacketSerialDevice_<COBSEncoding> PacketSerialDevice;
typedef PacketSerialDevice_<COBSEncoding> COBSPacketSerialDevice;
typedef PacketSerialDevice_<SLIPEncoding, SLIPEncoding::END> SLIPPacketSerialDevice;


} } // namespace ofx::IO
