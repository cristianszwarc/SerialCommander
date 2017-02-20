
Serial Commander
-------------------------------

Provide an interactive command line through Serial port in your Arduino / Platformio project.

This library allows you to react to user activity on the serial port and guide the user while accepting commands or values.

![Serial](terminal.gif)

**Behaviour**

When user activity is detected you can provide a welcome message and wait for a command.

A command is accepted when a new line is received (user press enter).

A timeout is in place to continue with code execution if the user does not answer.

The user input is ignored if is longer than expected or longer than the command buffer.

The received command can be compared to execute actions or can be used as input.

It allows the user to ESC or CTRL+C to cancel and allow the code to continue before timeout.

BACKSPACE is allowed to correct mistakes.

**Manual Installation**

[Download](https://github.com/cristianszwarc/SerialCommander/archive/master.zip) and decompress into your libraries folder.

**Platformio Installation**
By command line: `platformio lib install 288`

By platformio.ini:
```
...
lib_deps =
     SerialCommander
...
```

**Initialize**

```C++
#include <SerialCommander.h>			// Include library.

SerialCommander MyCommander;			// Initialize an object to use.

void setup()
{
	Serial.begin(9600);							// Initialize a serial port.
	while (!Serial) { ; }
	MyCommander.setPort(&Serial);			// Set the serial port to use.
}
```

**Detect user activity**

```C++
void loop()
{
	...
	if (MyCommander.available()) {  // If we have serial activity.
		presentOptions();							// Show some options to the user.
  };
	...
}

void presentOptions()
{
	Serial.println(F("Serial Commander"));			// A welcome msg (optional)
	Serial.println(F("conquer / surrender?"));	// Some help.

	if (MyCommander.read()) {										// Wait for user input.

		// check if we have a match
		if (MyCommander.is("conquer")) conquerFunction();
		if (MyCommander.is("surrender")) surrenderFunction();

	}

	Serial.println(F("Bye"));								// An end msg (optional)
}
```

**Request input from user**

```C++
	void conquerFunction() {
	  char country[10]; 	// a buffer to store the input

	  Serial.println(F("What country?"));

	  if (MyCommander.readTo(country, sizeof(country))) {

	    if (MyCommander.confirm(F("Are you sure?"))) {
	        // move trops to *country
	    }
	  }

	}
```

**Confirm Actions**

Confirm a command before execute an action.
Note: this expects a ```__FlashStringHelper``` .
```C++
	...
	if (MyCommander.is("surrender") && MyCommander.confirm(F("Are you sure?")) {
		// do something
	}
	...
```

**Buffer Size**

By default SerialCommander is set to read up to 30 characters plus a terminator.
You can override this by changing the line:
```C++
	...
	#define SERIAL_COMMANDER_MAX_LENGTH 30
	...

```
in `SerialCommander.h`

**Methods**

```void setPort(SerialPort);``` Set the serial port to use.

```bool available();```	Check if there are characters waiting on the serial port.

```bool read(timeout = 10000);``` Accept user input as a command for later use with ```.is("something")```

```bool is(command);``` Compare the last user input with a string.

```bool readTo(output, output_size, timeout = 10000);```	Accept user input into an array.

```bool confirm(question, timeout = 10000);``` Helper to require Y/n confirmations. **It expects the question as a FlashStringHelper!**.

**License**

MIT
