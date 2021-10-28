void load_room(void){
	offset = 0;
	
	set_data_pointer(Rooms[offset]);
	set_mt_pointer(metatiles1);
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
	
	
	++offset;
	
	// a little bit in the next room
	set_data_pointer(Rooms[offset]);
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
	
	--offset;
	// copy the room to the collision map
	// the second one should auto-load with the scrolling code
	memcpy (c_map, Rooms[offset], 240);
	
	
	
	sball.x = 0x4000;
	sball.y = 0xc400;
	sball.vel_x = 0;
	sball.vel_y = 0;
	
	map_loaded = 0;
}





void draw_sprites(void){
	
	oam_clear();
	temp_x = high_byte(sball.x);
	temp_y = high_byte(sball.y);
	
	//if(temp_x > 0) temp_x = 5;
	//if(temp_x == 0) temp_x = 5;
	
	oam_meta_spr(temp_x,temp_y,brotate[k]);	
}
void movement(void){
	
	old_x = sball.x;
	if(pad1 & PAD_LEFT) {
		
		sball.vel_x -= ACCEL;
		sball.x -=1;
		i++;
		
		scroll_x-=1;
		
		
		// direction = LEFT;
		// if(sball.x <= 0x100) {
			// sball.vel_x = 0;
			// sball.x = 0x100;
		// }
		// else if(sball.x < 0x400) { // don't want to wrap around to the other side
			// sball.vel_x = -0x100;
		// }
		// else {
			// sball.vel_x -= ACCEL;
			// if(sball.vel_x < -MAX_SPEED) sball.vel_x = -MAX_SPEED;
		// }
	}
	
	if (pad1 & PAD_RIGHT){
		sball.vel_x += ACCEL;
		sball.x +=1;
		i++;
		
		scroll_x+=1;
		
		if (k != 3 & i%7 ==0){
			k++;
		}
		else if(k==3){
		k=0;}
	}
	
	
	if(pad1 & PAD_UP){
		
		sball.y -=1;
		
		
	}
	else if (pad1 & PAD_DOWN){
		
		sball.y +=1;
		
	}
	
	
	
	
	
	
}	

void draw_screen_R(void){
	// scrolling to the right, draw metatiles as we go
	pseudo_scroll_x = scroll_x;
	
	temp1 = 1 ;
	
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
	scroll_count &= 3; //mask off top bits, keep it 0-3
}
