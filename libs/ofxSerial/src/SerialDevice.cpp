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
    return setup(device.getPath(),
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

    try
    {
        pSerial = SharedSerial(new serial::Serial(portName,
                                                  bauds,
                                                  timeout,
                                                  (serial::bytesize_t)dataBits,
                                                  (serial::parity_t)parity,
                                                  (serial::stopbits_t)stopBits,
                                                  (serial::flowcontrol_t)flowControl));
    }
    catch (const std::exception& exc)
    {
        ofLogError("SerialDevice::setup") << exc.what();
    }

    return confirmSetup();
}


std::size_t SerialDevice::readBytes(uint8_t* buffer, std::size_t size)
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->read(buffer, size);
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::readBytes") << exc.what();
            return 0;
        }
    }
    else
    {
        return 0;
    }
}


std::size_t SerialDevice::readByte(uint8_t& data)
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->read(&data,1);
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::readByte") << exc.what();
            return 0;
        }
    }
    else
    {
        return 0;
    }
}


std::size_t SerialDevice::available() const
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->available();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::available") << exc.what();
            return 0;
        }
    }
    else
    {
        return 0;
    }
}


std::size_t SerialDevice::writeByte(uint8_t data)
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->write(&data,1);
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::writeByte") << exc.what();
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

    
std::size_t SerialDevice::writeBytes(const uint8_t* buffer, std::size_t size)
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->write(buffer,size);
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::writeBytes") << exc.what();
            return 0;
        }
    }
    else
    {
        return 0;
    }
}


std::size_t SerialDevice::writeBytes(const std::vector<uint8_t>& buffer)
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->write(buffer);
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::writeBytes") << exc.what();
            return 0;
        }
    }
    else
    {
        return 0;
    }
}


std::size_t SerialDevice::writeBytes(const std::string& buffer)
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->write(buffer);
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::writeBytes") << exc.what();
            return 0;
        }
    }
    else
    {
        return 0;
    }
}


std::size_t SerialDevice::writeBytes(const AbstractByteSource& buffer)
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->write(buffer.readBytes());
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::writeBytes") << exc.what();
            return 0;
        }
    }
    else
    {
        return 0;
    }
}


std::string SerialDevice::getPortName() const
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->getPort();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::getPortName") << exc.what();
            return "";
        }
    }
    else
    {
        return "";
    }
}


uint32_t SerialDevice::getBauds() const
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->getBaudrate();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::getBauds") << exc.what();
            return 0;
        }
    }
    else
    {
        return 0;
    }
}


SerialDevice::DataBits SerialDevice::getDataBits() const
{
    if(confirmSetup())
    {
        try
        {
            return (SerialDevice::DataBits)pSerial->getBytesize();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::getDataBits") << exc.what();
            return DATA_BITS_UNKNOWN;
        }
    }
    else
    {
        return DATA_BITS_UNKNOWN;
    }
}


SerialDevice::Parity SerialDevice::getParity() const
{
    if(confirmSetup())
    {
        try
        {
            return (SerialDevice::Parity)pSerial->getParity();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::getParity") << exc.what();
            return PAR_UNKNOWN;
        }
    }
    else
    {
        return PAR_UNKNOWN;
    }
}


SerialDevice::StopBits SerialDevice::getStopBits() const
{
    if(confirmSetup())
    {
        try
        {
            return (SerialDevice::StopBits)pSerial->getStopbits();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::getStopBits") << exc.what();
            return STOP_UNKNOWN;
        }
    }
    else
    {
        return STOP_UNKNOWN;
    }
}


SerialDevice::FlowControl SerialDevice::getFlowControl() const
{
    if(confirmSetup())
    {
        try
        {
            return (SerialDevice::FlowControl)pSerial->getFlowcontrol();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::getStopBits") << exc.what();
            return FLOW_CTRL_UNKNOWN;
        }
    }
    else
    {
        return FLOW_CTRL_UNKNOWN;
    }
}


SerialDevice::Timeout SerialDevice::getTimeout() const
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->getTimeout();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::getStopBits") << exc.what();
            return Timeout();
        }
    }
    else
    {
        return Timeout();
    }
}


void SerialDevice::flush()
{
    if(confirmSetup())
    {
        try
        {
            pSerial->flush();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::flush") << exc.what();
        }
    }
}


void SerialDevice::flushInput()
{
    if(confirmSetup())
    {
        try
        {
            pSerial->flushInput();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::flushInput") << exc.what();
        }
    }
}


void SerialDevice::flushOutput()
{
    if(confirmSetup())
    {
        try
        {
            pSerial->flushOutput();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::flushOutput") << exc.what();
        }
    }
}


void SerialDevice::sendBreak(int duration)
{
    if(confirmSetup())
    {
        try
        {
            pSerial->sendBreak(duration);
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::sendBreak") << exc.what();
        }
    }
}


void SerialDevice::setBreak(bool level)
{
    if(confirmSetup())
    {
        try
        {
            pSerial->setBreak(level);
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::setBreak") << exc.what();
        }
    }
}


void SerialDevice::setRequestToSend(bool level)
{
    if(confirmSetup())
    {
        try
        {
            pSerial->setRTS(level);
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::setRTS") << exc.what();
        }
    }
}


void SerialDevice::setDataTerminalReady(bool level)
{
    if(confirmSetup())
    {
        try
        {
            pSerial->setDTR(level);
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::setRTS") << exc.what();
        }
    }
}


bool SerialDevice::isClearToSend() const
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->getCTS();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::getCTS") << exc.what();
            return false;
        }
    }
    else
    {
        return false;
    }
}


bool SerialDevice::isDataSetReady() const
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->getCTS();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::getDSR") << exc.what();
            return false;
        }
    }
    else
    {
        return false;
    }
}


bool SerialDevice::isRingIndicated() const
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->getRI();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::getRI") << exc.what();
            return false;
        }
    }
    else
    {
        return false;
    }
}


bool SerialDevice::isCarrierDetected() const
{
    if(confirmSetup())
    {
        try
        {
            return pSerial->getCD();
        }
        catch (const std::exception& exc)
        {
            ofLogError("SerialDevice::getCD") << exc.what();
            return false;
        }
    }
    else
    {
        return false;
    }
}


bool SerialDevice::confirmSetup() const
{
    if(0 != pSerial)
    {
        return true;
    }
    else
    {
        ofLogError("SerialDevice::readBytes") << "Serial Device is not configured.  Call setup() first.";
        return false;
    }
}


} } // namespace ofx::IO
