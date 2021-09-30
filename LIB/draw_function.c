void draw_mouse(void){
	if(mouse1.respawn =1){
		oam_spr(mouse1.mouse_x, mouse1.mouse_y, mouse1.mouse_spr,mouse1.sprite_att );
		

		 mouse1.mouse_x+=mouse1.mouse_dx;
		mouse1.mouse_y+=mouse1.mouse_dy;

		if(mouse1.mouse_x>=(256-8)) mouse1.mouse_dx=-mouse1.mouse_dx;
		if(mouse1.mouse_y>=(240-8)) mouse1.mouse_dy=-mouse1.mouse_dy;
	}
	mouse1.respawn =0;
}
	
void mouse_coord(void){
	mouse1.mouse_spr=MOUSE_LEFT;
	mouse1.mouse_x=rand8();
	mouse1.mouse_y=rand8();

	//direction bits
	j=rand8();

	//horizontal speed -3..-3, excluding 0
	spr=1+(rand8()%3);
	mouse1.mouse_dx=j&1?-spr:spr;

	//vertical speed
	spr=1+(rand8()%3);
	mouse1.mouse_dy=j&2?-spr:spr;
}

void draw_sprites(void){
	oam_clear();
	oam_spr(Snake1.x,Snake1.y,Snake1.head_sprite,Snake1.head_sprite_attribute);
}

void respawn_mouse(void){
	if (mouse1.respawn == 1){
		mouse_coord();
		mouse1.respawn =0;
		Snake1.ate =0;
	}	
}

void test1(void){
	if (test_eating()){
		mouse_coord();
	}
	respawn_mouse();
}
