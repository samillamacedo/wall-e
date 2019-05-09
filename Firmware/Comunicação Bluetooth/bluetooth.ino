#include <SoftwareSerial.h>
#include <Servo.h>
#include <SparkFun_TB6612.h>

Servo myservo1, myservo2, myservo3;

int bluetoothTx = 2;
int bluetoothRx = 4;

//motor
#define AIN1 13
#define BIN1 11
#define AIN2 12
#define BIN2 10
#define PWMA 9
#define PWMB 9
#define STBY 8

const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  myservo1.attach(3);
  myservo2.attach(5);
  myservo3.attach(6);

  //Setup usb serial connection to computer
  Serial.begin(115200);

  //Setup Bluetooth serial connection to android
  bluetooth.begin(115200);

}

void loop()
{
  
  //Read from bluetooth and write to usb serial
  if(bluetooth.available() >= 2 )
  {
    unsigned int servopos = bluetooth.read();
    unsigned int servopos1 = bluetooth.read();
    unsigned int realservo = (servopos1 *256) + servopos; 
    Serial.println(realservo); 

    
    if (realservo == 10) {
      //cima
      Serial.println("cima");
      motor2.drive(255,10000);
      forward(motor1, motor2, 150);
    } else if (realservo == 20) {
      //esq
      Serial.println("esq");
      motor1.drive(255,1000);
      
    } else if (realservo == 30) {
      //baixo
      Serial.println("baixo");
      motor1.drive(-255,1000);
      motor2.drive(-255,1000);
    } else if (realservo == 40){
      //direita
      Serial.println("dir");
      motor2.drive(255,1000);
    } else if (realservo == 50) {
      //parar
      Serial.println("parar");
      motor1.brake();
      motor2.brake();
    }
    
    if (realservo >= 1000 && realservo <1180){
    int servo1 = realservo;
    servo1 = map(servo1, 1000,1180,0,180);
    myservo1.write(servo1);
    Serial.println("cabeca");
    delay(10);

    }
    if (realservo >= 2000 && realservo <2180){
    int servo2 = realservo;
    servo2 = map(servo2, 2000,2180,0,180);
    myservo2.write(servo2);
    Serial.println("braco esq");
    delay(10);
    }

    if (realservo >= 3000 && realservo <3180){
    int servo3 = realservo;
    servo3 = map(servo3, 3000,3180,0,180);
    myservo3.write(servo3);
    Serial.println("braco direito");
    delay(10);
    } 
  }
}

