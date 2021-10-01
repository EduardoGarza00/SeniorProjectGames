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
#include "LIB/stats.c"
#include "GFX/titlescreen.h"
#include "GFX/titlescreenPal.h"
#include "GFX/gamescreen.h"
#include "GFX/gamescreenPal.h"
#include "GFX/winscreen.h"
#include "GFX/snakePal.h"
#pragma bss-name(push, "BSS")

extern const byte titlescreen[640];
extern const byte palette[16];
extern const byte gamescreen[579];
extern const byte palette2[16];
extern const byte winscreen[565];

//system vars used everywhere as well
unsigned char song, k, pad, game_lives, s;

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

void show_win_screen(void) {
	ppu_off();
	pal_bg(palette);
	pal_bright(0);
	oam_clear();

	vram_adr(NAMETABLE_A);
	vram_unrle(winscreen);
 
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
	vram_adr(NAMETABLE_A+0x0042);
	vram_write(lives3, 9);

	ppu_on_all();
	fade_in();
	spr=0;
	s=0;
	Snake1.size=0;
	mouse_coord();
	
	while(1) {
		
		ppu_wait_nmi(); 
		pad1 = pad_poll(0); // read the first controller
		movement();
		
		draw_sprites();
		mouse1.respawn=1;
		draw_mouse();
		test1();
		
		if(Snake1.size == 1) {
			updateListData[6]=0x31;
			updateListData[7]=0x32;
			updateListData[8]=0x37;
			updateListData[9]=0x31;
			updateListData[10]=0x38;
			
			while (s == 0) {
				ppu_off();
				vram_adr(NAMETABLE_A+0x0053);
				vram_write(updateListData, 11);
				ppu_on_all();
				s=1;
			}
		}
		if(Snake1.size == 2) {
			updateListData[6]=0x33;
			updateListData[7]=0x36;
			updateListData[8]=0x39;
			updateListData[9]=0x31;
			updateListData[10]=0x38;
			while (s == 1) {
				ppu_off();
				vram_adr(NAMETABLE_A+0x0053);
				vram_write(updateListData, 11);
				ppu_on_all();
				s=2;
			}
		}
		if(Snake1.size == 3) {
			updateListData[6]=0x34;
			updateListData[7]=0x31;
			updateListData[8]=0x35;
			updateListData[9]=0x31;
			updateListData[10]=0x39;
			while (s == 2) {
				ppu_off();
				vram_adr(NAMETABLE_A+0x0053);
				vram_write(updateListData, 11);
				ppu_on_all();
				s=3;
			}
		}
		if(Snake1.size == 4) {
			updateListData[6]=0x34;
			updateListData[7]=0x32;
			updateListData[8]=0x30;
			updateListData[9]=0x36;
			updateListData[10]=0x39;
			while (s == 3) {
				ppu_off();
				vram_adr(NAMETABLE_A+0x0053);
				vram_write(updateListData, 11);
				ppu_on_all();
				s=4;
			}
		}
		if(Snake1.size >= 5) {
			break;
		}
		if(pad_trigger(0)&PAD_START) {
			ppu_off();
			break;
		}
	}
}

void main(void)
{
	music_play(song);
	game_lives = 3;
	
	while(1) {
		
		show_title_screen();
		
		while(game_lives != 0) {
			game_loop();
			show_win_screen();
		}
	}
}