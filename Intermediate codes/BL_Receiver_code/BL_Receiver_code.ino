#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); //  CONNECT BT RX PIN TO ARDUINO 12 PIN | CONNECT BT TX PIN TO ARDUINO 11 PIN
#include<SPI.h>

  
int trigPin = 12;    // Trig
int echoPin = 13;    // Echo
long duration,  cm, inches;
int direct;
int l1=3;
int r1=5;
int l2=6;
int r2=9;

int  forword_corr;


int a = 0 ;
int s = 3; 


int b = 0 ;
int  c = 2; 





void setup() {
  Serial.begin(9600);      
  BTSerial.begin(9600);    
  
 
  pinMode(l1, OUTPUT);
  pinMode(r1,  OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(r2, OUTPUT);
  
  digitalWrite(l1,  LOW);
  digitalWrite(r1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(r2,  LOW);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void  loop() {
  
   digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,  LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if(BTSerial.available()>0){  // Witing for data incoming from the other XBee module
   direct=BTSerial.read();
    
                if(direct == 'B'){
            Serial.println("Backward");
            backward();
          }else if (direct=='F'){
              Serial.println("Forward");
            forward();
          }else if(direct == 'R'){
            Serial.println("Right");
            left();
          }else if(direct == 'L'){
            Serial.println("left");
            right();

           }else if(direct == 'r'){
            Serial.println("rotright");
            rotr();
            
          }else if(direct == 'l'){
            Serial.println("rotleft");
            rotl();
            }else if  (direct == 'S'){
            Serial.println("Stop");
            stopCar();
          }
                
     
           
     
  }
}
    
  


 
void forward()
{
  if(cm<=15){
     digitalWrite(l1, LOW);
      digitalWrite(r2, LOW);

    }
    else{
    digitalWrite(l1, HIGH);
  digitalWrite(r1, LOW);
  digitalWrite(l2, LOW);
  
  
    digitalWrite(r2, LOW);
 delay(2);
    digitalWrite(r2, HIGH);
   delay(2);
}
}
void backward()
{
  digitalWrite(l1, LOW);
  digitalWrite(l2,  HIGH);
  digitalWrite(r2, LOW);
  if(b%c == 0){
    digitalWrite(r1, HIGH);
  }else{
    digitalWrite(r1, LOW);
   }
   

    if(b > 1000 ) {
     b=0;
   }
}
void right()
{
  digitalWrite(l1, HIGH);
  digitalWrite(r1,  LOW);
  digitalWrite(l2, LOW);
  analogWrite(r2, 100);
 
    

}
void  left()
{
   analogWrite(l1, 100);
  digitalWrite(r1, LOW);
  digitalWrite(l2,  LOW);
  digitalWrite(r2, HIGH);
}

void stopCar() {
    digitalWrite(l1,  LOW);

  digitalWrite(r1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(r2,  LOW);
}
void rotr() {

  digitalWrite(l1, HIGH);
  digitalWrite(r1,  LOW);
  digitalWrite(l2, HIGH);
  digitalWrite(r2, LOW);
}
void rotl(){

  digitalWrite(l1, LOW);
  digitalWrite(r1, HIGH);
  digitalWrite(l2, LOW);
  digitalWrite(r2, HIGH);
}
