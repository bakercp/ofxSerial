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


#include "Poco/Platform.h"
#include "Poco/AutoPtr.h"
#include "Poco/DeviceIO/Serial/SerialChannel.h"
#include "ofLog.h"
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/Serial/DeviceInfo.h"


using Poco::DeviceIO::Serial::SerialConfig;
using Poco::DeviceIO::Serial::SerialChannel;


namespace ofx {
namespace IO {
namespace Serial {


class Serial: public virtual AbstractBufferedByteSource, public virtual AbstractByteSink
{
public:
    Serial();
    virtual ~Serial();

    bool setup(const std::string& name,
               SerialConfig::BPSRate bpsRate = SerialConfig::BPS_9600,
               SerialConfig::DataBits dataBits = SerialConfig::DATA_BITS_EIGHT,
               char parity = 'N',
               SerialConfig::StartBits startBits = SerialConfig::START_ONE,
               SerialConfig::StopBits stopBits = SerialConfig::STOP_ONE,
               SerialConfig::FlowControl flowControl = SerialConfig::FLOW_CTRL_HARDWARE,
               unsigned char xOnChar = 0,
               unsigned char xOffChar = 0,
               bool useEOF = true,
               unsigned char eof = SerialConfig::DEFAULT_EOF,
               int bufferSize = 1,
               int timeout = SerialConfig::INFINITE_TIMEOUT);

    virtual std::size_t readBytes(uint8_t* buffer, std::size_t size);
    virtual std::size_t readByte(uint8_t& data);
    virtual std::size_t available() const;

    virtual std::size_t writeByte(uint8_t data);
    virtual std::size_t writeBytes(const uint8_t* buffer, std::size_t size);
    virtual std::size_t writeBytes(const std::vector<uint8_t>& buffer);
    virtual std::size_t writeBytes(const std::string& buffer);



    std::string name() const;
	void setTimeout(unsigned long long timeoutMillis);
	void setBlocking();
	void setNonblocking(unsigned long long timeoutMillis);
	unsigned long long getTimeout() const;
	bool isBlocking() const;

    //    static std::vector<DeviceInfo> getDevices();

private:
    Poco::AutoPtr<SerialChannel> pChannel;

    bool isChannelClosed() const;

};


} } } // namespace ofx::IO::Serial
