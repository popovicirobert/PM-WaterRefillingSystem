
#include "ArduinoSTL.h"
#include "array"


// D22 -> R3
// D23 -> R6
// D24 -> C5
// D25 -> R8
// D26 -> C3
// D27 -> C2
// D28 -> R7
// D29 -> R5
// D30 -> R1
// D31 -> C4
// D32 -> C6
// D33 -> R4
// D34 -> C1
// D35 -> R2
// D36 -> C7
// D37 -> C8


template<size_t _RowSize, size_t _ColSize>
class LedMatrix {
public:
  LedMatrix(std::array<int, _RowSize> rowPins, std::array<int, _ColSize> colPins) : rowPins(rowPins), colPins(colPins) {}

  void turnOnLed(int row, int col) {
    digitalWrite(rowPins[row], HIGH);
    for (int i = 0; i < _ColSize; i++) {
      if (i != col) {
        digitalWrite(colPins[i], HIGH);
      } else {
        digitalWrite(colPins[i], LOW);
      }
    }
  }

  void turnOffLed(int row, int col) {
    digitalWrite(rowPins[row], LOW);
    for (int i = 0; i < _ColSize; i++) {
      digitalWrite(colPins[i], LOW);
    }
  }

  void turnAllOff() {
    for (auto pin : rowPins) {
      digitalWrite(pin, LOW);
    }

    for (auto pin : colPins) {
      digitalWrite(pin, LOW);
    }
  }

  std::array<int, _RowSize> getRowPins() {
    return rowPins;
  }

  std::array<int, _ColSize> getColPins() {
    return colPins;
  }

private:
  std::array<int, _RowSize> rowPins;
  std::array<int, _ColSize> colPins;
};


static constexpr int N = 8;
LedMatrix<N, N> ledMatrix({30, 35, 22, 33, 29, 23, 28, 25}, {34, 27, 26, 31, 24, 32, 36, 37});

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

int globalRow, globalCol;

void loop() {
  // put your main code here, to run repeatedly:
  
  ledMatrix.turnOnLed(globalRow, globalCol);
  delay(1000);
  
  ledMatrix.turnOffLed(globalRow, globalCol);
  delay(1000);

  globalCol++;
  if (globalCol == N) {
    globalCol = 0;
    globalRow = (globalRow + 1) % N;
  }
}
