#include "PhaseShift_Control.hpp"


void PhaseShift_GPIO_Init(void)
{
    //* GPIO mode settings *//
    pinMode(CONTROL_SOCKET1, OUTPUT);
    pinMode(CONTROL_SOCKET2, OUTPUT);
    pinMode(STATUS_LED1, OUTPUT);
    pinMode(STATUS_LED2, OUTPUT);
    pinMode(BUTTON_GREEN, INPUT_PULLUP);
    pinMode(BUTTON_RED, INPUT_PULLUP);
    pinMode(BUTTON_BLUE, INPUT_PULLUP);
    pinMode(BUTTON_BLACK, INPUT_PULLUP);

  //* If system start, all outputs set to LOW *//
    digitalWrite(CONTROL_SOCKET1, LOW);
    digitalWrite(CONTROL_SOCKET2, LOW);
    digitalWrite(STATUS_LED1, LOW);
    digitalWrite(STATUS_LED2, LOW);

  //* Set UART baudrate *//
    Serial.begin(BAUDRATE);
}