/*
*/

#include <Arduino.h>
#include <Servo.h>
#include "Cart.h"

Servo servo_H;
Servo servo_D;
Servo servo_BL;

Cart::Cart(byte LTRV, byte LTGV, byte LTBV, byte SSPH, byte SPD,
           byte LBRV, byte LBGV, byte LBBV, byte SPBL,
           byte UV_EL1, byte UV_EL2, byte UV_T, byte UV_BL)
//  int UV_EL1, int UV_EL2, int UV_T, int UV_BL, unsigned long *t, size_t len)

// DE LA LIBRERIA SOLO SIRVE PARA DECLARAR LAS ESCENAS
{
  pinMode(pinTravRed, OUTPUT);
  pinMode(pinTravGreen, OUTPUT);
  pinMode(pinTravBlue, OUTPUT);
  pinMode(pinTravMotorUp, OUTPUT);
  pinMode(pinTravMotorDown, OUTPUT);
  pinMode(pinTravMotorSpeed, OUTPUT);

  pinMode(pinBacklightingRed, OUTPUT);
  pinMode(pinBacklightingGreen, OUTPUT);
  pinMode(pinBacklightingBlue, OUTPUT);
  pinMode(pinBacklightingServo, OUTPUT);

  pinMode(pinUViolet_EL1, OUTPUT);
  pinMode(pinUViolet_EL2, OUTPUT);
  pinMode(pinUViolet_T, OUTPUT);
  pinMode(pinUViolet_BL, OUTPUT);

  ledTravRedValue = LTRV;
  ledTravGreenValue = LTGV;
  ledTravBlueValue = LTBV;

  ledBacklightRedValue = LBRV;
  ledBacklightGreenValue = LBGV;
  ledBacklightBlueValue = LBBV;

  UViolet_EL1 = UV_EL1;
  UViolet_EL2 = UV_EL2;
  UViolet_T = UV_T;
  UViolet_BL = UV_BL;

  servoPositionHeight = SSPH;
  servoPositionDirection = SPD;
  servoPositionBacklight = SPBL;

  // memcpy(timeLine, t, 10 * 10 * sizeof(timeLine)); //AQUI HACIA LA COPIA DEL TIMELINE
  // Time = millis();
}

//ESTO ERA EL DRAWSCENE
// void Cart::drawScene(String cartMode, int cartSpeed, int t)
// {
//   servo_H.attach(pinServoHeight);
//   servo_D.attach(pinServoDirection);
//   servo_BL.attach(pinBacklightingServo);

//   do
//   {
//     if (cartMode == "RIGHT")
//     {
//       digitalWrite(pinTravMotorUp, HIGH);
//       digitalWrite(pinTravMotorDown, LOW);
//       analogWrite(pinTravMotorSpeed, cartSpeed);
//     }

//     if (cartMode == "LEFT")
//     {
//       digitalWrite(pinTravMotorUp, LOW);
//       digitalWrite(pinTravMotorDown, HIGH);
//       analogWrite(pinTravMotorSpeed, cartSpeed);
//     }

//     if (cartMode == "STOP")
//     {
//       digitalWrite(pinTravMotorUp, LOW);
//       digitalWrite(pinTravMotorDown, LOW);
//       analogWrite(pinTravMotorSpeed, 0);
//     }

//     analogWrite(pinTravRed, ledTravRedValue);
//     analogWrite(pinTravGreen, ledTravGreenValue);
//     analogWrite(pinTravBlue, ledTravBlueValue);
//     servo_H.write(servoPositionHeight);
//     servo_D.write(servoPositionDirection);

//     analogWrite(pinBacklightingRed, ledBacklightRedValue);
//     analogWrite(pinBacklightingGreen, ledBacklightGreenValue);
//     analogWrite(pinBacklightingBlue, ledBacklightBlueValue);
//     servo_BL.write(servoPositionBacklight);

//     analogWrite(pinUViolet_EL1, UViolet_EL1);
//     analogWrite(pinUViolet_EL2, UViolet_EL2);
//     analogWrite(pinUViolet_T, UViolet_T);
//     analogWrite(pinUViolet_BL, UViolet_BL);
//   } while (millis() < timeLine[t + 1]);
//   //delay(t);
//   Serial.println("tiempos");
//   Serial.println(timeLine[t]);
//   Serial.println(timeLine[t + 1]);
//   digitalWrite(pinTravMotorUp, LOW);
//   digitalWrite(pinTravMotorDown, LOW);
//   analogWrite(pinTravMotorSpeed, 0);
//   servo_H.detach();
//   servo_D.detach();
//   servo_BL.detach();
// }

int Cart::readValue(String component)
{

  if (component == "LTRV")
  {
    return this->ledTravRedValue;
  }

  if (component == "LTGV")
  {
    return this->ledTravGreenValue;
  }

  if (component == "LTBV")
  {
    return this->ledTravBlueValue;
  }

  if (component == "LBRV")
  {
    return this->ledBacklightRedValue;
  }

  if (component == "LBGV")
  {
    return this->ledBacklightGreenValue;
  }

  if (component == "LBBV")
  {
    return this->ledBacklightBlueValue;
  }

  if (component == "UV_EL1")
  {
    return this->UViolet_EL1;
  }

  if (component == "UV_EL2")
  {
    return this->UViolet_EL2;
  }

  if (component == "UV_T")
  {
    return this->UViolet_T;
  }

  if (component == "UV_BL")
  {
    return this->UViolet_BL;
  }

  if (component == "SSPH")
  {
    return this->servoPositionHeight;
  }

  if (component == "SPD")
  {
    return this->servoPositionDirection;
  }

  if (component == "SPBL")
  {
    return this->servoPositionBacklight;
  }
}
