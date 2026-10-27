#define BUTTON_PIN 4
#define LED_PIN 5

#define DEBOUNCE_MS 50

volatile unsigned long rawCount = 0;
volatile unsigned long debounceCount = 0;
volatile unsigned long lastInterruptTime = 0;
volatile bool ledState = false;
volatile bool pressed = false;

void IRAM_ATTR buttonISR() {
  rawCount++;
  unsigned long now = millis();
  if (now - lastInterruptTime > DEBOUNCE_MS) {
    debounceCount++;
    ledState = !ledState;
    pressed = true;
  }
  lastInterruptTime = now;
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
  Serial.println("Demo debounce - nhan nut de thu");
}

void loop() {
  digitalWrite(LED_PIN, ledState);

  if (pressed) {
    delay(100);
    pressed = false;
    Serial.print("Khong debounce (so lan ngat): ");
    Serial.println(rawCount);
    Serial.print("Co debounce (so lan nhan that): ");
    Serial.println(debounceCount);
    Serial.print("LED: ");
    Serial.println(ledState ? "BAT" : "TAT");
    Serial.println("----------------");
  }
}
