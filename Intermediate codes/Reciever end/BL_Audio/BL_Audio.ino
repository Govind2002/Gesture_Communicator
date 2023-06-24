#include<SoftwareSerial.h>
#include <SD.h> // need to include the SD library
#define SD_ChipSelectPin 4 //connect pin 4 of arduino to cs pin of sd card
#include <TMRpcm.h> //Arduino library for asynchronous playback of PCM/WAV files
#include <SPI.h> //  need to include the SPI library

TMRpcm tmrpcm; // create an object for use in this sketch

/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(10,8); /* (Rx,Tx) */  

int message = 49;

void setup() {
  //bt.begin(9600); /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */ 
  tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc

  if (!SD.begin(SD_ChipSelectPin)) // returns 1 if the card is present
 {
  Serial.println("SD fail");
 }

 tmrpcm.setVolume(5); //
 //tmrpcm.play("road.wav"); //the sound file "song" will play each time the arduino powers up, or is reset
 //tmrpcm.play("help.wav");                         //try to provide the file name with extension
}

void loop() {
   Serial.println("message");
  
    /*if (bt.available()) // If data is available on serial port 
    {
   message=bt.read();
   Serial.println("message");
     
    }*/
    speaker();
  
}


void speaker(){

  tmrpcm.setVolume(5);
  tmrpcm.play("help.wav");
  //Serial.println("message");
  }
