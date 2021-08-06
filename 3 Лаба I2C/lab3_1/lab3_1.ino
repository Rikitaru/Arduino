#include<Wire.h>
#include <Servo.h>
int servoPin = 3;
Servo Servo1;
void setup() {
  Wire.begin();
  Serial.begin(9600);
  Servo1.attach(servoPin);
}

void loop() {
  Wire.requestFrom(9,1);
  Serial.println("Отдалите дальномер");
  while(Wire.available()) { 
    int x = Wire.read();
    Serial.println(x);
    if (x < 0){
      Serial.println("Отдалите дальномер");
    }
    if (x < 100){
      Serial.println("Расстояние меньше метра. Будет поворот в 0 градусов");
      Servo1.write(0);
      delay(1000);
    }
    if ((x >= 100) && (x <200)){
      Serial.println("Расстояние меньше двух метров. Будет поворот в 90 градусов");
      Servo1.write(90);
    }
    if ((x>=200)&&(x <=300)){
      Serial.println("Расстояние меньше трех метров. Будет поворот в 180 градусов");
      Servo1.write(180);
    }
  }
  delay(1000);
}
