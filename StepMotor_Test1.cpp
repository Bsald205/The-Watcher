/* Created by Daniel Rascón Carrillo 
  *
  * This code is made to control a step motor whit analog reads.
*/
#include <iostream>
#include <Stepper.h>

using namespace std;

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution

// ULN2003 Motor Driver Pins
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

int pos = 0;
const int pin_MicNorte = 26;
const int pin_MicEste = 27;
const int pin_MicOeste = 25;

// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

void movimiento(){
  cout << "Este : " << analogRead(pin_MicEste) << "\t Norte: " << analogRead(pin_MicNorte) << "\tOeste: " << analogRead(pin_MicOeste) << endl;
}

void mover_Norte() {
  cout << "Moviendo a Norte" << endl;
  movimiento();
  if (pos != 0){
    switch(pos){
      case 1:
        myStepper.step(-512);
      break;
      case -1:
        myStepper.step(512);
      break;
    }
    pos = 0;
  }
}

void mover_Este() {
  cout << "Moviendo a Este" << endl;
  if (pos != -1){
    switch(pos){
      case 0:
        myStepper.step(-512);
      break;
      case 1:
        myStepper.step(-1024);
      break;
    }
    pos = -1;
  }
}

void mover_Oeste() {
    cout << "Moviendo a Oeste" << endl;
    if (pos != 1){
      switch(pos){
        case 0:
          myStepper.step(512);
        break;
        case -1:
          myStepper.step(1024);
        break;
      }
      pos = 1;
  }
}

void setup() {
  // set the speed at 5 rpm
  myStepper.setSpeed(15);
  // initialize the serial port
  Serial.begin(115200);
}

void loop() {
  if (analogRead(pin_MicNorte) >= 2048){
    movimiento();
    mover_Norte();
  }
  if (analogRead(pin_MicEste) >= 2048){
    movimiento();
    mover_Este();
  }
  if (analogRead(pin_MicOeste) >= 2048){
    movimiento();
    mover_Oeste();
  }
}
