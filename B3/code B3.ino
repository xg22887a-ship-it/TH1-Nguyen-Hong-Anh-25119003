#define POT_PIN 34
#define LED_PIN 5

#define PWM_FREQ 5000
#define PWM_RES 12

#define SAMPLES 16

int buffer[SAMPLES];
int index_ = 0;
long sum = 0;
float ema = 0;
const float alpha = 0.2;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RES);

  int first = analogRead(POT_PIN);
  for (int i = 0; i < SAMPLES; i++) {
    buffer[i] = first;
    sum += first;
  }
  ema = first;
}

void loop() {
  int raw = analogRead(POT_PIN);

  sum -= buffer[index_];
  buffer[index_] = raw;
  sum += raw;
  index_ = (index_ + 1) % SAMPLES;
  int avg = sum / SAMPLES;

  ema = alpha * avg + (1 - alpha) * ema;
  int filtered = (int)ema;

  ledcWrite(LED_PIN, filtered);

  int percent = map(filtered, 0, 4095, 0, 100);

  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print(" | Loc nhieu: ");
  Serial.print(filtered);
  Serial.print(" | Do sang: ");
  Serial.print(percent);
  Serial.println("%");

  delay(20);
}
