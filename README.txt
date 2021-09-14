//How to import screens and pallets from NES Screen Tool
-Make Screen
-Nametable-Save as C header (.h file)
-#include the .h file for the title screen
-Palettes-Put to clipboard C data (.h file)
-#include the .h file for the title screen palettes

WORKING CODE THAT SHOWS TITLE SCREEN {

#include "LIB/neslib.h"
#include "titlescreen.h"
#include "titlescreenPal.h"

extern const byte titlescreen[214];
extern const byte palette[16];
 

void fade_in() {
  byte vb;
  for (vb=0; vb<=4; vb++) {
   
    pal_bright(vb);
  
    ppu_wait_frame();
    ppu_wait_frame();
    ppu_wait_frame();
    ppu_wait_frame();
  }
}

void show_title_screen(const byte* pal, const byte* rle) {
  
  ppu_off();

  pal_all(pal);
  pal_bright(0);

  vram_adr(0x2000);
  vram_unrle(rle);
 
  ppu_on_all();
  fade_in();
}

void main(void)
{
  show_title_screen(palette, titlescreen);
  while(1);//do nothing, infinite loop
}


}