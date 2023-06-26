#include<SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <SD.h> // need to include the SD library
#define SD_ChipSelectPin 4 //connect pin 4 of arduino to cs pin of sd card
#include <TMRpcm.h> //Arduino library for asynchronous playback of PCM/WAV files
#include <SPI.h> //  need to include the SPI library

TMRpcm tmrpcm; // create an object for use in this sketch

/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(10,8); /* (Rx,Tx) */  

int message;

void setup() {
  bt.begin(9600); /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */ 
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light

  tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc

  if (!SD.begin(SD_ChipSelectPin)) // returns 1 if the card is present
 {
  Serial.println("SD fail");
 }

 tmrpcm.setVolume(5); //
 tmrpcm.play("help.wav"); //the sound file "song" will play each time the arduino powers up, or is reset
                          //try to provide the file name with extension
}

void loop() {
  
    if (bt.available()) /* If data is available on serial port */
    {
   message=bt.read();
   Serial.println(message);
     
    }
    lcddisplay(message);
  
}


void lcddisplay(int b)
{
  lcd.setCursor(0,0); //Defining positon to write from first row,first column .
  
  switch(b){
  case 49:lcd.print("PLEASE HELP");
  Serial.println("message");
  delay(10);//You can write 16 Characters per line .
  break;
  case 50:lcd.print("HELLO");
  delay(10);
  break;
  case 51:lcd.print("MY NAME IS JOHN");
  delay(10);
  break;
  case 52:lcd.print("HAVE A NICE DAY");
  delay(10);
  break;
  case 53:lcd.print("I NEED WATER");
  delay(10);
  break;
  case 54:lcd.print("THANK YOU");
  delay(10);
  break;
  case 55:lcd.print("waiting for command...");
  delay(10);
  }

  lcd.clear();//Clean the screen
  //delay(100);
  
}

void speaker(int b){

  switch(b){
  case 49:tmrpcm.play("road.wav");
  break;

  case 50:tmrpcm.play("name.wav");
  break;

  case 51:tmrpcm.play("qn.wav");
  break;

  case 52:tmrpcm.play("road.wav");
  break;

  case 53:tmrpcm.play("road.wav");
  break;

  case 54:tmrpcm.play("road.wav");
  break;

  case 55:tmrpcm.play("road.wav");
  break;

  }

  
 }
