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


#include "ofx/IO/DeviceFilter.h"
#include "ofx/IO/RegexPathFilter.h"
#include "ofx/IO/SerialDeviceUtils.h"
#include "ofx/IO/PathFilterCollection.h"
#include "serial/serial.h"


namespace ofx {
namespace IO {


std::vector<SerialDeviceInfo> SerialDeviceUtils::getDevices(const std::string& regexPattern,
                                                            int regexOptions,
                                                            bool regexStudy)
{
    std::vector<SerialDeviceInfo> devices;

    std::shared_ptr<Poco::RegularExpression> pRegex;

    if (!regexPattern.empty())
    {
        try
        {
            pRegex = std::shared_ptr<Poco::RegularExpression>(new Poco::RegularExpression(regexPattern));
        }
        catch (Poco::RegularExpressionException& exception)
        {
            ofLogError("SerialDeviceUtils::getDevices") << exception.displayText();
        }
    }

    std::vector<serial::PortInfo> ports = serial::list_ports();

    std::vector<serial::PortInfo>::const_iterator iter = ports.begin();

    while (iter != ports.end())
    {
        const serial::PortInfo portInfo = *iter;

        if (!pRegex || (pRegex && pRegex->match(portInfo.port)))
        {
            devices.push_back(SerialDeviceInfo(portInfo.port,
                                               portInfo.description,
                                               portInfo.hardware_id));
        }

        ++iter;
    }

    return devices;
}




} } // namespace ofx::IO
