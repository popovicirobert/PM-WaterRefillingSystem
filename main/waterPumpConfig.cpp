#include "waterPumpConfig.h"

static constexpr PinInfo WATER_PUMP_PIN_INFO = {&DDRL, &PINL, &PORTL, PL1};
WaterPump waterPump(WATER_PUMP_PIN_INFO);

void setupWaterPump() {
	// ToDo: add setup if necessary
}