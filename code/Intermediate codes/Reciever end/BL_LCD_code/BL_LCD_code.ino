#include<SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(10,8); /* (Rx,Tx) */  

int message;

void setup() {
  bt.begin(9600); /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */ 
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
}

void loop() {
  
    if (bt.available()) /* If data is available on serial port */
    {
   message=bt.read();
   Serial.println(message);
     
    }
    lcddisplay(message);
    delay(10);
  
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
  break;
  }

  lcd.clear();//Clean the screen
  //delay(100);
  
}
