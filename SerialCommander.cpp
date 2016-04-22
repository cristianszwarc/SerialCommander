/*
  serialCommander.cpp - Interactive commands over serial port.
  Created by Cristian D. Szwarc, April 2016.
  Released into the public domain.
*/
#include "SerialCommander.h"

// attach a given serial port to be used accross our methods
void SerialCommander::setPort(Stream *SerialPort)
{
  this->Serial = SerialPort;
}

// check activity on the serial port
bool SerialCommander::available()
{
  if (this->Serial && this->Serial->available()) {
    return true;
  }
  return false;
}

// accept a command from the user for later comparison at SerialCommander::is();
bool SerialCommander::read(unsigned int timeout)
{
  return this->readTo(this->input, sizeof(this->input), timeout);
}

// check if the last received command matches with the given one
bool SerialCommander::is(const char *command)
{
  if (strncmp(command, this->input, SERIAL_COMMANDER_MAX_LENGTH) == 0) {
    return true;
  }
  return false;
}

// accept user's input into a given array.
// (checks for timeout and max size)
bool SerialCommander::readTo(char *buffer, unsigned int size, unsigned int timeout)
{
    unsigned int count = 0;
    unsigned long currentMillis  = millis();
    unsigned long previousMillis = currentMillis;
    char inChar;
    buffer[count] = '\0';             // clean the output buffer to avoid sequence issues

    // if input detected on time
    while( currentMillis - previousMillis < timeout )
    {
      // input available?
      if (this->Serial->available()) {
        inChar=this->Serial->read();

        // append the character when is not newline, carrie return, backspace, etx
        if (inChar != '\n' && inChar != '\r' && inChar != '\b' && inChar != 3 && inChar != 27) {
          buffer[count] = inChar;
          count++;
          buffer[count] = '\0';       // terminator is now at the new end

        } else if (inChar == '\b') {
          count--;                    // step back (unsigned, will never go lower than 0)
          buffer[count] = '\0';       // terminator is back again

        } else if (inChar == 3 || inChar == 27) {
          return false;               // user cancelation CTRL + C or ESC
        }

        this->Serial->print(inChar);  // user feedback

        if (inChar == '\n') {         // ends reading on newline
          return true;                // input correct, return!
        }

        if ( count >= size ) {        // invalid if longer than allowed
          return false;
        }

      }
      currentMillis = millis(); // keep time tracking
    }

    // timeout
    return false;
}

// Helper to confirm yes/no
bool SerialCommander::confirm(const __FlashStringHelper *question, unsigned int timeout)
{
  this->Serial->print(question);
  this->Serial->println(F(" Y/n"));
  if (this->readTo(this->input, 2, timeout) && this->is("Y")) {
    return true;
  }
  return false;
}
