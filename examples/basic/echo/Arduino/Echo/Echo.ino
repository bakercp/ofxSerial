//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


void setup()
{
  Serial.begin(115200);
}


void loop()
{
  while (Serial.available() > 0)
  {
      Serial.write(Serial.read());
  }
  
  delay(10);
}
