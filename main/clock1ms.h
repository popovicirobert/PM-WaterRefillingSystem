#pragma once

#include <avr/interrupt.h>

static volatile long long tickCounter = 0LL;

namespace clock_1ms {
	static long long lastTickCounter = 0LL;
	
	void startClock();
	
	bool periodElapsed();

	long long getTickCounter();
}
