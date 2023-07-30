#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "hand_sprites.h"
#include "frog.h"

BANKREF(hand_bank)

uint8_t hand_x;
uint8_t hand_y;
uint16_t hand_x_frac;
uint16_t hand_y_frac;

uint8_t hand_offset;

void setup_hand() {
	hand_x = 50;
	hand_y = 50;
	hand_x_frac = hand_x << 8;
	hand_y_frac = hand_y << 8;
	set_hand_sprite_data(HAND_DEFAULT);
}

void draw_hand(uint8_t *last_sprite, uint8_t frog_x) {
	hand_offset = 0;
	uint8_t frog_mod = frog_x % 8;
	uint8_t hand_mod = hand_x % 8;
	if (frog_mod > hand_mod) {
		hand_offset = (hand_mod + 8) - frog_mod;
	} else {
		hand_offset = hand_mod - frog_mod;
	}

	draw_hand_sprite(hand_x - hand_offset, hand_y, hand_offset, last_sprite);
}

void move_hand_by_frac(int16_t dx_frac, int16_t dy_frac) {
	hand_x_frac += dx_frac;
	hand_y_frac += dy_frac;
	hand_x = hand_x_frac >> 8;
	hand_y = hand_y_frac >> 8;
}
