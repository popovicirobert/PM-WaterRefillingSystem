#pragma once

#include "ledMatrix.h"
#include "displayConfig.h"
#include "potentiometerConfig.h"

static constexpr int LED_MATRIX_ROWS = 8;
static constexpr int LED_MATRIX_COLS = 8;

extern LedMatrixDriver<LED_MATRIX_ROWS, LED_MATRIX_COLS> ledMatrix;

void setupLedMatrix();

void updateLedMatrix();
