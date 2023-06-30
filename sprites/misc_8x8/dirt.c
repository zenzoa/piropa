#pragma bank 255

//AUTOGENERATED FILE FROM png2asset

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

BANKREF(dirt)

const palette_color_t dirt_palettes[4] = {
	RGB8(  0,  0,  0), RGB8(226,223,177), RGB8(176,184,127), RGB8( 68, 68, 41)
	
};

const uint8_t dirt_tiles[64] = {
	0x80,0x80,0x27,0xa7,
	0x08,0x2f,0x40,0x48,
	0x38,0x78,0x44,0x7c,
	0x00,0x44,0x00,0x00,
	
0x01,0x01,0x08,0x09,
	0x86,0x8e,0x39,0xbf,
	0x44,0x7d,0x00,0x44,
	0x00,0x00,0x00,0x00,
	
0x40,0x40,0x0e,0x4e,
	0x11,0x1f,0x80,0x91,
	0x1c,0x9c,0x22,0x3e,
	0x00,0x22,0x00,0x00,
	
0x04,0x04,0x40,0x44,
	0x06,0x46,0x71,0x7f,
	0x88,0xf9,0x00,0x88,
	0x00,0x00,0x00,0x00
	
};

const metasprite_t dirt_metasprite0[] = {
	METASPR_ITEM(-4, -4, 0, 0), METASPR_TERM
};

const metasprite_t dirt_metasprite1[] = {
	METASPR_ITEM(-4, -4, 1, 0), METASPR_TERM
};

const metasprite_t dirt_metasprite2[] = {
	METASPR_ITEM(-4, -4, 2, 0), METASPR_TERM
};

const metasprite_t dirt_metasprite3[] = {
	METASPR_ITEM(-4, -4, 3, 0), METASPR_TERM
};

const metasprite_t* const dirt_metasprites[4] = {
	dirt_metasprite0, dirt_metasprite1, dirt_metasprite2, dirt_metasprite3
};