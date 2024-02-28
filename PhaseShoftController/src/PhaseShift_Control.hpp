#ifndef PHASESHIFT_CONTROL_HPP
#define PHASESHIFT_CONTROL_HPP

#include <Arduino.h>

//* Private types *//
#define TABLE_SIZE          (4)
#define AMOUNT_OF_SIZE      (4)
#define STATES              (4)

//* GPIO settings *//
#define STATUS_LED1         (13)
#define STATUS_LED2         (12)
#define BUTTON_GREEN        (11)
#define BUTTON_RED          (10)
#define BUTTON_BLUE         (9)
#define BUTTON_BLACK        (8)
#define CONTROL_SOCKET1     (7)
#define CONTROL_SOCKET2     (6)

//* UART settings *//
#define BAUDRATE            (9600)

//* Local define *//
#define DEBOUNCE_TIME_MS    (50)

typedef enum
{
    LINE_1 = 0,
    LINE_2,
    LINE_3,
    LINE_4,
}TableLine;

typedef enum
{
    STATUS_IDLE = 0,
    STATUS_MINUS_135,
    STATUS_MINUS_45,
    STATUS_PLUS_45,
    STATUS_PLUS_135,
}PhaseShiftStatus;

typedef enum
{
    IDLE = 0,
    PHASE_SHIFT_MINUS_135,
    PHASE_SHIFT_MINUS_45,
    PHASE_SHIFT_PLUS_45,
    PHASE_SHIFT_PLUS_135,
}PhaseShiftState;

void PhaseShift_GPIO_Init(void);
void PhaseShift_StateMachine(PhaseShiftState phaseShiftStateMachine, String phaseShift, PhaseShiftStatus commandStatus, 
const uint8_t outputPinTable[], const uint8_t outputValues[][STATES]);
#endif //* PHASESHIFT_CONTROL_HPP *//