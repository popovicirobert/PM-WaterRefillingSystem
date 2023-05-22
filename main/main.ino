
#include "config.h"

void setup() {
	Serial.begin(9600);
	
	setupClock();
	
	setupLedMatrix();
	
	setupButton();
	
	setupWaterPump();
	
	setupEventHandler();
}

void loop() {	
	if (clock_1ms::periodElapsed()) {
		
		updatePotentiometer();
		
		updateEvents();
		
		updateButton();
	}

	updateLedMatrix();
}
