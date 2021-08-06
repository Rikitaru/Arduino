int N = 0; //Счетчик циклов
void setup() {
  pinMode(10, INPUT);
  pinMode(11, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
      delay(100);
  if (digitalRead(10)==1) {
    N = N + 1;
    for (int i = 0; i<N; i++) {
      digitalWrite(2, 1);
      delay(200);
      digitalWrite(2, 0);
      delay(200);
      digitalWrite(3, 1);
      delay(200);
      digitalWrite(3, 0);
      delay(200);
    }
    digitalWrite(11, 1);
    delay(100);
    digitalWrite(11, 0);
  }
}
