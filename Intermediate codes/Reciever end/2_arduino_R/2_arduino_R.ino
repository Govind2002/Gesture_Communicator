#include <SD.h> // need to include the SD library
#define SD_ChipSelectPin 4 //connect pin 4 of arduino to cs pin of sd card
#include <TMRpcm.h> //Arduino library for asynchronous playback of PCM/WAV files
#include <SPI.h> //  need to include the SPI library
#include<SoftwareSerial.h>

TMRpcm tmrpcm; // create an object for use in this sketch

SoftwareSerial AU(2,3);
int message;

void setup() {
  // put your setup code here, to run once:
AU.begin(9600);
Serial.begin(9600);
tmrpcm.speakerPin = 9;

if (!SD.begin(SD_ChipSelectPin)) // returns 1 if the card is present
 {
  Serial.println("SD fail");
  return;
 }

 tmrpcm.setVolume(3); 

}

void loop() {
  // put your main code here, to run repeatedly:

   if (AU.available()) /* If data is available on serial port */
    {
   message=AU.read();
   if (message==52|message==53){}
  else{
//   Serial.println("message");
//   Serial.println(message);
   speaker(message);
   }
}
}



void speaker(int b){

  switch(b){
  case 48:tmrpcm.play("help.wav");
  break;

  case 49:tmrpcm.play("name.wav");
  break;

  case 50:tmrpcm.play("road.wav");
  break;

  case 51:tmrpcm.play("qn.wav");
  break;

  case 54:tmrpcm.play("water.wav");
  break;

  case 55:tmrpcm.play("thank_you.wav");
  break;

//  case 53:tmrpcm.play("road.wav");
//  break;

  default:Serial.println(message);

  }

  
 }
