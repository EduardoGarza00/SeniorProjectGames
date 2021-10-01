void movement(void){
	if(pad1 & PAD_LEFT) {
		Snake1.x -= 1;
		Snake1.head_sprite = SNAKE_HEAD_TILE_LEFT;
		Snake1.body = SNAKE_BODY_HORZ;
	}
	else if (pad1 & PAD_RIGHT){
		Snake1.x += 1;
		Snake1.head_sprite = SNAKE_HEAD_TILE_RIGHT;
		Snake1.body = SNAKE_BODY_HORZ;
	}
	if(pad1 & PAD_UP){
		Snake1.y -= 1;
		Snake1.head_sprite=SNAKE_HEAD_TILE_UP;
		Snake1.body = SNAKE_BODY_VERT;
	}
	else if (pad1 & PAD_DOWN){
		Snake1.y += 1;
		Snake1.head_sprite=SNAKE_HEAD_TILE_DOWN;
		Snake1.body = SNAKE_BODY_VERT;
	}
}
unsigned char test_eating(void){
	collision = check_collision(&Snake1, &mouse1);
	if(collision){
		mouse1.eaten =1;
		mouse1.respawn = 1;
		Snake1.ate = 1;
		Snake1.size = Snake1.size+1;
		return 1;
	}
	return 0;
}