
#include "waterPump.h"

WaterPump::WaterPump(PinInfo pinInfo) {
	this->pinInfo = pinInfo;
	pinInfo.configure(PinInfo::PinType::_OUTPUT);
	stopPump();
}

void WaterPump::startPump() {
	if (state == WorkingState::RUNNING) {
		return;
	}
	pinInfo.write(LOW);
}

void WaterPump::stopPump() {
	pinInfo.write(HIGH);
	state = WorkingState::NOT_RUNNING;
}
