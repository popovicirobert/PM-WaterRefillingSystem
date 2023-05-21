#pragma once

#include "button.h"
#include "waterPumpConfig.h"
#include "displayConfig.h"
#include "eventHandlerConfig.h"

static constexpr PinInfo BUTTON_PIN_INFO = {&DDRD, &PIND, &PORTD, PD0};
AbstractCallableButton* button;

void printNumber(long long value) {
	static char temp[100];
	memset(temp, 0, sizeof(temp));

	int sz = 0;
	while (value > 0) {
		temp[sz++] = value % 10 + '0';	
		value /= 10;
	}

	int l = 0, r = sz - 1;
	while (l < r) {
		std::swap(temp[l], temp[r]);
		l++, r--;
	}

	Serial.println(temp);
}

void setupButton() {
	auto buttonCallback = []() {
		if (waterPump.getState() == WaterPump::WorkingState::RUNNING)
			return;
		
		// multiply displayNumber with SCALE_FACTOR for better granularity
		static constexpr int SCALE_FACTOR = 10;
		long long fillTime = WaterPump::getFillTime(displayNumber * SCALE_FACTOR);
		long long currentTime = clock_1ms::getTickCounter();
		long long expireTime = fillTime + currentTime;

		Serial.print("Current time: ");
		printNumber(currentTime);

		Serial.print("Fill time: ");
		printNumber(fillTime);
		
		Serial.print("Expire time: ");
		printNumber(expireTime);

		Serial.println("Starting pump...");
		waterPump.startPump();

		auto eventCallback = []() {
			Serial.print("Stopping pump: ");
			printNumber(clock_1ms::getTickCounter());
			waterPump.stopPump(); 
		};

		using event_callback_t = decltype(eventCallback);
		eventHandler.addEvent<event_callback_t>(expireTime, eventCallback);
	};


	using button_callback_t = decltype(buttonCallback);
	button = new CallableButton<button_callback_t>(BUTTON_PIN_INFO, buttonCallback);
}


void updateButton() {
	button->checkButton();
}
