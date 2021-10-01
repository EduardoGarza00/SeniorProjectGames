#define SNAKE_MAX_SIZE	35
struct Snake {
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
	unsigned char moving_dir;
	unsigned char head_sprite;
	unsigned char head_sprite_attribute;
	unsigned char ate;
	unsigned char size;
	unsigned char lastx;
	unsigned char body;
	unsigned char bodyx;
	unsigned char bodyy;
	unsigned char lasty;
	unsigned char body_coor[SNAKE_MAX_SIZE <<1];
};

struct mouse{
unsigned char mouse_x;
unsigned char mouse_y;
unsigned char width;
unsigned char height;
unsigned char mouse_dx;
unsigned char mouse_dy;
unsigned char moving_dir;
unsigned char mouse_spr;
unsigned char sprite_att;
unsigned char eaten;
unsigned char respawn;
unsigned char bounced;
};