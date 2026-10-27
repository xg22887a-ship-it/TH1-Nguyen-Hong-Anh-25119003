#define BUTTON_PIN 4
#define LED_PIN 5

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  ledcAttach(LED_PIN, 5000, 8);
}

void loop() {
  for (int h = 0; h <= 255; h++) {
    ledcWrite(LED_PIN, h);
    if (digitalRead(BUTTON_PIN) == LOW) {
      Serial.println("button pressed");
    }
    delay(10);
  }

  for (int h = 255; h >= 0; h--) {
    ledcWrite(LED_PIN, h);
    if (digitalRead(BUTTON_PIN) == LOW) {
      Serial.println("button pressed");
    }
    delay(10);
  }
}
