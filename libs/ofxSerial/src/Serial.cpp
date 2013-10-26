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


#include "Serial.h"


namespace ofx {
namespace IO {
namespace Serial {


Serial::Serial()
{
}


Serial::~Serial()
{
}


bool Serial::setup(const std::string& name,
                   SerialConfig::BPSRate bpsRate,
                   SerialConfig::DataBits dataBits,
                   char parity,
                   SerialConfig::StartBits startBits,
                   SerialConfig::StopBits stopBits,
                   SerialConfig::FlowControl flowControl,
                   unsigned char xOnChar,
                   unsigned char xOffChar,
                   bool useEOF,
                   unsigned char eof,
                   int bufferSize,
                   int timeout)
{
    if (!pChannel.isNull()) pChannel->release();  // release the old one

    SerialConfig* pConfig = new SerialConfig(name,
                                             bpsRate,
                                             dataBits,
                                             parity,
                                             startBits,
                                             stopBits,
                                             flowControl,
                                             xOnChar,
                                             xOffChar,
                                             useEOF,
                                             bufferSize,
                                             timeout);


    try
    {
        pChannel = new SerialChannel(pConfig);
        // pChannel->setBlocking();
    }
    catch (Poco::Exception& ex)
    {
        ofLogError("Serial::setup") << ex.what();
    }

    return !pChannel.isNull();
}


std::size_t Serial::readBytes(uint8_t* buffer, std::size_t size)
{
    if (isChannelClosed())
    {
        return 0;
    }
    else
    {
        try
        {
            return pChannel->read(reinterpret_cast<char*>(buffer), size);
        }
        catch (Poco::Exception& exc)
        {
            ofLogError("Serial::readBytes") << exc.displayText();
            return 0;
        }

    }
}


std::size_t Serial::readByte(uint8_t& data)
{
    if (isChannelClosed())
    {
        return 0;
    }
    else
    {
        try
        {
            data = pChannel->read();
            return 1;
        }
        catch (Poco::Exception& exc)
        {
            ofLogError("Serial::readByte") << exc.displayText();
            return 0;
        }
    }

}


std::size_t Serial::available() const
{
    if (isChannelClosed())
    {
        return 0;
    }
    else
    {
        int numBytes = 0;
//
//#if defined( TARGET_OSX ) || defined( TARGET_LINUX )
//		ioctl(fd,FIONREAD,&numBytes);
//#endif
//
//
//pChannel->
//
//#ifdef TARGET_WIN32
//        COMSTAT stat;
//       	DWORD err;
//       	if(hComm!=INVALID_HANDLE_VALUE){
//            if(!ClearCommError(hComm, &err, &stat)){
//                numBytes = 0;
//            } else {
//                numBytes = stat.cbInQue;
//            }
//       	} else {
//            numBytes = 0;
//       	}
//#endif
        return numBytes;
    }
}

std::size_t Serial::writeByte(uint8_t data)
{
    if (isChannelClosed())
        return 0;
    else
        return pChannel->write(data);
}

    
std::size_t Serial::writeBytes(const uint8_t* buffer, std::size_t size)
{
    if(isChannelClosed())
        return 0;
    else
        return pChannel->write(reinterpret_cast<const char*>(buffer),static_cast<int>(size));
}


std::string Serial::name() const
{
    if(isChannelClosed())
        return "";
    else
        return pChannel->name();
}


void Serial::setTimeout(unsigned long long timeoutMillis)
{
    if(isChannelClosed())
        return;
    else
        pChannel->setTimeout(timeoutMillis);
}


void Serial::setBlocking()
{
    if(isChannelClosed())
        return;
    else
        pChannel->setBlocking();
}


void Serial::setNonblocking(unsigned long long timeoutMillis)
{
    if(isChannelClosed())
        return;
    else
        pChannel->setNonblocking(timeoutMillis);
}


unsigned long long Serial::getTimeout() const
{
    if(isChannelClosed())
        return 0;
    else
        return pChannel->getTimeout();
}


bool Serial::isBlocking() const
{
    if(isChannelClosed())
        return false;
    else
        return pChannel->isBlocking();
}


//std::vector<DeviceInfo> Serial::getDevices()
//{
//}


bool Serial::isChannelClosed() const
{
    if (pChannel.isNull())
    {
        ofLogWarning("Serial::readBytes") << "Call Serial::setup() first.";
        return true;
    }

    return false;
}


} } } // namespace ofx::IO::Serial
