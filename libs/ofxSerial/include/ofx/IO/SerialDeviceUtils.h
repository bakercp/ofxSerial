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
    SerialDeviceInfo(std::string path):
        _path(path),
        _name(getNameFromPath(path))
    {
    }


    virtual ~SerialDeviceInfo()
    {
    }


    std::string getPath() const
    {
        return _path;
    }


    std::string getName() const
    {
        return _name;
    }


    friend std::ostream& operator << (std::ostream& os,
                                      const SerialDeviceInfo& deviceInfo);

protected:
    std::string _path;
    std::string _name;

    static std::string getNameFromPath(const std::string& path)
    {
        // this needs to be more sophisticated for dealing with Windows
        // We may also want to chop of tty, etc.
        return Poco::Path(path).getFileName();
    }

};


inline std::ostream& operator << (std::ostream& os,
                                  const SerialDeviceInfo& deviceInfo)
{
    os << deviceInfo._name << ", " << deviceInfo._path;
    return os;
}


class SerialDeviceUtils
{
public:
    static std::vector<SerialDeviceInfo> getDevices(const std::string& regexPattern = "",
                                                    int regexOptions = 0,
                                                    bool regexStudy = true);

protected:



//    friend class Poco::SingletonHolder<SerialDeviceInfo>;

};


} } // namespace ofx::IO
