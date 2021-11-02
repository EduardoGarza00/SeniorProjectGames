#include "LIB/neslib.h"
#include "LIB/nesdoug.h"
#include "Sprites.h" // holds our metasprite data
#include "scroll_r.h"

void load_room(void){
	pal_bg(paletter);
	set_data_pointer(Rooms[0]);
	set_mt_pointer(metatiles3);
	for(y=0; ;y+=0x20){
		for(x=0; ;x+=0x20){
			clear_vram_buffer(); // do each frame, and before putting anything in the buffer
			address = get_ppu_addr(0, x, y);
			index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			flush_vram_update_nmi();
			if (x == 0xe0) break;
		}
		if (y == 0xe0) break;
	}
	
	// a little bit in the next room
	set_data_pointer(Rooms[1]);
	for(y=0; ;y+=0x20){
		x = 0;
		clear_vram_buffer(); // do each frame, and before putting anything in the buffer
		address = get_ppu_addr(1, x, y);
		index = (y & 0xf0);
		buffer_4_mt(address, index); // ppu_address, index to the data
		flush_vram_update_nmi();
		if (y == 0xe0) break;
	}
	clear_vram_buffer();
	
	// copy the room to the collision map
	// the second one should auto-load with the scrolling code
	memcpy (c_map, room1, 240);
	sprite_obj_init();
}

char get_position(void){
	// is it in range ? return 1 if yes
	
	temp5 -= scroll_x;
	temp_x = temp5 & 0xff;
	if(high_byte(temp5)) return 0;
	return 1;
}

void draw_sprites(void){
	// clear all sprites from sprite buffer
	oam_clear();
	
	// draw 1 metasprite
	temp_x = high_byte(sball.x);
	temp_y = high_byte(sball.y);
	
	//if(temp_x > 0) temp_x = 5;
	//if(temp_x == 0) temp_x = 5;
	 if(lives<4){
		 
		 oam_meta_spr(temp_x,temp_y,brotate[k]);
	 }
	 else {
		 oam_meta_spr(temp_x,temp_y,bigbrotate[k]);	
	 }
	
	
	
	
	
	
	for(index = 0; index < MAX_MOUNDS; ++index){
		temp_y = mound_y[index];
		if(temp_y == TURN_OFF) continue;
		if(get_frame_count() & 8) ++temp_y; 
		if(!mound_active[index]) continue;
		temp_x = mound_x[index];
		if(temp_x > 0xf0) continue;
		if(temp_y < 0xf0) {
			
			if(spr_type[index]==MOUNDS){
			oam_meta_spr(temp_x, temp_y, mound);
			}
			else{oam_meta_spr(temp_x,temp_y,end);}
		}
	}
	
	for(index = 0; index < MAX_ENEMY; ++index){
		temp_y = enemy_y[index];
		if(temp_y == TURN_OFF) continue;
		temp1 = enemy_active[index];
		temp2 = enemy_x[index];
		if(temp2 > 0xf0) continue;
		if(temp1 && (temp_y < 0xf0)) {
			
			oam_meta_spr(temp2, temp_y, skier);
		}
	}
}
	
void movement(void){
	
	// handle x
	old_x = sball.x;
	
	if (pad1 & PAD_RIGHT){
		direction = RIGHT;
	
		sball.vel_x = SPEED;
		if (k != 3 & i%7 ==0){
			k++;
		}
		else if(k==3){
		k=0;}
	}
	
	sball.x += sball.vel_x;
	i++;
	if((sball.x < 0x100)||(sball.x > 0xf800)) { //make sure no wrap around to the other side
		sball.x = 0x100;
	} 
	
	L_R_switch = 1; // shinks the y values in bg_coll, less problems with head / feet collisions
	
	Generic.x = high_byte(sball.x); //this is much faster than passing a pointer to sball
	Generic.y = high_byte(sball.y);
	if(lives<4){
	Generic.width = HERO_WIDTH_SMALL;
	Generic.height = HERO_HEIGHT_SMALL;
	}
	else{
		Generic.width = HERO_WIDTH;
	Generic.height = HERO_HEIGHT;
	}
	bg_collision();
	if(collision_R && collision_L){ //if both true, probably half stuck in a wall
		sball.x = old_x;
	 
	}
	else if(collision_L) {
		high_byte(sball.x) = high_byte(sball.x) - eject_L;
		
	}
	else if(collision_R) {
		high_byte(sball.x) = high_byte(sball.x) - eject_R;
		
	}
	

	// handle y
	old_y = sball.y; //didn't end up using the old value
	
	if(pad1 & PAD_UP){
		if(sball.y <= 0x100) {
			sball.vel_y = 0;
			sball.y = 0x100;
		}
		else if(sball.y < 0x400) { //don't want to wrap around to the other side
			sball.vel_y = -0x100;
		}
		else {
			sball.vel_y = -SPEED;
		}
	}
	else if (pad1 & PAD_DOWN){
		if(sball.y >= 0xe000) {
			sball.vel_y = 0;
			sball.y = 0xe000;
		}
		else if(sball.y > 0xdc00) { //don't want to wrap around to the other side
			sball.vel_y = 0x100;
		}
		else {
			sball.vel_y = SPEED;
		}
	}
	//else { //nothing pressed
	//	sball.vel_y = 0;
	//}
	
	sball.y += sball.vel_y;
	
	if((sball.y < 0x100)||(sball.y > 0xf000)) { // make sure no wrap around to the other side
		sball.y = 0x100;
	} 
	
	L_R_switch = 0; // shinks the y values in bg_coll, less problems with head / feet collisions
	
	Generic.x = high_byte(sball.x); // this is much faster than passing a pointer to sball
	Generic.y = high_byte(sball.y);
	
	if(lives<4){
	Generic.width = HERO_WIDTH_SMALL;
	Generic.height = HERO_HEIGHT_SMALL;
	}
	else{
		Generic.width = HERO_WIDTH;
	Generic.height = HERO_HEIGHT;
	}
	bg_collision();
	if(collision_U && collision_D){ // if both true, probably half stuck in a wall
		sball.y = old_y;
		
	}
	else if(collision_U) {
		high_byte(sball.y) = high_byte(sball.y) - eject_U;
	
		
	}
	else if(collision_D) {
		high_byte(sball.y) = high_byte(sball.y) - eject_D;
	
	}
	
	
	// do we need to load a new collision map? (scrolled into a new room)
	if((scroll_x & 0xff) < 4){
		new_cmap(); //
	}
	
	// scroll
	temp5 = sball.x;
	if (sball.x > MAX_RIGHT){
		temp1 = (sball.x - MAX_RIGHT) >> 8;
		scroll_x += temp1;
		high_byte(sball.x) = high_byte(sball.x) - temp1;
	}

	if(scroll_x >= MAX_SCROLL) {
		scroll_x = MAX_SCROLL;	// stop scrolling right, end of level
		
		sball.x = temp5; // but allow the x position to go all the way right
		if(high_byte(sball.x) >= 0xf1) {
			sball.x = 0xf100;
			game_end =1;
		}
	}
}	

void bg_collision(void){
	// note, !0 = collision
	// sprite collision with backgrounds
	// load the object's x,y,width,height to Generic, then call this
	

	collision_L = 0;
	collision_R = 0;
	collision_U = 0;
	collision_D = 0;
	
	if(Generic.y >= 0xf0) return;
	
	temp6 = temp5 = Generic.x + scroll_x; // upper left (temp6 = save for reuse)
	temp1 = temp5 & 0xff; // low byte x
	temp2 = temp5 >> 8; // high byte x
	
	eject_L = temp1 | 0xf0;
	
	temp3 = Generic.y; // y top
	
	eject_U = temp3 | 0xf0;
	
	if(L_R_switch) temp3 += 2; // fix bug, walking through walls
	
	bg_collision_sub();
	
	if(collision){ // find a corner in the collision map
		++collision_L;
		++collision_U;
	}
	
	// upper right
	temp5 += Generic.width;
	temp1 = temp5 & 0xff; // low byte x
	temp2 = temp5 >> 8; // high byte x
	
	eject_R = (temp1 + 1) & 0x0f;
	
	// temp3 is unchanged
	bg_collision_sub();
	
	if(collision){ // find a corner in the collision map
		++collision_R;
		++collision_U;
	}
	
	
	// again, lower
	// bottom right, x hasn't changed

	temp3 = Generic.y + Generic.height; //y bottom
	if(L_R_switch) temp3 -= 2; // fix bug, walking through walls
	eject_D = (temp3 + 1) & 0x0f;
	if(temp3 >= 0xf0) return;
	
	bg_collision_sub();
	
	if(collision){ // find a corner in the collision map
		++collision_R;
		++collision_D;
	}
	
	// bottom left
	temp1 = temp6 & 0xff; // low byte x
	temp2 = temp6 >> 8; // high byte x
	
	//temp3, y is unchanged

	bg_collision_sub();
	
	if(collision){ // find a corner in the collision map
		++collision_L;
		++collision_D;
	}
}

void bg_collision_sub(void){
	coordinates = (temp1 >> 4) + (temp3 & 0xf0);
	
	map = temp2&1; // high byte
	if(!map){
		collision = c_map[coordinates];
	}
	else{
		collision = c_map2[coordinates];
	}
}

void draw_screen_R(void){
	// scrolling to the right, draw metatiles as we go
	pseudo_scroll_x = scroll_x + 0x120;
	
	temp1 = pseudo_scroll_x >> 8;
	
	set_data_pointer(Rooms[temp1]);
	nt = temp1 & 1;
	x = pseudo_scroll_x & 0xff;
	
	// important that the main loop clears the vram_buffer
	
	switch(scroll_count){
		case 0:
			address = get_ppu_addr(nt, x, 0);
			index = 0 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			
			address = get_ppu_addr(nt, x, 0x20);
			index = 0x20 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			break;
			
		case 1:
			address = get_ppu_addr(nt, x, 0x40);
			index = 0x40 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			
			address = get_ppu_addr(nt, x, 0x60);
			index = 0x60 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			break;
			
		case 2:
			address = get_ppu_addr(nt, x, 0x80);
			index = 0x80 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			
			address = get_ppu_addr(nt, x, 0xa0);
			index = 0xa0 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			break;
			
		default:
			address = get_ppu_addr(nt, x, 0xc0);
			index = 0xc0 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			
			address = get_ppu_addr(nt, x, 0xe0);
			index = 0xe0 + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
	}

	
	
	++scroll_count;
	scroll_count &= 3; // mask off top bits, keep it 0-3
}

void new_cmap(void){
	// copy a new collision map to one of the 2 c_map arrays
	room = ((scroll_x >> 8) +1); //high byte = room, one to the right
	
	map = room & 1; //even or odd?
	if(!map){
		memcpy (c_map, Rooms[room], 240);
	}
	else{
		memcpy (c_map2, Rooms[room], 240);
	}
}

void sprite_obj_init(void){
	
	pointer = level_1_mounds;
	for(index = 0,index2 = 0;index < MAX_MOUNDS; ++index){
		
		mound_x[index] = 0;

		temp1 = pointer[index2]; // get a byte of data
		mound_y[index] = temp1;
		
		if(temp1 == TURN_OFF) break;

		++index2;
		
		mound_active[index] = 0;

		
		temp1 = pointer[index2]; // get a byte of data
		mound_room[index] = temp1;
		
		++index2;
		
		temp1 = pointer[index2]; // get a byte of data
		mound_actual_x[index] = temp1;
		
		++index2;
		temp1 = pointer[index2];
		spr_type[index]=temp1;
		++index2;
	}
	
	for(++index;index < MAX_MOUNDS; ++index){
		mound_y[index] = TURN_OFF;
	}
	
	pointer = level_1_enemies;
	
	for(index = 0,index2 = 0;index < MAX_ENEMY; ++index){
		
		enemy_x[index] = 0;

		temp1 = pointer[index2]; // get a byte of data
		enemy_y[index] = temp1;
		
		if(temp1 == TURN_OFF) break;

		++index2;
		
		enemy_active[index] = 0;
		
		temp1 = pointer[index2]; // get a byte of data
		enemy_room[index] = temp1;
		
		++index2;
		
		temp1 = pointer[index2]; // get a byte of data
		enemy_actual_x[index] = temp1;
		
		++index2;
	}
	
	for(++index;index < MAX_ENEMY; ++index){
		enemy_y[index] = TURN_OFF;
	}
}

void check_spr_objects(void){
	
	Generic2.x = high_byte(sball.x);
	// mark each object "active" if they are, and get the screen x
	
	for(index = 0; index < MAX_MOUNDS; ++index){
		mound_active[index] = 0; //default to zero
		if(mound_y[index] != TURN_OFF){
			high_byte(temp5) = mound_room[index];
			low_byte(temp5) = mound_actual_x[index];
			mound_active[index] = get_position();
			mound_x[index] = temp_x; // screen x coords
		}

	}
	
	for(index = 0; index < MAX_ENEMY; ++index){
		enemy_active[index] = 0; //default to zero
		if(enemy_y[index] != TURN_OFF){
			temp5 = (enemy_room[index] << 8) + enemy_actual_x[index];
			enemy_active[index] = get_position();
			enemy_x[index] = temp_x; // screen x coords
		}

	}
	
}

void skier_move(void){
	
	temp1 = high_byte(sball.x);
	
	//if(get_frame_count() & 0x01) return; // half speed
	
	for(index = 0; index < MAX_ENEMY; ++index){
		if(enemy_active[index]){
			if(enemy_x[index] > temp1){
				if(enemy_actual_x[index] == 0) --enemy_room[index];
				--enemy_actual_x[index];
				--enemy_y[index];
			}
			else if(enemy_x[index] < temp1){
				++enemy_actual_x[index];
				enemy_y[index];
				if(enemy_actual_x[index] == 0) ++enemy_room[index];
			}
		}
	}
}

void show_title_screen(void) {
	//ppu_off();
	pal_all(palettetitle);
	

	vram_adr(NAMETABLE_A);
	vram_unrle(TitleScreen);
 
	ppu_on_all();

	while(1) {
		if(pad_poll(0) == PAD_START) {
			break;
		}
	}
}

void show_win_screen(void) {
	music_play(0); 
	ppu_off();
	oam_clear();
	clear_vram_buffer();
	set_scroll_x(0);
	pal_all(winpal);
	

	vram_adr(NAMETABLE_A);
	vram_unrle(winscreen);
 
	ppu_on_all();
	
	while(1) {
		if(pad_poll(0) == PAD_START) {
			break;
		}
	}
}

void show_lose_screen(void) {
	ppu_off();
	oam_clear();
	clear_vram_buffer();
	set_scroll_x(0);
	pal_all(losepal);
	

	vram_adr(NAMETABLE_A);
	vram_unrle(losescreen);
 
	ppu_on_all();
	
}

void sprite_collisions(void){

	Generic.x = high_byte(sball.x);
	Generic.y = high_byte(sball.y);
	if(lives<4){
	Generic.width = HERO_WIDTH_SMALL;
	Generic.height = HERO_HEIGHT_SMALL;
	}
	else{
		Generic.width = HERO_WIDTH;
	Generic.height = HERO_HEIGHT;
	}
	for(index = 0; index < MAX_MOUNDS; ++index){
		if(mound_active[index]){
			if(spr_type[index] == MOUNDS){
				Generic2.width = mound_WIDTH;
				Generic2.height = mound_HEIGHT;
			}
			else{
				Generic2.width = END_WIDTH;
				Generic2.height = END_HEIGHT;
			}
			Generic2.x = mound_x[index];
			Generic2.y = mound_y[index];
			if(check_collision(&Generic, &Generic2)){
				mound_y[index] = TURN_OFF;
				++lives;
				sfx_play(SFX_DING, 0);
				;
				
				if(spr_type[index] == END){ changemode++;}
			}
		}
	}

	Generic2.width = ENEMY_WIDTH;
	Generic2.height = ENEMY_HEIGHT;
	
	for(index = 0; index < MAX_ENEMY; ++index){
		if(enemy_active[index]){
			Generic2.x = enemy_x[index];
			Generic2.y = enemy_y[index];
			if(check_collision(&Generic, &Generic2)){
				enemy_y[index] = TURN_OFF;
				enemy_active[index] = 0;
				lives = lives -1;
				sfx_play(SFX_DING,0);
				
			}
		}
	}
}







void main (void) {
	
	show_title_screen();
		music_play(0);
		ppu_off();
		
		lives = 3;
		
		pal_bg(palette_bg);
		pal_spr(palette_sp);
		
		bank_spr(1);
	
		set_vram_buffer(); // do at least once, sets a pointer to a buffer
		clear_vram_buffer();
	
		
		scroll_y = 0xff;
		set_scroll_y(scroll_y); // shift the bg down 1 pixel
	
		ppu_on_all();
		
	while(1){
		
		while(mode == TITLE)
		{
			ppu_wait_nmi(); // wait till beginning of the frame
		
			pad1 = pad_poll(0); // read the first controller
		if(pad1 & PAD_START){
				
		   ppu_off();
			load_room();
			mode = PLAY;
			
			
				music_play(1);
			
			// set scroll
			set_scroll_x(scroll_x);
			set_scroll_y(scroll_y);
			ppu_on_all();
		
				
				
			}
			
			
		}
		while(mode==PLAY){
			
			ppu_wait_nmi();
			set_music_speed(8);
			pad1 = pad_poll(0);
			clear_vram_buffer();
			movement();
			check_spr_objects();
			sprite_collisions();
			skier_move();
			set_scroll_x(scroll_x);
			set_scroll_y(scroll_y);
			draw_screen_R();
			draw_sprites();
			if(lives == 0){
			mode = SWITCH;
			}
			if(changemode){
				mode = SWITCH;
				changemode =0;
				
			}
			
		}
		
		
		while(mode ==SWITCH){
			ppu_wait_nmi();
			set_scroll_x(scroll_x);
			
			mode = FINISH;
			vram_adr(NAMETABLE_A);
			vram_fill(0,1024);
			ppu_on_all();
			
			
			
		}
		
		while(mode == FINISH){
			ppu_wait_nmi();
			
			
			
			if(lives>4){
			show_win_screen();
			}
			else{show_lose_screen();}
		}
		
		
		//break;
	}
}