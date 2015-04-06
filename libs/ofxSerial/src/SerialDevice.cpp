// =============================================================================
//
// Copyright (c) 2010-2014 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/IO/SerialDevice.h"


namespace ofx {
namespace IO {


const SerialDevice::Timeout SerialDevice::DEFAULT_TIMEOUT(SerialDevice::Timeout::max(),
                                                          SerialDevice::DEFAULT_READ_TIMEOUT_CONSTANT_MS,
                                                          SerialDevice::DEFAULT_READ_TIMEOUT_MULTIPLIER_MS,
                                                          SerialDevice::DEFAULT_WRITE_TIMEOUT_CONSTANT,
                                                          SerialDevice::DEFAULT_WRITE_TIMEOUT_MULTIPLIER);

SerialDevice::SerialDevice()
{
}


SerialDevice::~SerialDevice()
{
}


bool SerialDevice::setup(const SerialDeviceInfo& device,
                         uint32_t bauds,
                         DataBits dataBits,
                         Parity parity,
                         StopBits stopBits,
                         FlowControl flowControl,
                         serial::Timeout timeout)
{
    return setup(device.getPort(),
                 bauds,
                 dataBits,
                 parity,
                 stopBits,
                 flowControl,
                 timeout);
}


bool SerialDevice::setup(const std::string& portName,
                         uint32_t bauds,
                         DataBits dataBits,
                         Parity parity,
                         StopBits stopBits,
                         FlowControl flowControl,
                         serial::Timeout timeout)
{
    try {
        pSerial = SharedSerial(new serial::Serial(portName,
                                                  bauds,
                                                  timeout,
                                                  (serial::bytesize_t)dataBits,
                                                  (serial::parity_t)parity,
                                                  (serial::stopbits_t)stopBits,
                                                  (serial::flowcontrol_t)flowControl));

    }
    catch (const serial::IOException& exc)
    {
        ofLogError("SerialDevice::setup") << exc.what();
        return false;
    }

    return pSerial->isOpen();
}


std::size_t SerialDevice::readBytes(uint8_t* buffer, std::size_t size)
{
    return pSerial ? pSerial->read(buffer, size) : 0;
}


std::size_t SerialDevice::readByte(uint8_t& data)
{
    return pSerial ? pSerial->read(&data, 1) : 0;
}


std::size_t SerialDevice::available() const
{
    return pSerial ? pSerial->available() : 0;
}


std::size_t SerialDevice::writeByte(uint8_t data)
{
    return pSerial ? pSerial->write(&data, 1) : 0;
}

    
std::size_t SerialDevice::writeBytes(const uint8_t* buffer, std::size_t size)
{
    return pSerial ? pSerial->write(buffer, size) : 0;
}


std::size_t SerialDevice::writeBytes(const std::vector<uint8_t>& buffer)
{
    return pSerial ? pSerial->write(buffer) : 0;
}


std::size_t SerialDevice::writeBytes(const std::string& buffer)
{
    return pSerial ? pSerial->write(buffer) : 0;
}


std::size_t SerialDevice::writeBytes(const AbstractByteSource& buffer)
{
    return pSerial ? pSerial->write(buffer.readBytes()) : 0;
}


std::string SerialDevice::getPortName() const
{
    return pSerial ? pSerial->getPort() : "";
}


uint32_t SerialDevice::getBauds() const
{
    return pSerial ? pSerial->getBaudrate() : 0;
}


SerialDevice::DataBits SerialDevice::getDataBits() const
{
    if (pSerial)
    {
        return (SerialDevice::DataBits)pSerial->getBytesize();
    }
    else
    {
        return DATA_BITS_UNKNOWN;
    }
}


SerialDevice::Parity SerialDevice::getParity() const
{
    if (pSerial)
    {
        return (SerialDevice::Parity)pSerial->getParity();
    }
    else
    {
        return PAR_UNKNOWN;
    }
}


SerialDevice::StopBits SerialDevice::getStopBits() const
{
    if (pSerial)
    {
        return (SerialDevice::StopBits)pSerial->getStopbits();
    }
    else
    {
        return STOP_UNKNOWN;
    }
}


SerialDevice::FlowControl SerialDevice::getFlowControl() const
{
    if (pSerial)
    {
        return (SerialDevice::FlowControl)pSerial->getFlowcontrol();
    }
    else
    {
        return FLOW_CTRL_UNKNOWN;
    }
}


SerialDevice::Timeout SerialDevice::getTimeout() const
{
    if (pSerial)
    {
        return pSerial->getTimeout();
    }
    else
    {
        return Timeout();
    }
}


void SerialDevice::flush()
{
    if (pSerial) pSerial->flush();
}


void SerialDevice::flushInput()
{
    if (pSerial) pSerial->flushInput();
}


void SerialDevice::flushOutput()
{
    if (pSerial) pSerial->flushOutput();
}


void SerialDevice::sendBreak(int duration)
{
    if (pSerial) pSerial->sendBreak(duration);
}


void SerialDevice::setBreak(bool level)
{
    if (pSerial) pSerial->setBreak(level);
}


void SerialDevice::setRequestToSend(bool level)
{
    if (pSerial) pSerial->setRTS(level);
}


void SerialDevice::setDataTerminalReady(bool level)
{
    if (pSerial) pSerial->setDTR(level);
}


bool SerialDevice::isClearToSend() const
{
    return pSerial && pSerial->getCTS();
}


bool SerialDevice::isDataSetReady() const
{
    return pSerial && pSerial->getCTS();
}


bool SerialDevice::isRingIndicated() const
{
    return pSerial && pSerial->getRI();
}


bool SerialDevice::isCarrierDetected() const
{
    return pSerial && pSerial->getCD();
}


bool SerialDevice::isOpen() const
{
    return pSerial && pSerial->isOpen();
}


} } // namespace ofx::IO
