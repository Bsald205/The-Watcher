///https://github.com/G6EJD/ESP32-8-Octave-Audio-Spectrum-Display/blob/master/ESP32_Spectrum_Display_03.ino
//Alan Aceves : a325103@uach.mx <?>
#include <iostream>
#include "arduinoFFT.h" // Standard Arduino FFT library https://github.com/kosme/arduinoFFT

using namespace std;

// GPIO INPUT
#define A0 34

arduinoFFT FFT = arduinoFFT();

int i;

//Samples 2^(10)
const int SAMPLES = 1024;            
const int SAMPLING_FREQUENCY = 4000000; 

//Dominion of time
unsigned long newTime;
unsigned int sampling_period_us;

float umbral_max = 2000;

// Data base of our Analog signal
double vReal[SAMPLES];  //Real numbers
double vImag[SAMPLES];  //Imaginary numbers

//This funcion take the most highest peak
void umbral (){
  if (vReal[i] > umbral_max){umbral_max = vReal[i];}
}

void setup() {
  Serial.begin(115200);

  // period Initialize
  sampling_period_us = round(10000000 * (1.0 / SAMPLING_FREQUENCY));
}

void loop() {

  ////Data capture in the Array
  for (int i = 0 ; i < SAMPLES ; i++) {
    newTime = micros();
    vReal[i] = analogRead(A0); //our Array 
    vImag[i] = 0;
    while ((micros() - newTime) < sampling_period_us) { /* do nothing to wait */ }
  }

  //// Fast fourier transform API 
  FFT.Windowing           (vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute             (vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude  (vReal, vImag, SAMPLES);
  double x = FFT.MajorPeak(vReal, SAMPLES, sampling_period_us);
  

  //// SHOWING SPECTRUM DATA
  for (i = 0 ; i < 512 ; i++){ 
    if (vReal[i] > 1500 && i > 1) { 
      umbral();
      /*
      cout << "SAMPLE #" << i 
           << " : "      << vReal[i] 
           << "\t-> "    << x
           << endl;*/
      cout << vReal[i] <<" [" << i-1 << "]" <<endl;
    }
  }
}
