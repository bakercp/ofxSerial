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


#include "ofx/IO/SerialEvents.h"
#include "ofx/IO/BufferedSerialDevice.h"


namespace ofx {
namespace IO {


SerialBufferEventArgs::SerialBufferEventArgs(const BufferedSerialDevice& device,
                                             const ByteBuffer& buffer):
    _device(device),
    _buffer(buffer)
{
}


const ByteBuffer& SerialBufferEventArgs::buffer() const
{
    return _buffer;
}


const ByteBuffer& SerialBufferEventArgs::getBuffer() const
{
    return buffer();
}

    
const BufferedSerialDevice& SerialBufferEventArgs::device() const
{
    return _device;
}




SerialBufferErrorEventArgs::SerialBufferErrorEventArgs(const BufferedSerialDevice& device,
                                                       const ByteBuffer& buffer,
                                                       const Poco::Exception& exception):
    SerialBufferEventArgs(device, buffer),
    _exception(exception)
{
}


const Poco::Exception& SerialBufferErrorEventArgs::exception() const
{
    return _exception;
}


const Poco::Exception& SerialBufferErrorEventArgs::getException() const
{
    return exception();
}


} } // namespace ofx::IO
