#include <gbdk/metasprites.h>

#include "sprites/hand_normal.h"

#define HAND_SPRITE 0

#define DEFAULT_HAND 0
#define TICKLE_1 1
#define TICKLE_2 2
#define HOLD_JAR_EMPTY 3
#define HOLD_JAR_FULL 4
#define HOLD_JAR_2_3 5
#define HOLD_JAR_1_3 6
#define TIP_JAR_EMPTY 7
#define TIP_JAR_FULL 8
#define TIP_JAR_2_3 9
#define TIP_JAR_1_3 10
#define HOLD_SOAP 11
#define HOLD_MOON 12
#define HOLD_STRAWBERRY 13
#define HOLD_BLUEBERRY 14
#define HOLD_BLACKBERRY 15

const metasprite_t** hand_metasprites;

uint8_t hand_type = DEFAULT_HAND;
uint8_t hand_swap = 0;

uint16_t hand_x = 60 << 8;
uint16_t hand_y = 60 << 8;

/* ========================================================================= */

void init_hand() {
	set_sprite_data(HAND_SPRITE, hand_normal_TILE_COUNT, hand_normal_tiles);
	hand_metasprites = hand_normal_metasprites;
}

// void set_hand_type(uint8_t new_hand_type) {
// 	if (hand_swap == 0) {
// 		hand_swap = 45;
// 	} else {
// 		hand_swap = 0;
// 	}
// 	// switch new_hand_type
// 	// set_sprite_data(HAND_SPRITE + hand_swap, hand_normal_TILE_COUNT, hand_normal_tiles);
// 	// hand_metasprites = hand_normal_metasprites;
// 	// hand_type = new_hand_type;
// }

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

	*last_used_sprite += move_metasprite(hand_metasprites[hand_offset], HAND_SPRITE + hand_swap, *last_used_sprite, hand_left + 12, hand_y >> 8);
	hide_sprites_range(*last_used_sprite, MAX_HARDWARE_SPRITES);
}

void get_hand_position(uint8_t *x, uint8_t *y) {
	*x = (hand_x >> 8);
	*y = (hand_y >> 8);
}
