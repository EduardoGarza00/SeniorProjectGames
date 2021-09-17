#include "LIB/neslib.h"
#include "GFX/titlescreen.h"
#include "GFX/titlescreenPal.h"
#include "GFX/gamescreen.h"
#include "GFX/gamescreenPal.h"

extern const byte titlescreen[640];
extern const byte palette[16];
extern const byte gamescreen[499];
extern const byte palette2[16];

unsigned char song, k, i;

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
	music_play(song);
	
	while(1) {
		i=pad_trigger(0);
		
		if(i&PAD_A)
		{
			show_title_screen(palette2, gamescreen);
		}
		
		if(i&PAD_B)
		{
			music_stop();
		}
		
		
	}
}