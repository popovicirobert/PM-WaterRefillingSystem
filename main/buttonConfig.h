#pragma once

#include "button.h"
#include "waterPumpConfig.h"
#include "displayConfig.h"
#include "eventHandlerConfig.h"
#include "logger.h"

extern AbstractCallableButton* button;

void setupButton();

void updateButton();
