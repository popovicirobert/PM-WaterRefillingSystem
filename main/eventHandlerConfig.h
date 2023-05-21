#pragma once

#include "eventHandler.h"

EventHandler eventHandler;

void setupEventHandler() {
	// ToDo: add setup if necessary
}


void updateEvents() {
	eventHandler.checkEvents();
}
