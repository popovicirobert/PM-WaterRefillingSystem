#include "potentiometerConfig.h"

static constexpr int POTENTIOMETER_PIN = A0;
int potentiometerValue = 0;

void updatePotentiometer() {
	potentiometerValue = analogRead(POTENTIOMETER_PIN);
}
