#pragma bank 255

//AUTOGENERATED FILE FROM png2asset

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

BANKREF(emote_happy)

const palette_color_t emote_happy_palettes[4] = {
	RGB8(  0,  0,  0), RGB8(226,223,177), RGB8(176,184,127), RGB8( 68, 68, 41)
	
};

const uint8_t emote_happy_tiles[32] = {
	0x18,0x10,0x7a,0x42,
	0x3e,0x18,0xff,0x25,
	0xff,0xa4,0x7c,0x18,
	0x5e,0x42,0x18,0x08,
	
0x00,0x00,0x38,0x28,
	0x3e,0x02,0x7e,0x58,
	0x7e,0x1a,0x7c,0x40,
	0x1c,0x14,0x00,0x00
	
};

const metasprite_t emote_happy_metasprite0[] = {
	METASPR_ITEM(0, 0, 0, 0), METASPR_TERM
};

const metasprite_t emote_happy_metasprite1[] = {
	METASPR_ITEM(0, 0, 1, 0), METASPR_TERM
};

const metasprite_t* const emote_happy_metasprites[2] = {
	emote_happy_metasprite0, emote_happy_metasprite1
};
