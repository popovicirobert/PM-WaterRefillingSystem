#pragma once

#include <avr/interrupt.h>

namespace clock_1ms {
	static long long lastTickCounter = 0LL;
	
	void startClock();
	
	bool periodElapsed();

	long long getTickCounter();
}
