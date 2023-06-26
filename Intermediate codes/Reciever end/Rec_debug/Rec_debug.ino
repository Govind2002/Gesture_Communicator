#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SD.h> // need to include the SD library
#define SD_ChipSelectPin 4 //connect pin 4 of arduino to cs pin of sd card
#include <TMRpcm.h> //Arduino library for asynchronous playback of PCM/WAV files
#include <SPI.h> //  need to include the SPI library

LiquidCrystal_I2C lcd(0x27,16,2); 
SoftwareSerial bt(10, 8); //  CONNECT BT RX PIN TO ARDUINO 11 PIN | CONNECT BT TX PIN TO ARDUINO 10 PIN
TMRpcm tmrpcm; // create an object for use in this sketch
int message = 49;

/*SD card connections
MISO - 12 (MISO of Master to MISO of Slave)
MOSI - 11  
SCK  - 13
CS   - 4
*/

void setup() {
  
  Serial.begin(9600);      
  bt.begin(9600);
  tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  tmrpcm.setVolume(5);
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  

  if (!SD.begin(SD_ChipSelectPin)) // returns 1 if the card is present
 {
  Serial.println("SD fail"); //for debug
 } else {
  Serial.println("SD success");
 }

}


void  loop() {          
  bt.begin(9600); 
  if(bt.available()>0){  
   message=bt.read();
   Serial.println(String(message));
  } 

//   Serial.println("message");
   tmrpcm.play("road.wav");
   lcddisplay(message);
   //speaker(message);
}   


void lcddisplay(int b)
{
  lcd.setCursor(0,0); //Defining positon to write from first row,first column .
  
  switch(b){
  case 49:lcd.print("PLEASE HELP");
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
  case 56:lcd.print("waiting for command...");
  delay(10);
  }

  lcd.clear();//Clean the screen
  //delay(100);
  
}

void speaker(int b){

  

}

  

  
 
