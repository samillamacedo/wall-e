#include <SoftwareSerial.h>
#include <Servo.h> 

Servo myservo1, myservo2, myservo3;

int bluetoothTx = 2;
int bluetoothRx = 4;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  myservo1.attach(13);
  myservo2.attach(12);
  myservo3.attach(11);

  //Setup usb serial connection to computer
  Serial.begin(9600);

  //Setup Bluetooth serial connection to android
  bluetooth.begin(9600);
}

void loop()
{
  //Read from bluetooth and write to usb serial
  if(bluetooth.available()>= 2 )
  {
    unsigned int servopos = bluetooth.read();
    unsigned int servopos1 = bluetooth.read();
    unsigned int realservo = (servopos1 *256) + servopos; 
    Serial.println(realservo); 
    
    if (realservo >= 1000 && realservo <1180){
    int servo1 = realservo;
    servo1 = map(servo1, 1000,1180,0,180);
    myservo1.write(servo1);
    Serial.println("servo 1 ON");
    delay(10);

    }
    if (realservo >= 2000 && realservo <2180){
    int servo2 = realservo;
    servo2 = map(servo2, 2000,2180,0,180);
    myservo2.write(servo2);
    Serial.println("servo 2 ON");
    delay(10);

    }

    if (realservo >= 3000 && realservo <3180){
    int servo3 = realservo;
    servo3 = map(servo3, 3000,3180,0,180);
    myservo3.write(servo3);
    Serial.println("servo 3 ON");
    delay(10);

    } 

  }
}
