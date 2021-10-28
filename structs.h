struct Ball {
	unsigned int x; // low byte is sub-pixel
	unsigned int y;
	signed int vel_x; // speed, signed, handle gravity
	signed int vel_y;
	
};


struct Ball sball = {20,20};

struct Base {
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
};

struct Base Generic; 
struct Base Generic2; 

const unsigned char palette_sp[]={
0x0f, 0x2C, 0x0C, 0x31, 
0,0,0,0,
0,0,0,0,
0,0,0,0
}; 

const unsigned char is_solid[]={
	0,
	COL_DOWN,
	COL_ALL+COL_DOWN,
	COL_DOWN,
	COL_DOWN,
	COL_DOWN,
	0,
	0,
	0,
	0,
	0,
	0
};

void bg_check_low(void);
void bg_collision(void);
void bg_collision_sub(void);
void draw_sprites(void);