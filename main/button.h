#pragma once

#include "clock1ms.h"
#include "pinInfo.h"

class AbstractButton {
public:
	AbstractButton(PinInfo pinInfo) {
		this->pinInfo = pinInfo;
	}

protected:
	PinInfo pinInfo;
};

class AbstractCallableButton : public AbstractButton {
public:
	enum class CallbackActivation {
		RISING_EDGE,
		FALLING_EDGE
	};

	AbstractCallableButton(PinInfo pinInfo) : AbstractButton(pinInfo) {}

	static inline CallbackActivation getFallingEdge() {
		return CallbackActivation::FALLING_EDGE;
	}

	static inline CallbackActivation getRisingEdge() {
		return CallbackActivation::RISING_EDGE;
	}
	
	virtual void checkButton() = 0;
};

template<typename T>
class BaseCallableButton : public AbstractCallableButton {
public:
	BaseCallableButton(PinInfo pinInfo, const T& callback, CallbackActivation activationEdge)
		: AbstractCallableButton(pinInfo),
		  callback(callback) {

		this->activationEdge = activationEdge;
		if (activationEdge == CallbackActivation::RISING_EDGE) {
			pinInfo.configure(PinInfo::PinType::_INPUT_PULLDOWN);
		} else {
			pinInfo.configure(PinInfo::PinType::_INPUT_PULLUP);
		}
	}

	inline bool isActiveOnFallingEdge() {
		return activationEdge == CallbackActivation::FALLING_EDGE;
	}

	inline bool isActiveOnRisingEdge() {
		return activationEdge == CallbackActivation::RISING_EDGE;
	}

protected:
	CallbackActivation activationEdge;
	const T& callback;
};

template<typename T>
class CallableButton : public BaseCallableButton<T> {
public:
	using CallbackActivation = AbstractCallableButton::CallbackActivation;
	
	CallableButton(PinInfo pinInfo, const T& callback, CallbackActivation activationEdge) 
		: BaseCallableButton<T>(pinInfo, callback, activationEdge) {}

	CallableButton(PinInfo pin, const T& callback) 
		: CallableButton<T>(pin, callback, AbstractCallableButton::getFallingEdge()) {}

	void checkButton() override {
		const long long tickCounter = clock_1ms::getTickCounter();
		
		int currentButtonState = this->pinInfo.read();
		if (lastButtonState != currentButtonState) {
			lastDebounceTime = tickCounter;
		}
		
		if (tickCounter - lastDebounceTime > DEBOUNCE_TIME_MILLIS) {
			if (currentButtonState != debouncedButtonState) {
				debouncedButtonState = currentButtonState;
				if (debouncedButtonState == LOW && isActiveOnFallingEdge() ||
				    debouncedButtonState == HIGH && isActiveOnRisingEdge()) {
					callback();
				}
			}
		}

		lastButtonState = currentButtonState;
	}

private:
	static constexpr long long DEBOUNCE_TIME_MILLIS = 50;
	
	int lastButtonState;
	int debouncedButtonState;
	long long lastDebounceTime;
};
