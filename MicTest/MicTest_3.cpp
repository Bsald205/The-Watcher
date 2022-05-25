/*  Alan Aceves : a325103@uach.mx <?>
 *   
 *  This code reads three analog signals and transforms its frequency to obtain the highest peak
 *  
 *  Standard Arduino FFT library https://github.com/kosme/arduinoFFT
 */

#include <iostream>
#include "arduinoFFT.h" //.1 Standard Arduino FFT library https://github.com/kosme/arduinoFFT

using namespace std;

///GPIO INPUT
#define right 34
#define left  32
#define front 35

arduinoFFT FFT = arduinoFFT(); //initializing FFT

int i ;

const int SAMPLE = 1024;    // Sampling period 128 bytes = 1024 bits
const int tolerance= 2600;  // 1500 to detect low noise :: 2600 to cancel low noise

//// Real number
double vRight [SAMPLE];      
double vLeft  [SAMPLE];     // use this variables for the microphones comparator  
double vFront [SAMPLE];    

//// Imaginary number
double iRight [SAMPLE];
double iLeft  [SAMPLE];    //  only usingned on the Fast Fourier Transform
double iFront [SAMPLE];

//// Data capture in the Array
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

void setup() {
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
  //.3For better performance remove all the couts
  for (i = 0 ; i < 512 ; i++){
    if ( vRight [i] > tolerance && i > 1 ){ cout << vRight[i] << " Right" << endl;}   //.3
    if ( vLeft  [i] > tolerance && i > 1 ){ cout << vLeft[i]  << " Left"  << endl;}   //.3
    if ( vFront [i] > tolerance && i > 1 ){ cout << vFront[i] << " Front" << endl;}   //.3
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
