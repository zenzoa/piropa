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

uint8_t hand_sprite_bank;
metasprite_t** hand_metasprites;

#define HAND_VRAM_1 0x50
#define HAND_VRAM_2 0x80
uint8_t hand_vram = HAND_VRAM_1;

void swap_hand_vram(void) {
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

		case HAND_POINT:
			hand_sprite_bank = BANK(hand_point);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_point_TILE_COUNT, hand_point_tiles);
			hand_metasprites = hand_point_metasprites;
			break;

		case HAND_PET1:
			hand_sprite_bank = BANK(hand_pet1);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_pet1_TILE_COUNT, hand_pet1_tiles);
			hand_metasprites = hand_pet1_metasprites;
			break;

		case HAND_PET2:
			hand_sprite_bank = BANK(hand_pet2);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_pet2_TILE_COUNT, hand_pet2_tiles);
			hand_metasprites = hand_pet2_metasprites;
			break;

		case HAND_MEDICINE:
			hand_sprite_bank = BANK(hand_medicine);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_medicine_TILE_COUNT, hand_medicine_tiles);
			hand_metasprites = hand_medicine_metasprites;
			break;

		case HAND_MEDICINE_USE:
			hand_sprite_bank = BANK(hand_medicine_use);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_medicine_use_TILE_COUNT, hand_medicine_use_tiles);
			hand_metasprites = hand_medicine_use_metasprites;
			break;

		case HAND_SOAP:
			hand_sprite_bank = BANK(hand_soap);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_soap_TILE_COUNT, hand_soap_tiles);
			hand_metasprites = hand_soap_metasprites;
			break;

		case HAND_SOAP_USE:
			hand_sprite_bank = BANK(hand_soap_use);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_soap_use_TILE_COUNT, hand_soap_use_tiles);
			hand_metasprites = hand_soap_use_metasprites;
			break;

		case HAND_BROOM:
			hand_sprite_bank = BANK(hand_broom);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_broom_TILE_COUNT, hand_broom_tiles);
			hand_metasprites = hand_broom_metasprites;
			break;

		case HAND_BROOM_USE:
			hand_sprite_bank = BANK(hand_broom_use);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_broom_use_TILE_COUNT, hand_broom_use_tiles);
			hand_metasprites = hand_broom_use_metasprites;
			break;

		case HAND_MOON:
			hand_sprite_bank = BANK(hand_moon);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_moon_TILE_COUNT, hand_moon_tiles);
			hand_metasprites = hand_moon_metasprites;
			break;

		case HAND_FLY:
			hand_sprite_bank = BANK(hand_fly);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_fly_TILE_COUNT, hand_fly_tiles);
			hand_metasprites = hand_fly_metasprites;
			break;

		case HAND_DRAGONFLY:
			hand_sprite_bank = BANK(hand_dragonfly);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_dragonfly_TILE_COUNT, hand_dragonfly_tiles);
			hand_metasprites = hand_dragonfly_metasprites;
			break;

		case HAND_FIREFLY:
			hand_sprite_bank = BANK(hand_firefly);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_firefly_TILE_COUNT, hand_firefly_tiles);
			hand_metasprites = hand_firefly_metasprites;
			break;

		case HAND_BUTTERFLY:
			hand_sprite_bank = BANK(hand_butterfly);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_butterfly_TILE_COUNT, hand_butterfly_tiles);
			hand_metasprites = hand_butterfly_metasprites;
			break;

	}

	SWITCH_ROM(saved_bank);
}

void draw_hand_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite) {
	uint8_t saved_bank = _current_bank;

	SWITCH_ROM(hand_sprite_bank);
	*last_sprite += move_metasprite_ex(hand_metasprites[frame], hand_vram, 0, *last_sprite, x, y);

	SWITCH_ROM(saved_bank);
}
