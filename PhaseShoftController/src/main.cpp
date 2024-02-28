#include <Arduino.h>
#include "PhaseShift_Control.hpp"

//* Private variables *//
const uint8_t outputPinTable[TABLE_SIZE] = {STATUS_LED1, STATUS_LED2, CONTROL_SOCKET1, CONTROL_SOCKET2};

const uint8_t outputValues[TABLE_SIZE][STATES] = {
  {LOW, LOW, LOW, LOW},
  {HIGH, LOW, HIGH, LOW},
  {LOW, HIGH, LOW, HIGH},
  {HIGH, HIGH, HIGH, HIGH}
};

const String uartLogTable[TABLE_SIZE] = {
  "Setting phaseshift on: -135 (B0 = 0, B1 = 0)",
  "Setting phaseshift on:  -45 (B0 = 1, B1 = 0)",
  "Setting phaseshift on:   45 (B0 = 0, B1 = 1)",
  "Setting phaseshift on:  135 (B0 = 1, B1 = 1)"
};

//* Private variables *//
PhaseShiftState phaseShiftStateMachine = IDLE;
String phaseShift = "\0";
PhaseShiftStatus commandStatus = STATUS_IDLE;

//* Setup *//
void setup()
{
    PhaseShift_GPIO_Init();
}

//* Main loop *//
void loop()
{
  //* State machine routine*//
  PhaseShift_StateMachine(phaseShiftStateMachine, phaseShift, commandStatus, outputPinTable, outputValues);
}

