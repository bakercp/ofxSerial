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


#include <stdint.h>
#include "Poco/Path.h"
#include "ofLog.h"
#include "ofx/IO/AbstractTypes.h"
#include "serial/serial.h"


namespace ofx {
namespace IO {


class DeviceInfo
{
public:
    DeviceInfo(std::string path):
        _path(path),
        _name(getNameFromPath(path))
    {
    }

    virtual ~DeviceInfo()
    {
    }

    std::string path()
    {
        return _path;
    }

    std::string name()
    {
        return getNameFromPath(_path);
    }

    static std::string getNameFromPath(const std::string& path)
    {
        Poco::Path p(path);
        return "s";
    }
    
protected:
    std::string _path;
    std::string _name;
    
};


class SerialDevice:
    public virtual AbstractBufferedByteSource,
    public virtual AbstractByteSink
{
public:
    typedef serial::Timeout Timeout;

    enum DataBits
    {
        DATA_BITS_FIVE = serial::fivebits,
        DATA_BITS_SIX = serial::sixbits,
        DATA_BITS_SEVEN = serial::sevenbits,
        DATA_BITS_EIGHT = serial::eightbits,
        DATA_BITS_UNKNOWN = -1
    };

    enum Parity
    {
        PAR_NONE = serial::parity_none,
        PAR_ODD = serial::parity_odd,
        PAR_EVEN = serial::parity_even,
        PAR_UNKNOWN = -1
    };

    enum StopBits
    {
        STOP_ONE = serial::stopbits_one,
        STOP_ONE5 = serial::stopbits_one_point_five,
        STOP_TWO = serial::stopbits_two,
        STOP_UNKNOWN = -1,
    };

    enum FlowControl
    {
        FLOW_CTRL_NONE = serial::flowcontrol_none,
        FLOW_CTRL_HARDWARE = serial::flowcontrol_hardware,
        FLOW_CTRL_SOFTWARE = serial::flowcontrol_software,
        FLOW_CTRL_UNKNOWN = -1
    };

    SerialDevice();
    virtual ~SerialDevice();

    bool setup(const std::string& portName,
               uint32_t bauds = 9600,
               DataBits dataBits = DATA_BITS_EIGHT,
               Parity parity = PAR_NONE,
               StopBits stopBits = STOP_ONE,
               FlowControl flowControl = FLOW_CTRL_NONE,
               Timeout timeout = Timeout());

    virtual std::size_t readBytes(uint8_t* buffer, std::size_t size);
    virtual std::size_t readByte(uint8_t& data);
    virtual std::size_t available() const;

    virtual std::size_t writeByte(uint8_t data);
    virtual std::size_t writeBytes(const uint8_t* buffer, std::size_t size);
    virtual std::size_t writeBytes(const std::vector<uint8_t>& buffer);
    virtual std::size_t writeBytes(const std::string& buffer);

    std::string getPortName() const;
    uint32_t getBauds() const;
    DataBits getDataBits() const;
    Parity getParity() const;
    StopBits getStopBits() const;
    FlowControl getFlowControl() const;
    Timeout getTimeout() const;

    void flush();
    void flushInput();
    void flushOutput();

    void sendBreak(int duration);
    void setBreak(bool level = true);
    void setRequestToSend(bool level = true);
    void setDataTerminalReady(bool level = true);

    bool isClearToSend() const;
    bool isDataSetReady() const;
    bool isRingIndicated() const;
    bool isCarrierDetected() const;

    //    static std::vector<DeviceInfo> getDevices();

protected:
    typedef std::shared_ptr<serial::Serial> SharedSerial;

    SharedSerial pSerial;


    bool confirmSetup() const;

};


} } // namespace ofx::IO
