#include  <Wire.h>
#include<SoftwareSerial.h>

/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(10,11); /* (Rx of Arduino,Tx of Arduino)( connect 10 to Bt Tx and 11 to Bt Rx */ 

const  int MPU_ADDRESS = 0x68; // MPU6050 I2C address

float AccX, AccY, AccZ;
float  GyroX, GyroY, GyroZ;

float accAngleX, accAngleY, gyroAngleX, gyroAngleY,  gyroAngleZ;
float roll, pitch, yaw;

float AccErrorX, AccErrorY, GyroErrorX,  GyroErrorY, GyroErrorZ;

float elapsedTime, currentTime, previousTime;

int  c = 0;
int pushbutton = 1;
int flexsensor = A0;

void  MPU_read_accel_data();
void  MPU_read_gyro_data();
void calculate_IMU_error();

void setup()
{
  
  pinMode(flexsensor,INPUT);
  Serial.begin(9600);
  bt.begin(9600); /* Define baud rate for software serial communication */

  Wire.begin();                      //  Initialize comunication
  Wire.beginTransmission(MPU_ADDRESS);       // Start  communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  //  Talk to the register 6B
  Wire.write(0x00);                  // Make reset -  place a 0 into the 6B register
  Wire.endTransmission(true);        //end the  transmission

  
  
//Call this function  if you need to get the IMU error values for your module*/
//while(true) calculate_IMU_error();
//delay(20);
  
}

void loop()
{
  
  MPU_read_accel_data();
  MPU_read_gyro_data();

 
  // calculate time elapsed since last time  we were here
   
  previousTime = currentTime;        // Previous time is stored  before the actual time read
  currentTime = millis();            // Current time  actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide  by 1000 to get seconds


  // Complementary filter - combine acceleromter  and gyro angle values
  
  roll  = 0.92 * (roll  + (GyroX * elapsedTime)) + 0.08  * accAngleX;
  pitch = 0.92 * (pitch + (GyroY * elapsedTime)) + 0.08 * accAngleY;
  yaw   = gyroAngleZ;


  // Currently the raw values are in degrees  per seconds, deg/s, so we need to multiply by sendonds (s) to get the angle in degrees
  gyroAngleX += GyroX * elapsedTime; // deg/s * s = deg
  gyroAngleY += GyroY  * elapsedTime;
  gyroAngleZ += GyroZ * elapsedTime;
  
  /*by me */
  // Print the values on the serial monitor
    /*Serial.print("roll:");
    Serial.println(roll);

    Serial.print("pitch:");
    Serial.println(pitch);
    
    Serial.print("yaw:");
    Serial.println(yaw);

    Serial.println("");*/
    
if(pushbutton){
    if(analogRead(flexsensor)>500){
      Serial.println("PLEASE HELP");
      bt.print("1");
    }else if(pitch>20){
      Serial.println("HELLO");
      bt.print("2");
    }else if(roll>30){
      Serial.println("MY NAME IS JOHN");
      bt.print("3");
    }else if(roll<-30){
      Serial.println("HAVE A NICE DAY");
      bt.print("4");
    }else if(yaw>30){
      Serial.println("I NEED WATER");
      bt.print("5");
    }else if(yaw<-30){
      Serial.println("THANK YOU");
      bt.print("6");
    }else if(pitch<-17){
      Serial.println("HUNGRY");
      bt.print("7");
    }else{ 
      Serial.println("waiting for command...");
      bt.print("8");}

     Serial.println(" ");
  
    
    }
     
}

void  MPU_read_accel_data()
{
  // === Read acceleromter data === //
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESS, 6, true); // Read 6 registers total, each axis value  is stored in 2 registers
  
  //For a range of +-2g, we need to divide the  raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 |  Wire.read()) / 16384.0; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read())  / 16384.0; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0;  // Z-axis value
  
  // Calculating Roll and Pitch from the accelerometer  data
  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI)      - (-0.40);  // AccErrorX ~(0.58) See the calculate_IMU_error()custom function  for more details
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ,  2))) * 180 / PI) - (-3.75); // AccErrorY ~(-1.58)
  
}


void MPU_read_gyro_data()
{
  // === Read gyroscope data === //
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESS, 6, true); // Read 4 registers total, each axis value  is stored in 2 registers

  // For a 250deg/s range we have to divide first  the raw value by 131.0, according to the datasheet
  GyroX = (Wire.read() <<  8 | Wire.read()) / 131.0;
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
  
  // Correct the outputs  with the calculated error values
  GyroX = GyroX - (-6.68); // GyroErrorX = ~  (-2.12) 
  GyroY = GyroY - (-0.98);  // GyroErrorY = ~ (4.12)
  GyroZ = GyroZ  - (2.94);  // GyroErrorZ = ~ (1.20)


}


void calculate_IMU_error()
{
  
  // We can call this funtion in the setup section to calculate the accelerometer  and gyro data error. From here we will get the error values used in the above equations  printed on the Serial Monitor.
  // Note that we should place the IMU flat in  order to get the proper values, so that we then can the correct values
  // Read  accelerometer values 200 times
  
  while (c < 200)
  {
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS,  6, true);
    AccX = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    AccY  = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    AccZ = (Wire.read() << 8 |  Wire.read()) / 16384.0 ;
    // Sum all readings
    AccErrorX = AccErrorX  + ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / PI));
    AccErrorY  = AccErrorY + ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180  / PI));
    c++;
  }
  
  //Divide the sum by 200 to get the error value
  AccErrorX = AccErrorX / 200;
  AccErrorY = AccErrorY / 200;
  
  c =  0;
  
  // Read gyro values 200 times
  while (c < 200)
  {
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS,  6, true);
    
    GyroX = Wire.read() << 8 | Wire.read();
    GyroY =  Wire.read() << 8 | Wire.read();
    GyroZ = Wire.read() << 8 | Wire.read();
    
    // Sum all readings
    GyroErrorX = GyroErrorX + (GyroX / 131.0);
    GyroErrorY = GyroErrorY + (GyroY / 131.0);
    GyroErrorZ = GyroErrorZ +  (GyroZ / 131.0);
    
    c++;
    
  }
  
  //Divide the sum  by 200 to get the error value
  GyroErrorX = GyroErrorX / 200;
  GyroErrorY  = GyroErrorY / 200;
  GyroErrorZ = GyroErrorZ / 200;
  
  // Print the  error values on the Serial Monitor
  
  Serial.print("AccErrorX: ");
  Serial.print(AccErrorX);
  Serial.print(" | AccErrorY: ");
  Serial.print(AccErrorY);
  Serial.print(" | GyroErrorX: ");
  Serial.print(GyroErrorX);
  Serial.print("  | GyroErrorY: ");
  Serial.print(GyroErrorY);
  Serial.print(" | GyroErrorZ:  ");
  Serial.println(GyroErrorZ);
  

  delay(1000);
}




 /*To Configure Accelerometer Sensitivity - Full Scale  Range (default +/- 2g)
 Wire.beginTransmission(MPU);
  Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
  Wire.write(0x10);                  //Set the register bits as 00010000 (+/- 8g full scale range)
  Wire.endTransmission(true);
  
  // Configure Gyro Sensitivity - Full Scale  Range (default +/- 250deg/s)
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
  Wire.write(0x10);                   // Set the register bits as 00010000 (1000deg/s full scale)
  Wire.endTransmission(true);
  delay(20);*/
