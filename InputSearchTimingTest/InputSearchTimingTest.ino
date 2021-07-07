#include "Arduino.h"


#define OPEN false
#define CLOSED true


static constexpr unsigned short SWITCH_PIN_INDEX = A0;
unsigned long lastDebounceTime = 0;
static constexpr unsigned short DEBOUNCE_DELAY = 25;

unsigned short pinValue = 0;


void setup() {
	Serial.begin(9600);
	while(!Serial) {
		delay(250);
	}

	pinMode(SWITCH_PIN_INDEX, INPUT);
}


void loop() {
	pinValue = analogRead(SWITCH_PIN_INDEX);

	Serial.print(millis());
	Serial.print(F(" "));
	Serial.println(pinValue);


	/*if(pinValue != lastSwitchState) {
		lastDebounceTime = millis();
	}

	if(millis() - lastDebounceTime > DEBOUNCE_DELAY) {
		if(pinValue == HIGH) {
			if(switchState != CLOSED) {
				Serial.println(millis());
				switchState = CLOSED;
			}
		} else {
			if(switchState != OPEN) {
				Serial.println(millis());
				switchState = OPEN;
			}
		}
	}

	lastSwitchState = pinValue;*/
}
