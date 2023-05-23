#include "clock1ms.h"

static volatile long long tickCounter = 0LL;

ISR(TIMER1_COMPA_vect) {
	tickCounter++;
}

namespace clock_1ms {
	void startClock() {
		// disable all interrupts
		cli();
		
		// we want to check status every 1ms (f = 1KHz)
		// f_clk = 16MHz => N = 64 and OCR1A = 249
		
		TCNT1 = 0;
		TCCR1A = 0;
		TCCR1B = 0;
		
		OCR1A = 249;
		TCCR1B |= (1 << WGM12);   // CTC mode
		TCCR1B |= (1 << CS11);    // 64 prescaler 
		TCCR1B |= (1 << CS10);
		
		TIMSK1 |= (1 << OCIE1A);  // OCR1A compare match interrupt
		
		// enable back interrupts
		sei();
	}

	bool periodElapsed() {
		const long long elapsed = tickCounter - lastTickCounter;
		lastTickCounter = tickCounter;
		return elapsed > 0;
	}

	long long getTickCounter() {
		return tickCounter;
	}
}
