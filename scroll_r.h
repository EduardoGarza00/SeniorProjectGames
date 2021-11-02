#define SPEED 0x180
#define MAX_RIGHT 0xb000



#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
unsigned char mounds;
const unsigned char * pointer;
unsigned char game = 0;
unsigned char lives;
unsigned char game_end = 0;
unsigned char win, lose;
unsigned char pad1;
unsigned char collision;
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;
unsigned char coordinates;
unsigned char changemode;
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;
unsigned char temp4;
unsigned int temp5;
unsigned int temp6;
unsigned char temp_x;
unsigned char temp_y;
unsigned char eject_L; // from the left
unsigned char eject_R; // remember these from the collision sub routine
unsigned char eject_D; // from below
unsigned char eject_U; // from up
unsigned char direction; //facing left or right?
unsigned char song;
#define MAX_SONGS 2
enum {SONG_GAME, SONG_PAUSE};
enum {SFX_JUMP, SFX_DING, SFX_NOISE};
#define LEFT 0
#define RIGHT 1
unsigned char mode;
enum {TITLE,PLAY, FINISH, SWITCH};
int address;
unsigned char x; // room loader code
unsigned char y,k,i;
unsigned char nt;
unsigned char index;
unsigned char index2;
unsigned char room;
unsigned char map;
unsigned int scroll_x;
unsigned int scroll_y;
unsigned char scroll_count; 
unsigned int pseudo_scroll_x; 
//unsigned int pseudo_scroll_y;
unsigned char L_R_switch;
unsigned int old_x;
unsigned int old_y;





#pragma bss-name(push, "BSS")

unsigned char c_map[240];
unsigned char c_map2[240];

struct Base {
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
};

struct Base Generic; 
struct Base Generic2; 
struct enemySkier {
	unsigned int x; // low byte is sub-pixel
	unsigned int y;
	signed int vel_x; // speed, signed, low byte is sub-pixel
	signed int vel_y;
};

struct Ball {
	unsigned int x; // low byte is sub-pixel
	unsigned int y;
	signed int vel_x; // speed, signed, handle gravity
	signed int vel_y;
	unsigned int size;
	
};


struct Ball sball = {0x4000,0x7100};

const unsigned char * const brotate[]={
ball1, ball2, ball3, ball4
};
const unsigned char * const bigbrotate[]={
	bigball1, bigball2, bigball3,bigball4
};

struct enemySkier BoxGuy1 = {0x4000,0x6100}; // starting position
// the width and height should be 1 less than the dimensions (14x14)
// note, I'm using the top left as the 0,0 on x,y

#define HERO_WIDTH 5
#define HERO_HEIGHT 5
#define HERO_HEIGHT_SMALL 1
#define HERO_WIDTH_SMALL 2




const unsigned char palettetitle[16]={ 0x0f,0x01,0x21,0x31,0x0f,0x06,0x16,0x26,0x0f,0x07,0x19,0x29 };

const unsigned char palette_bg[]={
0x0f, 0x00, 0x10, 0x30, // black, gray, lt gray, white
0x0f, 0x07, 0x17, 0x27, // oranges
0x0f, 0x02, 0x12, 0x22, // blues
0x0f, 0x09, 0x19, 0x29, // greens
}; 

const unsigned char palette_sp[]={
0x0f, 0x07, 0x28, 0x38, // dk brown, yellow, white yellow
0,0,0,0,
0,0,0,0,
0,0,0,0
}; 
const unsigned char enemypal[]={
0x0f, 0x06, 0x16, 0x26, 
0,0,0,0,
0,0,0,0,
0,0,0,0
};

const unsigned char paletter[16]={ 0x0f,0x00,0x10,0x30,0x0f,0x01,0x21,0x30,0x0f,0x07,0x16,0x26,0x0f,0x09,0x19,0x29 };
const unsigned char winpal[16]={ 0x0f,0x00,0x10,0x30,0x0f,0x01,0x21,0x31,0x0f,0x06,0x16,0x26,0x0f,0x05,0x0c,0x28 };
const unsigned char losepal[16]={ 0x0f,0x00,0x10,0x30,0x0f,0x01,0x21,0x31,0x0f,0x06,0x16,0x26,0x0f,0x05,0x0c,0x28 };
// 5 bytes per metatile definition, tile TL, TR, BL, BR, palette 0-3
// T means top, B means bottom, L left,R right
// 51 maximum # of metatiles = 255 bytes

const unsigned char metatiles1[]={
	2, 2, 2, 2,  3,
	4, 4, 4, 4,  1,
	9, 9, 9, 9,  2,
	5, 6, 8, 7,  1,
	5, 6, 8, 7,  0
};

const unsigned char metatiles3[]={
	2, 2, 2, 2,  1,
	1, 1, 1, 1,  3,
	3, 3, 3, 3,  1,
	1, 1, 1, 1,  2
};

#include "BG/room1.c"
#include "BG/room2.c"
#include "BG/room3.c"
#include "BG/room4.c"
#include "BG/room5.c"
#include "BG/room6.c"
#include "BG/TitleScreen.h"
#include "BG/winscreen.h"
#include "BG/losescreen.h"
#define MAX_ROOMS (6-1)
#define MAX_SCROLL (MAX_ROOMS*0x100)-1
// data is exactly 240 bytes, 16 * 15
// doubles as the collision map data


const unsigned char * const Rooms[]= {
	room1, room2, room3, room4, room5,room6
};
#define MAX_MOUNDS 16
unsigned char mound_x[MAX_MOUNDS];
unsigned char mound_y[MAX_MOUNDS];
unsigned char mound_active[MAX_MOUNDS];
unsigned char mound_room[MAX_MOUNDS];
unsigned char mound_actual_x[MAX_MOUNDS];
unsigned char spr_type[MAX_MOUNDS];

#define TURN_OFF 0xff
#define mound_WIDTH 7
#define mound_HEIGHT 11
#define END_HEIGHT 100
#define END_WIDTH 100



enum{MOUNDS, END};
const unsigned char level_1_mounds[]={
	0x61,0,0x65,MOUNDS,
	0x81,1,0x85,MOUNDS,
	0x61,2,0x95,MOUNDS,
	0x61,3,0x75,MOUNDS,
	0x81,4,0x85,MOUNDS,
	0x61,5,0x125,MOUNDS,
	0x70,5,0x70,END,
	TURN_OFF
};


#define MAX_ENEMY 17
unsigned char enemy_x[MAX_ENEMY];
unsigned char enemy_y[MAX_ENEMY];
unsigned char enemy_active[MAX_ENEMY];
unsigned char enemy_room[MAX_ENEMY];
unsigned char enemy_actual_y[MAX_ENEMY];
unsigned char enemy_actual_x[MAX_ENEMY];
#define ENEMY_WIDTH 13
#define ENEMY_HEIGHT 13
const unsigned char level_1_enemies[]={
	0xc2,0,0xb0,
	
	0xc2,2,0xc0,
	0xc2,3,0xf0,
	TURN_OFF
};

// PROTOTYPES
void load_room(void);
void draw_sprites(void);
void movement(void);	
void bg_collision(void);
void draw_screen_R(void);
void new_cmap(void);
void bg_collision_sub(void);
void show_title_screen(void);
void show_win_screen(void);
void show_lose_screen(void);
void check_spr_objects(void);
char get_position(void);
void sprite_obj_init(void);
void skier_move(void);