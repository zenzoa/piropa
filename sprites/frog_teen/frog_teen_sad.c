#pragma bank 255

//AUTOGENERATED FILE FROM png2asset

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

BANKREF(frog_teen_sad)

const palette_color_t frog_teen_sad_palettes[4] = {
	RGB8(101,255,  0), RGB8(224,248,207), RGB8(134,192,108), RGB8(  7, 24, 33)
	
};

const uint8_t frog_teen_sad_tiles[128] = {
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x3c,0x3c,
	0x7a,0x46,0xfd,0x83,
	
0x00,0x00,0x01,0x01,
	0x01,0x01,0x02,0x03,
	0x03,0x02,0x03,0x02,
	0x02,0x03,0x02,0x03,
	
0xff,0x84,0xf8,0x1f,
	0xe0,0x1f,0xff,0x01,
	0xfe,0x03,0xfd,0x02,
	0xff,0x00,0x7f,0x90,
	
0x02,0x03,0x01,0x01,
	0x01,0x01,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	
0x77,0xd8,0x20,0xff,
	0x00,0xff,0x80,0xff,
	0x7c,0x67,0x1f,0x1f,
	0x00,0x00,0x00,0x00,
	
0x00,0x00,0x01,0x01,
	0x01,0x01,0x02,0x03,
	0x03,0x02,0x03,0x02,
	0x03,0x02,0x02,0x03,
	
0xff,0x80,0xff,0x04,
	0xf8,0x1f,0xe0,0x1f,
	0xff,0x01,0xfe,0x03,
	0xff,0x00,0xff,0x00,
	
0x7f,0x90,0x77,0xd8,
	0x20,0xff,0x80,0xff,
	0x7c,0x67,0x1f,0x1f,
	0x00,0x00,0x00,0x00
	
};

const metasprite_t frog_teen_sad_metasprite0[] = {
	METASPR_ITEM(-8, -8, 0, 0), METASPR_ITEM(0, 8, 0, 32), METASPR_ITEM(8, -16, 1, 0), METASPR_ITEM(0, 8, 2, 0), METASPR_ITEM(0, 8, 2, 32), METASPR_ITEM(0, 8, 1, 32), METASPR_ITEM(8, -24, 3, 0), METASPR_ITEM(0, 8, 4, 0), METASPR_ITEM(0, 8, 4, 32), METASPR_ITEM(0, 8, 3, 32), METASPR_TERM
};

const metasprite_t frog_teen_sad_metasprite1[] = {
	METASPR_ITEM(-8, -8, 0, 0), METASPR_ITEM(0, 8, 0, 32), METASPR_ITEM(8, -16, 5, 0), METASPR_ITEM(0, 8, 6, 0), METASPR_ITEM(0, 8, 6, 32), METASPR_ITEM(0, 8, 5, 32), METASPR_ITEM(8, -24, 3, 0), METASPR_ITEM(0, 8, 7, 0), METASPR_ITEM(0, 8, 7, 32), METASPR_ITEM(0, 8, 3, 32), METASPR_TERM
};

const metasprite_t* const frog_teen_sad_metasprites[2] = {
	frog_teen_sad_metasprite0, frog_teen_sad_metasprite1
};