#include <SD.h> // need to include the SD library
#define SD_ChipSelectPin 4 //connect pin 4 of arduino to cs pin of sd card
#include <TMRpcm.h> //Arduino library for asynchronous playback of PCM/WAV files
#include <SPI.h> //  need to include the SPI library

TMRpcm tmrpcm; // create an object for use in this sketch
int temp=1;
int pp=5;
int next=6;
int prev=7;
void setup()
{ 
 pinMode(pp,INPUT_PULLUP);
 pinMode(next,INPUT_PULLUP);
 pinMode(prev,INPUT_PULLUP);
 
 tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
 Serial.begin(9600);
 if (!SD.begin(SD_ChipSelectPin)) // returns 1 if the card is present
 {
  Serial.println("SD fail");
  return;
 }

 tmrpcm.setVolume(5); //
 tmrpcm.play("kesariya.wav"); //the sound file "song" will play each time the arduino powers up, or is reset
                          //try to provide the file name with extension
                     
}


void loop()
{  
if (Serial.available()) {
  char receivedChar = Serial.read();
  
  if (receivedChar == 'p') {
    tmrpcm.play("high.wav");
    Serial.println("2");
  }
  else if (receivedChar == 'l') {
    tmrpcm.play("high_1.wav");
    Serial.println("3");
  }
  else if (receivedChar == 'm') {
    tmrpcm.play("auto.wav");
    Serial.println("4");
  }
  else if (receivedChar == 't') {
    tmrpcm.play("last.wav");
    Serial.println("4");
}
  }
}
