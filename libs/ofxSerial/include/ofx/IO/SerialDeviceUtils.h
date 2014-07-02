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


#include "ofLog.h"
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/DirectoryUtils.h"


namespace ofx {
namespace IO {


class SerialDeviceInfo
{
public:
    SerialDeviceInfo(const std::string& port,
                     const std::string& description,
                     const std::string& hardwareId):
        _port(port),
        _description(description),
        _hardwareId(hardwareId)
    {
    }


    /// \brief Destroy the SerialDeviceInfo.
    virtual ~SerialDeviceInfo()
    {
    }


    /// \brief Get the address of the serial port.
    ///
    /// This can be passed to the constructor of ofxSerial.
    ///
    /// \returns the address of the serial port.
    const std::string& getPort() const
    {
        return _port;
    }


    const std::string& getDescription() const
    {
        return _description;
    }


    const std::string& getHardwareId() const
    {
        return _hardwareId;
    }


    friend std::ostream& operator << (std::ostream& os,
                                      const SerialDeviceInfo& deviceInfo);

protected:
    std::string _port;
    std::string _description;
    std::string _hardwareId;

};


inline std::ostream& operator << (std::ostream& os,
                                  const SerialDeviceInfo& deviceInfo)
{
    os << deviceInfo._port << ", " << deviceInfo._description << ", " << deviceInfo._hardwareId;
    return os;
}


class SerialDeviceUtils
{
public:
    static std::vector<SerialDeviceInfo> getDevices(const std::string& regexPattern = "",
                                                    int regexOptions = 0,
                                                    bool regexStudy = true);

};


} } // namespace ofx::IO
