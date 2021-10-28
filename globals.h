#define MAX_ROOMS (2-1)
#define MAX_SCROLL (MAX_ROOMS*0x100)-1
#define GRAVITY 0x50
#define COL_DOWN 0x80
#define COL_ALL 0x40
#define ACCEL 0x30
#define MAX_SPEED 0x240
#define JUMP_VEL -0x600
#define MAX_RIGHT 0x9000
#define LEFT 0
#define RIGHT 1
unsigned char map_loaded;
unsigned char level;
int address;
unsigned char map;
unsigned char room;
unsigned char direction;
unsigned char x; 
unsigned char prevx;
unsigned char y;
unsigned char pad1;
unsigned char i,j,k;
unsigned char collision;
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;
unsigned char coordinates;
unsigned char temp_x, temp_y;
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;
unsigned char temp4;
unsigned char L_R_switch;
unsigned char old_x;
unsigned int temp5;
unsigned int temp6;
unsigned int temp7;
unsigned int temp8;
unsigned char eject_L; // from the left
unsigned char eject_R; // remember these from the collision sub routine
unsigned char eject_D; // from below
unsigned char eject_U;
unsigned char index;
unsigned int scroll_x;
unsigned int scroll_y;
unsigned char scroll_count; 
unsigned int pseudo_scroll_x; 
unsigned char nt; 
unsigned char offset;
unsigned char temp1; 
unsigned char c_map[240];
unsigned char c_map2[240];
const unsigned char * const bodies[]= {
	runlb,runmid,runrf
};

const unsigned char * const Rooms[]= {
	Room1, Room2
};
const unsigned char * const brotate[]={
ball1, ball2, ball3, ball4
};
const unsigned char Level_offsets[]={
	0,1
};