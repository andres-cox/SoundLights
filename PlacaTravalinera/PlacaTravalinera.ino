#include <Servo.h>
#include <Cart.h>

byte pinTravRed = 12;
byte pinTravGreen = 11;
byte pinTravBlue = 10;
byte pinTravMotorSpeed = 2;
byte pinTravMotorUp = 24;
byte pinTravMotorDown = 26;
byte pinServoHeight = 28;
byte pinServoDirection = 30;

byte pinBacklightingRed = 9;
byte pinBacklightingGreen = 8;
byte pinBacklightingBlue = 7;
byte pinBacklightingServo = 32;

byte pinUViolet_EL1 = 6;
byte pinUViolet_EL2 = 5;
byte pinUViolet_T = 4;
byte pinUViolet_BL = 3;

Servo servoH;
Servo servoD;
Servo servoBL;

unsigned int timeLine[10][100] = {  // los valores del array son modificables 
  //song 1
    { 0,  12,  32,  53,   61,  71,  82, 103,  112,  123, 133, 153, 163, 173, 184, 203, 213, 223, 233, 253, 263, 272, 281, 289, 300,
      
    308, 318, 321, 326, 337, 343, 349, 356  , 363, 375, 383, 393, 396, 401, 412, 418, 425, 431, 453, 487, 501, 519, 580, 618},
  {0,  12 , 34, 57, 61, 71, 82, 103, 112, 123 },
  //song 2
  {0,  412 , 2665, 5584, 6176, 7165, 8286, 10385, 11229, 12342 },
  //song 3
  {0,  522 , 4885, 5658, 6176, 7165, 8286, 10385, 11229, 12342 },
  //song 4
  {0,  522 , 4885, 5658, 6176, 7165, 8286, 10385, 11229, 12342 }

  // no es necesario escribir las 10 canciones para que funcione
};  

unsigned long prevMillis = 0;
int state = LOW;


extern volatile unsigned long timer0_millis;
unsigned long new_value = 0; /// para el reseteo del timeline
volatile int var;
const byte interruptPin1 = 19;
const byte interruptPin2 = 18;


int count;
boolean musicState;

//Cart scene1(  TR TG,TB,   SAlt  SDir,   CR, CG, CB, SC,    UE1,UE2,UVT,UVc);
Cart scene1 (   0,  0,  0,   90,  90,     0,  0,  0, 90,     0,  0,  0, 20);
Cart scene2 (   0,  0,  0,   90,  90,     0, 30,  0, 70,     0,  0,  0,  0); 
Cart scene3 (   0,  0,  0,   90,  90,     0, 30,  0, 70,    50, 50, 50,  0);
Cart scene4 (   0,  0,  0,   90,  90,     0, 30,  0, 70,    20, 20, 20,  0);

Cart scene9 (   0,  0,  0,   90,  90,    25, 60, 20, 60,     0,  0,  0,  0);
Cart scene10(   0,  0,  0,   90,  90,    50, 10, 50, 60,     0,  0,  0,  0);
Cart scene11(  30, 30, 30,   40,  90,    30, 30, 30, 130,    0,  0,  0,  0);
Cart scene12(  30, 30, 30,   50,  80,    30, 30, 30, 130,    0,  0,  0,  0);

/////////FUNCIONES///////////// 
//drawScene(Cart scene, String cartMode, int cartSpeed, int t)
//drawFade(Cart sceneStart, Cart sceneEnd, String cartMode, int cartSpeed, int t);
//blinkScenes(Cart sc1, Cart sc2, int f, int t)


///////////////////POT DISPLAY/////////////
byte  numero[10][7] =
{
//{ a, b, c, d, e, f, g }
  { 1, 1, 1, 1, 1, 1, 0 }, // 0
  { 0, 1, 1, 0, 0, 0, 0 }, // 1
  { 1, 1, 0, 1, 1, 0, 1 }, // 2
  { 1, 1, 1, 1, 0, 0, 1 }, // 3
  { 0, 1, 1, 0, 0, 1, 1 }, // 4
  { 1, 0, 1, 1, 0, 1, 1 }, // 5
  { 1, 0, 1, 1, 1, 1, 1 }, // 6
  { 1, 1, 1, 0, 0, 0, 0 }, // 7
  { 1, 1, 1, 1, 1, 1, 1 }, // 8
  { 1, 1, 1, 1, 0, 1, 1 }  // 9
};
//              a   b   c   d   e   f   g
byte disp[7] = {43, 47, 49, 51, 45, 41, 39 };
int valPot;

void setup() {
  Serial.begin(9600);
  pinMode(33, OUTPUT);
  pinMode(interruptPin1, INPUT_PULLUP);
  for (byte i = 0; i < 7; i++) // POTDISPLAY
  {
    pinMode(disp[i], OUTPUT);
  }
  var = 2;
  endScene();

}

void loop() {
  valPot = analogRead(A0);
  if (var >= 9) {
    var = 9;
  }
  if (var <= 0) {
    var = 0;
  }

  if (valPot > 900) {
    var++;
    Display(var);
    digitalWrite(33, LOW);
    delay(1500);
  }
  if (valPot > 250 && valPot < 900) {
    Display(var);
    digitalWrite(33, HIGH);
  }
  if (valPot < 250) {
    var--;
    Display(var);
    digitalWrite(33, LOW);
    delay(1500);
  }

  int sensorValue = analogRead(A1);

  if (sensorValue == 0) {
    count++;
  }
  if (count > 50) {
    count = 0;
    musicState = 0;
  }

  if (sensorValue > 50) {
    count = 0;
    musicState = 1;
  }

  Serial.print("var: ");
  Serial.println(var);
  Serial.print("musicState: ");
  Serial.println(musicState);
  if (musicState) {
    switch (var) {
      case 1:
        setMillis(new_value);
        Serial.print("Song1: ");
        // la forma antigua era scene1.drawScene("RIGHT", 50, 0);
        // esta es ahora:
        drawScene(scene1, "STOP", 150, 0); // <--

        drawFade(scene2, scene1, "STOP", 0, 1);

        drawFade(scene1, scene3, "STOP", 0, 2);

        drawFade(scene3, scene1, "STOP", 0, 3);

        drawFade(scene1, scene4, "STOP", 0, 4);

        drawFade(scene4, scene1, "STOP", 0, 5);

        drawFade(scene1, scene3, "STOP", 0, 6);

        drawFade(scene3, scene1, "STOP", 0, 7);

        drawFade(scene1, scene4, "STOP", 0, 8);

        drawFade(scene4, scene1, "STOP", 0, 9);
        //inspira exala con movimiento

        drawFade(scene1, scene3, "STOP", 90, 10);

        drawFade(scene3, scene1, "STOP", 90, 11);

        drawFade(scene1, scene4, "STOP", 90, 12);

        drawFade(scene4, scene1, "STOP", 90, 13);

        drawFade(scene1, scene3, "STOP", 90, 14);

        drawFade(scene3, scene1, "STOP", 100, 15);

        drawFade(scene1, scene4, "STOP", 100, 16);

        drawFade(scene4, scene1, "STOP", 100, 17);

        drawFade(scene1, scene3, "STOP", 0, 18);

        drawFade(scene3, scene1, "STOP", 0, 19);

        drawFade(scene1, scene4, "STOP", 0, 20);

        drawFade(scene4, scene1, "STOP", 0, 21);

        drawScene(scene18, "STOP", 150, 22);

        drawFade(scene9, scene18, "STOP", 0, 23);

        drawScene(scene18, "STOP", 150, 24);

        drawFade(scene9, scene18, "STOP", 0, 25);

        drawScene(scene18, "STOP", 150, 26);

        drawScene(scene18, "STOP", 150, 27);

        drawFade(scene9, scene18, "STOP", 0, 28);

        drawScene(scene18, "STOP", 150, 29);

        drawScene(scene18, "STOP", 150, 30);

        drawFade(scene10, scene18, "STOP", 0, 31);

        drawScene(scene18, "STOP", 150, 32);

        drawFade(scene9, scene18, "STOP", 0, 33);

        drawScene(scene18, "STOP", 150, 34);

        drawFade(scene9, scene18, "STOP", 0, 35);

        drawScene(scene18, "STOP", 150, 36);

        drawScene(scene18, "STOP", 150, 37);

        drawFade(scene9, scene18, "STOP", 0, 38);

        drawScene(scene18, "STOP", 150, 39);

        drawScene(scene18, "STOP", 150, 40);

        drawFade(scene10, scene18, "STOP", 0, 41);

        drawScene(scene18, "STOP", 150, 42);

        drawFade(scene11, scene18, "STOP", 0, 43);

        drawScene(scene18, "STOP", 150, 44);

        drawFade(scene10, scene18, "STOP", 0, 45);

        drawFade(scene12, scene18, "STOP", 0, 46);

        drawFade(scene13, scene18, "STOP", 0, 47);

        drawFade(scene14, scene18, "STOP", 0, 48);

        drawScene(scene18, "STOP", 150, 49);

        drawScene(scene18, "STOP", 150, 50);

        drawFade(scene15, scene18, "STOP", 0, 51);

        drawFade(scene15, scene18, "STOP", 0, 52);

        drawScene(scene18, "STOP", 150, 53);

        drawFade(scene15, scene18, "STOP", 0, 54);

        drawFade(scene15, scene18, "STOP", 0, 55);

        drawFade(scene15, scene18, "STOP", 0, 56);

        drawFade(scene15, scene18, "STOP", 0, 57);

        drawFade(scene15, scene18, "STOP", 0, 58);

        drawFade(scene15, scene18, "STOP", 0, 59);

        drawFade(scene15, scene18, "STOP", 0, 60);

        drawFade(scene15, scene18, "STOP", 0, 61);

        drawScene(scene18, "STOP", 150, 62);

        drawScene(scene18, "STOP", 150, 63);

        drawScene(scene18, "STOP", 150, 64);

        drawFade(scene11, scene18, "STOP", 0, 65);

        drawScene(scene18, "STOP", 150, 66);

        drawScene(scene18, "STOP", 150, 67);

        drawFade(scene10, scene18, "STOP", 0, 68);

        drawFade(scene12, scene18, "STOP", 0, 69);

        drawScene(scene18, "STOP", 150, 70);

        drawFade(scene13, scene18, "STOP", 0, 71);

        drawScene(scene18, "STOP", 150, 72);

        drawFade(scene14, scene18, "STOP", 0, 73);

        drawScene(scene18, "STOP", 150, 74);

        drawScene(scene18, "STOP", 150, 75);

        drawScene(scene18, "STOP", 150, 76);

        drawFade(scene18, scene16, "STOP", 0, 77);

        drawFade(scene16, scene17, "STOP", 0, 78);

        drawFade(scene17, scene16, "STOP", 0, 79);

        drawFade(scene16, scene18, "STOP", 0, 80);

        endScene();
        break;
      case 2:

        setMillis(new_value); /// el reseteo se tiene que quedar asi para cada cancion
        Serial.print("Song2: ");
        Serial.print("scene2: ");
        Serial.println(millis());
        drawScene(scene2, "RIGHT", 50, 0);
        Serial.print("scene1: ");
        Serial.println(millis());
        drawScene(scene1, "LEFT", 50, 1);
        Serial.print("scene2: ");
        Serial.println(millis());
        drawScene(scene3, "STOP", 0, 2);
        Serial.print("scene2: ");
        Serial.println(millis());
        drawScene(scene2, "STOP", 0, 3);
        Serial.print("scene2: ");
        Serial.println(millis());
        drawScene(scene1, "STOP", 0, 4);

        Serial.print("end: ");
        Serial.println(millis());
        endScene();
        break;
      case 3:

        setMillis(new_value); ///reseteo del tiempo
        Serial.print("Song3: ");
        //drawScene(Cart scene, String cartMode, int cartSpeed, int t)
        Serial.print("scene2: ");
        Serial.println(millis());
        drawScene(scene2, "STOP", 0, 0);
        Serial.print("scene2: ");
        Serial.println(millis());
        drawScene(scene3, "STOP", 0, 1);
        Serial.print("scene4: ");
        Serial.println(millis());
        drawScene(scene4, "STOP", 0, 2);
        Serial.print("end: ");
        Serial.println(millis());
        endScene();
        break;


      default:
        endScene();
        break;
    }
  }
  endScene();
}



void blinkScenes(Cart sc1, Cart sc2, int f, int t)
{
  int time = t;
  int frecuency = f;
  float count = (t * 0.5) / f;
  byte sc1_TravR = sc1.readValue("LTRV");
  byte sc1_TravG = sc1.readValue("LTGV");
  byte sc1_TravB = sc1.readValue("LTBV");
  byte sc1_BLR   = sc1.readValue("LBRV");
  byte sc1_BLG   = sc1.readValue("LBGV");
  byte sc1_BLB   = sc1.readValue("LBBV");
  byte sc1_UVEL1 = sc1.readValue("UV_EL1");
  byte sc1_UVEL2 = sc1.readValue("UV_EL2");
  byte sc1_UVT   = sc1.readValue("UV_T");
  byte sc1_UVBL  = sc1.readValue("UV_BL");

  byte sc2_TravR = sc2.readValue("LTRV");
  byte sc2_TravG = sc2.readValue("LTGV");
  byte sc2_TravB = sc2.readValue("LTBV");
  byte sc2_BLR   = sc2.readValue("LBRV");
  byte sc2_BLG   = sc2.readValue("LBGV");
  byte sc2_BLB   = sc2.readValue("LBBV");
  byte sc2_UVEL1 = sc2.readValue("UV_EL1");
  byte sc2_UVEL2 = sc2.readValue("UV_EL2");
  byte sc2_UVT   = sc2.readValue("UV_T");
  byte sc2_UVBL  = sc2.readValue("UV_BL");


  do
  {
    if (millis() - prevMillis >= f)
    {
      prevMillis = millis();
      if (state == LOW)
      {
        analogWrite(pinTravRed,   sc1_TravR);
        analogWrite(pinTravGreen, sc1_TravG);
        analogWrite(pinTravBlue,  sc1_TravB);
        analogWrite(pinBacklightingRed,   sc1_BLR);
        analogWrite(pinBacklightingGreen, sc1_BLG);
        analogWrite(pinBacklightingBlue,  sc1_BLB);
        analogWrite(pinUViolet_EL1, sc1_UVEL1);
        analogWrite(pinUViolet_EL2, sc1_UVEL2);
        analogWrite(pinUViolet_T,   sc1_UVT);
        analogWrite(pinUViolet_BL,  sc1_UVBL);
        state = HIGH;
      }
      else
      {
        analogWrite(pinTravRed,   sc2_TravR);
        analogWrite(pinTravGreen, sc2_TravG);
        analogWrite(pinTravBlue,  sc2_TravB);
        analogWrite(pinBacklightingRed,   sc2_BLR);
        analogWrite(pinBacklightingGreen, sc2_BLG);
        analogWrite(pinBacklightingBlue,  sc2_BLB);
        analogWrite(pinUViolet_EL1, sc2_UVEL1);
        analogWrite(pinUViolet_EL2, sc2_UVEL2);
        analogWrite(pinUViolet_T,   sc2_UVT);
        analogWrite(pinUViolet_BL,  sc2_UVBL);
        state = LOW;
      }
    }
  } while (millis() / 100 < timeLine[var - 1][t + 1]);
}


void drawFade(Cart sceneStart, Cart sceneEnd, String cartMode, int cartSpeed, int t)
{

  servoH.attach(pinServoHeight);
  servoD.attach(pinServoDirection);
  servoBL.attach(pinBacklightingServo);

  byte constLedTravRedValue;
  byte constLedTravGreenValue;
  byte constLedTravBlueValue;
  byte constLedBacklightRedValue;
  byte constLedBacklightGreenValue;
  byte constLedBacklightBlueValue;
  byte constUViolet_EL1;
  byte constUViolet_EL2;
  byte constUViolet_T;
  byte constUViolet_BL;
  byte constServoPositionHeight;
  byte constServoPositionDirection;
  byte constServoPositionBacklight;


  unsigned long  fade;
  unsigned int fadeStart = timeLine[var - 1][t];
  unsigned int fadeEnd = timeLine[var - 1][t + 1];
  //int fade = 0;
  //int fadeStart = 0;
  //float fadeEnd;
  int fadeAmount = 1;

  byte ledTravRedValueStart = sceneStart.readValue("LTRV");
  byte ledTravGreenValueStart = sceneStart.readValue("LTGV");
  byte ledTravBlueValueStart = sceneStart.readValue("LTBV");
  byte ledBacklightRedValueStart = sceneStart.readValue("LBRV");
  byte ledBacklightGreenValueStart = sceneStart.readValue("LBGV");
  byte ledBacklightBlueValueStart = sceneStart.readValue("LBBV");
  byte UViolet_EL1Start = sceneStart.readValue("UV_EL1");
  byte UViolet_EL2Start = sceneStart.readValue("UV_EL2");
  byte UViolet_TStart = sceneStart.readValue("UV_T");
  byte UViolet_BLStart = sceneStart.readValue("UV_BL");
  byte servoPositionHeightStart = sceneStart.readValue("SSPH");
  byte servoPositionDirectionStart = sceneStart.readValue("SPD");
  byte servoPositionBacklightStart = sceneStart.readValue("SPBL");

  byte ledTravRedValueEnd = sceneEnd.readValue("LTRV");
  byte ledTravGreenValueEnd = sceneEnd.readValue("LTGV");
  byte ledTravBlueValueEnd = sceneEnd.readValue("LTBV");
  byte ledBacklightRedValueEnd = sceneEnd.readValue("LBRV");
  byte ledBacklightGreenValueEnd = sceneEnd.readValue("LBGV");
  byte ledBacklightBlueValueEnd = sceneEnd.readValue("LBBV");
  byte UViolet_EL1End = sceneEnd.readValue("UV_EL1");
  byte UViolet_EL2End = sceneEnd.readValue("UV_EL2");
  byte UViolet_TEnd = sceneEnd.readValue("UV_T");
  byte UViolet_BLEnd = sceneEnd.readValue("UV_BL");
  byte servoPositionHeightEnd = sceneEnd.readValue("SSPH");
  byte servoPositionDirectionEnd = sceneEnd.readValue("SPD");
  byte servoPositionBacklightEnd = sceneEnd.readValue("SPBL");

  if (cartMode == "RIGHT")
  {
    digitalWrite(pinTravMotorUp, HIGH);
    digitalWrite(pinTravMotorDown, LOW);
    analogWrite(pinTravMotorSpeed, cartSpeed);
  }

  if (cartMode == "LEFT")
  {
    digitalWrite(pinTravMotorUp, LOW);
    digitalWrite(pinTravMotorDown, HIGH);
    analogWrite(pinTravMotorSpeed, cartSpeed);
  }

  if (cartMode == "STOP")
  {
    digitalWrite(pinTravMotorUp, LOW);
    digitalWrite(pinTravMotorDown, LOW);
    analogWrite(pinTravMotorSpeed, 0);
  }

  Serial.print("FadeStart: ");
  Serial.println(fadeStart);

  //Serial.print("FadeEnd: ");
  //Serial.println(fadeEnd);
  do {
    
    fade = millis()/100;
    constLedTravRedValue = round(map(fade, fadeStart, fadeEnd, ledTravRedValueStart, ledTravRedValueEnd));
    constLedTravGreenValue = round(map(fade, fadeStart, fadeEnd, ledTravGreenValueStart, ledTravGreenValueEnd));
    constLedTravBlueValue = round(map(fade, fadeStart, fadeEnd, ledTravBlueValueStart, ledTravBlueValueEnd));
    constLedBacklightRedValue = round(map(fade, fadeStart, fadeEnd, ledBacklightRedValueStart, ledBacklightRedValueEnd));
    constLedBacklightGreenValue = round(map(fade, fadeStart, fadeEnd, ledBacklightGreenValueStart, ledBacklightGreenValueEnd));
    constLedBacklightBlueValue = round(map(fade, fadeStart, fadeEnd, ledBacklightBlueValueStart, ledBacklightBlueValueEnd));
    constUViolet_EL1 = round(map(fade, fadeStart, fadeEnd, UViolet_EL1Start, UViolet_EL1End));
    constUViolet_EL2 = round(map(fade, fadeStart, fadeEnd, UViolet_EL2Start, UViolet_EL2End));
    constUViolet_T = round(map(fade, fadeStart, fadeEnd, UViolet_TStart, UViolet_TEnd));
    constUViolet_BL = round(map(fade, fadeStart, fadeEnd, UViolet_BLStart, UViolet_BLEnd));
    constServoPositionHeight = round(map(fade, fadeStart, fadeEnd, servoPositionHeightStart, servoPositionHeightEnd));
    constServoPositionDirection = round(map(fade, fadeStart, fadeEnd, servoPositionDirectionStart, servoPositionDirectionEnd));
    constServoPositionBacklight = round(map(fade, fadeStart, fadeEnd, servoPositionBacklightStart, servoPositionBacklightEnd));


    analogWrite(pinTravRed, constLedTravRedValue);
    analogWrite(pinTravGreen, constLedTravGreenValue);
    analogWrite(pinTravBlue, constLedTravBlueValue);
    servoH.write(constServoPositionHeight);
    servoD.write(constServoPositionDirection);

    analogWrite(pinBacklightingRed, constLedBacklightRedValue);
    analogWrite(pinBacklightingGreen, constLedBacklightGreenValue);
    analogWrite(pinBacklightingBlue, constLedBacklightBlueValue);
    servoBL.write(constServoPositionBacklight);

    analogWrite(pinUViolet_EL1, constUViolet_EL1);
    analogWrite(pinUViolet_EL2, constUViolet_EL2);
    analogWrite(pinUViolet_T, constUViolet_T);
    analogWrite(pinUViolet_BL, constUViolet_BL);
    //delay(1);

  } while (millis() / 100 < timeLine[var - 1][t + 1]);

  servoH.detach();
  servoD.detach();
  servoBL.detach();
  digitalWrite(pinTravMotorUp, LOW);
  digitalWrite(pinTravMotorDown, LOW);
  analogWrite(pinTravMotorSpeed, 0);

}
//////////////////
void drawScene(Cart scene, String cartMode, int cartSpeed, int t)
{
  servoH.attach(pinServoHeight);
  servoD.attach(pinServoDirection);
  servoBL.attach(pinBacklightingServo);


  byte ledTravRedValue = scene.readValue("LTRV");
  byte ledTravGreenValue = scene.readValue("LTGV");
  byte ledTravBlueValue = scene.readValue("LTBV");
  byte ledBacklightRedValue = scene.readValue("LBRV");
  byte ledBacklightGreenValue = scene.readValue("LBGV");
  byte ledBacklightBlueValue = scene.readValue("LBBV");
  byte UViolet_EL1 = scene.readValue("UV_EL1");
  byte UViolet_EL2 = scene.readValue("UV_EL2");
  byte UViolet_T = scene.readValue("UV_T");
  byte UViolet_BL = scene.readValue("UV_BL");
  byte servoPositionHeight = scene.readValue("SSPH");
  byte servoPositionDirection = scene.readValue("SPD");
  byte servoPositionBacklight = scene.readValue("SPBL");

  Serial.println("tiempos");
  Serial.println(timeLine[var - 1][t]);
  Serial.println(timeLine[var - 1][t + 1]);

  do
  {
    if (cartMode == "RIGHT")
    {
      digitalWrite(pinTravMotorUp, HIGH);
      digitalWrite(pinTravMotorDown, LOW);
      analogWrite(pinTravMotorSpeed, cartSpeed);
    }

    if (cartMode == "LEFT")
    {
      digitalWrite(pinTravMotorUp, LOW);
      digitalWrite(pinTravMotorDown, HIGH);
      analogWrite(pinTravMotorSpeed, cartSpeed);
    }

    if (cartMode == "STOP")
    {
      digitalWrite(pinTravMotorUp, LOW);
      digitalWrite(pinTravMotorDown, LOW);
      analogWrite(pinTravMotorSpeed, 0);
    }

    analogWrite(pinTravRed, ledTravRedValue);
    analogWrite(pinTravGreen, ledTravGreenValue);
    analogWrite(pinTravBlue, ledTravBlueValue);
    servoH.write(servoPositionHeight);
    servoD.write(servoPositionDirection);

    analogWrite(pinBacklightingRed, ledBacklightRedValue);
    analogWrite(pinBacklightingGreen, ledBacklightGreenValue);
    analogWrite(pinBacklightingBlue, ledBacklightBlueValue);
    servoBL.write(servoPositionBacklight);

    analogWrite(pinUViolet_EL1, UViolet_EL1);
    analogWrite(pinUViolet_EL2, UViolet_EL2);
    analogWrite(pinUViolet_T, UViolet_T);
    analogWrite(pinUViolet_BL, UViolet_BL);
  } while (millis() / 100 < timeLine[var - 1][t + 1]);


  digitalWrite(pinTravMotorUp, LOW);
  digitalWrite(pinTravMotorDown, LOW);
  analogWrite(pinTravMotorSpeed, 0);
  servoH.detach();
  servoD.detach();
  servoBL.detach();
}

void endScene() {


  musicState = 0;
  analogWrite(pinTravRed, 0);
  analogWrite(pinTravGreen, 0);
  analogWrite(pinTravBlue, 0);

  analogWrite(pinBacklightingRed, 0);
  analogWrite(pinBacklightingGreen, 0);
  analogWrite(pinBacklightingBlue, 0);

  analogWrite(pinUViolet_EL1, 0);
  analogWrite(pinUViolet_EL2, 0);
  analogWrite(pinUViolet_T, 0);
  analogWrite(pinUViolet_BL, 0);
  digitalWrite(pinTravMotorUp, LOW);
  digitalWrite(pinTravMotorDown, LOW);
  analogWrite(pinTravMotorSpeed, 0);

}


void setMillis(unsigned long new_millis) {
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}


void Display(byte N)
{
  for (byte i = 0 ; i < 7 ; i++)
  { byte valor = numero[N][i] ;
    digitalWrite(disp[i] , valor);
  }
}
