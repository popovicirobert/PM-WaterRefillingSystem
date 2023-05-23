
#include "config.h"

static constexpr int BAUD_RATE = 9600;

void setup() {
	Logger::setup(BAUD_RATE);
	
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
