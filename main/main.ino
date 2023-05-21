
#include "config.h"

constexpr int POTENTIOMETER_PIN = A0;
int potentiometerValue = 0;

void updatePotentiometer() {
	potentiometerValue = analogRead(POTENTIOMETER_PIN);
}

void updateLedMatrix() {
	displayNumber = map(potentiometerValue, 0, 1023, DISPLAY_RANGE_HIGH, DISPLAY_RANGE_LOW);
	ledMatrix.drawNumber(displayNumber, DISPLAY_OFFSET_ROW, DISPLAY_OFFSET_COL);
}


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
