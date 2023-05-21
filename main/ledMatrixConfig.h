#pragma once

#include "ledMatrix.h"

static constexpr int LED_MATRIX_ROWS = 8;
static constexpr int LED_MATRIX_COLS = 8;

static const std::array<PinInfo, LED_MATRIX_ROWS> ROW_PINS = 
	{{&DDRC, &PINC, &PORTC, PC7},
	 {&DDRC, &PINC, &PORTC, PC2},
	 {&DDRA, &PINA, &PORTA, PA0},
	 {&DDRC, &PINC, &PORTC, PC4},
	 {&DDRA, &PINA, &PORTA, PA7},
	 {&DDRA, &PINA, &PORTA, PA1},
	 {&DDRA, &PINA, &PORTA, PA6},
	 {&DDRA, &PINA, &PORTA, PA3}};

static const std::array<PinInfo, LED_MATRIX_COLS> COL_PINS = 
	{{&DDRC, &PINC, &PORTC, PC3},
	 {&DDRA, &PINA, &PORTA, PA5},
	 {&DDRA, &PINA, &PORTA, PA4},
	 {&DDRC, &PINC, &PORTC, PC6},
	 {&DDRA, &PINA, &PORTA, PA2},
	 {&DDRC, &PINC, &PORTC, PC5},
	 {&DDRC, &PINC, &PORTC, PC1},
	 {&DDRC, &PINC, &PORTC, PC0}};


LedMatrixDriver<LED_MATRIX_ROWS, LED_MATRIX_COLS> ledMatrix(ROW_PINS, COL_PINS);

void setupLedMatrix() {
	// ToDo: add setup if necessary
}
