#include <Adafruit_NeoPixel.h>

#define PIN            4
#define NUMPIXELS      2

int r1 = 0;
int g1 = 0;
int b1 = 0;
int r2 = 0;
int g2 = 0;
int b2 = 0;
int tr1 = 0;
int tg1 = 0;
int tb1 = 0;
int tr2 = 0;
int tg2 = 0;
int tb2 = 0;

unsigned long displayChangeTime = 0;
int schemes = 18;
int colorScheme[] = 
  {
    0, 205, 153,    255, 102, 0,    
    255, 153, 0,    255, 204, 51,    
    153, 102, 153,  102, 102, 153,
    255, 255, 153,  204, 204, 153,
    255, 153, 154,  153, 204, 153,
    204, 102, 51,   102, 153, 102,
    0, 51, 102,     102, 153, 255,
    255, 204, 255,  204, 204, 255,
    255, 255, 204,  255, 255, 255,
    153, 102, 0,    204, 153, 51,
    153, 0, 102,    0, 102, 102,
    102, 255, 255,  204, 255, 255, 
    102, 0, 0,      102, 51, 0,
    115, 16, 0,     91, 0, 55,
    251, 164, 189,  78, 1, 23,
    231, 253, 166,  245, 161, 222,
    35, 49, 158,    6, 16, 85,
    230, 172, 23,   35, 49, 158
  };

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  
  pixels.begin();
  pixels.setBrightness(250);
  changeStyle();
}

void loop() {

  if ((millis() - displayChangeTime) >= (60000 * 1)) {

    // change colors    
    changeStyle();
    displayChangeTime = millis();
  }

  // fade colors towards targets
  r1 = moveTowards(r1, tr1, 1);
  g1 = moveTowards(g1, tg1, 1);
  b1 = moveTowards(b1, tb1, 1);
  r2 = moveTowards(r2, tr2, 1);
  g2 = moveTowards(g2, tg2, 1);
  b2 = moveTowards(b2, tb2, 1);  

  // display them  
  pixels.setPixelColor(0, pixels.Color(r1, g1, b1));
  pixels.setPixelColor(1, pixels.Color(r2, g2, b2));
  pixels.show();
  delay(66);
}

void changeStyle() {
  
    int scheme = random(schemes);
    int style = random(4);

    if (style == 0) {

      tr2 = colorScheme[(scheme * 6) + 0 + 0]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tg2 = colorScheme[(scheme * 6) + 0 + 1]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tb2 = colorScheme[(scheme * 6) + 0 + 2]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tr1 = colorScheme[(scheme * 6) + 3 + 0]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tg1 = colorScheme[(scheme * 6) + 3 + 1]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tb1 = colorScheme[(scheme * 6) + 3 + 2]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      
    } else if (style == 1) {

      tr1 = colorScheme[(scheme * 6) + 0 + 0]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tg1 = colorScheme[(scheme * 6) + 0 + 1]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tb1 = colorScheme[(scheme * 6) + 0 + 2]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tr2 = colorScheme[(scheme * 6) + 3 + 0]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tg2 = colorScheme[(scheme * 6) + 3 + 1]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tb2 = colorScheme[(scheme * 6) + 3 + 2]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      
    } else if (style == 2) {

      tr1 = tr2 = colorScheme[(scheme * 6) + 0 + 0]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tg1 = tg2 = colorScheme[(scheme * 6) + 0 + 1]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tb1 = tb2 = colorScheme[(scheme * 6) + 0 + 2]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      
    } else if (style == 3) {

      tr2 = tr1 = colorScheme[(scheme * 6) + 3 + 0]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tg2 = tg1 = colorScheme[(scheme * 6) + 3 + 1]; // scheme + row (0 / 3) + color (0 / 1 / 2)
      tb2 = tb1 = colorScheme[(scheme * 6) + 3 + 2]; // scheme + row (0 / 3) + color (0 / 1 / 2)
    }
}

int moveTowards(int current, int target, int changeSpeed) {

  if (current < target) {
    
    return current += changeSpeed;
  
  } else if (current > target) {
  
    return current -= changeSpeed;
  }

  return target;
}

int fixVal(int val) {

  while (val >= 255) {
    
    val -= 255;
  }

  while (val < 0) {
    
    val += 255;
  }
  
  return val;
}
