
#include "ledMatrix.h"
#include "clock1ms.h"

static constexpr int LED_MATRIX_ROWS = 8;
static constexpr int LED_MATRIX_COLS = 8;

LedMatrixDriver<LED_MATRIX_ROWS, LED_MATRIX_COLS> ledMatrix({30, 35, 22, 33, 29, 23, 28, 25}, {34, 27, 26, 31, 24, 32, 36, 37});
int potentiometerValue;

void setup() {
	// start 1ms high-precision clock
	clock_1ms::startClock();

	potentiometerValue = analogRead(A0);
}


void loop() {
	if (clock_1ms::periodElapsed()) {
		potentiometerValue = analogRead(A0);
		
		// ToDo: check water pump state
	}
	
	int displayNumber = map(potentiometerValue, 0, 1023, 99, 0);
	ledMatrix.drawNumber(displayNumber, 3, 0);
}
