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


#include "ofx/IO/BufferedSerialDevice.h"
#include "ofx/IO/SerialEvents.h"
#include "Poco/Buffer.h"


namespace ofx {
namespace IO {


const uint8_t BufferedSerialDevice::DEFAULT_MARKER = '\n';


BufferedSerialDevice::BufferedSerialDevice(uint8_t marker,
                                           std::size_t maxBufferSize):
    _marker(marker),
    _maxBufferSize(maxBufferSize)
{
    ofAddListener(ofEvents().update, this, &BufferedSerialDevice::update);
}


BufferedSerialDevice::~BufferedSerialDevice()
{
    ofRemoveListener(ofEvents().update, this, &BufferedSerialDevice::update);
}


void BufferedSerialDevice::update(ofEventArgs& args)
{
    if (!isOpen()) return;

    Poco::Buffer<uint8_t> buffer(UPDATE_BUFFER_SIZE);

    try
    {
        while (available())
        {
            std::size_t nBytes = _serial->read(buffer.begin(),
                                               UPDATE_BUFFER_SIZE);

            for (std::size_t i = 0; i < nBytes; ++i)
            {
                if (buffer[i] == _marker)
                {
                    // Decode the buffer if needed.
                    //decodeBuffer();

                    // Send the buffer if there are any bytes.
                    if (buffer.size() > 0)
                    {
                        SerialBufferEventArgs args(*this, _buffer);
                        ofNotifyEvent(events.onSerialBuffer, args, this);
                    }

                    _buffer.reserve(_maxBufferSize);
                    _buffer.clear();
                }
                else
                {
                    if (_buffer.size() + 1 >= _maxBufferSize)
                    {
                        // Send the overflow;
                        std::stringstream ss;
                        ss << "maxBufferSize exceeded: " << _maxBufferSize;

                        Poco::Exception exception(ss.str());

                        SerialBufferErrorEventArgs args(*this,
                                                        _buffer,
                                                        exception);

                        ofNotifyEvent(events.onSerialError, args, this);

                        _buffer.reserve(_maxBufferSize);
                        _buffer.clear();
                    }

                    _buffer.writeByte(buffer[i]);
                }
            }
        }
    }
    catch (const Poco::Exception& exc)
    {
        SerialBufferErrorEventArgs args(*this, _buffer, exc);
        ofNotifyEvent(events.onSerialError, args, this);
    }
    catch (const std::exception& exc)
    {
        Poco::Exception e(exc.what());
        SerialBufferErrorEventArgs args(*this, _buffer, e);
        ofNotifyEvent(events.onSerialError, args, this);
    }
    catch (...)
    {
        Poco::Exception exc("Unknown error.");
        SerialBufferErrorEventArgs args(*this, _buffer, exc);
        ofNotifyEvent(events.onSerialError, args, this);
    }
}


void BufferedSerialDevice::setMarker(uint8_t marker)
{
    _marker = marker;
}


uint8_t BufferedSerialDevice::getMarker() const
{
    return _marker;
}


void BufferedSerialDevice::clear()
{
    _buffer.clear();
}


std::size_t BufferedSerialDevice::getMaximumBufferSize() const
{
    return _maxBufferSize;
}

void BufferedSerialDevice::setMaximumBufferSize(std::size_t maxBufferSize)
{
    if (maxBufferSize > 0)
    {
        _maxBufferSize = maxBufferSize;
    }
}


} } // namespace ofx::IO
