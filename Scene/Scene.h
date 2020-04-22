/*
*/

#ifndef Scene_h
#define Scene_h

#include <Arduino.h>

class Scene
{
public:
    Scene(
        byte LRV_1, byte LGV_1, byte LBV_1, byte SP_1,
        byte LRV_2, byte LGV_2, byte LBV_2, byte SP_2);
    int readValue(String component);

private:
    uint8_t pinLedRedElevator_1 = 6;
    uint8_t pinLedGreenElevator_1 = 5;
    uint8_t pinLedBlueElevator_1 = 4;
    uint8_t pinServoElevator_1 = 3;

    uint8_t motorPinHigh_1 = 24;
    uint8_t motorPinLow_1 = 22;
    uint8_t motorPinSpeed_1 = 11;

    uint8_t pinLedRedElevator_2 = 9;
    uint8_t pinLedGreenElevator_2 = 8;
    uint8_t pinLedBlueElevator_2 = 7;
    uint8_t pinServoElevator_2 = 2;

    uint8_t motorPinHigh_2 = 26;
    uint8_t motorPinLow_2 = 28;
    uint8_t motorPinSpeed_2 = 12;

    uint8_t ledRedValueElevator_1;
    uint8_t ledGreenValueElevator_1;
    uint8_t ledBlueValueElevator_1;
    uint8_t servoPositionElevator_1;

    uint8_t ledRedValueElevator_2;
    uint8_t ledGreenValueElevator_2;
    uint8_t ledBlueValueElevator_2;
    uint8_t servoPositionElevator_2;
};

#endif
