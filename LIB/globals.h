// GLOBAL VARIABLES
unsigned char pad1;
unsigned char pad2;
unsigned char i,j,l,k;
unsigned char collision, collision_body;
static unsigned char spr;
int address;
unsigned char x; 
unsigned char y;
unsigned char index;
unsigned char map;
unsigned char c_map[522];
struct Snake Snake1 = {20,20,5,5};
struct mouse mouse1= {80,20,0, 0x07, 0};
static unsigned char snakeVram[SNAKE_MAX_SIZE * 3 + 1];
static unsigned char updateListData[11]={
0x53,0x63,0x6f,
0x72,0x65,0x3a,
0x30,0x30,0x30,0x30,0x30
};
static unsigned char lives[10]={
	0x00,
	0x4c,0x69,0x76,
	0x65,0x73,0x3a,
	0x9d,0x9d,0x9d
};

