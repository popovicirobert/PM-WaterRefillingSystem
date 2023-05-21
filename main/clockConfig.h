#pragma once

#include "clock1ms.h"

void setupClock() {
	// start 1ms high-precision clock
	clock_1ms::startClock();
}
