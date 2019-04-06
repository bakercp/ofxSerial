/*
  SLIP-OSC.ino

  listen on USB Serial for slip encoded OSC packet
  to switch an LED on and off

  Depends on [PacketSerial](https://github.com/bakercp/PacketSerial)
  and [OSC](https://github.com/CNMAT/OSC/) libraries.

  Copyright Antoine Villeret - 2015

*/
#include <OSCBundle.h>
#include <PacketSerial.h>


PacketSerial_<SLIP, SLIP::END, 8192> serial;


const uint8_t LED_PIN = 13;


void setup()
{
  serial.setPacketHandler(&onPacket);
  serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  serial.update();
}

void onPacket(const uint8_t* buffer, size_t size)
{
  OSCBundle bundle;
  bundle.fill(buffer, size);

  if (!bundle.hasError())
    bundle.dispatch("/led", onLED);
}


void onLED(OSCMessage& msg)
{
  if (msg.isInt(0))
  {
    digitalWrite(LED_PIN, msg.getInt(0));
    serial.send(msg.
  }
}

