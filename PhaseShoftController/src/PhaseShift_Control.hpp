#ifndef PHASESHIFT_CONTROL_HPP
#define PHASESHIFT_CONTROL_HPP

#include <Arduino.h>

//* Private types *//

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

#endif //* PHASESHIFT_CONTROL_HPP *//