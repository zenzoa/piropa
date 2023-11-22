#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "shared_variables.h"

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

#define HAND_VRAM_1 0x50
#define HAND_VRAM_2 0x80
static uint8_t hand_vram = HAND_VRAM_1;

typedef struct hand_sprite_t {
	uint8_t bank;
	uint8_t tile_count;
	uint8_t * tiles;
	uint8_t * metasprites;
} hand_sprite_t;

static hand_sprite_t hand_sprite_data;
static const hand_sprite_t hand_sprite_data_table[15] = {
	{ BANK(hand_default), hand_default_TILE_COUNT, (uint8_t *)hand_default_tiles, (uint8_t *)hand_default_metasprites },
	{ BANK(hand_point), hand_point_TILE_COUNT, (uint8_t *)hand_point_tiles, (uint8_t *)hand_point_metasprites },
	{ BANK(hand_pet1), hand_pet1_TILE_COUNT, (uint8_t *)hand_pet1_tiles, (uint8_t *)hand_pet1_metasprites },
	{ BANK(hand_pet2), hand_pet2_TILE_COUNT, (uint8_t *)hand_pet2_tiles, (uint8_t *)hand_pet2_metasprites },
	{ BANK(hand_medicine), hand_medicine_TILE_COUNT, (uint8_t *)hand_medicine_tiles, (uint8_t *)hand_medicine_metasprites },
	{ BANK(hand_medicine_use), hand_medicine_use_TILE_COUNT, (uint8_t *)hand_medicine_use_tiles, (uint8_t *)hand_medicine_use_metasprites },
	{ BANK(hand_soap), hand_soap_TILE_COUNT, (uint8_t *)hand_soap_tiles, (uint8_t *)hand_soap_metasprites },
	{ BANK(hand_soap_use), hand_soap_use_TILE_COUNT, (uint8_t *)hand_soap_use_tiles, (uint8_t *)hand_soap_use_metasprites },
	{ BANK(hand_broom), hand_broom_TILE_COUNT, (uint8_t *)hand_broom_tiles, (uint8_t *)hand_broom_metasprites },
	{ BANK(hand_broom_use), hand_broom_use_TILE_COUNT, (uint8_t *)hand_broom_use_tiles, (uint8_t *)hand_broom_use_metasprites },
	{ BANK(hand_moon), hand_moon_TILE_COUNT, (uint8_t *)hand_moon_tiles, (uint8_t *)hand_moon_metasprites },
	{ BANK(hand_fly), hand_fly_TILE_COUNT, (uint8_t *)hand_fly_tiles, (uint8_t *)hand_fly_metasprites },
	{ BANK(hand_dragonfly), hand_dragonfly_TILE_COUNT, (uint8_t *)hand_dragonfly_tiles, (uint8_t *)hand_dragonfly_metasprites },
	{ BANK(hand_firefly), hand_firefly_TILE_COUNT, (uint8_t *)hand_firefly_tiles, (uint8_t *)hand_firefly_metasprites },
	{ BANK(hand_butterfly), hand_butterfly_TILE_COUNT, (uint8_t *)hand_butterfly_tiles, (uint8_t *)hand_butterfly_metasprites }
};

void swap_hand_vram(void) {
	if (hand_vram == HAND_VRAM_1) {
		hand_vram = HAND_VRAM_2;
	} else {
		hand_vram = HAND_VRAM_1;
	}
}

void set_hand_sprite_data(uint8_t hand_state) {
	saved_bank = _current_bank;

	hand_sprite_data = hand_sprite_data_table[hand_state];
	SWITCH_ROM(hand_sprite_data.bank);
	set_sprite_data(hand_vram, hand_sprite_data.tile_count, hand_sprite_data.tiles);

	SWITCH_ROM(saved_bank);
}

void draw_hand_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite) {
	uint8_t saved_bank = _current_bank;

	SWITCH_ROM(hand_sprite_data.bank);
	*last_sprite += move_metasprite_ex(
		((metasprite_t**)hand_sprite_data.metasprites)[frame],
		hand_vram, 0, *last_sprite,
		x, y
	);

	SWITCH_ROM(saved_bank);
}
