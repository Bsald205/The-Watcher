/*  
    Alan Aceves      : a325103@uach.mx <?> alan.aceves.chavez@gmail.com 
    Daniel Rascón    : a329625@uach.mx <?>
    Brandon Saldivar : bsaldivar205@gmail.com <?>
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

arduinoFFT FFT = arduinoFFT(); //initializing FFT

int i ;

const int stepsPerRevolution = 2048;
int pos = 0;

//initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

const int SAMPLE = 1024;   // Sampling period 128 bytes = 1024 bits
const int tolerance= 2000; // 1500 to detect low noise :: 2600 to cancel low noise

//Real number
double vRight [SAMPLE];        
double vLeft  [SAMPLE];      // use this variables for the microphones comparator  
double vFront [SAMPLE];

//Imaginary number
double iRight [SAMPLE];
double iLeft  [SAMPLE];      // only usingned on the Fast Fourier Transform
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
/// Motor function to move Front
void mover_Norte() {
  cout << "Moviendo a Norte" << endl; //.3
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
/// Motor function to move Front
void mover_Este() {
  cout << "Moviendo a Este" << endl; //.3
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
/// Motor function to move Front
void mover_Oeste() {
    cout << "Moviendo a Oeste" << endl; //.3
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

  //// MASTER COMPARATOR
  //.3 For better performance remove all the couts
  for (i = 0 ; i < 512 ; i++){
    if ( vRight [i] > tolerance && i > 1 ){
      mover_Oeste();
      //cout << vRight[i] << " Right" << endl; //.3
    }
    if ( vLeft  [i] > tolerance && i > 1 ){
      mover_Este();
     // cout << vLeft[i]  << " Left"  << endl; //.3
    }
    if ( vFront [i] > tolerance && i > 1 ){
      mover_Norte();
      //cout << vFront[i] << " Front" << endl; //.3
    }
  }
}

//.1
void fourierRight(){
  FFT.Windowing           (vRight, SAMPLE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute             (vRight, iRight, SAMPLE, FFT_FORWARD);
  FFT.ComplexToMagnitude  (vRight, iRight, SAMPLE);
}
//.1
void fourierLeft(){
  FFT.Windowing           (vLeft, SAMPLE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute             (vLeft, iLeft, SAMPLE, FFT_FORWARD);
  FFT.ComplexToMagnitude  (vLeft, iLeft, SAMPLE);
}
//.1
void fourierFront(){
  FFT.Windowing           (vFront, SAMPLE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute             (vFront, iFront, SAMPLE, FFT_FORWARD);
  FFT.ComplexToMagnitude  (vFront, iFront, SAMPLE);
}
