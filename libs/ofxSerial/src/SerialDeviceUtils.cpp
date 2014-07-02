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


namespace ofx {
namespace IO {



#ifdef TARGET_WIN32

#include <winbase.h>
#include <tchar.h>
#include <iostream>
#include <string.h>
#include <setupapi.h>
#include <regstr.h>
#define MAX_SERIAL_PORTS 256
#include <winioctl.h>

#ifdef __MINGW32__
#define INITGUID
#include <initguid.h> // needed for dev-c++ & DEFINE_GUID
#endif

// needed for serial bus enumeration:
// 4d36e978-e325-11ce-bfc1-08002be10318}
DEFINE_GUID (GUID_SERENUM_BUS_ENUMERATOR,
             0x4D36E978,
             0xE325,
             0x11CE,
             0xBF,
             0xC1,
             0x08,
             0x00,
             0x2B,
             0xE1,
             0x03,
             0x18);

void SerialDeviceUtils::enumerateWin32Ports()
{
    SP_DEVINFO_DATA DeviceInterfaceData;
    int i = 0;
    DWORD dataType = 0;
    DWORD actualSize = 0;

    unsigned char dataBuf[MAX_PATH + 1];

    // Reset Port List
    int nPorts = 0;

    // Search device set
    HDEVINFO hDevInfo = SetupDiGetClassDevs((struct _GUID *)&GUID_SERENUM_BUS_ENUMERATOR,0,0,DIGCF_PRESENT);

    if (hDevInfo)
    {
        while (true)
        {
            ZeroMemory(&DeviceInterfaceData, sizeof(DeviceInterfaceData));
            DeviceInterfaceData.cbSize = sizeof(DeviceInterfaceData);

            if (!SetupDiEnumDeviceInfo(hDevInfo,
                                       i,
                                       &DeviceInterfaceData))
            {
                // SetupDiEnumDeviceInfo failed
                break;
            }

            if (SetupDiGetDeviceRegistryPropertyA(hDevInfo,
                                                  &DeviceInterfaceData,
                                                  SPDRP_FRIENDLYNAME,
                                                  &dataType,
                                                  dataBuf,
                                                  sizeof(dataBuf),
                                                  &actualSize))
            {
                sprintf(portNamesFriendly[nPorts], "%s", dataBuf);
                portNamesShort[nPorts][0] = 0;

                // TODO: implement this using modern C++

                // turn blahblahblah(COM4) into COM4

                char* begin = strstr((char*)dataBuf, "COM");
                char* end   = 0;

                if (begin)
                {
                    end = strstr(begin, ")");
                    if (end)
                    {
                        *end = 0;   // get rid of the )...
                        strcpy(portNamesShort[nPorts], begin);
                    }
                    if (nPorts++ > MAX_SERIAL_PORTS)
                    {
                        break;
                    }
                }
            }
            
            i++;
        }
    }
    
    SetupDiDestroyDeviceInfoList(hDevInfo);
}

#endif



std::vector<SerialDeviceInfo> SerialDeviceUtils::getDevices(const std::string& regexPattern,
                                                            int regexOptions,
                                                            bool regexStudy)
{
    std::vector<SerialDeviceInfo> devices;
    std::vector<std::string> devicePaths;

    std::string _regexPattern;

    if(!regexPattern.empty())
    {
        _regexPattern = regexPattern;
    }
    else
    {
        switch(ofGetTargetPlatform())
        {
            case OF_TARGET_OSX:
            case OF_TARGET_IOS:
                _regexPattern = ".*/cu[.].*";
                break;
            case OF_TARGET_LINUX:
            case OF_TARGET_LINUX64:
            case OF_TARGET_LINUXARMV6L: // arm v6 little endian
            case OF_TARGET_LINUXARMV7L: // arm v7 little endian
                _regexPattern = ".*/tty.*";
                break;
            case OF_TARGET_ANDROID:
            case OF_TARGET_WINGCC:
            case OF_TARGET_WINVS:
                ofLogError("SerialDeviceUtils::getDevices") << "Not yet implemented for this platform.";
                return devices;
        }
    }

    DeviceFilter deviceFilter;
    RegexPathFilter pathFilter(_regexPattern, regexOptions, regexStudy);
    PathFilterCollection filters;

    filters.addFilter(&deviceFilter);
    filters.addFilter(&pathFilter);

    DirectoryUtils::list("/dev/", devicePaths, true, &filters);

    std::vector<std::string>::const_iterator iter = devicePaths.begin();

    while (iter != devicePaths.end())
    {
        SerialDeviceInfo deviceInfo((*iter));
        devices.push_back(deviceInfo);
        ++iter;
    }

    return devices;
}




} } // namespace ofx::IO
