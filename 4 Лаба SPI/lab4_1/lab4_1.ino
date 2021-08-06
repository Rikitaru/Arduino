#include <Wire.h>
#include <SD.h>
int CS_pin = 10;
int pow_pin = 8;  // Если вы используете SD Shield
String name_file = "LOG.txt";
char name_file2[10] = "LOG.txt";
int flag=0;
int size_file = 16; //одна запись равна 5 байтам
void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initializing Card");
  //Назначаем пин CS_pin выходом
  //Если мы используем шилд то назначаем выходом пин для питания шилда
  pinMode(pow_pin, OUTPUT);  
  digitalWrite(pow_pin, HIGH);
}
void loop() {
  if (!SD.begin(CS_pin)) {
    if (flag!=0){
      Serial.println("Card Failure");
    }
    flag=0;
    return;
  }
  else {
    if (flag==0){
      Serial.println("Card Ready");
      flag=1;
      return;
    }
 }
 if (flag == 1){
    Serial.println("Ожидается ввод имени файла");
    flag = 2;
 }
 if ((flag == 2) && (Serial.available() > 0)){    
      name_file = Serial.readString();
      name_file.toCharArray(name_file2, name_file.length());
      Serial.println("Было принято название:");
      Serial.println(name_file2);
      Serial.println("Ожидается ввод допустимого размера файла");
      flag = 3;
 }
 if ((flag == 3) && (Serial.available() > 0)){     
    size_file= Serial.parseInt();
    Serial.println("Был принят размер файла:");
    Serial.println(size_file);
    flag = 4;
 }
 if (flag == 4){
    Wire.requestFrom(9,1);
    while (Wire.available()) {
      int x = Wire.read();
      Serial.print(x);
      Serial.print(" - Полученные данные.");
      Serial.println();
      File logFile = SD.open(name_file2, FILE_WRITE);
      name_file = Serial.readString();
      if (logFile) {
        if ((logFile.size()+4) <= size_file){
            Serial.print("Данные будут записаны в файл ");
            Serial.println(name_file2);
            logFile.println(x);
            logFile.close();
            Serial.print(x);
            Serial.print(" - Эти данные были записаны.");
            Serial.println();
            delay(2000);
        }
        else{
            Serial.println("Файл переполнен данными. Запись данных прервана");
            flag = 1;
        }
      }
      else {
          Serial.println(name_file2);
          Serial.println("Couldn't open log file");
          flag = 1;
      }
    }
 }
}
