/*
*/

#ifndef Cart_h
#define Cart_h

#include <Arduino.h>
#include <Servo.h>

class Cart
{
public:
    Cart(
        byte LTRV, byte LTGV, byte LTBV, byte SSPH, byte SPD,
        byte LBRV, byte LBGV, byte LBBV, byte SPBL,
        byte UV_EL1, byte UV_EL2, byte UV_T, byte UV_BL);
    // int UV_EL1, int UV_EL2, int UV_T, int UV_BL, unsigned long *t, size_t len);
    //void drawScene(String cartMode, int cartSpeed, int t);
    int readValue(String component);

private:
    Servo servo_H;
    Servo servo_D;
    Servo servo_BL;
    uint8_t pinTravRed = 12;
    uint8_t pinTravGreen = 11;
    uint8_t pinTravBlue = 10;
    uint8_t pinTravMotorSpeed = 2;
    uint8_t pinTravMotorUp = 24;
    uint8_t pinTravMotorDown = 26;
    uint8_t pinServoHeight = 28;
    uint8_t pinServoDirection = 30;

    uint8_t pinBacklightingRed = 9;
    uint8_t pinBacklightingGreen = 8;
    uint8_t pinBacklightingBlue = 7;
    uint8_t pinBacklightingServo = 32;

    uint8_t pinUViolet_EL1 = 6;
    uint8_t pinUViolet_EL2 = 5;
    uint8_t pinUViolet_T = 4;
    uint8_t pinUViolet_BL = 3;

    uint8_t ledTravRedValue;
    uint8_t ledTravGreenValue;
    uint8_t ledTravBlueValue;
    uint8_t ledBacklightRedValue;
    uint8_t ledBacklightGreenValue;
    uint8_t ledBacklightBlueValue;
    uint8_t UViolet_EL1;
    uint8_t UViolet_EL2;
    uint8_t UViolet_T;
    uint8_t UViolet_BL;
    uint8_t servoPositionHeight;
    uint8_t servoPositionDirection;
    uint8_t servoPositionBacklight;

    // unsigned long timeLine[10][10];
    // unsigned long Time;
    // unsigned long previousMillis = 0;
    int ledState;
};
#endif
