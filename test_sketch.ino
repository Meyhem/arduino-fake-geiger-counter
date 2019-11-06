#define HALT() while(1) {}
#define DEBUG(x) Serial.println((x))
#define BUZZ_PIN 8

/*
  Generate random float between <0, 1)
*/
float random_normal() {
  return random(0, 100000) / (float)100000;
}

/*
  Discrete Poisson rng
*/
float random_poisson(float rate) {
  return -log(1 - random_normal()) / (float)rate;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Events (tocks) per second
  float eps = analogRead(A0) / (float)10 + 1;

  // Generate new poisson state. It's amount of second we should wait for next tock
  float p = random_poisson(eps);

  // Generate tock sound
  // 30 -+100 Hertz for 5 +- 10 miliseconds to give sense of randomness
  // Sounds like Geiger tock
  tone(BUZZ_PIN, random_normal() * 100 + 30, 10*random_normal() + 5);

  // Wait for next tock
  delay(p * 1000);
}
