#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "hand_sprites.h"
#include "poop.h"
#include "scene.h"
#include "shared_variables.h"

static uint16_t push_left;
static uint16_t push_right;

static uint8_t hand_offset;

static uint8_t hand_timeout;

static uint8_t wiggle_anim_counter;
static uint8_t wiggle_frame;
static uint8_t wiggle_loops;

uint8_t sweep_count;

void move_hand_by_frac(int16_t dx_frac, int16_t dy_frac) BANKED {
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
				transition_to_scene(POND, is_night);
			} else if (hand_x > 160 && dx_frac > 0) {
				transition_to_scene(GARDEN, is_night);
			}
			break;

		case POND:
			if (hand_x > 160 && hand_x < 240 && dx_frac > 0) {
				transition_to_scene(FIELD, is_night);
			} else if (hand_x > 176 && dx_frac < 0) {
				hand_x = 0;
				hand_x_frac = hand_x << 8;
			}
			break;

		case GARDEN:
			if (hand_x > 176 && dx_frac < 0) {
				transition_to_scene(FIELD, is_night);
			} else if (hand_x > 160 && dx_frac > 0) {
				hand_x = 160;
				hand_x_frac = hand_x << 8;
			}
			break;
	}
}

void move_hand(uint8_t joypad_value) BANKED {
	if (joypad_value & J_LEFT) {
		if (joypad_value & J_UP) {
			move_hand_by_frac(-181, -181);
		} else if (joypad_value & J_DOWN) {
			move_hand_by_frac(-181, 181);
		} else {
			move_hand_by_frac(-256, 0);
		}
	} else if (joypad_value & J_RIGHT) {
		if (joypad_value & J_UP) {
			move_hand_by_frac(181, -181);
		} else if (joypad_value & J_DOWN) {
			move_hand_by_frac(181, 181);
		} else {
			move_hand_by_frac(256, 0);
		}
	} else if (joypad_value & J_UP) {
		move_hand_by_frac(0, -256);
	} else if (joypad_value & J_DOWN) {
		move_hand_by_frac(0, 256);
	}
}

uint8_t is_hand_empty(void) BANKED {
	return (hand_state == HAND_DEFAULT || hand_state == HAND_POINT);
}

uint8_t is_hand_over_frog(void) BANKED {
	return (hand_x + 8 >= frog_x && hand_x < frog_x + 32 && hand_y + 8 >= frog_y && hand_y < frog_y + 24);
}

static uint8_t is_hand_over_plant(void) {
	return (hand_x >= PLANT_0_X*8 && hand_x < PLANT_0_X*8+24 && hand_y >= PLANT_0_Y*8+4 && hand_y < PLANT_0_Y*8+28) ||
		(hand_x >= PLANT_1_X*8 && hand_x < PLANT_1_X*8+24 && hand_y >= PLANT_1_Y*8+4 && hand_y < PLANT_1_Y*8+28) ||
		(hand_x >= PLANT_2_X*8 && hand_x < PLANT_2_X*8+24 && hand_y >= PLANT_2_Y*8+4 && hand_y < PLANT_2_Y*8+28);
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

void setup_hand(void) BANKED {
	hand_x = 104;
	hand_y = 60;
	hand_x_frac = hand_x << 8;
	hand_y_frac = hand_y << 8;
	set_hand_state(HAND_DEFAULT);
}

void draw_hand(uint8_t *last_sprite) BANKED {
	if (is_evolving) { return; }

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

static uint8_t update_wiggle(void) {
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

void update_hand(void) BANKED {
	if (hand_timeout > 0) {
		hand_timeout -= 1;
	}

	switch(hand_state) {

		case HAND_DEFAULT:
			if (is_hand_over_frog() && !is_night && life_stage != EGG && life_stage != DEAD) {
				set_hand_state(HAND_POINT);
			} else if (current_scene == GARDEN && is_hand_over_plant()) {
				set_hand_state(HAND_POINT);
			}
			break;

		case HAND_POINT:
			if (!is_hand_over_frog() && (current_scene != GARDEN || !is_hand_over_plant())) {
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
