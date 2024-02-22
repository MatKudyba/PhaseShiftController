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

//* Prototypes of private functions *//
static bool isButtonPressed(const uint8_t button);
static String getUartCommand(void);
static PhaseShiftStatus checkCommand(String command);
static void setPhaseShift(const uint8_t *outputsTable, const uint8_t phaseShiftTable[][4], const TableLine line);
static void sendUartLog(const uint8_t line);
static PhaseShiftState setPhaseShiftState(const PhaseShiftStatus command);

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

  phaseShift = getUartCommand();
  commandStatus = checkCommand(phaseShift);
  phaseShiftStateMachine = setPhaseShiftState(commandStatus);

  switch(phaseShiftStateMachine)
  {
    case IDLE:
      //* Do idle *//
      break;

    case PHASE_SHIFT_MINUS_135: //* Phase shift by -135 *//
      setPhaseShift(outputPinTable, outputValues, LINE_1);
      sendUartLog(LINE_1);
      phaseShiftStateMachine = IDLE;
      break;

    case PHASE_SHIFT_MINUS_45: //* Phase shift by -45 *//
      setPhaseShift(outputPinTable, outputValues, LINE_2);
      sendUartLog(LINE_2);
      phaseShiftStateMachine = IDLE;
      break;

    case PHASE_SHIFT_PLUS_45: //* Phase shift by 45 *//
      setPhaseShift(outputPinTable, outputValues, LINE_3);
      sendUartLog(LINE_3);
      phaseShiftStateMachine = IDLE;
      break;

    case PHASE_SHIFT_PLUS_135: //* Phase shift by 135 *//
      setPhaseShift(outputPinTable, outputValues, LINE_4);
      sendUartLog(LINE_4);
      phaseShiftStateMachine = IDLE;
      break;

    default:
      phaseShiftStateMachine = IDLE;
      break;
  }
}

static bool isButtonPressed(const uint8_t button)
{
  const uint8_t debounceDelay = DEBOUNCE_TIME_MS;
  static unsigned long lastDebounceTime = 0;
  bool retStatus;
  bool currentStatus;

  uint8_t value = digitalRead(button);
  if ((millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();

    currentStatus = (LOW == value);

    if (currentStatus != retStatus) {
      retStatus = currentStatus;
    }
  }

  return retStatus;
}

static String getUartCommand(void)
{
  String command;
  if(Serial.available() > 0) 
  {
    command = Serial.readStringUntil('\n');
  }
  else
  {
    command = "\0";
  }
  return command;
}

static PhaseShiftStatus checkCommand(String command)
{
  PhaseShiftStatus status;
  if(command.equals("-135"))
  {
    status = STATUS_MINUS_135;
  }
  else if(command.equals("-45"))
  {
    status = STATUS_MINUS_45;
  }
  else if(command.equals("45"))
  {
    status = STATUS_PLUS_45;
  }
    else if(command.equals("135"))
  {
    status = STATUS_PLUS_135;
  }
    else
  {
    status = STATUS_IDLE;
  }
  return status;
}

static void setPhaseShift(const uint8_t *outputsTable, const uint8_t phaseShiftTable[][STATES], const TableLine line)
{
  uint8_t tmpIndex = 0;

  for (uint8_t i = 0; i < AMOUNT_OF_SIZE; i++)
  {
    tmpIndex = phaseShiftTable[line][i];
    digitalWrite(outputsTable[i], tmpIndex);
  }
  
} 

static void sendUartLog(const uint8_t line)
{
  Serial.println(uartLogTable[line]);
}

static PhaseShiftState setPhaseShiftState(const PhaseShiftStatus command)
{
  PhaseShiftState state;

  if(isButtonPressed(BUTTON_GREEN) || (STATUS_MINUS_135 == command))
    {
      state = PHASE_SHIFT_MINUS_135;
    }
  else if(isButtonPressed(BUTTON_RED) || (STATUS_MINUS_45 == command))
    {
      state = PHASE_SHIFT_MINUS_45;
    }
  else if(isButtonPressed(BUTTON_BLUE) || (STATUS_PLUS_45 == command))
  {
    state = PHASE_SHIFT_PLUS_45;
  }
  else if(isButtonPressed(BUTTON_BLACK) || (STATUS_PLUS_135 == command))
  {
    state = PHASE_SHIFT_PLUS_135;
  }
  else
  {
    state = IDLE;
  }

  return state;
}