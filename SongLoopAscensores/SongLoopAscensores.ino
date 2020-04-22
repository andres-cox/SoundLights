#include <Servo.h>
#include <Scene.h>

byte pinLedRedElevator_1 = 6;
byte pinLedGreenElevator_1 = 5;
byte pinLedBlueElevator_1 = 4;

byte pinLedRedElevator_2 = 9;
byte pinLedGreenElevator_2 = 8;
byte pinLedBlueElevator_2 = 7;

byte pinMotorHigh_1 = 24;  //9 10 11
byte pinMotorLow_1 = 22;
byte pinMotorSpeed_1 = 11;

byte pinMotorHigh_2 = 26;  //9 10 11
byte pinMotorLow_2 = 28;
byte pinMotorSpeed_2 = 12;

byte motorSpeedLimitLow = 100;
byte motorSpeedLimitHigh = 200;

byte pinServoElevator_1 = 3;
byte pinServoElevator_2 = 2;


Servo servoElevator_1;
Servo servoElevator_2;
/////////LA IGLESIA

unsigned int timeLine[] = {0,  10, 32, 53, 75, 81, 95, 115};
unsigned long prevMillis = 0;
boolean state = LOW;
boolean ledState = LOW;

extern volatile unsigned long timer0_millis;
unsigned long new_value = 0;

int valPot;

//Scene sc1(  LedRedValue_1, LedGreenValue_1, LedBlueValue_1, ServoPosition_1,  LedRedValue_2, LedGreenValue_2, LedBlueValue_2, ServoPosition_2);
Scene scene1( 10,    0,  10,    0,        10,    0,  10,    0);
Scene scene2( 0,  10,    0,   180,       0,  10,    0,   180);




void setup() {
  Serial.begin(9600);
  //pinMode(interruptPin2, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(interruptPin1), song1, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(interruptPin2), song2, CHANGE);


  endScene();
  //RESUMEN DE FUNCIONES
  //DIBUJAR ESCENA
  //scene.drawScene(String elevator_1, int elevatorSpeed_1, String elevator_2, int elevatorSpeed_2, int time)

  //BLINK DE LA ESCENA
  //scene.blink(frecuencia,tiempo)                      //a menor frecuencia mayor titileo

  //BLINK ENTRE ESCENAS
  //blinkScenes(escena1, escena2, frecuencia, tiempo);  //a menor frecuencia mayor titileo

  //FADE ENTRE ESCENAS
  //drawFade(Scene sceneStart, Scene sceneEnd, String elevator_1, int elevatorSpeed_1, String elevator_2, int elevatorSpeed_2, int time);
}

void loop() {
 
        setMillis(new_value);
        //scene.drawScene(String elevator_1, int elevatorSpeed_1, String elevator_2, int elevatorSpeed_2, int timeLine)
        Serial.println("Song1: ");
        Serial.print("scene1: ");
        Serial.println(millis());
        drawScene(scene1, "STOP", 150, "STOP", 150, 0);

        Serial.print("scene2: ");
        Serial.println(millis());
        drawScene(scene2, "STOP", 150, "STOP", 150, 1);

        //scene.blink(frecuencia,timeLine)                  //a menor frecuencia mayor titileo
        Serial.print("blink1: ");
        Serial.println(millis());
        blink(scene1,100, 2);

        Serial.print("blink2: ");
        Serial.println(millis());
        blink(scene2,500, 3);

        //blinkScenes(escena1, escena2, frecuencia, tiempo);  //a menor frecuencia mayor titileo
        Serial.print("blinkScenes: ");
        Serial.println(millis());
        blinkScenes(scene1, scene2, 150, 4);

        //drawFade(Scene sceneStart, Scene sceneEnd, String elevator_1, int elevatorSpeed_1, String elevator_2, int elevatorSpeed_2, int time);

        Serial.print("drawfade: ");
        Serial.println(millis());
        drawFade(scene2, scene1, "UP", 150, "UP", 150, 5);

   
        //endScene();
     

}


void blinkScenes(Scene sc1, Scene sc2, int f, int t)
{

  byte sc1_Elev1R = sc1.readValue("LRV_1");
  byte sc1_Elev1G = sc1.readValue("LGV_1");
  byte sc1_Elev1B = sc1.readValue("LBV_1");
  byte sc1_Elev2R = sc1.readValue("LRV_2");
  byte sc1_Elev2G = sc1.readValue("LGV_2");
  byte sc1_Elev2B = sc1.readValue("LBV_2");

  byte sc2_Elev1R = sc2.readValue("LRV_1");
  byte sc2_Elev1G = sc2.readValue("LGV_1");
  byte sc2_Elev1B = sc2.readValue("LBV_1");
  byte sc2_Elev2R = sc2.readValue("LRV_2");
  byte sc2_Elev2G = sc2.readValue("LGV_2");
  byte sc2_Elev2B = sc2.readValue("LBV_2");

  do
  {

    if (millis() - prevMillis >= f)
    {
      prevMillis = millis();

      if (state == LOW)
      {
        analogWrite(pinLedRedElevator_1, sc1_Elev1R);
        analogWrite(pinLedGreenElevator_1, sc1_Elev1G);
        analogWrite(pinLedBlueElevator_1, sc1_Elev1B);
        analogWrite(pinLedRedElevator_2, sc1_Elev2R);
        analogWrite(pinLedGreenElevator_2, sc1_Elev2G);
        analogWrite(pinLedBlueElevator_2, sc1_Elev2B);
        state = HIGH;
      }
      else
      {
        analogWrite(pinLedRedElevator_1, sc2_Elev1R);
        analogWrite(pinLedGreenElevator_1, sc2_Elev1G);
        analogWrite(pinLedBlueElevator_1, sc2_Elev1B);
        analogWrite(pinLedRedElevator_2, sc2_Elev2R);
        analogWrite(pinLedGreenElevator_2, sc2_Elev2G);
        analogWrite(pinLedBlueElevator_2, sc2_Elev2B);
        state = LOW;
      }


    }
  } while (millis()/100 < timeLine[t + 1]);

}


void drawFade(Scene sceneStart, Scene sceneEnd, String elevator_1, int elevatorSpeed_1, String elevator_2, int elevatorSpeed_2, int t)
{
  servoElevator_1.attach(pinServoElevator_1);
  servoElevator_2.attach(pinServoElevator_2);

  byte constServo_1;
  byte constLedRed_1;
  byte constLedBlue_1;
  byte constLedGreen_1;
  byte constServo_2;
  byte constLedRed_2;
  byte constLedBlue_2;
  byte constLedGreen_2;

  unsigned long  fade;
  unsigned int fadeStart = timeLine[t];// + 100;
  unsigned int fadeEnd = timeLine[t + 1];


  byte ledRedValueStart_1 = sceneStart.readValue("LRV_1");
  byte ledRedValueEnd_1 = sceneEnd.readValue("LRV_1");
  byte ledBlueValueStart_1 = sceneStart.readValue("LBV_1");
  byte ledBlueValueEnd_1 = sceneEnd.readValue("LBV_1");
  byte ledGreenValueStart_1 = sceneStart.readValue("LGV_1");
  byte ledGreenValueEnd_1 = sceneEnd.readValue("LGV_1");
  byte servoPositionStart_1 = sceneStart.readValue("SP_1");
  byte servoPositionEnd_1 = sceneEnd.readValue("SP_1");

  byte ledRedValueStart_2 = sceneStart.readValue("LRV_2");
  byte ledRedValueEnd_2 = sceneEnd.readValue("LRV_2");
  byte ledBlueValueStart_2 = sceneStart.readValue("LBV_2");
  byte ledBlueValueEnd_2 = sceneEnd.readValue("LBV_2");
  byte ledGreenValueStart_2 = sceneStart.readValue("LGV_2");
  byte ledGreenValueEnd_2 = sceneEnd.readValue("LGV_2");
  byte servoPositionStart_2 = sceneStart.readValue("SP_2");
  byte servoPositionEnd_2 = sceneEnd.readValue("SP_2");

  //fadeEnd = (timeLine[t + 1] - timeLine[t]);

  if (elevator_1 == "UP")
  {
    digitalWrite(pinMotorHigh_1, HIGH);
    digitalWrite(pinMotorLow_1, LOW);
    analogWrite(pinMotorSpeed_1, elevatorSpeed_1);
  }

  if (elevator_1 == "DOWN")
  {
    digitalWrite(pinMotorHigh_1, LOW);
    digitalWrite(pinMotorLow_1, HIGH);
    analogWrite(pinMotorSpeed_1, elevatorSpeed_1);
  }

  if (elevator_1 == "STOP")
  {
    digitalWrite(pinMotorHigh_1, LOW);
    digitalWrite(pinMotorLow_1, LOW);
    analogWrite(pinMotorSpeed_1, 0);
  }

  if (elevator_2 == "UP")
  {
    digitalWrite(pinMotorHigh_2, HIGH);
    digitalWrite(pinMotorLow_2, LOW);
    analogWrite(pinMotorSpeed_2, elevatorSpeed_2);
  }

  if (elevator_2 == "DOWN")
  {
    digitalWrite(pinMotorHigh_2, LOW);
    digitalWrite(pinMotorLow_2, HIGH);
    analogWrite(pinMotorSpeed_2, elevatorSpeed_2);
  }

  if (elevator_2 == "STOP")
  {
    digitalWrite(pinMotorHigh_2, LOW);
    digitalWrite(pinMotorLow_2, LOW);
    analogWrite(pinMotorSpeed_2, 0);
  }
  //Serial.print("FadeStart: ");
  //Serial.println(fadeStart);

  //Serial.print("FadeEnd: ");
  //Serial.println(fadeEnd);



  do {
    fade = millis()/100;

    constLedRed_1 = round(map(fade, fadeStart, fadeEnd, ledRedValueStart_1, ledRedValueEnd_1));
    constLedBlue_1 = round(map(fade, fadeStart, fadeEnd, ledBlueValueStart_1, ledBlueValueEnd_1));
    constLedGreen_1 = round(map(fade, fadeStart, fadeEnd, ledGreenValueStart_1, ledGreenValueEnd_1));
    constServo_1 = round(map(fade, fadeStart, fadeEnd, servoPositionStart_1, servoPositionEnd_1));

    constLedRed_2 = round(map(fade, fadeStart, fadeEnd, ledRedValueStart_2, ledRedValueEnd_2));
    constLedBlue_2 = round(map(fade, fadeStart, fadeEnd, ledBlueValueStart_2, ledBlueValueEnd_2));
    constLedGreen_2 = round(map(fade, fadeStart, fadeEnd, ledGreenValueStart_2, ledGreenValueEnd_2));
    constServo_2 = round(map(fade, fadeStart, fadeEnd, servoPositionStart_2, servoPositionEnd_2));


    servoElevator_1.write(constServo_1);
    analogWrite(pinLedRedElevator_1, constLedRed_1);
    analogWrite(pinLedGreenElevator_1, constLedBlue_1);
    analogWrite(pinLedBlueElevator_1, constLedGreen_1);

    servoElevator_2.write(constServo_2);
    analogWrite(pinLedRedElevator_2, constLedRed_2);
    analogWrite(pinLedGreenElevator_2, constLedBlue_2);
    analogWrite(pinLedBlueElevator_2, constLedGreen_2);

  } while (millis()/100 < timeLine[t + 1]);



  //Serial.print("fade: ");
  //Serial.println(fade);
  servoElevator_1.detach();
  servoElevator_2.detach();

  digitalWrite(pinMotorHigh_1, LOW);
  digitalWrite(pinMotorLow_1, LOW);
  analogWrite(pinMotorSpeed_1, 0);
  digitalWrite(pinMotorHigh_2, LOW);
  digitalWrite(pinMotorLow_2, LOW);
  analogWrite(pinMotorSpeed_2, 0);

}

void blink(Scene scene, int f, int t)
{
  servoElevator_1.attach(pinServoElevator_1);
  servoElevator_2.attach(pinServoElevator_2);

  byte ledRedValueElevator_1 = scene.readValue("LRV_1");
  byte ledBlueValueElevator_1 = scene.readValue("LBV_1");
  byte ledGreenValueElevator_1 = scene.readValue("LGV_1");
  byte servoPositionElevator_1 = scene.readValue("SP_1");

  byte ledRedValueElevator_2 = scene.readValue("LRV_2");
  byte ledBlueValueElevator_2 = scene.readValue("LBV_2");
  byte ledGreenValueElevator_2 = scene.readValue("LGV_2");
  byte servoPositionElevator_2 = scene.readValue("SP_2");

  servoElevator_1.write(servoPositionElevator_1);
  servoElevator_2.write(servoPositionElevator_2);
  
  do
  {

    if (millis() - prevMillis >= f)
    {
      prevMillis = millis();

      if (ledState == LOW)
      {
        analogWrite(pinLedRedElevator_1, ledRedValueElevator_1);
        analogWrite(pinLedGreenElevator_1, ledGreenValueElevator_1);
        analogWrite(pinLedBlueElevator_1, ledBlueValueElevator_1);
        analogWrite(pinLedRedElevator_2, ledRedValueElevator_2);
        analogWrite(pinLedGreenElevator_2, ledGreenValueElevator_2);
        analogWrite(pinLedBlueElevator_2, ledBlueValueElevator_2);
        ledState = HIGH;
      }
      else
      {
        analogWrite(pinLedRedElevator_1, 0);
        analogWrite(pinLedGreenElevator_1, 0);
        analogWrite(pinLedBlueElevator_1, 0);
        analogWrite(pinLedRedElevator_2, 0);
        analogWrite(pinLedGreenElevator_2, 0);
        analogWrite(pinLedBlueElevator_2, 0);
        ledState = LOW;
      }
    }
  } while (millis()/100 < timeLine[t + 1]);
  servoElevator_1.detach();
  servoElevator_2.detach();
}

void drawScene(Scene scene, String elevator_1, byte elevatorSpeed_1, String elevator_2, byte elevatorSpeed_2, int t)
{
  servoElevator_1.attach(pinServoElevator_1);
  servoElevator_2.attach(pinServoElevator_2);
  
  byte ledRedValueElevator_1 = scene.readValue("LRV_1");
  byte ledBlueValueElevator_1 = scene.readValue("LBV_1");
  byte ledGreenValueElevator_1 = scene.readValue("LGV_1");
  byte servoPositionElevator_1 = scene.readValue("SP_1");

  byte ledRedValueElevator_2 = scene.readValue("LRV_2");
  byte ledBlueValueElevator_2 = scene.readValue("LBV_2");
  byte ledGreenValueElevator_2 = scene.readValue("LGV_2");
  byte servoPositionElevator_2 = scene.readValue("SP_2");
  
  do
  {
     if (elevator_1 == "UP")
    {
      digitalWrite(pinMotorHigh_1, HIGH);
      digitalWrite(pinMotorLow_1, LOW);
      analogWrite(pinMotorSpeed_1, elevatorSpeed_1);
    }

    if (elevator_1 == "DOWN")
    {
      digitalWrite(pinMotorHigh_1, LOW);
      digitalWrite(pinMotorLow_1, HIGH);
      analogWrite(pinMotorSpeed_1, elevatorSpeed_1);
    }

    if (elevator_1 == "STOP")
    {
      digitalWrite(pinMotorHigh_1, LOW);
      digitalWrite(pinMotorLow_1, LOW);
      analogWrite(pinMotorSpeed_1, 0);
    }

    if (elevator_2 == "UP")
    {
      digitalWrite(pinMotorHigh_2, HIGH);
      digitalWrite(pinMotorLow_2, LOW);
      analogWrite(pinMotorSpeed_2, elevatorSpeed_2);
    }

    if (elevator_2 == "DOWN")
    {
      digitalWrite(pinMotorHigh_2, LOW);
      digitalWrite(pinMotorLow_2, HIGH);
      analogWrite(pinMotorSpeed_2, elevatorSpeed_2);
    }

    if (elevator_2 == "STOP")
    {
      digitalWrite(pinMotorHigh_2, LOW);
      digitalWrite(pinMotorLow_2, LOW);
      analogWrite(pinMotorSpeed_2, 0);
    }

    analogWrite(pinLedRedElevator_1, ledRedValueElevator_1);
    analogWrite(pinLedGreenElevator_1, ledGreenValueElevator_1);
    analogWrite(pinLedBlueElevator_1, ledBlueValueElevator_1);
    servoElevator_1.write(servoPositionElevator_1);

    analogWrite(pinLedRedElevator_2, ledRedValueElevator_2);
    analogWrite(pinLedGreenElevator_2, ledGreenValueElevator_2);
    analogWrite(pinLedBlueElevator_2, ledBlueValueElevator_2);
    servoElevator_2.write(servoPositionElevator_2);
  } while (millis()/100 < timeLine[t + 1]);
  //delay(timeLine[t + 1] - timeLine[t]);
   digitalWrite(pinMotorHigh_1, LOW);
  digitalWrite(pinMotorLow_1, LOW);
  analogWrite(pinMotorSpeed_1, 0);
  digitalWrite(pinMotorHigh_2, LOW);
  digitalWrite(pinMotorLow_2, LOW);
  analogWrite(pinMotorSpeed_2, 0);
  servoElevator_1.detach();
  servoElevator_2.detach();
}

void endScene() {
  analogWrite(pinLedRedElevator_1, 0);
  analogWrite(pinLedGreenElevator_1, 0);
  analogWrite(pinLedBlueElevator_1, 0);

  analogWrite(pinLedRedElevator_2, 0);
  analogWrite(pinLedGreenElevator_2, 0);
  analogWrite(pinLedBlueElevator_2, 0);

  digitalWrite(pinMotorHigh_1, LOW);
  digitalWrite(pinMotorLow_1, LOW);
  analogWrite(pinMotorSpeed_1, 0);

  digitalWrite(pinMotorHigh_2, LOW);
  digitalWrite(pinMotorLow_2, LOW);
  analogWrite(pinMotorSpeed_2, 0);

}

void setMillis(unsigned long new_millis) {
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}
