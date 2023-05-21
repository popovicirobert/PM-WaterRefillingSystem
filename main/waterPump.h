#pragma once

#include "pinInfo.h"

class WaterPump {
public:
	enum class WorkingState {
		RUNNING,
		NOT_RUNNING
	};

	WaterPump(PinInfo pinInfo);

	void startPump();

	void stopPump();

	inline WorkingState getState() {
		return state;
	}

	/**
	 * arg[1]: volume - volume that should be filled measured in ml
	 * ret: expected time in which the volume will be filled measured in ms
	 */
	static double getFillTime(double volume) {
		return volume / FLOW_PER_MILLI;
	}

private:
	static constexpr double FLOW_PER_SEC = 35; // 35 ml/s
	static constexpr double FLOW_PER_MILLI = FLOW_PER_SEC / 1000.0f;

	PinInfo pinInfo;
	WorkingState state;
};
