#include <Wire.h>
int echoPin = 2;
int trigPin = 3;
int x;
void setup() {
    Wire.begin(9);
    Wire.onRequest(receiveEvent);
    Serial.begin (9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.println("ARD2: I'm ready.");
}

int receiveEvent () {
    int duration, cm;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    cm = duration / 58;
    Serial.print("Получен запрос на данные ");
    Serial.print(cm);
    Serial.println("cm.");
    Wire.write(cm);
    return cm;
}
void loop() {
//receiveEvent();
}
