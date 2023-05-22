#pragma once

#include "button.h"
#include "waterPumpConfig.h"
#include "displayConfig.h"
#include "eventHandlerConfig.h"
#include "logger.h"

static constexpr PinInfo BUTTON_PIN_INFO = {&DDRD, &PIND, &PORTD, PD0};
AbstractCallableButton* button;
static Logger logger = Logger::getLogger();

void setupButton() {
	auto buttonCallback = []() {
		if (waterPump.getState() == WaterPump::WorkingState::RUNNING)
			return;
		
		// multiply displayNumber with SCALE_FACTOR for better granularity
		static constexpr int SCALE_FACTOR = 10;
		long long fillTime = WaterPump::getFillTime(displayNumber * SCALE_FACTOR);
		long long currentTime = clock_1ms::getTickCounter();
		long long expireTime = fillTime + currentTime;

		logger.debug().append("Current time: ").append(currentTime).commit();
		logger.debug().append("Fill time: ").append(fillTime).commit();
		logger.debug().append("Expire time: ").append(expireTime).commit();

		logger.info().append("Starting pump...").commit();

		auto eventCallback = []() {
			logger.info().append("Stopping pump...").append(clock_1ms::getTickCounter()).commit();
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
