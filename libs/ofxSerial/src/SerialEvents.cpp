//
// Copyright (c) 2010 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


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
