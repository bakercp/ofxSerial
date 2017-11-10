//
// Copyright (c) 2010 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofEvents.h"
#include "Poco/Exception.h"
#include "ofx/IO/ByteBuffer.h"


namespace ofx {
namespace IO {


class BufferedSerialDevice;


class SerialBufferEventArgs: public ofEventArgs
{
public:
    SerialBufferEventArgs(const BufferedSerialDevice& device,
                          const ByteBuffer& buffer);

    const ByteBuffer& buffer() const;
    OF_DEPRECATED_MSG("Use buffer() instead", const ByteBuffer& getBuffer() const);

    const BufferedSerialDevice& device() const;

protected:
    const ByteBuffer& _buffer;
    const BufferedSerialDevice& _device;
    
};


class SerialBufferErrorEventArgs: public SerialBufferEventArgs
{
public:
    SerialBufferErrorEventArgs(const BufferedSerialDevice& device,
                               const ByteBuffer& buffer,
                               const Poco::Exception& exception);

    const Poco::Exception& exception() const;
    OF_DEPRECATED_MSG("Use exception() instead", const Poco::Exception& getException() const);


protected:
    const Poco::Exception& _exception;

};


class SerialEvents
{
public:
    ofEvent<const SerialBufferEventArgs> onSerialBuffer;
    ofEvent<const SerialBufferErrorEventArgs> onSerialError;

};


} } // namespace ofx::IO
