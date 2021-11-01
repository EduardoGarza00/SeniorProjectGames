// a 16x16 pixel metasprite

const unsigned char RoundSprL[]={
	  0xff,  0xff,0x02,0,
	  7,  0xff,0x03,0,
	  0xff,  7,0x12,0,
	  7,  7,0x13,0,
	128
};


const unsigned char RoundSprR[]={
	  0xff,  0xff,0x00,0,
	  7,  0xff,0x01,0,
	  0xff,  7,0x10,0,
	  7,  7,0x11,0,
	128
};



const unsigned char ball1[]={
	-15,-12,0x10,0,
	128
};
const unsigned char ball2[]={
	- 15,-12,0x11,0,
	128
};

const unsigned char ball3[]={
	  -15,- 12,0x12,0,
	128
};
const unsigned char ball4[]={
	 -15, -12,0x13,0,
	128
};

const unsigned char bigball1[]={
	- 8,- 8,0x20,0,
	  0,- 8,0x21,0,
	  0,  0,0x31,0,
	- 8,  0,0x30,0,
	128
};

const unsigned char bigball2[]={
	  0,- 8,0x20,0|OAM_FLIP_H,
	- 8,- 8,0x21,0|OAM_FLIP_H,
	- 8,  0,0x31,0|OAM_FLIP_H,
	  0,  0,0x30,0|OAM_FLIP_H,
	128
};

const unsigned char bigball3[]={
	  0,  0,0x20,0|OAM_FLIP_H|OAM_FLIP_V,
	- 8,  0,0x21,0|OAM_FLIP_H|OAM_FLIP_V,
	- 8,- 8,0x31,0|OAM_FLIP_H|OAM_FLIP_V,
	  0,- 8,0x30,0|OAM_FLIP_H|OAM_FLIP_V,
	128
};

const unsigned char bigball4[]={
	- 8,  0,0x20,0|OAM_FLIP_V,
	  0,  0,0x21,0|OAM_FLIP_V,
	  0,- 8,0x31,0|OAM_FLIP_V,
	- 8,- 8,0x30,0|OAM_FLIP_V,
	128
};

const unsigned char mound[]={
	- 8,  0,0x14,0,
	128
};

const unsigned char endSprite[]={
	  0,-16,0x1b,1,
	  0,- 8,0x1b,1,
	  0,  0,0x1b,1,
	128
};


const unsigned char skier[]={
	- 8,- 8,0x15,0,
	  0,- 8,0x16,0,
	- 8,  0,0x18,0,
	  0,  0,0x19,0,
	128
};
 

