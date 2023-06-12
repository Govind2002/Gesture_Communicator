#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 
SoftwareSerial bt(10, 11); //  CONNECT BT RX PIN TO ARDUINO 11 PIN | CONNECT BT TX PIN TO ARDUINO 10 PIN

int message=0;

void lcddisplay();


void setup() {
  Serial.begin(9600);      
  bt.begin(9600);
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  }

void  loop() {
  if(bt.available()>0){  
   message=bt.read();
  } 

   Serial.println(message);
   lcddisplay(message);
    

   /*switch(message){
    case 1:
    lcddisplay("HELP");
    break;

    case 2:
    lcddisplay("HELLO");
    break;

    case 3:
    lcddisplay("Hiiii");
    break;

    case 4:
    lcddisplay("THANK YOU");
    break;

    case 5:
    lcddisplay("I Need Water");
    break;

    case 6:
    lcddisplay("Welcome");
    break;

    case 7:
    lcddisplay("Have a nice day");
    break;

    case 8:
    lcddisplay("Bye");
    break;

    default:
    lcddisplay("waiting for command");
   }*/



}

/*void lcddisplay(char a){
  lcd.setCursor(0,0); //Defining positon to write from first row,first column .
  lcd.print(a); //You can write 16 Characters per line .
  delay(1000);//Delay used to give a dynamic effect
  lcd.clear();//Clean the screen
  }*/

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

//void speaker{
 // }
