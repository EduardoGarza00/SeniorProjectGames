#include "LIB/neslib.h"
#include "LIB/nesdoug.h"
#include "LIB/structs.h"
#include "LIB/definitions.h"
#include "LIB/Sprites.h"
#include "LIB/globals.h"
#include "LIB/inputs_movement.c"
#include "LIB/draw_function.c"
#include "LIB/room1.h"
#include "LIB/metatiles.h"
#include "GFX/titlescreen.h"
#include "GFX/titlescreenPal.h"
#include "GFX/gamescreen.h"
#include "GFX/gamescreenPal.h"
#include "GFX/snakePal.h"
#pragma bss-name(push, "BSS")

extern const byte titlescreen[640];
extern const byte palette[16];
extern const byte gamescreen[581];
extern const byte palette2[16];

//system vars used everywhere as well
unsigned char song, k, pad, game_lives;

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

void show_title_screen(void) {
  
	ppu_off();
	pal_all(palette);
	pal_bright(0);

	vram_adr(NAMETABLE_A);
	vram_unrle(titlescreen);
 
	ppu_on_all();
	fade_in();
	
	while(1) {
		if(pad_trigger(0)&PAD_START) {
			ppu_off();
			break;
		}
	}
}

void game_loop(void) {
	
	vram_adr(NAMETABLE_A);
	vram_unrle(gamescreen);
	pal_spr(palette5);
	pal_bright(0);
	
	bank_spr(1);

	ppu_on_all();
	fade_in();
	spr=0;
	mouse_coord();
	
	
	while(1) {
		
		ppu_wait_nmi(); 
		pad1 = pad_poll(0); // read the first controller
	
		movement();
		
		draw_sprites();
		mouse1.respawn=1;
		draw_mouse();
		test1();
		
		if(pad_trigger(0)&PAD_START) {
			ppu_off();
			break;
		}
	}
}

void main(void)
{
	music_play(song);

	while(1) {
		
		show_title_screen();
		game_lives = 3;
		
		while(game_lives != 0) {
			game_loop();
		}
		
		//To stop the music
		if(pad_trigger(0)&PAD_SELECT)
		{
			music_stop();
		}
		
	}
}