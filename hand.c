#include <gbdk/metasprites.h>

#include "sprites/hand.h"

#define HAND_SPRITE 0

uint16_t hand_x = 60 << 8;
uint16_t hand_y = 60 << 8;

void init_hand();
void draw_hand(uint8_t *last_used_sprite);
void move_hand(int16_t dx, int16_t dy);

/* ========================================================================= */

void init_hand() {
	set_sprite_data(HAND_SPRITE, hand_TILE_COUNT, hand_tiles);
}

void move_hand(int16_t dx, int16_t dy) {
	hand_x += dx;
	hand_y += dy;
	if (hand_y < 6144) { // 24 -> Q8.8
		hand_y = 6144;
	} else if (hand_y > 38912) { // 152 -> Q8.8
		hand_y = 38912;
	}
	if (hand_x < 2048) { // 8 -> Q8.8
		hand_x = 2048;
		// TODO: move to pond
	} else if (hand_x > 43008) { // 168 -> Q8.8
		hand_x = 43008;
		// TODO: move to garden
	}
}

void draw_hand(uint8_t *last_used_sprite) {
	*last_used_sprite += move_metasprite(hand_metasprites[0], HAND_SPRITE, *last_used_sprite, hand_x >> 8, hand_y >> 8);
	hide_sprites_range(*last_used_sprite, MAX_HARDWARE_SPRITES);
}
