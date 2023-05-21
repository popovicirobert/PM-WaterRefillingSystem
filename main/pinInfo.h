#pragma once

#include <Arduino.h>

struct PinInfo {
	enum class PinType {
		_INPUT,
		_OUTPUT,
		_INPUT_PULLUP,
		_INPUT_PULLDOWN
	};
	
	volatile uint8_t* DDR;
	volatile uint8_t* PIN;
	volatile uint8_t* PORT;
	uint8_t ID;

	inline volatile uint8_t& getDDR() {
		return *DDR;
	}

	inline volatile uint8_t& getPIN() {
		return *PIN;
	}

	inline volatile uint8_t& getPORT() {
		return *PORT;
	}

	inline uint8_t getID() {
		return ID;
	}

	inline int read() {
		return getPIN() & (1 << getID());
	}

	inline void write(int value) {
		if (value == LOW) {
			getPORT() &= ~(1 << getID());
		} else {
			getPORT() |= (1 << getID());
		}
	}

	inline int configure(PinType type) {
		if (type == PinType::_INPUT) {
			getDDR() &= ~(1 << getID());
		} else if (type == PinType::_OUTPUT) {
			getDDR() |= (1 << getID());
		} else if (type == PinType::_INPUT_PULLUP) {
			getDDR() &= ~(1 << getID());
			write(HIGH);
		} else if (type == PinType::_INPUT_PULLDOWN) {
			getDDR() &= ~(1 << getID());
			write(LOW);
		}
	}
};
