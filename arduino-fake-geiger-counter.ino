#define BUZZ_PIN 8

// Uniform RNG <0, 1)
float random_normal() {
  return random(0, 100000) / (float)100000;
}

// Exponential RNG
float random_exponential(float rate) {
  return -log(1 - random_normal()) / (float)rate;
}

void setup() { }

void loop() {
  // Events (tocks) per second.
  float eps = 10;

  // Generate random time until next tock should hit.
  // It's time between events in poisson process
  float p = random_exponential(eps);

  // Generate tock sound
  // 30 -+100 Hertz for 5 +- 10 miliseconds to give sense of randomness
  // Sounds like Geiger tock
  tone(BUZZ_PIN, random_normal() * 100 + 30, 10 * random_normal() + 5);

  // Wait for next tock
  delay(p * 1000);

  // In case of high eps (hundreds eps) we need to interrupt tone playing as they would mutually interfere.
  // It increases tocking quality for high eps
  noTone(BUZZ_PIN);
}
