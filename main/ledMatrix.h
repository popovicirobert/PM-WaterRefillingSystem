#pragma once

#include "ArduinoSTL.h"
#include "array"

static constexpr int DIGIT_ROWS = 5;
static constexpr int DIGIT_COLS = 3;

static char digits[10][DIGIT_ROWS][DIGIT_COLS] = 
         {{{'1', '1', '1'}, 
          {'1', '0', '1'},
          {'1', '0', '1'},
          {'1', '0', '1'},
          {'1', '1', '1'}},

          {{'0', '0', '1'}, 
          {'0', '0', '1'},
          {'0', '0', '1'},
          {'0', '0', '1'},
          {'0', '0', '1'}},

          {{'1', '1', '1'}, 
          {'0', '0', '1'},
          {'1', '1', '1'},
          {'1', '0', '0'},
          {'1', '1', '1'}},

          {{'1', '1', '1'}, 
          {'0', '0', '1'},
          {'1', '1', '1'},
          {'0', '0', '1'},
          {'1', '1', '1'}},

          {{'1', '0', '1'}, 
          {'1', '0', '1'},
          {'1', '1', '1'},
          {'0', '0', '1'},
          {'0', '0', '1'}},

          {{'1', '1', '1'}, 
          {'1', '0', '0'},
          {'1', '1', '1'},
          {'0', '0', '1'},
          {'1', '1', '1'}},

          {{'1', '1', '1'}, 
          {'1', '0', '0'},
          {'1', '1', '1'},
          {'1', '0', '1'},
          {'1', '1', '1'}},

          {{'1', '1', '1'}, 
          {'0', '0', '1'},
          {'0', '0', '1'},
          {'0', '0', '1'},
          {'0', '0', '1'}},

          {{'1', '1', '1'}, 
          {'1', '0', '1'},
          {'1', '1', '1'},
          {'1', '0', '1'},
          {'1', '1', '1'}},

          {{'1', '1', '1'}, 
          {'1', '0', '1'},
          {'1', '1', '1'},
          {'0', '0', '1'},
          {'1', '1', '1'}}};
          

template<size_t _RowSize, size_t _ColSize>
class LedMatrix {
public:
  LedMatrix(std::array<int, _RowSize> rowPins, std::array<int, _ColSize> colPins) : rowPins(rowPins), colPins(colPins) {}

private:
  void write(int pin, int value) {
    digitalWrite(pin, value);
  }

public:
  void turnOnLed(int row, int col) {
    for (int i = 0; i < _ColSize; i++) {
      if (i != col) {
        write(colPins[i], HIGH);
      } else {
        write(colPins[i], LOW);
      }
    }
    write(rowPins[row], HIGH);
  }

  void turnOffLed(int row, int col) {
    write(rowPins[row], LOW);
    for (int i = 0; i < _ColSize; i++) {
      write(colPins[i], LOW);
    }
  }

  void turnAllOff() {
    for (auto pin : rowPins) {
      write(pin, LOW);
    }

    for (auto pin : colPins) {
      write(pin, LOW);
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


template<size_t _RowSize, size_t _ColSize>
class LedMatrixDriver : public LedMatrix<_RowSize, _ColSize> {
public:
  LedMatrixDriver(std::array<int, _RowSize> rowPins, std::array<int, _ColSize> colPins) : LedMatrix<_RowSize, _ColSize>(rowPins, colPins) {}
  
  void drawDigit(int digit, int offsetRow, int offsetCol) {
    for (int r = 0; r < DIGIT_ROWS; r++) {
      for (int c = 0; c < DIGIT_COLS; c++) {
        int row = r + offsetRow;
        int col = c + offsetCol;
        if (digits[digit][r][c] == '1') {
          this->turnOnLed(row, col);
        }
        this->turnOffLed(row, col);
      }
    }
  }

  void drawDigit(int digit) {
    drawDigit(digit, 0, 0);
  }
};
