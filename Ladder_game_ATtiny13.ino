/*

  @file Ladder_game_ATtiny13.ino

  @brief Ladder game (ATtiny13a)
  @author Kei Takagi
  @date 2016.9.25

  Copyright (c) 2016 Kei Takagi
  Released under the MIT license
  http://opensource.org/licenses/mit-license.php

*/

const uint8_t pin[12][2]  = {
  {PB0, PB4},
  {PB4, PB0},
  {PB1, PB4},
  {PB4, PB1},
  {PB1, PB0},
  {PB0, PB1},
  {PB2, PB4},
  {PB4, PB2},
  {PB2, PB0},
  {PB0, PB2},
  {PB2, PB1},
  {PB1, PB2}
};

static int i = 0;
static boolean flg = false;
static unsigned long t = 0;

void setup() {
  while (1) {
    if ( analogRead(PB3) < 50)break;
    if (flg == true) {
      i < 11 ? i++ : flg = false;
    } else {
      0 < i ? i-- : flg = true;
    }
    LED(i);
    delay(8);
  }
  for (; 0 <= i; i--) {
    LED(i);
    delay(100);
  }
  delay(300);
  i=0;
}

void loop() {
  LED(i + flg);
  if ( t < millis() ) {
    t = millis() + 300 - i * 15;
    flg = !flg;
  } else {
    if (analogRead(PB3) < 50) {
      if (flg == true) {
        if (i < 10) {
          // up
          delay(200);
          i++;
          flg = false;
          t = millis() + 300;
        } else {
          // clear
          delay(500);
          for (i = 0; i < 200; i++) {
            LED(millis() % 12);
            delay(15);
          }
          delay(500);
          ((void (*)())0x00)();// fail:Softwear Reset
        }
      } else {
        // miss
        delay(500);
        for (; 0 <= i; i--) {
          LED(i);
          delay(100);
        }
        delay(1000);
        ((void (*)())0x00)();// fail:Softwear Reset
      }
    }
  }
}

void LED(int in) {
  DDRB = 1 << pin[in][0] |  1 << pin[in][1];
  PORTB = 1 << pin[in][1];
}
