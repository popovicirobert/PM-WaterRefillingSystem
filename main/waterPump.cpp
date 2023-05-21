
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
	pinInfo.write(HIGH);
}

void WaterPump::stopPump() {
	pinInfo.write(LOW);
	state = WorkingState::NOT_RUNNING;
}
