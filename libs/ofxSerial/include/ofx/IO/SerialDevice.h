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


#include <stdint.h>
#include "Poco/Path.h"
#include "serial/serial.h"
#include "ofLog.h"
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/SerialDeviceUtils.h"


namespace ofx {
namespace IO {


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

    bool setup(const SerialDeviceInfo& device,
               uint32_t bauds = DEFAULT_BAUD_RATE,
               DataBits dataBits = DATA_BITS_EIGHT,
               Parity parity = PAR_NONE,
               StopBits stopBits = STOP_ONE,
               FlowControl flowControl = FLOW_CTRL_NONE,
               Timeout timeout = DEFAULT_TIMEOUT);

    bool setup(const std::string& portName,
               uint32_t bauds = DEFAULT_BAUD_RATE,
               DataBits dataBits = DATA_BITS_EIGHT,
               Parity parity = PAR_NONE,
               StopBits stopBits = STOP_ONE,
               FlowControl flowControl = FLOW_CTRL_NONE,
               Timeout timeout = DEFAULT_TIMEOUT);

    std::size_t readBytes(uint8_t* buffer, std::size_t size) override;
    std::size_t readByte(uint8_t& data) override;
    std::size_t available() const override;

    std::size_t writeByte(uint8_t data) override;
    std::size_t writeBytes(const uint8_t* buffer, std::size_t size) override;
    std::size_t writeBytes(const std::vector<uint8_t>& buffer) override;
    std::size_t writeBytes(const std::string& buffer) override;
    std::size_t writeBytes(const AbstractByteSource& buffer) override;

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

    bool isOpen() const;

    enum
    {
        DEFAULT_BAUD_RATE = 9600
    };

    enum
    {
        /// \brief The default read timeout.  0 is a non-blocking timeout.
        DEFAULT_READ_TIMEOUT_CONSTANT_MS = 0,
        DEFAULT_READ_TIMEOUT_MULTIPLIER_MS = 0,
        /// \brief The default write timeout constant.
        /// This usually blocks for one or two milliseconds.
        DEFAULT_WRITE_TIMEOUT_CONSTANT = 1000,
        DEFAULT_WRITE_TIMEOUT_MULTIPLIER = 0
    };

    static const Timeout DEFAULT_TIMEOUT;

    std::shared_ptr<serial::Serial> getSerial()
    {
        return pSerial;
    }
    
protected:
    typedef std::shared_ptr<serial::Serial> SharedSerial;

    SharedSerial pSerial;

};


} } // namespace ofx::IO
