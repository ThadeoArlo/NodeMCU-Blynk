//Simple Arduino control with PIR sensor

int outPin = 13; //defineing the pins
int inPin = 2;
int pirState = LOW; //pir initial state
int val = 0;

void setup() {
    pinMode(outPin, OUTPUT);
    pinMode(inPin, INPUT);
    Serial.begin(115200);
}

void loop() {
  val = digitalRead(inPin);
  if (val == HIGH) {
    digitalWrite(outPin, HIGH);
    delay(120000); // 60000ms = 1 minute, set how long you want the output to be.

    if (pirState == LOW) {
      Serial.println("Motion Detected!");
      pirState = HIGH;
    }
  } else {
      digitalWrite(outPin, LOW);
      delay(300);
      if (pirState == HIGH){
      Serial.println("No Motion");
      pirState = LOW;
    }
  }
}

