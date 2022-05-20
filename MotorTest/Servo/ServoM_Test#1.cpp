// Servo motor, Prueba 1
// Prueba utilizando interrupciones y botones controlado por ESP32
// By Brandon Saldivar

//Referemces https://dronebotworkshop.com/esp32-servo/
//References http://kio4.com/arduino/220_Wemos_Interrupcion.htm

// servo.cpp

#include <iostream>
#include <ESP32Servo.h>

using namespace std;

Servo myservo;  
int pos = 0;  
const int pulsador12 = 12;
const int pulsador14 = 14;
const int pulsador27 = 27;
int servoPin = 13;


void Norte() {
  while (digitalRead(pulsador12)== HIGH){
    myservo.write(0);
  }
}

void Este() {
  while (digitalRead(pulsador14)== HIGH){
    myservo.write(90);
  }
}

void Oeste() {
  while (digitalRead(pulsador27)== HIGH){
    myservo.write(180);
  }
}

void setup() {

  Serial.begin(115200);  
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);  
  myservo.attach(servoPin, 500, 2400); 
  pinMode(pulsador12, INPUT_PULLUP);
  pinMode(pulsador14, INPUT_PULLUP);
  pinMode(pulsador27, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(12), Norte, RISING);
  attachInterrupt(digitalPinToInterrupt(14), Este, RISING);
  attachInterrupt(digitalPinToInterrupt(27), Oeste, RISING);

}

void loop() {
cout << "Lectura de Microfono" << "\n";
delay(500);
}
