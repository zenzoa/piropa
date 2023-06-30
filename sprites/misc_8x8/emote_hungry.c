#pragma bank 255

//AUTOGENERATED FILE FROM png2asset

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

BANKREF(emote_hungry)

const palette_color_t emote_hungry_palettes[4] = {
	RGB8(  0,  0,  0), RGB8(226,223,177), RGB8(176,184,127), RGB8( 68, 68, 41)
	
};

const uint8_t emote_hungry_tiles[32] = {
	0x00,0x00,0x00,0x00,
	0x0c,0x08,0x78,0x70,
	0x76,0x44,0x4e,0x0c,
	0x0c,0x08,0x08,0x00,
	
0x60,0x60,0x70,0x30,
	0x30,0x00,0x06,0x04,
	0x3c,0x38,0x38,0x20,
	0x20,0x00,0x00,0x00
	
};

const metasprite_t emote_hungry_metasprite0[] = {
	METASPR_ITEM(-4, -4, 0, 0), METASPR_TERM
};

const metasprite_t emote_hungry_metasprite1[] = {
	METASPR_ITEM(-4, -4, 1, 0), METASPR_TERM
};

const metasprite_t* const emote_hungry_metasprites[2] = {
	emote_hungry_metasprite0, emote_hungry_metasprite1
};