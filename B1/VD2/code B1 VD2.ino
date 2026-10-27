#define BUTTON_PIN 4
#define LED_PIN 5

#define PWM_FREQ 5000
#define PWM_RES 8

volatile bool fadingEnabled = false;
volatile bool interruptFlag = false;
volatile unsigned long lastInterruptTime = 0;

int brightness = 0;
int fadeStep = 5;

void IRAM_ATTR buttonISR() {
  unsigned long now = millis();
  if (now - lastInterruptTime > 200) {
    fadingEnabled = !fadingEnabled;
    interruptFlag = true;
    lastInterruptTime = now;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RES);
  ledcWrite(LED_PIN, 0);
}

void loop() {
  if (interruptFlag) {
    interruptFlag = false;
    Serial.println("NGAT!");
    if (fadingEnabled) {
      Serial.println("LED fading: BAT");
    } else {
      Serial.println("LED fading: TAT");
    }
  }

  if (fadingEnabled) {
    ledcWrite(LED_PIN, brightness);
    brightness += fadeStep;
    if (brightness <= 0 || brightness >= 255) {
      fadeStep = -fadeStep;
      brightness = constrain(brightness, 0, 255);
    }
    delay(15);
  } else {
    ledcWrite(LED_PIN, 0);
    brightness = 0;
    fadeStep = abs(fadeStep);
  }
}
