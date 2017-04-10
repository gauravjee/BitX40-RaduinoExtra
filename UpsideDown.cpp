#include "Arduino.h"
#include "UpsideDown.h"

extern long frequency;

#ifdef UPSIDE_DOWN

char number_chars[10] = { '0', (char) 0x01, (char) 0x02, (char) 0x03, (char) 0x04, (char) 0x05, '9', (char) 0x07, '8', '6' };

byte one[8] = {
  B01110,
  B00100,
  B00100,
  B00100,
  B00100,
  B00110,
  B00100,
  B00000
};

byte two[8] = {
  B11111,
  B00010,
  B00100,
  B01000,
  B10000,
  B10001,
  B01110,
  B00000
};

byte three[8] = {
  B01110,
  B10001,
  B10000,
  B01000,
  B00100,
  B01000,
  B11111,
  B00000
};

byte four[8] = {
  B01000,
  B01000,
  B11111,
  B01001,
  B01010,
  B01100,
  B01000,
  B00000
};

byte five[8] = {
  B01110,
  B10001,
  B10000,
  B10000,
  B01111,
  B00001,
  B11111,
  B00000
};

byte seven[8] = {
  B00100,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B11111,
  B00000
};

#endif

byte bar[8] = {
  B00000,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B00000,
  B00000
};

byte half_bar[8] = {
#ifdef UPSIDE_DOWN
  B00000,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00000,
  B00000
#else
  B00000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B00000,
  B00000
#endif
};



void setupUpsideDown(LiquidCrystal * lcd) 
{
  lcd->noDisplay();
  delay(15);
  lcd->createChar(0, bar);
  delay(15);
#ifdef UPSIDE_DOWN
  // We'll reuse zero as is
  lcd->createChar(1, one);
  delay(15);
  lcd->createChar(2, two);
  delay(15);
  lcd->createChar(3, three);
  delay(15);
  lcd->createChar(4, four);
  delay(15);
  lcd->createChar(5, five);
  delay(15);
  lcd->createChar(6, half_bar);
  delay(15);
  // We can use an inverted 9 as a 6
  lcd->createChar(7, seven);
  delay(15);
  // 8 can be used as is
  // We can use an inverted 6 as a 9

#else
  lcd->createChar(6, half_bar);
  delay(15);
#endif
  lcd->display();
}




void printFrequency(char * buffer, unsigned long f)
{
   int i;
   char b[10];
   sprintf(b, "%08ld", frequency); 
   
#ifdef UPSIDE_DOWN
   char br[9];
   for (i=0; i<7; i++)
   {
       br[6-i] = number_chars[b[i]-48];
   }
   br[7] = 0;
   sprintf(buffer, "%.5s%c%.2s", br, (char) 0b10100101,  br+5);
#else
   sprintf(buffer, "%.2s%c%.5s", b, (char) 0b10100101,  b+2);
#endif
}
