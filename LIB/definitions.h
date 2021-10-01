#define SNAKE_HEAD_TILE_UP 	0x01
/** Tile of horizontal snake head element */
#define SNAKE_HEAD_TILE_DOWN 	0x02
/** Tile of snake body element */
#define SNAKE_HEAD_TILE_LEFT 	0x00
/** Tile of horizontal snake head element */
#define SNAKE_HEAD_TILE_RIGHT	0x03
/** Tile of snake body element */
/** Tile of horizontal snake head element */
#define SNAKE_BODY_VERT 	0x05
/** Tile of snake body element */
#define SNAKE_BODY_HORZ		0x04
#define MOUSE_LEFT          0x07
#define MOUSE_RIGHT       0x06
#define SPRITE_ATTR(flip_horz,flip_vert,prio,pal) ((flip_horz<<7) + (flip_vert<<6) + (prio<<5) + pal)
#define MAX_NUM	                64
#define MAPARRAY_ADR(x,y)	((y<<2)|(x>>3))
#define SNAKE_EMPTY          0x16           //check this after merging code to make sure it is still empty tile
