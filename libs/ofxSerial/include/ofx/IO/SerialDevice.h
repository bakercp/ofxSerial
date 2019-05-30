//
// Copyright (c) 2010 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <stdint.h>
#include "serial/serial.h"
#include "ofJson.h"
#include "ofLog.h"
#include "ofMath.h"
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/SerialDeviceUtils.h"


namespace ofx {
namespace IO {


class SerialDevice:
    public virtual AbstractBufferedByteSource,
    public virtual AbstractByteSink
{
public:
    typedef serial::Timeout Timeout;

    enum DataBits
    {
        DATA_BITS_FIVE = serial::fivebits,
        DATA_BITS_SIX = serial::sixbits,
        DATA_BITS_SEVEN = serial::sevenbits,
        DATA_BITS_EIGHT = serial::eightbits,
        DATA_BITS_UNKNOWN = -1
    };

    enum Parity
    {
        PAR_NONE = serial::parity_none,
        PAR_ODD = serial::parity_odd,
        PAR_EVEN = serial::parity_even,
        PAR_MARK = serial::parity_mark,
        PAR_SPACE = serial::parity_space,
        PAR_UNKNOWN = -1
    };

    enum StopBits
    {
        STOP_ONE = serial::stopbits_one,
        STOP_ONE_POINT_FIVE = serial::stopbits_one_point_five,
        STOP_TWO = serial::stopbits_two,
        STOP_UNKNOWN = -1,
    };

    enum FlowControl
    {
        FLOW_CTRL_NONE = serial::flowcontrol_none,
        FLOW_CTRL_HARDWARE = serial::flowcontrol_hardware,
        FLOW_CTRL_SOFTWARE = serial::flowcontrol_software,
        FLOW_CTRL_UNKNOWN = -1
    };

    class Settings
    {
    public:
        Settings()
        {
        }

        Settings(std::string& _portName): portName(_portName)
        {
        }

        static Settings fromJSON(const ofJson& json)
        {
            Settings settings;

            settings.portName = json.value("port_name", "");
            settings.baudRate = json.value("baud_rate", static_cast<uint32_t>(DEFAULT_BAUD_RATE));

            int dataBits = json.value("data_bits", 8);

            switch (dataBits)
            {
                case 5:
                    settings.dataBits = DATA_BITS_FIVE;
                    break;
                case 6:
                    settings.dataBits = DATA_BITS_SIX;
                    break;
                case 7:
                    settings.dataBits = DATA_BITS_SEVEN;
                    break;
                case 8:
                    settings.dataBits = DATA_BITS_EIGHT;
                    break;
                default:
                    ofLogWarning("Settings::fromJSON") << "Invalid data bits: " << dataBits << ". Using default.";
            }

            std::string parity = json.value("parity", "none");

            if (parity == "none")
                settings.parity = PAR_NONE;
            else if (parity == "odd")
                settings.parity = PAR_ODD;
            else if (parity == "even")
                settings.parity = PAR_EVEN;
            else if (parity == "mark")
                settings.parity = PAR_MARK;
            else if (parity == "space")
                settings.parity = PAR_SPACE;
            else
            {
                ofLogWarning("Settings::fromJSON") << "Invalid parity: " << parity << ". Using default.";
                settings.parity = PAR_NONE;
            }

            float stopBits = json.value("stop_bits", 1.0f);

            if (ofIsFloatEqual(stopBits, 1.0f))
                settings.stopBits = STOP_ONE;
            else if (ofIsFloatEqual(stopBits, 1.5f))
                settings.stopBits = STOP_ONE_POINT_FIVE;
            else if (ofIsFloatEqual(stopBits, 2.0f))
                settings.stopBits = STOP_TWO;
            else
                ofLogWarning("Settings::fromJSON") << "Invalid stop bits: " << stopBits << ". Using default.";

            std::string flowControl = json.value("flow_control", "none");

            if (flowControl == "none")
                settings.flowControl = FLOW_CTRL_NONE;
            else if (flowControl == "hardware")
                settings.flowControl = FLOW_CTRL_HARDWARE;
            else if (flowControl == "software")
                settings.flowControl = FLOW_CTRL_SOFTWARE;
            else
                ofLogWarning("Settings::fromJSON") << "Invalid flow control: " << flowControl << ". Using default.";

//            ofJson timeout = json["timeout"];
//
//            if (!timeout.is_null())
//            {
//                if (timeout.is_object())
//                {
//                    settings.timeout = serial::Timeout(timeout.value("inter_byte_timeout", 0),
//                                                       timeout.value("read_timeout_constant", 0),
//                                                       timeout.value("read_timeout_multiplier", 0),
//                                                       timeout.value("write_timeout_constant", 0),
//                                                       timeout.value("write_timeout_multiplier", 0));
//
//                }
//                else
//                {
//                    settings.timeout = serial::Timeout::simpleTimeout(json.value("timeout", 1000));
//                }
//            }
//            else
//            {
//                settings.timeout = DEFAULT_TIMEOUT;
//            }

            return settings;
        }

        std::string portName;
        uint32_t baudRate = DEFAULT_BAUD_RATE;
        DataBits dataBits = DATA_BITS_EIGHT;
        Parity parity = PAR_NONE;
        StopBits stopBits = STOP_ONE;
        FlowControl flowControl = FLOW_CTRL_NONE;
        Timeout timeout = DEFAULT_TIMEOUT;

    };

    SerialDevice();

    virtual ~SerialDevice();

    bool setup(const Settings& settings);

    /// \brief Connect to the first listed device.
    bool setup(uint32_t baudRate = DEFAULT_BAUD_RATE,
               DataBits dataBits = DATA_BITS_EIGHT,
               Parity parity = PAR_NONE,
               StopBits stopBits = STOP_ONE,
               FlowControl flowControl = FLOW_CTRL_NONE,
               Timeout timeout = DEFAULT_TIMEOUT);

    bool setup(const SerialDeviceInfo& device,
               uint32_t baudRate = DEFAULT_BAUD_RATE,
               DataBits dataBits = DATA_BITS_EIGHT,
               Parity parity = PAR_NONE,
               StopBits stopBits = STOP_ONE,
               FlowControl flowControl = FLOW_CTRL_NONE,
               Timeout timeout = DEFAULT_TIMEOUT);

    bool setup(const std::string& portName,
               uint32_t baudRate = DEFAULT_BAUD_RATE,
               DataBits dataBits = DATA_BITS_EIGHT,
               Parity parity = PAR_NONE,
               StopBits stopBits = STOP_ONE,
               FlowControl flowControl = FLOW_CTRL_NONE,
               Timeout timeout = DEFAULT_TIMEOUT);

    /// \brief Read bytes until the end of line byte or until timeout.
    /// \param eol The end of line character.
    /// \param maxSize The maximum size to be read.
    /// \returns a std::string of bytes that were read.
    std::string readStringUntil(char eol = '\n',
                                std::size_t maxSize = 65536);

    /// \brief Read bytes until the end of line byte or until timeout.
    /// \param eol The end of line character.
    /// \param maxSize The maximum size to be read.
    /// \returns a vector of bytes that were read.
    std::vector<uint8_t> readBytesUntil(uint8_t eol = '\n',
                                        std::size_t maxSize = 65536);


    std::size_t readBytes(uint8_t* buffer, std::size_t size) override;
    std::size_t readByte(uint8_t& data) override;
    std::size_t available() const override;

    std::size_t writeByte(uint8_t data) override;
    std::size_t writeBytes(const uint8_t* buffer, std::size_t size) override;
    std::size_t writeBytes(const std::vector<uint8_t>& buffer) override;
    std::size_t writeBytes(std::initializer_list<uint8_t> bytes) override;
    std::size_t writeBytes(const std::string& buffer) override;
    std::size_t writeBytes(const AbstractByteSource& buffer) override;

    std::string port() const;
    OF_DEPRECATED_MSG("Use port() instead", std::string getPortName() const);

    uint32_t baudRate() const;
    OF_DEPRECATED_MSG("Use baudRate() instead", uint32_t getBauds() const);

    DataBits dataBits() const;
    OF_DEPRECATED_MSG("Use dataBits() instead", DataBits getDataBits() const);

    Parity parity() const;
    OF_DEPRECATED_MSG("Use parity() instead", SerialDevice::Parity getParity() const);

    StopBits stopBits() const;
    OF_DEPRECATED_MSG("Use stopBits() instead", StopBits getStopBits() const);

    FlowControl flowControl() const;
    OF_DEPRECATED_MSG("Use flowControl() instead", FlowControl getFlowControl() const);

    Timeout timeout() const;
    OF_DEPRECATED_MSG("Use timeout() instead", Timeout getTimeout() const);

    void flush();
    void flushInput();
    void flushOutput();

    void sendBreak(int duration);
    void setBreak(bool level = true);
    void setRequestToSend(bool level = true);
    void setDataTerminalReady(bool level = true);

    bool isClearToSend() const;
    bool isDataSetReady() const;
    bool isRingIndicated() const;
    bool isCarrierDetected() const;

    bool isOpen() const;

    /// \returns the underlying serial::Serial object if valuid, or nullptr otherwise.
    const serial::Serial* serial() const;

    serial::Serial* serial();

    enum
    {
        DEFAULT_BAUD_RATE = 9600
    };

    enum
    {
        /// \brief The default read timeout.  0 is a non-blocking timeout.
        DEFAULT_READ_TIMEOUT_CONSTANT_MS = 1000,
        DEFAULT_READ_TIMEOUT_MULTIPLIER_MS = 0,
        /// \brief The default write timeout constant.
        /// This usually blocks for one or two milliseconds.
        DEFAULT_WRITE_TIMEOUT_CONSTANT = 1000,
        DEFAULT_WRITE_TIMEOUT_MULTIPLIER = 0
    };

    /// \brief The default Serial read/write timeout.
    static const Timeout DEFAULT_TIMEOUT;

protected:
    /// \brief A pointer to the underlying serial object.
    std::shared_ptr<serial::Serial> _serial;

};


} } // namespace ofx::IO
