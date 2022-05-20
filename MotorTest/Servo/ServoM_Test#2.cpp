// Servo motor, Prueba 2
// Prueba utilizando señales analogicas de un potenciometro a un servo, controlado por ESP32
// By Brandon Saldivar

//Referemces https://dronebotworkshop.com/esp32-servo/
//References http://kio4.com/arduino/220_Wemos_Interrupcion.htm

// servo.cpp

#include <iostream>
#include <ESP32Servo.h>

using namespace std;

Servo myservo;  
const int Pot = 34;
int Valor;
int servoPin = 13;
bool mic1;
bool mic2;

void Norte () {
  if (Valor >= 2650 && Valor <= 5000){
    myservo.write(45);
    cout << "Norte"<< endl;
  }
}

void Este (){
  if (Valor >= 0 && Valor <= 1300){
    myservo.write(0);;
   cout << "Este"<<endl;
  }
}

void Oeste () {
  if (Valor >= 1350 && Valor <= 2600){
    myservo.write(180);
    cout << "Oeste" <<endl;
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

}

void loop() {

Valor = analogRead (Pot);
cout << Valor << endl;
delay(500);

Norte();
Este();
Oeste();
 
}
