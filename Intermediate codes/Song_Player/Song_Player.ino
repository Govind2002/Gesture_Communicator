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
 tmrpcm.play("song1.wav"); //the sound file "song" will play each time the arduino powers up, or is reset
                          //try to provide the file name with extension
                     
}


void loop()
{  
  while(digitalRead(pp)==0 || digitalRead(next)==0 || digitalRead(prev)==0)
  {
    if(digitalRead(pp)==0)
    {
      tmrpcm.pause();
      while(digitalRead(pp)==0);
      delay(200);
    }
    else if(digitalRead(next)==0)
    {
      if(temp<4)//temp should be lesser than no. of songs 
      temp=temp+1;
      while(digitalRead(next)==0);
      delay(200);
      song();
    }
    else if(digitalRead(prev)==0)
    {
      if(temp>1)
      temp=temp-1;
      while(digitalRead(prev)==0);
      delay(200);
      song();
    }
  }
}

void song (void)
{
  if(temp==1)
  {
    tmrpcm.play("Song1.wav");  
  }
  else if(temp==2)
  {
    tmrpcm.play("Song2.wav");  
  }
  else if(temp==3)
  {
    tmrpcm.play("Song3.wav");  
  }
  else if(temp==4)
  {
    tmrpcm.play("Song4.wav");  
  }
}
