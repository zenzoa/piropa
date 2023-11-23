#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "common.h"

#include "sprites/hand/hand_default.h"
#include "sprites/hand/hand_point.h"
#include "sprites/hand/hand_pet1.h"
#include "sprites/hand/hand_pet2.h"
#include "sprites/hand/hand_medicine.h"
#include "sprites/hand/hand_medicine_use.h"
#include "sprites/hand/hand_soap.h"
#include "sprites/hand/hand_soap_use.h"
#include "sprites/hand/hand_broom.h"
#include "sprites/hand/hand_broom_use.h"
#include "sprites/hand/hand_moon.h"
#include "sprites/hand/hand_fly.h"
#include "sprites/hand/hand_dragonfly.h"
#include "sprites/hand/hand_firefly.h"
#include "sprites/hand/hand_butterfly.h"

#define HAND_TILE_COUNT 48

static const metasprite_t hand_metasprite0[] = {
	METASPR_ITEM(0, 0, 0x00, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x01, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x02, S_PAL(0)),
	METASPR_ITEM(8, -16, 0x18, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x19, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x1a, S_PAL(0)),
	METASPR_TERM
};

static const metasprite_t hand_metasprite1[] = {
	METASPR_ITEM(0, 0, 0x03, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x04, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x05, S_PAL(0)),
	METASPR_ITEM(8, -16, 0x1b, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x1c, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x1d, S_PAL(0)),
	METASPR_TERM
};

static const metasprite_t hand_metasprite2[] = {
	METASPR_ITEM(0, 0, 0x06, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x07, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x08, S_PAL(0)),
	METASPR_ITEM(8, -16, 0x1e, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x1f, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x20, S_PAL(0)),
	METASPR_TERM
};

static const metasprite_t hand_metasprite3[] = {
	METASPR_ITEM(0, 0, 0x09, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x0a, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x0b, S_PAL(0)),
	METASPR_ITEM(8, -16, 0x21, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x22, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x23, S_PAL(0)),
	METASPR_TERM
};

static const metasprite_t hand_metasprite4[] = {
	METASPR_ITEM(0, 0, 0x0c, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x0d, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x0e, S_PAL(0)),
	METASPR_ITEM(8, -16, 0x24, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x25, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x26, S_PAL(0)),
	METASPR_TERM
};

static const metasprite_t hand_metasprite5[] = {
	METASPR_ITEM(0, 0, 0x0f, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x10, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x11, S_PAL(0)),
	METASPR_ITEM(8, -16, 0x27, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x28, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x29, S_PAL(0)),
	METASPR_TERM
};

static const metasprite_t hand_metasprite6[] = {
	METASPR_ITEM(0, 0, 0x12, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x13, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x14, S_PAL(0)),
	METASPR_ITEM(8, -16, 0x2a, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x2b, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x2c, S_PAL(0)),
	METASPR_TERM
};

static const metasprite_t hand_metasprite7[] = {
	METASPR_ITEM(0, 0, 0x15, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x16, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x17, S_PAL(0)),
	METASPR_ITEM(8, -16, 0x2d, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x2e, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x2f, S_PAL(0)),
	METASPR_TERM
};

static const metasprite_t* const hand_metasprites[8] = { hand_metasprite0, hand_metasprite1, hand_metasprite2, hand_metasprite3, hand_metasprite4, hand_metasprite5, hand_metasprite6, hand_metasprite7 };

const sprite_data_t hand_sprite_table[15] = {
	{ BANK(hand_default), HAND_TILE_COUNT, (uint8_t *)hand_default_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_point), HAND_TILE_COUNT, (uint8_t *)hand_point_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_pet1), HAND_TILE_COUNT, (uint8_t *)hand_pet1_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_pet2), HAND_TILE_COUNT, (uint8_t *)hand_pet2_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_medicine), HAND_TILE_COUNT, (uint8_t *)hand_medicine_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_medicine_use), HAND_TILE_COUNT, (uint8_t *)hand_medicine_use_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_soap), HAND_TILE_COUNT, (uint8_t *)hand_soap_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_soap_use), HAND_TILE_COUNT, (uint8_t *)hand_soap_use_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_broom), HAND_TILE_COUNT, (uint8_t *)hand_broom_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_broom_use), HAND_TILE_COUNT, (uint8_t *)hand_broom_use_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_moon), HAND_TILE_COUNT, (uint8_t *)hand_moon_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_fly), HAND_TILE_COUNT, (uint8_t *)hand_fly_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_dragonfly), HAND_TILE_COUNT, (uint8_t *)hand_dragonfly_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_firefly), HAND_TILE_COUNT, (uint8_t *)hand_firefly_tiles, (uint8_t *)hand_metasprites },
	{ BANK(hand_butterfly), HAND_TILE_COUNT, (uint8_t *)hand_butterfly_tiles, (uint8_t *)hand_metasprites }
};
