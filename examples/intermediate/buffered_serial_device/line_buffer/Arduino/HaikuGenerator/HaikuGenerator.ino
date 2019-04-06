//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


const int numLines = 3;

String haiku[] = {
  "at the age old pond",
  "a frog leaps into water",
  "a deep resonance"
};

byte currentLine = 0;
byte currentChar = 0;

void setup()
{
  Serial.begin(115200);
}


void loop()
{
  if (currentChar < haiku[currentLine].length())
  {
    Serial.print(haiku[currentLine][currentChar]);
    currentChar++;
  }
  else
  {
    Serial.println("");
    currentChar = 0;
    currentLine = random(0, numLines);
  }

  delay(random(250));
}
