

#include <Arduino.h>
#include "Scene.h"

Scene::Scene(byte LRV_1, byte LGV_1, byte LBV_1, byte SP_1,
             byte LRV_2, byte LGV_2, byte LBV_2, byte SP_2)
{
  pinMode(pinLedRedElevator_1, OUTPUT);   // LR_1
  pinMode(pinLedGreenElevator_1, OUTPUT); // LG_1
  pinMode(pinLedBlueElevator_1, OUTPUT);  // LB_1
  pinMode(motorPinHigh_1, OUTPUT);        // MH_1
  pinMode(motorPinLow_1, OUTPUT);         // ML_1
  pinMode(motorPinSpeed_1, OUTPUT);       // MS_1

  pinMode(pinLedRedElevator_2, OUTPUT);   // LR_2
  pinMode(pinLedGreenElevator_2, OUTPUT); // LG_2
  pinMode(pinLedBlueElevator_2, OUTPUT);  // LB_2
  pinMode(motorPinHigh_2, OUTPUT);        // MH_2
  pinMode(motorPinLow_2, OUTPUT);         // ML_2
  pinMode(motorPinSpeed_2, OUTPUT);       // MS_2

  ledRedValueElevator_1 = LRV_1;
  ledGreenValueElevator_1 = LGV_1;
  ledBlueValueElevator_1 = LBV_1;
  servoPositionElevator_1 = SP_1;

  ledRedValueElevator_2 = LRV_2;
  ledGreenValueElevator_2 = LGV_2;
  ledBlueValueElevator_2 = LBV_2;
  servoPositionElevator_2 = SP_2;

}

int Scene::readValue(String component)
{
  if (component == "LRV_1")
  {
    return this->ledRedValueElevator_1;
  }

  if (component == "LGV_1")
  {
    return this->ledGreenValueElevator_1;
  }

  if (component == "LBV_1")
  {
    return this->ledBlueValueElevator_1;
  }

  if (component == "SP_1")
  {
    return this->servoPositionElevator_1;
  }

  if (component == "LRV_2")
  {
    return this->ledRedValueElevator_2;
  }

  if (component == "LGV_2")
  {
    return this->ledGreenValueElevator_2;
  }

  if (component == "LBV_2")
  {
    return this->ledBlueValueElevator_2;
  }

  if (component == "SP_2")
  {
    return this->servoPositionElevator_2;
  }
}
