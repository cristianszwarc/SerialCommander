// SerialCommander example
// Cristian D. Szwarc
// April 2016

#include <SerialCommander.h>

SerialCommander MyCommander;	               // Initialize

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }
  MyCommander.setPort(&Serial);	              // set the serial port to use
}

void loop() {

  if (MyCommander.available()) {              // if we have serial activity
    presentOptions();							            // your custom function
  };

}

void presentOptions()
{
  Serial.println(F("Serial Commander"));			// A welcome msg (optional)
	Serial.println(F("conquer / surrender?"));	// Some help.

	if (MyCommander.read()) {								    // allow user input (default timeout 10 seconds)

		// expect a simple command
		if (MyCommander.is("conquer")) conquerFunction();

    // command with confirmation
    if (MyCommander.is("surrender") && MyCommander.confirm(F("Are you sure?"))) {
  		Serial.println(F("White flag!"));
  	}

	}

	Serial.println(F("Bye"));								    // end msg (optional)
}

// a function that requires input from user
void conquerFunction() {
  char country[10]; 	                       // a buffer to store the input

  Serial.println(F("What country?"));

  if (MyCommander.readTo(country, sizeof(country))) {

    if (MyCommander.confirm(F("Are you sure?"))) {
        Serial.print(F("Moving army to: "));
        Serial.println(country);
    }
  }

}
