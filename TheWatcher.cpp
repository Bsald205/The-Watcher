/*  Alan Aceves : a325103@uach.mx <?>
 *  Daniel Rascón Carrillo : a329625 @uach.mx <?>
 *  Brandon Saldivar : bsaldivar205@gmail.com
 *   
 *  
 *  
 *  Standard Arduino FFT library https://github.com/kosme/arduinoFFT
 */

#include <iostream>
#include <Stepper.h>
#include "arduinoFFT.h" //.1 Standard Arduino FFT library https://github.com/kosme/arduinoFFT

using namespace std;

//ULN20003 Motor Driver Pins
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

///GPIO INPUT
#define right 34
#define left  32
#define front 35

arduinoFFT FFT = arduinoFFT();

int i ;

const int stepsPerRevolution = 2048;
int pos = 0;

//initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

const int SAMPLE = 1024;
const int tolerance= 2600;

//Real number
double vRight [SAMPLE];        
double vLeft  [SAMPLE];      //use this variables for the microphones comparator  
double vFront [SAMPLE];

//Imaginary number
double iRight [SAMPLE];
double iLeft  [SAMPLE];
double iFront [SAMPLE];

////Data capture in the Array
void readMicrophones (){
   for (int i = 0 ; i < SAMPLE ; i++){
    vRight[i] = analogRead(right);
    iRight[i] = 0;

    vLeft[i]  = analogRead(left);
    iLeft[i]  = 0 ;

    vFront[i] = analogRead(front);
    iFront[i] = 0 ;
  }
}

void mover_Norte() {
  cout << "Moviendo a Norte" << endl;
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
  myStepper.setSpeed(15);
  Serial.begin(115200);
}

void loop() {

 //// Reading Signals
  readMicrophones();

  ////.1 Fast Fourier Transform Right
  fourierRight();
  
  ////.1 Fast Fourier Transform Left
  fourierLeft();
  
  ////.1 Fast Fourier Transform Front
  fourierFront();

  //// SHOWING SPECTRUM DATA
  for (i = 0 ; i < 512 ; i++){
    if ( vRight [i] > tolerance && i > 1 ){
      mover_Oeste();
      cout << vRight[i] << " Right" << endl;
    }
    if ( vLeft  [i] > tolerance && i > 1 ){
      mover_Este();
      cout << vLeft[i]  << " Left"  << endl;
    }
    if ( vFront [i] > tolerance && i > 1 ){
      mover_Norte();
      cout << vFront[i] << " Front" << endl;
    }
  }
}

void fourierRight(){
  FFT.Windowing           (vRight, SAMPLE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute             (vRight, iRight, SAMPLE, FFT_FORWARD);
  FFT.ComplexToMagnitude  (vRight, iRight, SAMPLE);
}

void fourierLeft(){
  FFT.Windowing           (vLeft, SAMPLE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute             (vLeft, iLeft, SAMPLE, FFT_FORWARD);
  FFT.ComplexToMagnitude  (vLeft, iLeft, SAMPLE);
}

void fourierFront(){
  FFT.Windowing           (vFront, SAMPLE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute             (vFront, iFront, SAMPLE, FFT_FORWARD);
  FFT.ComplexToMagnitude  (vFront, iFront, SAMPLE);
}
