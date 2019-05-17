//
// Copyright (c) 2010 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/IO/SerialDevice.h"
#include <cerrno>


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



bool SerialDevice::setup(const Settings& settings)
{
    return setup(settings.portName,
                 settings.baudRate,
                 settings.dataBits,
                 settings.parity,
                 settings.stopBits,
                 settings.flowControl,
                 settings.timeout);
}


bool SerialDevice::setup(uint32_t baudRate,
                         DataBits dataBits,
                         Parity parity,
                         StopBits stopBits,
                         FlowControl flowControl,
                         serial::Timeout timeout)
{
    auto devices = SerialDeviceUtils::listDevices();

    if (!devices.empty())
    {
        return setup(devices[0].port(),
                     baudRate,
                     dataBits,
                     parity,
                     stopBits,
                     flowControl,
                     timeout);
    }
    else
    {
        ofLogVerbose("SerialDevice::setup") << "No available serial devices.";
        return false;
    }
}


bool SerialDevice::setup(const SerialDeviceInfo& device,
                         uint32_t baudRate,
                         DataBits dataBits,
                         Parity parity,
                         StopBits stopBits,
                         FlowControl flowControl,
                         serial::Timeout timeout)
{
    return setup(device.port(),
                 baudRate,
                 dataBits,
                 parity,
                 stopBits,
                 flowControl,
                 timeout);
}


bool SerialDevice::setup(const std::string& portName,
                         uint32_t baudRate,
                         DataBits dataBits,
                         Parity parity,
                         StopBits stopBits,
                         FlowControl flowControl,
                         serial::Timeout timeout)
{
    try
    {
        _serial = std::make_shared<serial::Serial>(portName,
                                                   baudRate,
                                                   timeout,
                                                   static_cast<serial::bytesize_t>(dataBits),
                                                   static_cast<serial::parity_t>(parity),
                                                   static_cast<serial::stopbits_t>(stopBits),
                                                   static_cast<serial::flowcontrol_t>(flowControl));

    }
    catch (const serial::IOException& exc)
    {
        if (exc.getErrorNumber() == EBUSY)
        {
            ofLogError("SerialDevice::setup") << portName << " is busy -- is it in use by another application?";
        }
        else
        {
            ofLogError("SerialDevice::setup") << exc.what();
        }

        return false;
    }

    return _serial->isOpen();
}


std::size_t SerialDevice::readBytes(uint8_t* buffer, std::size_t size)
{
    return _serial != nullptr ? _serial->read(buffer, size) : 0;
}


std::size_t SerialDevice::readByte(uint8_t& data)
{
    return _serial != nullptr ? _serial->read(&data, 1) : 0;
}


std::size_t SerialDevice::available() const
{
    return _serial != nullptr ? _serial->available() : 0;
}


std::size_t SerialDevice::writeByte(uint8_t data)
{
    return _serial != nullptr ? _serial->write(&data, 1) : 0;
}


std::size_t SerialDevice::writeBytes(const uint8_t* buffer, std::size_t size)
{
    return _serial != nullptr ? _serial->write(buffer, size) : 0;
}


std::size_t SerialDevice::writeBytes(const std::vector<uint8_t>& buffer)
{
    return _serial != nullptr ? _serial->write(buffer) : 0;
}


std::size_t SerialDevice::writeBytes(const std::string& buffer)
{
    return _serial != nullptr ? _serial->write(buffer) : 0;
}


std::size_t SerialDevice::writeBytes(const AbstractByteSource& buffer)
{
    return _serial != nullptr ? _serial->write(buffer.readBytes()) : 0;
}


std::string SerialDevice::port() const
{
    return _serial != nullptr ? _serial->getPort() : "";
}


std::string SerialDevice::getPortName() const
{
    return port();
}


uint32_t SerialDevice::baudRate() const
{
    return _serial != nullptr ? _serial->getBaudrate() : 0;
}


uint32_t SerialDevice::getBauds() const
{
    return baudRate();
}


SerialDevice::DataBits SerialDevice::dataBits() const
{
    if (_serial != nullptr)
    {
        return static_cast<SerialDevice::DataBits>(_serial->getBytesize());
    }
    else
    {
        return DATA_BITS_UNKNOWN;
    }
}



SerialDevice::DataBits SerialDevice::getDataBits() const
{
    return dataBits();
}


SerialDevice::Parity SerialDevice::parity() const
{
    if (_serial != nullptr)
    {
        return static_cast<SerialDevice::Parity>(_serial->getParity());
    }
    else
    {
        return PAR_UNKNOWN;
    }
}


SerialDevice::Parity SerialDevice::getParity() const
{
    return parity();
}


SerialDevice::StopBits SerialDevice::stopBits() const
{
    if (_serial != nullptr)
    {
        return static_cast<SerialDevice::StopBits>(_serial->getStopbits());
    }
    else
    {
        return STOP_UNKNOWN;
    }
}


SerialDevice::StopBits SerialDevice::getStopBits() const
{
    return stopBits();
}


SerialDevice::FlowControl SerialDevice::flowControl() const
{
    if (_serial != nullptr)
    {
        return static_cast<SerialDevice::FlowControl>(_serial->getFlowcontrol());
    }
    else
    {
        return FLOW_CTRL_UNKNOWN;
    }
}


SerialDevice::FlowControl SerialDevice::getFlowControl() const
{
    return flowControl();
}



SerialDevice::Timeout SerialDevice::timeout() const
{
    if (_serial != nullptr)
    {
        return _serial->getTimeout();
    }
    else
    {
        return Timeout();
    }
}


SerialDevice::Timeout SerialDevice::getTimeout() const
{
    return timeout();
}


void SerialDevice::flush()
{
    if (_serial != nullptr) _serial->flush();
}


void SerialDevice::flushInput()
{
    if (_serial != nullptr) _serial->flushInput();
}


void SerialDevice::flushOutput()
{
    if (_serial != nullptr) _serial->flushOutput();
}


void SerialDevice::sendBreak(int duration)
{
    if (_serial != nullptr) _serial->sendBreak(duration);
}


void SerialDevice::setBreak(bool level)
{
    if (_serial != nullptr) _serial->setBreak(level);
}


void SerialDevice::setRequestToSend(bool level)
{
    if (_serial != nullptr) _serial->setRTS(level);
}


void SerialDevice::setDataTerminalReady(bool level)
{
    if (_serial != nullptr) _serial->setDTR(level);
}


bool SerialDevice::isClearToSend() const
{
    return _serial != nullptr && _serial->getCTS();
}


bool SerialDevice::isDataSetReady() const
{
    return _serial != nullptr && _serial->getCTS();
}


bool SerialDevice::isRingIndicated() const
{
    return _serial != nullptr && _serial->getRI();
}


bool SerialDevice::isCarrierDetected() const
{
    return _serial != nullptr && _serial->getCD();
}


bool SerialDevice::isOpen() const
{
    return _serial != nullptr && _serial->isOpen();
}


const serial::Serial* SerialDevice::serial() const
{
    return _serial.get();
}


serial::Serial* SerialDevice::serial()
{
    return _serial.get();
}


} } // namespace ofx::IO
