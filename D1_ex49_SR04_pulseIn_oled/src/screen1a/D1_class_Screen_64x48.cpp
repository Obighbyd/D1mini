//_____D1_class_Screen_64x48.cpp______________171229-180515_____
// The class Screen_64x48 contains basic OLED functions only for
// WeMos D1 mini OLED shield 0,66" 64*48 pixel.
// Special: char(158) = Euro instead of Pt (Pesetas) (158=9E)
// The code is strongly based on Adafruit libs
//   * _Adafruit_SSD1306-esp8266-64x48.zip and
//   * Adafruit-GFX-Library-1.1.5.zip
// Use this class, if you have problems with the Adafruit
// classes especially after an update of the libraries.
//
#include "D1_class_Screen_64x48.h"     // basic oled functions

//**************************************************************
//    class _Adafruit_SSD1306 (renamed to _Adafruit_SSD1306)
//**************************************************************
#define ssd1306_swap(a, b) { int16_t t = a; a = b; b = t; }

static uint8_t buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0,
0xE0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFF, 0xFC, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0xC0, 0xFC, 0xFF, 0xFF,
0xFF, 0xFF, 0x7F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xC7, 0xC7, 0x87, 0x8F, 0x9F, 0x9F, 0xFF, 0xFF,
0xFF, 0xC1, 0xC0, 0xE0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC, 0xFC, 0xFE, 0xFE,
0xFE, 0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xE0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0,
0xE0, 0xF1, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x0F, 0x0F, 0x87, 0xE7, 0xFF, 0xFF,
0xFF, 0x1F, 0x1F, 0x3F, 0xF9, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFE, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x7E, 0x3F, 0x3F, 0x0F, 0x1F, 0xFF, 0xFF,
0xFF, 0xFC, 0xF0, 0xE0, 0xF1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF0, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03,
0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
0x0F, 0x1F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x1F, 0x03, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//_____the most important basic function, set a single pixel____
void _Adafruit_SSD1306::drawPixel(int16_t x, int16_t y, uint16_t color){
 if ((x < 0) || (x >= width()) || (y < 0) || (y >= height()))
  return;
 //-----check rotation, move pixel around if necessary----------
 switch (getRotation()) {
 case 1: //.....90 deg..........................................
  ssd1306_swap(x, y);
  x = WIDTH - x - 1;
  break;
 case 2: //.....180 deg.........................................
  x = WIDTH - x - 1;
  y = HEIGHT - y - 1;
  break;
 case 3: //.....270 deg.........................................
  ssd1306_swap(x, y);
  y = HEIGHT - y - 1;
  break;
 default: //.....no rotation....................................
  break;
 }
 //-----set pixel-----------------------------------------------
 switch (color)
 {
  case WHITE:   buffer[x+(y/8)*SSD1306_LCDWIDTH] |=  (1<<(y&7));
   break;
  case BLACK:   buffer[x+(y/8)*SSD1306_LCDWIDTH] &= ~(1<<(y&7)); 
   break;
  case INVERSE: buffer[x+(y/8)*SSD1306_LCDWIDTH] ^=  (1<<(y&7)); 
   break;
  default: break;
 }
}

//==============================================================
//     constructor & co
//==============================================================
//_____constructor______________________________________________
_Adafruit_SSD1306::_Adafruit_SSD1306(int8_t SID, int8_t SCLK, 
  int8_t DC, int8_t RST, int8_t CS) :
  _Adafruit_GFX(SSD1306_LCDWIDTH, SSD1306_LCDHEIGHT) 
{
 cs = CS;
 rst = RST;
 dc = DC;
 sclk = SCLK;
 sid = SID;
}

//_____constructor for hardware SPI_____________________________
// we indicate DataCommand, ChipSelect, Reset
_Adafruit_SSD1306::_Adafruit_SSD1306(int8_t DC, int8_t RST,
  int8_t CS) : _Adafruit_GFX(SSD1306_LCDWIDTH, SSD1306_LCDHEIGHT) 
{
 dc = DC;
 rst = RST;
 cs = CS;
}

//_____constructor for I2C - we only indicate the reset pin!____
_Adafruit_SSD1306::_Adafruit_SSD1306(int8_t resetpin) :
  _Adafruit_GFX(SSD1306_LCDWIDTH, SSD1306_LCDHEIGHT) 
{
 sclk = dc = cs = sid = -1;
 rst = resetpin;
}

//_____init i2c_________________________________________________
void _Adafruit_SSD1306::begin(uint8_t vccstate, uint8_t i2caddr,
  bool reset) 
{
 _vccstate = vccstate;
 _i2caddr = i2caddr;
 //-----set pin directions--------------------------------------
 if (sid != -1){
  pinMode(dc, OUTPUT);
  pinMode(cs, OUTPUT);
 }
 else
 {
  //.....I2C init...............................................
  Wire.begin();
 }
 
 if ((reset) && (rst >= 0)) {
  //.....Setup reset pin direction (used by both SPI and I2C)...
  pinMode(rst, OUTPUT);                // reset pin = putput
  digitalWrite(rst, HIGH);             // VDD (3.3V) goes high
  delay(1);                            // at start, wait
  digitalWrite(rst, LOW);              // bring reset low
  delay(10);                           // wait 10ms
  digitalWrite(rst, HIGH);             // bring out of reset
 }
 //-----init sequence-------------------------------------------
 ssd1306_command(SSD1306_DISPLAYOFF);            // 0xAE
 ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);    // 0xD5
 ssd1306_command(0x80);                          // suggested ratio
 ssd1306_command(SSD1306_SETMULTIPLEX);          // 0xA8
 ssd1306_command(SSD1306_LCDHEIGHT - 1);
 ssd1306_command(SSD1306_SETDISPLAYOFFSET);      // 0xD3
 ssd1306_command(0x0);                           // no offset
 ssd1306_command(SSD1306_SETSTARTLINE | 0x0);    // line #0
 ssd1306_command(SSD1306_CHARGEPUMP);            // 0x8D
 if (vccstate == SSD1306_EXTERNALVCC)
 { ssd1306_command(0x10); }
 else
 { ssd1306_command(0x14); }
 ssd1306_command(SSD1306_MEMORYMODE);  // horizontal addr. mode
 ssd1306_command(0x00);                // act like ks0108
 ssd1306_command(SSD1306_SEGREMAP | 0x1);
 ssd1306_command(SSD1306_COMSCANDEC);
 ssd1306_command(SSD1306_SETCOMPINS);            // 0xDA
 ssd1306_command(0x12);
 ssd1306_command(SSD1306_SETCONTRAST);           // 0x81
 if (vccstate == SSD1306_EXTERNALVCC)
 { ssd1306_command(0x9F); }
 else
 { ssd1306_command(0xCF); }
 ssd1306_command(SSD1306_SETPRECHARGE);          // 0xd9
 if (vccstate == SSD1306_EXTERNALVCC)
 { ssd1306_command(0x22); }
 else
 { ssd1306_command(0xF1); }
 ssd1306_command(SSD1306_SETVCOMDETECT);         // 0xDB
 ssd1306_command(0x40);
 ssd1306_command(SSD1306_DISPLAYALLON_RESUME);   // 0xA4
 ssd1306_command(SSD1306_NORMALDISPLAY);         // 0xA6
 ssd1306_command(SSD1306_DEACTIVATE_SCROLL);
 ssd1306_command(SSD1306_DISPLAYON);//--turn on oled panel
}

//_____invert display___________________________________________
void _Adafruit_SSD1306::invertDisplay(uint8_t i) 
{
 if (i) ssd1306_command(SSD1306_INVERTDISPLAY);
 else   ssd1306_command(SSD1306_NORMALDISPLAY);
}

//_____send a i2c command_______________________________________
void _Adafruit_SSD1306::ssd1306_command(uint8_t c) 
{
 uint8_t control = 0x00;                         // Co=0, D/C=0
 Wire.beginTransmission(_i2caddr);
 Wire.write(control);
 Wire.write(c);
 Wire.endTransmission();
}

//_____startscrollright_________________________________________
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)
void _Adafruit_SSD1306::startscrollright(uint8_t start, uint8_t stop){
 ssd1306_command(SSD1306_RIGHT_HORIZONTAL_SCROLL);
 ssd1306_command(0x00);
 ssd1306_command(start);
 ssd1306_command(0x00);
 ssd1306_command(stop);
 ssd1306_command(0x00);
 ssd1306_command(0xFF);
 ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

//_____startscrollleft__________________________________________
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole 
// display, run: display.scrollright(0x00, 0x0F)
void _Adafruit_SSD1306::startscrollleft(uint8_t start, uint8_t stop){
 ssd1306_command(SSD1306_LEFT_HORIZONTAL_SCROLL);
 ssd1306_command(0x00);
 ssd1306_command(start);
 ssd1306_command(0x00);
 ssd1306_command(stop);
 ssd1306_command(0x00);
 ssd1306_command(0xFF);
 ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

//_____startscrolldiagright_____________________________________
// Activate a diagonal scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole 
// display, run: display.scrollright(0x00, 0x0F)
void _Adafruit_SSD1306::startscrolldiagright(uint8_t start,
 uint8_t stop)
{
 ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
 ssd1306_command(0x00);
 ssd1306_command(SSD1306_LCDHEIGHT);
 ssd1306_command(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
 ssd1306_command(0x00);
 ssd1306_command(start);
 ssd1306_command(0x00);
 ssd1306_command(stop);
 ssd1306_command(0x01);
 ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

//_____startscrolldiagleft______________________________________
// Activate a diagonal scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole 
// display, run: display.scrollright(0x00, 0x0F)
void _Adafruit_SSD1306::startscrolldiagleft(uint8_t start,
 uint8_t stop)
{
 ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
 ssd1306_command(0x00);
 ssd1306_command(SSD1306_LCDHEIGHT);
 ssd1306_command(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
 ssd1306_command(0x00);
 ssd1306_command(start);
 ssd1306_command(0x00);
 ssd1306_command(stop);
 ssd1306_command(0x01);
 ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

//_____stop scrolling___________________________________________
void _Adafruit_SSD1306::stopscroll(void){
  ssd1306_command(SSD1306_DEACTIVATE_SCROLL);
}

//_____Dim the display__________________________________________
// dim = true: display is dimmed
// dim = false: display is normal
void _Adafruit_SSD1306::dim(boolean dim) 
{
 uint8_t contrast;
 if (dim) { contrast = 0; }            // Dimmed display
 else 
 {
  if (_vccstate == SSD1306_EXTERNALVCC) { contrast = 0x9F;}
  else { contrast = 0xCF; }
 }
 ssd1306_command(SSD1306_SETCONTRAST);
 ssd1306_command(contrast);
}

//_____show content of display buffer___________________________
void _Adafruit_SSD1306::display(void) {
 ssd1306_command(SSD1306_COLUMNADDR);
 ssd1306_command(32);
 ssd1306_command(32 + SSD1306_LCDWIDTH - 1);
 ssd1306_command(SSD1306_PAGEADDR);
 ssd1306_command(0); // Page start address (0 = reset)
 ssd1306_command((SSD1306_LCDHEIGHT/8) - 1);  //Page end address
 //-----send buffer to oled-------------------------------------
 for(uint16_t i=0; i<(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8);i++)
 { //.....send a block of data in one transmission..............
  Wire.beginTransmission(_i2caddr);
  Wire.write(0x40);
  for (uint8_t x=0; x<16; x++) 
  {
   Wire.write(buffer[i]);
   i++;
  }
  i--;
  Wire.endTransmission();
 }
}

//_____clear display buffer_____________________________________
void _Adafruit_SSD1306::clearDisplay(void) {
 memset(buffer, 0, (SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8));
}

//_____draw a fast horizontal line (depending on rotation ;)____
void _Adafruit_SSD1306::drawFastHLine(int16_t x, int16_t y, 
 int16_t w, uint16_t color) 
{
 boolean bSwap = false;
 //-----calc start position depending on rotation---------------
 switch(rotation) {
  case 0: //.....0 degree rotation, do nothing..................
   break;
  case 1: //.....90????????????, swap x & y for rotation, then invert x....
   bSwap = true;
   ssd1306_swap(x, y);
   x = WIDTH - x - 1;
   break;
  case 2: // 180????????????, invert x and y, shift y around for height....
   x = WIDTH - x - 1;
   y = HEIGHT - y - 1;
   x -= (w-1);
   break;
  case 3: // 270????????????, swap x & y for rotation, then invert y  
          // and adjust y for w (not to become h)
   bSwap = true;
   ssd1306_swap(x, y);
   y = HEIGHT - y - 1;
   y -= (w-1);
   break;
  default: break; //.....just for safety........................
 }
 //-----draw line-----------------------------------------------
 if(bSwap) { drawFastVLineInternal(x, y, w, color); }
      else { drawFastHLineInternal(x, y, w, color); }
}

//_____draw horizontal line in buffer (for internal use)________
void _Adafruit_SSD1306::drawFastHLineInternal
 (int16_t x, int16_t y, int16_t w, uint16_t color) 
{
 //-----Do bounds/limit checks----------------------------------
 if(y < 0 || y >= HEIGHT) { return; }
 //-----make sure we don't try to draw below 0------------------
 if(x < 0) { w += x; x = 0; }
 //-----make sure we don't go off the edge of the display-------
 if( (x + w) > WIDTH) { w = (WIDTH - x); }
 //-----if our width is now negative, punt----------------------
 if(w <= 0) { return; }
 //-----set up the pointer for  movement through the buffer-----
 register uint8_t *pBuf = buffer;
 //-----adjust the buffer pointer for the current row-----------
 pBuf += ((y/8) * SSD1306_LCDWIDTH);
 pBuf += x;                       // and offset x columns in
 register uint8_t mask = 1 << (y&7);
 //-----now draw the line in buffer-----------------------------
 switch (color)
 {
  case WHITE:   while(w--) { *pBuf++ |= mask; }; break;
  case BLACK:   mask = ~mask;   while(w--) { *pBuf++ &= mask; }; 
                break;
  case INVERSE: while(w--) { *pBuf++ ^= mask; }; break;
  default: break; //.....just for safety........................
 }
}

//_____draw a fast vertical line (depending on rotation ;)______
void _Adafruit_SSD1306::drawFastVLine
 (int16_t x, int16_t y, int16_t h, uint16_t color) 
{
 bool bSwap = false;
 //-----calc start position depending on rotation---------------
 switch(rotation) {
  case 0: //.....0 degree rotation, do nothing..................
   break;
  case 1: // 90????????????, swap x & y for rotation, then invert x and 
          // adjust x for h (now to become w)
   bSwap = true;
   ssd1306_swap(x, y);
   x = WIDTH - x - 1;
   x -= (h-1);
   break;
  case 2: // 180????????????, invert x and y then shift y around for height
   x = WIDTH - x - 1;
   y = HEIGHT - y - 1;
   y -= (h-1);
   break;
  case 3:// 270????????????, swap x & y for rotation, then invert y........
   bSwap = true;
   ssd1306_swap(x, y);
   y = HEIGHT - y - 1;
   break;
  default: break; //.....just for safety........................  
 }
 //-----draw line-----------------------------------------------
 if(bSwap) { drawFastHLineInternal(x, y, h, color); }
      else { drawFastVLineInternal(x, y, h, color); }
}

//_____draw vertical line in buffer (for internal use)__________
void _Adafruit_SSD1306::drawFastVLineInternal
 (int16_t x, int16_t __y, int16_t __h, uint16_t color) 
{
 //.do nothing if we're off the left or right side of the screen
 if(x < 0 || x >= WIDTH) { return; }
 //-----make sure we don't try to draw below 0------------------
 if(__y < 0)       // __y is negative, this will subtract 
 {	           // enough from __h to account for __y being 0
  __h += __y;
  __y = 0;
 }
 //-----make sure we don't go past the height of the display----
 if( (__y + __h) > HEIGHT) { __h = (HEIGHT - __y); }
 //-----if our height is now negative, punt---------------------
 if(__h <= 0) { return; }
 //-----this display doesn't need ints for coordinates,---------
 // use local byte registers for faster juggling
 register uint8_t y = __y;
 register uint8_t h = __h;
 //-----set up the pointer for fast movement through the buffer-
 register uint8_t *pBuf = buffer;
 //-----adjust the buffer pointer for the current row-----------
 pBuf += ((y/8) * SSD1306_LCDWIDTH);
 pBuf += x;                       // and offset x columns in
 // do first partial byte, if necessary - requires some masking
 register uint8_t mod = (y&7);
 if(mod) 
 {
  //.....mask off the high n bits we want to set................
  mod = 8-mod;
  // note - lookup table results in a nearly 10% performance
  // improvement in fill* functions
  // register uint8_t mask = ~(0xFF >> (mod));
  static uint8_t premask[8] = 
   {0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE };
  register uint8_t mask = premask[mod];
  // adjust the mask if we're not going to reach the end 
  // of this byte
  if( h < mod) { mask &= (0xFF >> (mod-h)); }

  switch (color)
  {
   case WHITE:   *pBuf |=  mask;  break;
   case BLACK:   *pBuf &= ~mask;  break;
   case INVERSE: *pBuf ^=  mask;  break;
   default: break; //.....just for safety.......................
  }
  //-----fast exit if we're done here!--------------------------
  if(h<mod) { return; }
  h -= mod;
  pBuf += SSD1306_LCDWIDTH;
 }
 //-----write solid bytes while we can--------------------------
 // effectively doing 8 rows at a time
 if(h >= 8) {
  if (color == INVERSE)  
  {// separate copy of the code so we don't impact performance
   // of black/white write version with an extra comparison per loop
   do  
   {
    *pBuf=~(*pBuf);
    // adjust the buffer forward 8 rows worth of data
    pBuf += SSD1306_LCDWIDTH;
    // adjust h & y (there's got to be a faster way for me to do
    // this, but this should still help a fair bit for now)
    h -= 8;
   } while(h >= 8);
  }
  else {
   // store a local value to work with
   register uint8_t val = (color == WHITE) ? 255 : 0;
   do  {
    // write our value in
    *pBuf = val;
    // adjust the buffer forward 8 rows worth of data
    pBuf += SSD1306_LCDWIDTH;
    // adjust h & y (there's got to be a faster way for me to do
    // this, but this should still help a fair bit for now)
    h -= 8;
   } while(h >= 8);
  }
 }
 //-----now do the final partial byte, if necessary-------------
 if(h) {
  mod = h & 7;
  // this time we want to mask the low bits of the byte, vs the 
  // high bits we did above 
  // register uint8_t mask = (1 << mod) - 1;
  // note - lookup table results in a nearly 10% performance
  // improvement in fill* functions
  static uint8_t postmask[8] = 
   { 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F };
  register uint8_t mask = postmask[mod];
  switch (color)
  {
   case WHITE:   *pBuf |=  mask;  break;
   case BLACK:   *pBuf &= ~mask;  break;
   case INVERSE: *pBuf ^=  mask;  break;
   default: break; //.....just for safety.......................
  }
 }
}

//**************************************************************
//    class Adafruit_GFX (renamed to _Adafruit_GFX)
//**************************************************************

#ifndef pgm_read_byte
 #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
 #define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
 #define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#endif

// Pointers are a peculiar case...typically 16-bit on AVR boards,
// 32 bits elsewhere.  Try to accommodate both...
#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
 #define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
 #define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

//_____constructor______________________________________________
_Adafruit_GFX::_Adafruit_GFX(int16_t w, int16_t h):
WIDTH(w), HEIGHT(h)
{
 _width    = WIDTH;
 _height   = HEIGHT;
 rotation  = 0;
 cursor_y  = cursor_x    = 0;
 textsize  = 1;
 textcolor = textbgcolor = 0xFFFF;
 wrap      = true;
 _cp437    = false;
 gfxFont   = NULL;
}

//_____Bresenham's algorithm - thx wikpedia_____________________
void _Adafruit_GFX::writeLine(int16_t x0, int16_t y0, 
 int16_t x1, int16_t y1, uint16_t color) 
{
 int16_t steep = abs(y1 - y0) > abs(x1 - x0);
 if (steep) {
  _swap_int16_t(x0, y0);
  _swap_int16_t(x1, y1);
 }
 if (x0 > x1) {
  _swap_int16_t(x0, x1);
  _swap_int16_t(y0, y1);
 }
 int16_t dx, dy;
 dx = x1 - x0;
 dy = abs(y1 - y0);
 int16_t err = dx / 2;
 int16_t ystep;
 if (y0 < y1) { ystep =  1; }
         else { ystep = -1; }
 for (; x0<=x1; x0++) {
  if (steep) { writePixel(y0, x0, color); }
        else { writePixel(x0, y0, color); }
  err -= dy;
  if (err < 0) {
   y0 += ystep;
   err += dx;
  }
 }
}

//_____Overwrite in subclasses if desired!______________________
void _Adafruit_GFX::startWrite(){ }

//_____Overwrite in subclasses if startWrite is defined!________
void _Adafruit_GFX::writePixel(int16_t x, int16_t y, 
 uint16_t color)
{ drawPixel(x, y, color); }

// (x,y) is topmost point; if unsure, calling function
// should sort endpoints or call writeLine() instead
void _Adafruit_GFX::writeFastVLine(int16_t x, int16_t y,
 int16_t h, uint16_t color) 
{
 // Overwrite in subclasses if startWrite is defined!
 // Can be just writeLine(x, y, x, y+h-1, color);
 // or writeFillRect(x, y, 1, h, color);
 drawFastVLine(x, y, h, color);
}

// (x,y) is leftmost point; if unsure, calling function
// should sort endpoints or call writeLine() instead
void _Adafruit_GFX::writeFastHLine(int16_t x, int16_t y,
 int16_t w, uint16_t color) 
{
 // Overwrite in subclasses if startWrite is defined!
 // Example: writeLine(x, y, x+w-1, y, color);
 // or writeFillRect(x, y, w, 1, color);
 drawFastHLine(x, y, w, color);
}

//_____Overwrite in subclasses if desired!______________________
void _Adafruit_GFX::writeFillRect(int16_t x, int16_t y,
 int16_t w, int16_t h, uint16_t color) 
{ 
 fillRect(x,y,w,h,color);
}

//_____Overwrite in subclasses if startWrite is defined!________
void _Adafruit_GFX::endWrite() { }

// (x,y) is topmost point; if unsure, calling function
// should sort endpoints or call drawLine() instead
void _Adafruit_GFX::drawFastVLine(int16_t x, int16_t y,
 int16_t h, uint16_t color) 
{ // Update in subclasses if desired!
 startWrite();
 writeLine(x, y, x, y+h-1, color);
 endWrite();
}

//_____draw fast horizontal line________________________________
// (x,y) is leftmost point; if unsure, calling function
// should sort endpoints or call drawLine() instead
void _Adafruit_GFX::drawFastHLine(int16_t x, int16_t y,
 int16_t w, uint16_t color) 
{ // Update in subclasses if desired!
 startWrite();
 writeLine(x, y, x+w-1, y, color);
 endWrite();
}

void _Adafruit_GFX::fillRect(int16_t x, int16_t y, 
 int16_t w, int16_t h, uint16_t color) 
{ // Update in subclasses if desired!
 startWrite();
 for (int16_t i=x; i<x+w; i++) {writeFastVLine(i, y, h, color);}
 endWrite();
}

void _Adafruit_GFX::fillScreen(uint16_t color) 
{
 // Update in subclasses if desired!
 fillRect(0, 0, _width, _height, color);
}

void _Adafruit_GFX::drawLine(int16_t x0, int16_t y0, 
 int16_t x1, int16_t y1, uint16_t color) 
{ // Update in subclasses if desired!
 if(x0 == x1){
  if(y0 > y1) _swap_int16_t(y0, y1);
  drawFastVLine(x0, y0, y1 - y0 + 1, color);
 } else 
 if(y0 == y1)
 {
  if(x0 > x1) _swap_int16_t(x0, x1);
  drawFastHLine(x0, y0, x1 - x0 + 1, color);
 } else {
  startWrite();
  writeLine(x0, y0, x1, y1, color);
  endWrite();
 }
}

//_____Draw a circle outline____________________________________
void _Adafruit_GFX::drawCircle(int16_t x0, int16_t y0,int16_t r,
 uint16_t color) 
{
 int16_t f = 1 - r;
 int16_t ddF_x = 1;
 int16_t ddF_y = -2 * r;
 int16_t x = 0;
 int16_t y = r;
 startWrite();
 writePixel(x0  , y0+r, color);
 writePixel(x0  , y0-r, color);
 writePixel(x0+r, y0  , color);
 writePixel(x0-r, y0  , color);
 while (x<y) {
  if (f >= 0) {
   y--;
   ddF_y += 2;
   f += ddF_y;
  }
  x++;
  ddF_x += 2;
  f += ddF_x;
  writePixel(x0 + x, y0 + y, color);
  writePixel(x0 - x, y0 + y, color);
  writePixel(x0 + x, y0 - y, color);
  writePixel(x0 - x, y0 - y, color);
  writePixel(x0 + y, y0 + x, color);
  writePixel(x0 - y, y0 + x, color);
  writePixel(x0 + y, y0 - x, color);
  writePixel(x0 - y, y0 - x, color);
 }
 endWrite();
}

void _Adafruit_GFX::drawCircleHelper( int16_t x0, int16_t y0,
 int16_t r, uint8_t cornername, uint16_t color) 
{
 int16_t f     = 1 - r;
 int16_t ddF_x = 1;
 int16_t ddF_y = -2 * r;
 int16_t x     = 0;
 int16_t y     = r;
 while (x<y) {
  if (f >= 0) {
   y--;
   ddF_y += 2;
   f     += ddF_y;
  }
  x++;
  ddF_x += 2;
  f     += ddF_x;
  if (cornername & 0x4) {
      writePixel(x0 + x, y0 + y, color);
      writePixel(x0 + y, y0 + x, color);
  }
  if (cornername & 0x2) {
      writePixel(x0 + x, y0 - y, color);
      writePixel(x0 + y, y0 - x, color);
  }
  if (cornername & 0x8) {
      writePixel(x0 - y, y0 + x, color);
      writePixel(x0 - x, y0 + y, color);
  }
  if (cornername & 0x1) {
      writePixel(x0 - y, y0 - x, color);
      writePixel(x0 - x, y0 - y, color);
  }
 }
}

//_____Draw a filled circle_____________________________________
void _Adafruit_GFX::fillCircle(int16_t x0, int16_t y0, int16_t r,
  uint16_t color) {
    startWrite();
    writeFastVLine(x0, y0-r, 2*r+1, color);
    fillCircleHelper(x0, y0, r, 3, 0, color);
    endWrite();
}

//_____Used to do circles and roundrects________________________
void _Adafruit_GFX::fillCircleHelper(int16_t x0, int16_t y0, 
 int16_t r, uint8_t cornername, int16_t delta, uint16_t color)
{
 int16_t f     = 1 - r;
 int16_t ddF_x = 1;
 int16_t ddF_y = -2 * r;
 int16_t x     = 0;
 int16_t y     = r;
 while (x<y) {
  if (f >= 0) {
   y--;
   ddF_y += 2;
   f     += ddF_y;
  }
  x++;
  ddF_x += 2;
  f     += ddF_x;
  if (cornername & 0x1) {
      writeFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      writeFastVLine(x0+y, y0-x, 2*x+1+delta, color);
  }
  if (cornername & 0x2) {
      writeFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      writeFastVLine(x0-y, y0-x, 2*x+1+delta, color);
  }
 }
}

//_____Draw a rectangle_________________________________________
void _Adafruit_GFX::drawRect(int16_t x, int16_t y, 
 int16_t w, int16_t h, uint16_t color) 
{
 startWrite();
 writeFastHLine(x, y, w, color);
 writeFastHLine(x, y+h-1, w, color);
 writeFastVLine(x, y, h, color);
 writeFastVLine(x+w-1, y, h, color);
 endWrite();
}

//_____Draw a rounded rectangle_________________________________
void _Adafruit_GFX::drawRoundRect(int16_t x, int16_t y, 
 int16_t w, int16_t h, int16_t r, uint16_t color) 
{
 // smarter version
 startWrite();
 writeFastHLine(x+r  , y    , w-2*r, color); // Top
 writeFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
 writeFastVLine(x    , y+r  , h-2*r, color); // Left
 writeFastVLine(x+w-1, y+r  , h-2*r, color); // Right
 // draw four corners
 drawCircleHelper(x+r    , y+r    , r, 1, color);
 drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
 drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
 drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
 endWrite();
}

//_____Fill a rounded rectangle_________________________________
void _Adafruit_GFX::fillRoundRect(int16_t x, int16_t y, 
 int16_t w, int16_t h, int16_t r, uint16_t color) 
{
 // smarter version
 startWrite();
 writeFillRect(x+r, y, w-2*r, h, color);
 // draw four corners
 fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
 fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
 endWrite();
}

//_____Draw a triangle__________________________________________
void _Adafruit_GFX::drawTriangle(int16_t x0, int16_t y0,
 int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
 drawLine(x0, y0, x1, y1, color);
 drawLine(x1, y1, x2, y2, color);
 drawLine(x2, y2, x0, y0, color);
}

//_____Fill a triangle__________________________________________
void _Adafruit_GFX::fillTriangle(int16_t x0, int16_t y0,
 int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
 int16_t a, b, y, last;
 // Sort coordinates by Y order (y2 >= y1 >= y0)
 if (y0 > y1) { _swap_int16_t(y0, y1); _swap_int16_t(x0, x1); }
 if (y1 > y2) { _swap_int16_t(y2, y1); _swap_int16_t(x2, x1); }
 if (y0 > y1) { _swap_int16_t(y0, y1); _swap_int16_t(x0, x1); }
 startWrite();
 if(y0 == y2) 
 { // Handle awkward all-on-same-line case as ts own thing
  a = b = x0;
  if(x1 < a)      a = x1;
  else if(x1 > b) b = x1;
  if(x2 < a)      a = x2;
  else if(x2 > b) b = x2;
  writeFastHLine(a, y0, b-a+1, color);
  endWrite();
  return;
 }
 int16_t
 dx01 = x1 - x0,
 dy01 = y1 - y0,
 dx02 = x2 - x0,
 dy02 = y2 - y0,
 dx12 = x2 - x1,
 dy12 = y2 - y1;
 int32_t
 sa   = 0,
 sb   = 0;
 
 // For upper part of triangle, find scanline crossings for 
 // segments 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle),
 // the scanline y1 is included here (and second loop will be
 // skipped, avoiding a /0 error there), otherwise scanline y1
 // is skipped here and handled in the second loop...which also
 // avoids a /0 error here if y0=y1 (flat-topped triangle).
 if(y1 == y2) last = y1;   // Include y1 scanline
         else last = y1-1; // Skip it
 for(y=y0; y<=last; y++) {
  a   = x0 + sa / dy01;
  b   = x0 + sb / dy02;
  sa += dx01;
  sb += dx02;
  /* longhand:
  a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
  b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
  */
  if(a > b) _swap_int16_t(a,b);
  writeFastHLine(a, y, b-a+1, color);
 }
 
 // For lower part of triangle, find scanline crossings for 
 // segments 0-2 and 1-2.  This loop is skipped if y1=y2.
 sa = dx12 * (y - y1);
 sb = dx02 * (y - y0);
 for(; y<=y2; y++) {
  a   = x1 + sa / dy12;
  b   = x0 + sb / dy02;
  sa += dx12;
  sb += dx02;
  /* longhand:
  a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
  b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
  */
  if(a > b) _swap_int16_t(a,b);
  writeFastHLine(a, y, b-a+1, color);
 }
 endWrite();
}

//==============================================================
// BITMAP / XBITMAP / GRAYSCALE / RGB BITMAP FUNCTIONS
//==============================================================

//_____Draw a PROGMEM-resident 1-bit image at the specified_____
// (x,y) position, using the specified foreground color 
// (unset bits are transparent).
void _Adafruit_GFX::drawBitmap(int16_t x, int16_t y,
 const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) 
{
 int16_t byteWidth = (w+7)/8;   //Bitmap scanline pad=whole byte
 uint8_t byte = 0;
 startWrite();
 for(int16_t j=0; j<h; j++, y++) {
  for(int16_t i=0; i<w; i++) {
   if(i & 7) byte <<= 1;
   else byte = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
   if(byte & 0x80) writePixel(x+i, y, color);
  }
 }
 endWrite();
}

//_____Draw a PROGMEM-resident 1-bit image at the specified_____
// (x,y) position, using the specified foreground (for set bits)
// and background (unset bits) colors.
void _Adafruit_GFX::drawBitmap(int16_t x, int16_t y,
 const uint8_t bitmap[], int16_t w, int16_t h,
 uint16_t color, uint16_t bg) 
{
 int16_t byteWidth = (w+7)/8;  // Bitmap scanline pad=whole byte
 uint8_t byte = 0;
 startWrite();
 for(int16_t j=0; j<h; j++, y++) {
  for(int16_t i=0; i<w; i++ ) {
   if(i & 7) byte <<= 1;
   else byte = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
   writePixel(x+i, y, (byte & 0x80) ? color : bg);
  }
 }
 endWrite();
}

//_____Draw a RAM-resident 1-bit image at the specified (x,y)___
// position, using the specified foreground color
// (unset bits are transparent).
void _Adafruit_GFX::drawBitmap(int16_t x, int16_t y,
  uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) 
{
 int16_t byteWidth = (w+7)/8; // Bitmap scanline pad=whole byte
 uint8_t byte = 0;
 startWrite();
 for(int16_t j=0; j<h; j++, y++) {
  for(int16_t i=0; i<w; i++ ) {
   if(i & 7) byte <<= 1;
   else      byte   = bitmap[j * byteWidth + i / 8];
   if(byte & 0x80) writePixel(x+i, y, color);
  }
 }
 endWrite();
}

//_____Draw a RAM-resident 1-bit image at the specified (x,y)___
// position, using the specified foreground (for set bits) and
// background (unset bits) colors.
void _Adafruit_GFX::drawBitmap(int16_t x, int16_t y,
 uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, 
 uint16_t bg)
{
 int16_t byteWidth = (w+7)/8; // Bitmap scanline pad=whole byte
 uint8_t byte = 0;
 startWrite();
 for(int16_t j=0; j<h; j++, y++) {
  for(int16_t i=0; i<w; i++ ) {
   if(i & 7) byte <<= 1;
   else      byte   = bitmap[j * byteWidth + i / 8];
   writePixel(x+i, y, (byte & 0x80) ? color : bg);
  }
 }
 endWrite();
}

//_____Draw PROGMEM-resident XBitMap Files (*.xbm)______________
// exported from GIMP
// Usage: Export from GIMP to *.xbm, rename *.xbm to *.c and 
//        open in editor.
// C Array can be directly used with this function.
// There is no RAM-resident version of this function;
// if generating bitmaps in RAM, use the format defined by 
// drawBitmap() and call that instead.
void _Adafruit_GFX::drawXBitmap(int16_t x, int16_t y,
 const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) 
{
 int16_t byteWidth = (w+7)/8; // Bitmap scanline pad=whole byte
 uint8_t byte = 0;
 startWrite();
 for(int16_t j=0; j<h; j++, y++) {
  for(int16_t i=0; i<w; i++ ) {
   if(i & 7) byte >>= 1;
   else byte = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
   // Nearly identical to drawBitmap(), only the bit order
   // is reversed here (left-to-right = LSB to MSB):
   if(byte & 0x01) writePixel(x+i, y, color);
  }
 }
 endWrite();
}

//_____Draw a PROGMEM-resident 8-bit image (grayscale) at the___
// specified (x,y) pos. Specifically for 8-bit display devices 
// such as IS31FL3731; no color reduction/expansion is performed
void _Adafruit_GFX::drawGrayscaleBitmap(int16_t x, int16_t y,
 const uint8_t bitmap[], int16_t w, int16_t h) 
{
 startWrite();
 for(int16_t j=0; j<h; j++, y++) {
  for(int16_t i=0; i<w; i++ ) {
   writePixel(x+i, y, (uint8_t)pgm_read_byte(&bitmap[j*w + i]));
  }
 }
 endWrite();
}

//___Draw a RAM-resident 8-bit image (grayscale) at the_________
// specified (x,y) pos. Specifically for 8-bit display devices
// such as IS31FL3731;
// no color reduction/expansion is performed.
void _Adafruit_GFX::drawGrayscaleBitmap(int16_t x, int16_t y,
 uint8_t *bitmap, int16_t w, int16_t h) 
{
 startWrite();
 for(int16_t j=0; j<h; j++, y++) {
  for(int16_t i=0; i<w; i++ ) {
   writePixel(x+i, y, bitmap[j * w + i]);
  }
 }
 endWrite();
}

//_____Draw a PROGMEM-resident 8-bit image (grayscale)__________
// with a 1-bit mask (set bits = opaque, unset bits = clear)
// at the specified (x,y) position.
// BOTH buffers (grayscale and mask) must be PROGMEM-resident.
// Specifically for 8-bit display devices such as IS31FL3731;
// no color reduction/expansion is performed.
void _Adafruit_GFX::drawGrayscaleBitmap(int16_t x, int16_t y,
 const uint8_t bitmap[], const uint8_t mask[],
 int16_t w, int16_t h) 
{
 int16_t bw   = (w + 7) / 8; // Bitmask scanline pad=whole byte
 uint8_t byte = 0;
 startWrite();
 for(int16_t j=0; j<h; j++, y++) {
  for(int16_t i=0; i<w; i++ ) {
   if(i & 7) byte <<= 1;
   else      byte   = pgm_read_byte(&mask[j * bw + i / 8]);
   if(byte & 0x80) {
    writePixel(x+i, y, (uint8_t)pgm_read_byte(&bitmap[j*w+i]));
   }
  }
 }
 endWrite();
}

//_____Draw a RAM-resident 8-bit image (grayscale)______________
// with a 1-bit mask (set bits = opaque, unset bits = clear)
// at the specified (x,y) pos.
// BOTH buffers (grayscale and mask) must be RAM-resident,
// no mix-and-match.  Specifically for 8-bit display devices 
// such as IS31FL3731;no color reduction/expansion is performed.
void _Adafruit_GFX::drawGrayscaleBitmap(int16_t x, int16_t y,
 uint8_t *bitmap, uint8_t *mask, int16_t w, int16_t h) 
{
 int16_t bw  = (w + 7) / 8; // Bitmask scanline pad = whole byte
 uint8_t byte = 0;
 startWrite();
 for(int16_t j=0; j<h; j++, y++) {
  for(int16_t i=0; i<w; i++ ) {
   if(i & 7) byte <<= 1;
   else      byte   = mask[j * bw + i / 8];
   if(byte & 0x80) {
    writePixel(x+i, y, bitmap[j * w + i]);
   }
  }
 }
 endWrite();
}

//_____Draw a PROGMEM-resident 16-bit image (RGB 5/6/5)_________
// at the specified (x,y) position.  For 16-bit display devices;
// no color reduction performed.
void _Adafruit_GFX::drawRGBBitmap(int16_t x, int16_t y,
 const uint16_t bitmap[], int16_t w, int16_t h) 
{
 startWrite();
 for(int16_t j=0; j<h; j++, y++) {
  for(int16_t i=0; i<w; i++ ) {
   writePixel(x+i, y, pgm_read_word(&bitmap[j * w + i]));
  }
 }
 endWrite();
}

//_____Draw a RAM-resident 16-bit image (RGB 5/6/5)_____________
// at the specified (x,y) position.  For 16-bit display devices;
// no color reduction performed.
void _Adafruit_GFX::drawRGBBitmap(int16_t x, int16_t y,
 uint16_t *bitmap, int16_t w, int16_t h) 
{
 startWrite();
 for(int16_t j=0; j<h; j++, y++) {
  for(int16_t i=0; i<w; i++ ) {
   writePixel(x+i, y, bitmap[j * w + i]);
  }
 }
 endWrite();
}

//_____Draw a PROGMEM-resident 16-bit image (RGB 5/6/5)_________
// with a 1-bit mask (set bits = opaque, unset bits = clear) at
// the specified (x,y) position.
// BOTH buffers (color and mask) must be PROGMEM-resident.
// For 16-bit display devices; no color reduction performed.
void _Adafruit_GFX::drawRGBBitmap(int16_t x, int16_t y,
 const uint16_t bitmap[], const uint8_t mask[], 
 int16_t w, int16_t h) 
{
 int16_t bw  = (w + 7) / 8; // Bitmask scanline pad = whole byte
 uint8_t byte = 0;
 startWrite();
 for(int16_t j=0; j<h; j++, y++) {
  for(int16_t i=0; i<w; i++ ) {
   if(i & 7) byte <<= 1;
   else      byte   = pgm_read_byte(&mask[j * bw + i / 8]);
   if(byte & 0x80) {
    writePixel(x+i, y, pgm_read_word(&bitmap[j * w + i]));
   }
  }
 }
 endWrite();
}

//_____Draw a RAM-resident 16-bit image (RGB 5/6/5)_____________
// with a 1-bit mask (set bits = opaque, unset bits = clear)
// at the specified (x,y) pos. BOTH buffers (color and mask)
// must be RAM-resident, no mix-and-match.
// For 16-bit display devices; no color reduction performed.
void _Adafruit_GFX::drawRGBBitmap(int16_t x, int16_t y,
 uint16_t *bitmap, uint8_t *mask, int16_t w, int16_t h) 
{
 int16_t bw  = (w + 7) / 8; // Bitmask scanline pad = whole byte
 uint8_t byte = 0;
 startWrite();
 for(int16_t j=0; j<h; j++, y++) {
  for(int16_t i=0; i<w; i++ ) {
   if(i & 7) byte <<= 1;
   else      byte   = mask[j * bw + i / 8];
   if(byte & 0x80) {
    writePixel(x+i, y, bitmap[j * w + i]);
   }
  }
 }
 endWrite();
}

//==============================================================
// TEXT- AND CHARACTER-HANDLING FUNCTIONS
//==============================================================

//_____Draw a character_________________________________________
void _Adafruit_GFX::drawChar(int16_t x, int16_t y, 
 unsigned char c, uint16_t color, uint16_t bg, uint8_t size) 
{
 if(!gfxFont)                          
 { //----- 'Classic' built-in font------------------------------
  if((x >= _width)  ||                  // Clip right
     (y >= _height) ||                  // Clip bottom
     ((x + 6 * size - 1) < 0) ||        // Clip left
     ((y + 8 * size - 1) < 0))          // Clip top
     return;

if(!_cp437 && (c >= 176)) c++; // Handle 'classic' charset behavior

  startWrite();
  for(int8_t i=0; i<5; i++ )            // Char bitmap=5 columns
  { 
   uint8_t line = pgm_read_byte(&fontKH_5x8Bitmaps[c * 5 + i]);
   for(int8_t j=0; j<8; j++, line >>= 1) {
    if(line & 1) 
    {
     if(size == 1)
      writePixel(x+i, y+j, color);
     else
      writeFillRect(x+i*size, y+j*size, size, size, color);
    } else 
    if(bg != color) 
    {
     if(size == 1)
      writePixel(x+i, y+j, bg);
     else
      writeFillRect(x+i*size, y+j*size, size, size, bg);
    }
   }
  }
  if(bg != color) 
  { // If opaque, draw vertical line for last column
   if(size == 1) writeFastVLine(x+5, y, 8, bg);
   else    writeFillRect(x+5*size, y, size, 8*size, bg);
  }
  endWrite();
 }
 else
 { //-----Custom font-------------------------------------------
  // Character is assumed previously filtered by write() to 
  // eliminate newlines, returns, non-printable characters, etc.
  // Calling drawChar() directly with 'bad' characters of font
  // may cause mayhem!
  c -= (uint8_t)pgm_read_byte(&gfxFont->first);
  _GFXglyph *glyph  = &(((_GFXglyph *)
   pgm_read_pointer(&gfxFont->glyph))[c]);
  uint8_t *bitmap=(uint8_t *)pgm_read_pointer(&gfxFont->bitmap);
  uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
  uint8_t  w  = pgm_read_byte(&glyph->width),
     h  = pgm_read_byte(&glyph->height);
  int8_t   xo = pgm_read_byte(&glyph->xOffset),
     yo = pgm_read_byte(&glyph->yOffset);
  uint8_t  xx, yy, bits = 0, bit = 0;
  int16_t  xo16 = 0, yo16 = 0;
  if(size > 1) {
      xo16 = xo;
      yo16 = yo;
  }
  // Todo: Add character clipping here
  // NOTE: THERE IS NO 'BACKGROUND' COLOR OPTION ON CUSTOM FONTS
  // THIS IS ON PURPOSE AND BY DESIGN.  The background color 
  // feature has typically been used with the 'classic' font to
  // overwrite old screen contents with new data. This ONLY 
  // works because the characters are a uniform size; it's not a
  // sensible thing to do with proportionally-spaced fonts with
  // glyphs of varying sizes (and that may overlap).  To replace
  // previously-drawn text when using a custom font, use the
  // getTextBounds() function to determine the smallest 
  // rectangle encompassing a string, erase the area with 
  // fillRect(), then draw new text. This WILL infortunately
  // 'blink' the text, but is unavoidable.  Drawing 'background'
  // pixels will NOT fix this, only creates a new set of 
  // problems.  Have an idea to work around this (a canvas 
  // object type for MCUs that can afford the RAM and displays
  // supporting setAddrWindow() and pushColors()), but haven't
  // implemented this yet.
  startWrite();
  for(yy=0; yy<h; yy++) {
   for(xx=0; xx<w; xx++) {
    if(!(bit++ & 7)) {
     bits = pgm_read_byte(&bitmap[bo++]);
    }
    if(bits & 0x80) {
     if(size == 1) {
      writePixel(x+xo+xx, y+yo+yy, color);
     } else {
      writeFillRect(x+(xo16+xx)*size, y+(yo16+yy)*size, 
       size, size, color);
      }
    }
    bits <<= 1;
   }
  }
  endWrite();
 } // End classic vs custom font
}

//_____write a character________________________________________
size_t _Adafruit_GFX::write(uint8_t c)
{
 if(!gfxFont) 
 { //-----'Classic' built-in font-------------------------------
  if(c == '\n') {                // Newline?
   cursor_x  = 0;                // Reset x to zero,
   cursor_y += textsize * 8;     // advance y one line
  } else if(c != '\r') 
  {     // Ignore carriage returns
   if(wrap && ((cursor_x + textsize * 6) > _width)) 
   { // Off right?
    cursor_x  = 0;     // Reset x to zero,
    cursor_y += textsize * 8;      // advance y one line
   }
   drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
   cursor_x += textsize * 6;    // Advance x one char
  }
 } else 
 { //-----Custom font-------------------------------------------
  if(c == '\n') {
   cursor_x  = 0;
   cursor_y += (int16_t)textsize *
    (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
  } else if(c != '\r') 
  {
   uint8_t first = pgm_read_byte(&gfxFont->first);
   if((c>=first) && (c<=(uint8_t)pgm_read_byte(&gfxFont->last)))
   {
    _GFXglyph *glyph = &(((_GFXglyph *)pgm_read_pointer(
      &gfxFont->glyph))[c - first]);
    uint8_t   w     = pgm_read_byte(&glyph->width),
        h     = pgm_read_byte(&glyph->height);
    if((w > 0) && (h > 0)) { // Is there an associated bitmap?
     int16_t xo = (int8_t)pgm_read_byte(&glyph->xOffset); // sic
     if(wrap && ((cursor_x + textsize * (xo + w)) > _width)) {
      cursor_x  = 0;
      cursor_y += (int16_t)textsize *
        (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
     }
     drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
    }
    cursor_x += (uint8_t)pgm_read_byte(&glyph->xAdvance) * (int16_t)textsize;
   }
  }
 }
 return 1;
}

//_____set cursor to given position_____________________________
void _Adafruit_GFX::setCursor(int16_t x, int16_t y) {
 cursor_x = x;
 cursor_y = y;
}

//_____get cursor position______________________________________
int16_t _Adafruit_GFX::getCursorX(void) const {return cursor_x;}
int16_t _Adafruit_GFX::getCursorY(void) const {return cursor_y;}

//_____set text size (1 or greater)_____________________________
void _Adafruit_GFX::setTextSize(uint8_t s) {
 textsize = (s > 0) ? s : 1;
}

//_____set text color___________________________________________
void _Adafruit_GFX::setTextColor(uint16_t c) {
 // For 'transparent' background, we'll set the bg
 // to the same as fg instead of using a flag
 textcolor = textbgcolor = c;
}

//_____set text and background color____________________________
void _Adafruit_GFX::setTextColor(uint16_t c, uint16_t b) {
 textcolor   = c;
 textbgcolor = b;
}

//_____do text wrap (write to much text in next line(s))________
void _Adafruit_GFX::setTextWrap(boolean w) { wrap = w; }

//_____get rotation (0..3)______________________________________
uint8_t _Adafruit_GFX::getRotation(void) const { 
 return rotation;
}

//_____set rotation (0..3)______________________________________
void _Adafruit_GFX::setRotation(uint8_t x) {
 rotation = (x & 3);
 switch(rotation) {
  case 0: case 2:
   _width  = WIDTH;
   _height = HEIGHT;
   break;
  case 1: case 3:
   _width  = HEIGHT;
   _height = WIDTH;
   break;
 }
}

//_____set font_________________________________________________
void _Adafruit_GFX::setFont(const _GFXfont *f) {
 if(f) {      // Font struct pointer passed in?
  if(!gfxFont) { // And no current font struct?
   // Switching from classic to new font behavior.
   // Move cursor pos down 6 pixels so it's on baseline.
   cursor_y += 6;
  }
 } else if(gfxFont) 
 { // NULL passed.  Current font struct defined?
   // Switching from new to classic font behavior.
   // Move cursor pos up 6 pixels so it's at top-left of char.
  cursor_y -= 6;
 }
 gfxFont = (_GFXfont *)f;
}

//_____Broke this out as it's used by both the PROGMEM- and_____
// RAM-resident getTextBounds() functions.
void _Adafruit_GFX::charBounds(char c, int16_t *x, int16_t *y,
 int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy) 
{
 if(gfxFont) 
 { //-----gfxFont-----------------------------------------------
  if(c == '\n') { // Newline?
   *x  = 0;    // Reset x to zero, advance y by one line
   *y += textsize * (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
  } else if(c != '\r') 
  { // Not a carriage return; is normal char
   uint8_t first = pgm_read_byte(&gfxFont->first),
    last  = pgm_read_byte(&gfxFont->last);
   if((c >= first) && (c <= last)) 
   { // Char present in this font?
    _GFXglyph *glyph = &(((_GFXglyph *)pgm_read_pointer(
      &gfxFont->glyph))[c - first]);
    uint8_t gw = pgm_read_byte(&glyph->width),
      gh = pgm_read_byte(&glyph->height),
      xa = pgm_read_byte(&glyph->xAdvance);
    int8_t  xo = pgm_read_byte(&glyph->xOffset),
      yo = pgm_read_byte(&glyph->yOffset);
    if(wrap && ((*x+(((int16_t)xo+gw)*textsize)) > _width)) 
    {
     *x  = 0; // Reset x to zero, advance y by one line
     *y += textsize * (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
    }
    int16_t ts = (int16_t)textsize,
      x1 = *x + xo * ts,
      y1 = *y + yo * ts,
      x2 = x1 + gw * ts - 1,
      y2 = y1 + gh * ts - 1;
    if(x1 < *minx) *minx = x1;
    if(y1 < *miny) *miny = y1;
    if(x2 > *maxx) *maxx = x2;
    if(y2 > *maxy) *maxy = y2;
    *x += xa * ts;
   }
  }
 } else 
 { //-----Default font------------------------------------------
  if(c == '\n') {   // Newline?
   *x  = 0;      // Reset x to zero,
   *y += textsize * 8;       // advance y one line min/max x/y
   // unchaged -- that waits for next 'normal' character
  } else if(c != '\r') 
  { // Normal char; ignore carriage returns
   if(wrap && ((*x + textsize * 6) > _width)) { // Off right?
    *x  = 0;        // Reset x to zero,
    *y += textsize * 8;   // advance y one line
   }
   int x2 = *x + textsize * 6 - 1, // Lower-right pixel of char
    y2 = *y + textsize * 8 - 1;
   if(x2 > *maxx) *maxx = x2;      // Track max x, y
   if(y2 > *maxy) *maxy = y2;
   if(*x < *minx) *minx = *x;      // Track min x, y
   if(*y < *miny) *miny = *y;
   *x += textsize * 6;       // Advance x one char
  }
 }
}

//_____Pass string and cursor position, returns* UL corner, W,H__
void _Adafruit_GFX::getTextBounds(char *str, int16_t x, 
 int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) 
{
 uint8_t c;     // Current character
 *x1 = x;
 *y1 = y;
 *w  = *h = 0;
 int16_t minx = _width, miny = _height, maxx = -1, maxy = -1;
 while((c = *str++))
  charBounds(c, &x, &y, &minx, &miny, &maxx, &maxy);
 if(maxx >= minx) {
  *x1 = minx;
  *w  = maxx - minx + 1;
 }
 if(maxy >= miny) {
  *y1 = miny;
  *h  = maxy - miny + 1;
 }
}

//_____Same as above, but for PROGMEM strings___________________
void _Adafruit_GFX::getTextBounds(const __FlashStringHelper *str,
 int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, 
 uint16_t *h) 
{
 uint8_t *s = (uint8_t *)str, c;
 *x1 = x;
 *y1 = y;
 *w  = *h = 0;
 int16_t minx = _width, miny = _height, maxx = -1, maxy = -1;
 while((c = pgm_read_byte(s++)))
  charBounds(c, &x, &y, &minx, &miny, &maxx, &maxy);
 if(maxx >= minx) {
  *x1 = minx;
  *w  = maxx - minx + 1;
 }
 if(maxy >= miny) {
  *y1 = miny;
  *h  = maxy - miny + 1;
 }
}

//_____Return the size of the display (per current rotation)____
int16_t _Adafruit_GFX::width(void) const { return _width; }
int16_t _Adafruit_GFX::height(void) const { return _height; }

//_____invert display___________________________________________
// Overwrite in subclass if inverting is supported by hardware!
void _Adafruit_GFX::invertDisplay(boolean i) { // Do nothing
}


