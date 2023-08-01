#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "sprites/hand/hand_default.h"
#include "sprites/hand/hand_open.h"

#define HAND_DEFAULT 0
#define HAND_OPEN 1

uint8_t hand_sprite_bank;
metasprite_t** hand_metasprites;

#define HAND_VRAM_1 0x40
#define HAND_VRAM_2 0x70
uint8_t hand_vram = HAND_VRAM_1;

void swap_hand_vram() {
	if (hand_vram == HAND_VRAM_1) {
		hand_vram = HAND_VRAM_2;
	} else {
		hand_vram = HAND_VRAM_1;
	}
}

void set_hand_sprite_data(uint8_t hand_state) {
	uint8_t saved_bank = _current_bank;

	switch(hand_state) {

		case HAND_DEFAULT:
			hand_sprite_bank = BANK(hand_default);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_default_TILE_COUNT, hand_default_tiles);
			hand_metasprites = hand_default_metasprites;
			break;

		case HAND_OPEN:
			hand_sprite_bank = BANK(hand_open);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_open_TILE_COUNT, hand_open_tiles);
			hand_metasprites = hand_open_metasprites;
			break;

	}

	SWITCH_ROM(saved_bank);
}

void draw_hand_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite) {
	uint8_t saved_bank = _current_bank;

	SWITCH_ROM(hand_sprite_bank);
	*last_sprite += move_metasprite(hand_metasprites[frame], hand_vram, *last_sprite, x, y);

	SWITCH_ROM(saved_bank);
}
