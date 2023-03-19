#include <gbdk/metasprites.h>

#include "sprites/hand/hand_normal.h"
#include "sprites/hand/hand_tickle_1.h"
#include "sprites/hand/hand_tickle_2.h"
#include "sprites/hand/hand_jar_empty.h"
#include "sprites/hand/hand_jar_empty_tip.h"
#include "sprites/hand/hand_jar_full.h"
#include "sprites/hand/hand_jar_full_tip.h"
#include "sprites/hand/hand_jar_2_3.h"
#include "sprites/hand/hand_jar_2_3_tip.h"
#include "sprites/hand/hand_jar_1_3.h"
#include "sprites/hand/hand_jar_1_3_tip.h"
#include "sprites/hand/hand_soap.h"
#include "sprites/hand/hand_moon.h"
#include "sprites/hand/hand_strawberry.h"
#include "sprites/hand/hand_blueberry.h"
#include "sprites/hand/hand_blackberry.h"

#define HAND_SPRITE 0

#define DEFAULT_HAND 0
#define TICKLE_1 1
#define TICKLE_2 2
#define JAR_EMPTY 3
#define JAR_EMPTY_TIP 4
#define JAR_FULL 5
#define JAR_FULL_TIP 6
#define JAR_2_3 7
#define JAR_2_3_TIP 8
#define JAR_1_3 9
#define JAR_1_3_TIP 10
#define HOLD_SOAP 11
#define HOLD_MOON 12
#define HOLD_STRAWBERRY 13
#define HOLD_BLUEBERRY 14
#define HOLD_BLACKBERRY 15

uint8_t hand_bank = BANK(hand_normal);
const metasprite_t** hand_metasprites;

uint8_t hand_type = DEFAULT_HAND;

uint16_t hand_x = 60 << 8;
uint16_t hand_y = 60 << 8;

uint8_t animating_hand = 0;
uint8_t jar_animation = 0;

void set_hand_type(uint8_t new_hand_type);

/* ========================================================================= */

void init_hand() {
	set_hand_type(DEFAULT_HAND);
}

void set_hand_type(uint8_t new_hand_type) NONBANKED {
	hand_type = new_hand_type;

	uint8_t old_bank = CURRENT_BANK;

	switch (hand_type) {
		case DEFAULT_HAND:
			hand_bank = BANK(hand_normal);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_normal_TILE_COUNT, hand_normal_tiles);
			hand_metasprites = hand_normal_metasprites;
			break;

		case TICKLE_1:
			hand_bank = BANK(hand_tickle_1);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_tickle_1_TILE_COUNT, hand_tickle_1_tiles);
			hand_metasprites = hand_tickle_1_metasprites;
			break;

		case TICKLE_2:
			hand_bank = BANK(hand_tickle_2);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_tickle_2_TILE_COUNT, hand_tickle_2_tiles);
			hand_metasprites = hand_tickle_2_metasprites;
			break;

		case JAR_EMPTY:
			hand_bank = BANK(hand_jar_empty);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_jar_empty_TILE_COUNT, hand_jar_empty_tiles);
			hand_metasprites = hand_jar_empty_metasprites;
			break;

		case JAR_EMPTY_TIP:
			hand_bank = BANK(hand_jar_empty_tip);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_jar_empty_tip_TILE_COUNT, hand_jar_empty_tip_tiles);
			hand_metasprites = hand_jar_empty_tip_metasprites;
			break;

		case JAR_FULL:
			hand_bank = BANK(hand_jar_full);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_jar_full_TILE_COUNT, hand_jar_full_tiles);
			hand_metasprites = hand_jar_full_metasprites;
			break;

		case JAR_FULL_TIP:
			hand_bank = BANK(hand_jar_full_tip);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_jar_full_tip_TILE_COUNT, hand_jar_full_tip_tiles);
			hand_metasprites = hand_jar_full_tip_metasprites;
			break;

		case JAR_2_3:
			hand_bank = BANK(hand_jar_2_3);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_jar_2_3_TILE_COUNT, hand_jar_2_3_tiles);
			hand_metasprites = hand_jar_2_3_metasprites;
			break;

		case JAR_2_3_TIP:
			hand_bank = BANK(hand_jar_2_3_tip);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_jar_2_3_tip_TILE_COUNT, hand_jar_2_3_tip_tiles);
			hand_metasprites = hand_jar_2_3_tip_metasprites;
			break;

		case JAR_1_3:
			hand_bank = BANK(hand_jar_1_3);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_jar_1_3_TILE_COUNT, hand_jar_1_3_tiles);
			hand_metasprites = hand_jar_1_3_metasprites;
			break;

		case JAR_1_3_TIP:
			hand_bank = BANK(hand_jar_1_3_tip);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_jar_1_3_tip_TILE_COUNT, hand_jar_1_3_tip_tiles);
			hand_metasprites = hand_jar_1_3_tip_metasprites;
			break;

		case HOLD_SOAP:
			hand_bank = BANK(hand_soap);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_soap_TILE_COUNT, hand_soap_tiles);
			hand_metasprites = hand_soap_metasprites;
			break;

		case HOLD_MOON:
			hand_bank = BANK(hand_moon);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_moon_TILE_COUNT, hand_moon_tiles);
			hand_metasprites = hand_moon_metasprites;
			break;

		case HOLD_STRAWBERRY:
			hand_bank = BANK(hand_strawberry);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_strawberry_TILE_COUNT, hand_strawberry_tiles);
			hand_metasprites = hand_strawberry_metasprites;
			break;

		case HOLD_BLUEBERRY:
			hand_bank = BANK(hand_blueberry);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_blueberry_TILE_COUNT, hand_blueberry_tiles);
			hand_metasprites = hand_blueberry_metasprites;
			break;

		case HOLD_BLACKBERRY:
			hand_bank = BANK(hand_blackberry);
			SWITCH_ROM(hand_bank);
			set_sprite_data(HAND_SPRITE, hand_blackberry_TILE_COUNT, hand_blackberry_tiles);
			hand_metasprites = hand_blackberry_metasprites;
			break;
	}

	SWITCH_ROM(old_bank);
}

void move_hand(int16_t dx, int16_t dy) {
	hand_x += dx;
	hand_y += dy;
	if (hand_y < 6144) { // 24 -> Q8.8
		hand_y = 6144;
	} else if (hand_y > 38912) { // 152 -> Q8.8
		hand_y = 38912;
	}
	if (hand_x < 4096) { // 16 -> Q8.8
		hand_x = 4096;
		// TODO: move to pond
	} else if (hand_x > 40960) { // 168 -> Q8.8
		hand_x = 40960;
		// TODO: move to garden
	}
}

void draw_hand(uint8_t *last_used_sprite, uint8_t frog_x) {
	uint8_t frog_left = frog_x - 16; // adjust for pivot to find left edge
	uint8_t hand_left = (hand_x >> 8) - 12;

	uint8_t hand_offset = 0;
	uint8_t frog_mod = frog_left % 8;
	uint8_t hand_mod = hand_left % 8;
	if (frog_mod > hand_mod) {
		hand_offset = (hand_mod + 8) - frog_mod;
	} else {
		hand_offset = hand_mod - frog_mod;
	}
	hand_left -= hand_offset;

	uint8_t old_bank = CURRENT_BANK;
	SWITCH_ROM(hand_bank);

	*last_used_sprite += move_metasprite(hand_metasprites[hand_offset], HAND_SPRITE, *last_used_sprite, hand_left + 12, hand_y >> 8);
	hide_sprites_range(*last_used_sprite, MAX_HARDWARE_SPRITES);

	SWITCH_ROM(old_bank);
}

void get_hand_position(uint8_t *x, uint8_t *y) {
	*x = (hand_x >> 8);
	*y = (hand_y >> 8);
}

void update_hand() {
	if (jar_animation == 2) {
		switch (hand_type) {
			case JAR_FULL_TIP:
				set_hand_type(JAR_2_3_TIP);
				break;

			case JAR_2_3_TIP:
				set_hand_type(JAR_1_3_TIP);
				break;

			case JAR_1_3_TIP:
				set_hand_type(JAR_EMPTY_TIP);
				break;

			case JAR_EMPTY_TIP:
				set_hand_type(JAR_EMPTY);
				break;
		}
	} else if (jar_animation == 1) {
		switch (hand_type) {
			case JAR_FULL_TIP:
				set_hand_type(JAR_FULL);
				break;

			case JAR_2_3_TIP:
				set_hand_type(JAR_2_3);
				break;

			case JAR_1_3_TIP:
				set_hand_type(JAR_1_3);
				break;

			case JAR_EMPTY_TIP:
				set_hand_type(JAR_EMPTY);
				break;
		}
		animating_hand = 0;
	}
	if (jar_animation > 0) {
		jar_animation--;
	}
}
