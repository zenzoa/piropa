#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "hand_sprites.h"
#include "frog.h"
#include "poop.h"
#include "scene.h"
#include "field.h"

BANKREF(hand_bank)

uint8_t hand_state;
#define HAND_DEFAULT 0
#define HAND_POINT 1
#define HAND_PET1 2
#define HAND_PET2 3
#define HAND_MEDICINE 4
#define HAND_MEDICINE_USE 5
#define HAND_SOAP 6
#define HAND_SOAP_USE 7
#define HAND_BROOM 8
#define HAND_BROOM_USE 9
#define HAND_MOON 10
#define HAND_FLY 11
#define HAND_DRAGONFLY 12
#define HAND_FIREFLY 13
#define HAND_BUTTERFLY 14

uint8_t hand_x;
uint8_t hand_y;
uint16_t hand_x_frac;
uint16_t hand_y_frac;

uint16_t push_left = 0;
uint16_t push_right = 0;

uint8_t hand_offset;

uint8_t hand_timeout = 0;

uint8_t wiggle_anim_counter = 0;
uint8_t wiggle_frame = 0;
uint8_t wiggle_loops = 0;

uint8_t sweep_count = 0;

void move_hand_by_frac(int16_t dx_frac, int16_t dy_frac) {
	hand_x_frac += dx_frac;
	hand_y_frac += dy_frac;
	hand_x = hand_x_frac >> 8;
	hand_y = hand_y_frac >> 8;

	if (hand_y < 8) {
		hand_y = 8;
		hand_y_frac = hand_y << 8;
	} else if (hand_y > 152) {
		hand_y = 152;
		hand_y_frac = hand_y << 8;
	}

	switch(current_scene) {
		case FIELD:
			if (hand_x > 176 && dx_frac < 0) {
				start_transition_to_scene(POND, is_night);
			} else if (hand_x > 160 && dx_frac > 0) {
				start_transition_to_scene(GARDEN, is_night);
			}
			break;

		case POND:
			if (hand_x > 160 && hand_x < 240 && dx_frac > 0) {
				start_transition_to_scene(FIELD, is_night);
			} else if (hand_x > 176 && dx_frac < 0) {
				hand_x = 0;
				hand_x_frac = hand_x << 8;
			}
			break;

		case GARDEN:
			if (hand_x > 176 && dx_frac < 0) {
				start_transition_to_scene(FIELD, is_night);
			} else if (hand_x > 160 && dx_frac > 0) {
				hand_x = 160;
				hand_x_frac = hand_x << 8;
			}
			break;
	}
}

uint8_t is_hand_empty(void) {
	return (hand_state == HAND_DEFAULT || hand_state == HAND_POINT);
}

uint8_t is_hand_over_frog(void) {
	// SWITCH_ROM(BANK(frog_bank));
	return (hand_x + 8 >= frog_x && hand_x < frog_x + 32 && hand_y + 8 >= frog_y && hand_y < frog_y + 24);
}

void set_hand_state(uint8_t new_state) NONBANKED {
	hand_state = new_state;
	swap_hand_vram();
	set_hand_sprite_data(new_state);

	if (new_state == HAND_PET1 || new_state == HAND_PET2) {
		hand_timeout = 32;
	} else if (new_state == HAND_SOAP_USE) {
		wiggle_loops = 0;
	} else if (new_state == HAND_BROOM && sweep_count > 0) {
		hand_timeout = 12;
	} else if (new_state == HAND_BROOM_USE) {
		hand_timeout = 12;
	}
}

void setup_hand(void) {
	hand_x = 104;
	hand_y = 60;
	hand_x_frac = hand_x << 8;
	hand_y_frac = hand_y << 8;
	set_hand_state(HAND_DEFAULT);
}

void draw_hand(uint8_t *last_sprite) {
	if (is_evolving) { return; }

	hand_offset = 0;

	// SWITCH_ROM(BANK(frog_bank));
	uint8_t frog_mod = frog_x % 8;
	uint8_t hand_mod = hand_x % 8;

	if (frog_mod > hand_mod) {
		hand_offset = (hand_mod + 8) - frog_mod;
	} else {
		hand_offset = hand_mod - frog_mod;
	}

	draw_hand_sprite(hand_x - hand_offset, hand_y, hand_offset, last_sprite);
}

uint8_t update_wiggle(void) {
	wiggle_anim_counter += 1;
	if (wiggle_anim_counter > 2) {
		wiggle_anim_counter = 0;
		wiggle_frame += 1;
		if (wiggle_frame < 3) {
			hand_x += 1;
		} else if (wiggle_frame < 9) {
			hand_x -= 1;
		} else if (wiggle_frame < 12) {
			hand_x += 1;
		} else {
			wiggle_frame = 0;
			return 1;
		}
	}
	return 0;
}

void update_hand(void) {
	if (hand_timeout > 0) {
		hand_timeout -= 1;
	}

	switch(hand_state) {

		case HAND_DEFAULT:
			if (is_hand_over_frog() && !is_night && life_stage != EGG && life_stage != DEAD) {
				set_hand_state(HAND_POINT);
			}
			break;

		case HAND_POINT:
			if (!is_hand_over_frog()) {
				set_hand_state(HAND_DEFAULT);
			}
			break;

		case HAND_PET1:
			if (!is_hand_over_frog() || hand_timeout == 0) {
				set_hand_state(HAND_DEFAULT);
			}
			break;

		case HAND_PET2:
			if (!is_hand_over_frog() || hand_timeout == 0) {
				set_hand_state(HAND_DEFAULT);
			}
			break;

		case HAND_MEDICINE_USE:
			if (update_wiggle()) {
				set_hand_state(HAND_MEDICINE);
			}
			break;

		case HAND_SOAP_USE:
			if (update_wiggle()) {
				wiggle_loops += 1;
				if (wiggle_loops >= 2) {
					wiggle_loops = 0;
					set_hand_state(HAND_SOAP);
				}
			}
			break;

		case HAND_BROOM:
			if (sweep_count > 0 && hand_timeout == 0) {
				set_hand_state(HAND_BROOM_USE);
			}
			break;

		case HAND_BROOM_USE:
			if (hand_timeout == 0) {
				sweep_count -= 1;
				if (sweep_count == 0) {
					clean_poop_at(hand_x / 8, hand_y / 8);
				}
				set_hand_state(HAND_BROOM);
			}
			break;

	}
}
