#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// put function declarations here:
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 10, NEO_RGB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pixels.begin();
  pixels.clear();
  
pinMode(11, INPUT);
randomSeed(analogRead(11));

pinMode(9, INPUT_PULLUP);

}

int randomHue;
int choosenHue = 0;
int brightness = 255;
float difficultyMultiplier = 1;
int prevDifficulty = 0;

void loop() {

  if (digitalRead(9) == LOW) {
    pixels.setPixelColor(0, pixels.Color(255, 255, 255));
    pixels.show();
    if (brightness == 10) {
      brightness = 255;
      pixels.setBrightness(brightness);
      pixels.show();
      delay(1000);
    }
    while (digitalRead(9) == LOW) {
      delay(100);
      brightness -= 10;
      if (brightness < 10) {
        brightness = 10;
      }
      pixels.setBrightness(brightness);
      pixels.show();
    }
  }

  randomHue = random(255);
  uint32_t randomColor = pixels.gamma32(pixels.ColorHSV(randomHue*257, 255, 255));
  pixels.setPixelColor(0, randomColor);
  pixels.show();
  delay(int(1000/difficultyMultiplier));

  pixels.setPixelColor(0, 0);
  pixels.show();
  delay(int(random(1000, 5000)*difficultyMultiplier));
  choosenHue = 0;
  while (digitalRead(9) == HIGH) {
    uint32_t rgbcolor = pixels.gamma32(pixels.ColorHSV(choosenHue*257, 255, 255));
    pixels.setPixelColor(0, rgbcolor);
    pixels.show();
    choosenHue += 3;
    choosenHue = choosenHue % 256;
    delay(int(50/difficultyMultiplier));
  }
  pixels.setPixelColor(0, 0);
  pixels.show();
  delay(500);
  // calculate difference between the colors
  int diff = randomHue - choosenHue;
  Serial.printf("Random Hue: %d, Choosen Hue: %d, Diff: %d\n", randomHue, choosenHue, abs(diff));
  if (abs(diff) <= int(30/difficultyMultiplier)) {
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.show();
    Serial.println("You win!");
    difficultyMultiplier += 0.1;
  } else {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
    Serial.println("You lose!");
    difficultyMultiplier = 1;
  }
  delay(1000);
  pixels.setPixelColor(0, 0);
  pixels.show();
  delay(500);

  for (int i = 0; i < int(difficultyMultiplier*10-10); i++) {
    pixels.setPixelColor(0, pixels.Color(255, 255, 255));
    pixels.show();
    delay(300);
    pixels.setPixelColor(0, 0);
    pixels.show();
    delay(300);
  }

  pixels.setPixelColor(0, 0);
  pixels.show();
  delay(2500);
}

// put function definitions here:
