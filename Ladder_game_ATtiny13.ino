/*

 @file Ladder_game_ATtiny13.ino
 
 @brief Ladder game (ATtiny13a)
 @author Kei Takagi
 @date 2016.9.26
 
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
static unsigned short t = 280;

void setup() {
  while (1) {
    if (  analogRead(PB3) < 1)break;
    LED(i);
    delay(8);
    if(flg==false){
      i < 12 ? i++ : flg=true;
    } 
    else { 
      0 < i ? i-- : flg=false;
    }
  }
  DDRB = 0;
  delay(500);
  i=0;
}

void loop() {
  if (analogRead(PB3) > 1) {
    LED(i + flg);
    delay(1);
    t--;
  }
  else{
    if (flg == true) {
      if (i < 10) {
        // up
        delay(200);
        flg=(i%2==0?false:true); 
        t = 0;
        i++;
      } 
      else {
        // clear
        delay(500);
        for (i = 0; i < 400; i++) {
          LED(millis() % 12);
          delay(8);
        }
        ((void (*)())0x00)();// fail:Softwear Reset
      }
    } 
    else {
      // miss
      for (; 0 <= i; i--) {
        DDRB = 0;
        delay(100);
        LED(i);
        delay(300);
      }
      ((void (*)())0x00)();// fail:Softwear Reset
    }
  }
  if( t == 0) {
    flg = !flg;
    t = 280 - 20 * i;
  } 
}

void LED(int in) {
  DDRB = 1 << pin[in][0] |  1 << pin[in][1];
  PORTB = 1 << pin[in][1];
}

