/*
  serialCommander.h - Interactive commands over serial port.
  Created by Cristian D. Szwarc, April 2016.
  Released into the public domain.
*/
#ifndef SERIAL_COMMANDER
#define SERIAL_COMMANDER

#define SERIAL_COMMANDER_MAX_LENGTH 30

#include <Arduino.h>

class SerialCommander
{
  private:
    Stream * Serial;
    char input[SERIAL_COMMANDER_MAX_LENGTH + 1];

  public:
    void setPort(Stream *SerialPort);
    bool read(unsigned int timeout = 10000);
    bool readTo(char *buffer, unsigned int size, unsigned int timeout = 10000);
    bool available();
    bool is(const char *command);
    bool confirm(const __FlashStringHelper *question, unsigned int timeout = 10000);

};

#endif
