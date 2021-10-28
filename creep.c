#include "LIB/neslib.h"
#include "LIB/nesdoug.h"
#include "Sprites.h"
#include "BG/Room1.h"
#include "BG/Room2.h"
#include "globals.h"
#include "structs.h"
#include "functions.c"

const unsigned char palette[16]={ 
	0x09,0x31,0x30,0x07, //green, light blue, white, brown
	0,0,0,0,
	0,0,0,0,
	0,0,0,0 
};

void main (void) {
	
	ppu_off(); 
	
	
	pal_bg(palette);
	pal_spr(palette_sp);
	bank_spr(1);

	vram_adr(NAMETABLE_A);
	vram_unrle(Room1);
	
	vram_adr(NAMETABLE_B);
	vram_unrle(Room2);
	
	sball.x = 0x4000;
	sball.y = 0x7500;
	
	ppu_on_all(); // turn on screen
	
	
	while (1){
		// infinite loop

		ppu_wait_nmi(); // wait till beginning of the frame
		// the sprites are pushed from a buffer to the OAM during nmi
		pad1 = pad_poll(0); // read the first controller
		
		clear_vram_buffer(); // do at the beginning of each frame
		
		movement();
		set_scroll_x(scroll_x);
		set_scroll_y(scroll_y);
		draw_screen_R();
		draw_sprites();
	}
}
	