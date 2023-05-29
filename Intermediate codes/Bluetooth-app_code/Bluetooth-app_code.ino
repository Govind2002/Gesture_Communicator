#include <SoftwareSerial.h>

SoftwareSerial BTserial(10,11); // RX | TX

int sensorPin = A0;

int sensorValue = 0;

void setup() {

BTserial.begin(9600); }

void loop() {

sensorValue = analogRead(sensorPin);

//IMPORTANT: The complete String has to be of the Form: 1234,1234,1234,1234;

//(every Value has to be seperated through a comma (',') and the message has to

//end with a semikolon (';'))

BTserial.print("1234");

BTserial.print(",");

BTserial.print("1234.0");

BTserial.print(",");

BTserial.print("1234 hPa");

BTserial.print(",");

BTserial.print("500 ml/s");

BTserial.print(",");

BTserial.print(sensorValue);

BTserial.print(";");

//message to the receiving device

delay(20);

}
