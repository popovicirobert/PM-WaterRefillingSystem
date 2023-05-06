
#include "ledMatrix.h"

static constexpr int LED_MATRIX_ROWS = 8;
static constexpr int LED_MATRIX_COLS = 8;

LedMatrixDriver<LED_MATRIX_ROWS, LED_MATRIX_COLS> ledMatrix({30, 35, 22, 33, 29, 23, 28, 25}, {34, 27, 26, 31, 24, 32, 36, 37});

volatile bool shouldUpdate = false;
int potentiometerValue;

ISR(TIMER1_COMPA_vect) {
  shouldUpdate = true;
}

void setUpTimer() {
  // disable all interrupts
  cli();

  // we want to check status every 10ms (f = 100Hz)
  // f_clk = 16MHz => N = 256 and OCR1A = 624

  TCNT1 = 0;
  TCCR1A = 0;
  TCCR1B = 0;
  
  OCR1A = 624;
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  
  TIMSK1 |= (1 << OCIE1A);  // OCR1A compare match interrupt

  // enable back interrupts
  sei();
}

void setUpLedMatrix() {
  // set row pins as OUTPUT
  for (auto pin : ledMatrix.getRowPins()) {
    pinMode(pin, OUTPUT);  
  }

  // set column pins as OUTPUT
  for (auto pin : ledMatrix.getColPins()) {
    pinMode(pin, OUTPUT);
  }

  // turn off all matrix leds
  ledMatrix.turnAllOff();

  setUpTimer();
}

void setup() {
  Serial.begin(9600);

  setUpLedMatrix();

  potentiometerValue = analogRead(A0);
}


void loop() {
  if (shouldUpdate) {
    potentiometerValue = analogRead(A0);
    
    // ToDo: check water pump state
    
    shouldUpdate = false;
  }
  
  int number = map(potentiometerValue, 0, 1023, 0, 9);
  ledMatrix.drawDigit(number, 0, 3);
}
