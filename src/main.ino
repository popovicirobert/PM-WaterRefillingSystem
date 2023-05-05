
#include "ledMatrix.h"

static constexpr int LED_MATRIX_ROWS = 8;
static constexpr int LED_MATRIX_COLS = 8;

LedMatrixDriver<LED_MATRIX_ROWS, LED_MATRIX_COLS> ledMatrix({30, 35, 22, 33, 29, 23, 28, 25}, {34, 27, 26, 31, 24, 32, 36, 37});
                                            

void setup() {
  Serial.begin(9600);
  
  for (auto pin : ledMatrix.getRowPins()) {
    pinMode(pin, OUTPUT);  
  }

  for (auto pin : ledMatrix.getColPins()) {
    pinMode(pin, OUTPUT);
  }
  
  ledMatrix.turnAllOff();
}


void loop() {
  int sensorValue = analogRead(A0);
  int number = map(sensorValue, 0, 1023, 0, 9);
  ledMatrix.drawDigit(number, 0, 3);
  
}
