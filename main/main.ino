
#include "config.h"

void setup() {
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
