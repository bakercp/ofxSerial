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


#pragma once


#include "ofx/IO/SerialEvents.h"
#include "ofx/IO/BufferedSerialDevice.h"


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

    bool setup(const SerialDeviceInfo& device,
               uint32_t bauds = DEFAULT_BAUD_RATE,
               DataBits dataBits = DATA_BITS_EIGHT,
               Parity parity = PAR_NONE,
               StopBits stopBits = STOP_ONE,
               FlowControl flowControl = FLOW_CTRL_NONE,
               Timeout timeout = DEFAULT_TIMEOUT)
    {
        return BufferedSerialDevice::setup(device,
                                           bauds,
                                           dataBits,
                                           parity,
                                           stopBits,
                                           flowControl,
                                           timeout);
    }

    bool setup(const std::string& portName,
               uint32_t bauds = DEFAULT_BAUD_RATE,
               DataBits dataBits = DATA_BITS_EIGHT,
               Parity parity = PAR_NONE,
               StopBits stopBits = STOP_ONE,
               FlowControl flowControl = FLOW_CTRL_NONE,
               Timeout timeout = DEFAULT_TIMEOUT)
    {
        return BufferedSerialDevice::setup(portName,
                                           bauds,
                                           dataBits,
                                           parity,
                                           stopBits,
                                           flowControl,
                                           timeout);
    }

    void send(const ByteBuffer& buffer)
    {
        ofx::IO::ByteBuffer encoded;
        _encoder.encode(buffer, encoded);
        BufferedSerialDevice::writeBytes(encoded);
        BufferedSerialDevice::writeByte(PacketMarker);
    }

    std::string getPortName() const
    {
        return BufferedSerialDevice::getPortName();
    }

    uint32_t getBauds() const
    {
        return BufferedSerialDevice::getBauds();
    }

    DataBits getDataBits() const
    {
        return BufferedSerialDevice::getDataBits();
    }

    Parity getParity() const
    {
        return BufferedSerialDevice::getParity();
    }

    StopBits getStopBits() const
    {
        return BufferedSerialDevice::getStopBits();
    }

    FlowControl getFlowControl() const
    {
        return BufferedSerialDevice::getFlowControl();
    }

    Timeout getTimeout() const
    {
        return BufferedSerialDevice::getTimeout();
    }

    bool isClearToSend() const
    {
        return BufferedSerialDevice::isClearToSend();
    }

    bool isDataSetReady() const
    {
        return BufferedSerialDevice::isDataSetReady();
    }

    bool isRingIndicated() const
    {
        return BufferedSerialDevice::isRingIndicated();
    }

    bool isCarrierDetected() const
    {
        return BufferedSerialDevice::isCarrierDetected();
    }

    bool isOpen() const
    {
        return BufferedSerialDevice::isOpen();
    }

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
    void unregisterAllEvents(ListenerClass* listener)
    {
        ofRemoveListener(packetEvents.onSerialBuffer, listener, &ListenerClass::onSerialBuffer);
        ofRemoveListener(packetEvents.onSerialError, listener, &ListenerClass::onSerialError);
    }

    /// \brief The SerialEvents that the user can subscribe to.
    SerialEvents packetEvents;

    void onSerialBuffer(const SerialBufferEventArgs& args)
    {
        ofx::IO::ByteBuffer decoded;
        _encoder.decode(args.getBuffer(), decoded);
        SerialBufferEventArgs evt(decoded);
        ofNotifyEvent(packetEvents.onSerialBuffer, evt, this);
    }

    void onSerialError(const SerialBufferErrorEventArgs& args)
    {
        // Pass it along.
        ofNotifyEvent(packetEvents.onSerialError, args, this);
    }

private:
    Encoder _encoder;

};


typedef PacketSerialDevice_<COBSEncoding> PacketSerialDevice;


} } // namespace ofx::IO
