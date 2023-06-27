#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <rand.h>

BANKREF(pond_code)

#define POND_SPARKLE_VRAM 0xE6

uint8_t pond_sparkle_counter = 0;
uint8_t pond_sparkle_frame = 0;

#define FLY_VRAM 0xCC

#define FLY_OFF 0
#define FLY_ALIVE 1
#define FLY_HELD 2
#define FLY_FLEE 3
#define FLY_EATEN 4

uint8_t fly1_state = FLY_ALIVE;
uint8_t fly1_x = 40;
uint8_t fly1_y = 40;
uint8_t fly1_frame = 0;
uint8_t fly1_counter = 0;
uint8_t fly1_respawn = 0;

uint8_t fly2_state = FLY_ALIVE;
uint8_t fly2_x = 20;
uint8_t fly2_y = 30;
uint8_t fly2_frame = 0;
uint8_t fly2_counter = 0;
uint8_t fly2_respawn = 0;

uint8_t fly3_state = FLY_ALIVE;
uint8_t fly3_x = 30;
uint8_t fly3_y = 50;
uint8_t fly3_frame = 0;
uint8_t fly3_counter = 0;
uint8_t fly3_respawn = 0;

const metasprite_t my_fly_metasprite0[] = {
	METASPR_ITEM(-4, -4, 0, 0), METASPR_TERM
};

const metasprite_t my_fly_metasprite1[] = {
	METASPR_ITEM(-4, -4, 1, 0), METASPR_TERM
};

const metasprite_t* const my_fly_metasprites[2] = {
	my_fly_metasprite0, my_fly_metasprite1
};

void draw_pond_sparkles(uint8_t is_night, uint8_t at_pond) {
	if (!is_night && at_pond) {
		pond_sparkle_counter += 1;
		if (pond_sparkle_counter > 48) {
			pond_sparkle_counter = 0;
			if (pond_sparkle_frame == 1) {
				pond_sparkle_frame = 0;
			} else {
				pond_sparkle_frame = 1;
			}
		}
		set_bkg_tile_xy(1, 10, POND_SPARKLE_VRAM + 2 + pond_sparkle_frame);
		set_bkg_tile_xy(2, 10, POND_SPARKLE_VRAM + pond_sparkle_frame);
		set_bkg_tile_xy(9, 11, POND_SPARKLE_VRAM + pond_sparkle_frame);
		set_bkg_tile_xy(10, 11, POND_SPARKLE_VRAM + 2 + pond_sparkle_frame);
		set_bkg_tile_xy(8, 12, POND_SPARKLE_VRAM + 4 + pond_sparkle_frame);
	}
}

void draw_fly(uint8_t *last_used_sprite, uint8_t *x, uint8_t *y, uint8_t *frame, uint8_t *counter, uint8_t *state) {
	*counter += 1;
	if ((*state == FLY_ALIVE && *counter > 12) || (*state == FLY_FLEE && *counter > 6)) {
		*counter = 0;
		if (*frame == 0) {
			*frame = 1;
		} else {
			*frame = 0;
		}
		if (*state == FLY_ALIVE) {
			uint8_t dir = rand();
			if (dir < 64 && *x >= 14) {
				*x -= 2;
			} else if (dir < 128 && *x <= 162) {
				*x += 2;
			} else if (dir < 192 && *y >= 26) {
				*y -= 2;
			} else if (*y <= 58) {
				*y += 2;
			}
		} else {
			*x -= 2;
			*y -= 2;
			if (*x < 8 || *y < 8) {
				*state = FLY_OFF;
			}
		}
	}

	*last_used_sprite += move_metasprite(my_fly_metasprites[*frame], FLY_VRAM, *last_used_sprite, *x, *y);
}

void draw_flies(uint8_t *last_used_sprite, uint8_t is_night, uint8_t at_pond) {
	if ((fly1_state == FLY_ALIVE && !is_night && at_pond) || fly1_state == FLY_FLEE) {
		draw_fly(last_used_sprite, &fly1_x, &fly1_y, &fly1_frame, &fly1_counter, &fly1_state);
	}
	if ((fly2_state == FLY_ALIVE && !is_night && at_pond) || fly2_state == FLY_FLEE) {
		draw_fly(last_used_sprite, &fly2_x, &fly2_y, &fly2_frame, &fly2_counter, &fly2_state);
	}
	if ((fly3_state == FLY_ALIVE && !is_night && at_pond) || fly3_state == FLY_FLEE) {
		draw_fly(last_used_sprite, &fly3_x, &fly3_y, &fly3_frame, &fly3_counter, &fly3_state);
	}
}

uint8_t grab_fly(uint8_t hand_x, uint8_t hand_y) {
	if (fly1_state == FLY_ALIVE && hand_x - 12 <= fly1_x + 8 && hand_x + 4 >= fly1_x && hand_y - 8 <= fly1_y + 8 && hand_y + 8 >= fly1_y) {
		fly1_state = FLY_HELD;
		return 1;
	} else if (fly2_state == FLY_ALIVE && hand_x - 12 <= fly2_x + 8 && hand_x + 4 >= fly2_x && hand_y - 8 <= fly2_y + 8 && hand_y + 8 >= fly2_y) {
		fly2_state = FLY_HELD;
		return 2;
	} else if (fly3_state == FLY_ALIVE && hand_x - 12 <= fly3_x + 8 && hand_x + 4 >= fly3_x && hand_y - 8 <= fly3_y + 8 && hand_y + 8 >= fly3_y) {
		fly3_state = FLY_HELD;
		return 3;
	} else {
		return 0;
	}
}

void release_fly(uint8_t hand_x, uint8_t hand_y) {
	if (fly1_state == FLY_HELD) {
		fly1_x = hand_x - 8;
		fly1_y = hand_y;
		fly1_state = FLY_FLEE;
	} else if (fly2_state == FLY_HELD) {
		fly2_x = hand_x - 8;
		fly2_y = hand_y;
		fly2_state = FLY_FLEE;
	} else {
		fly3_x = hand_x - 8;
		fly3_y = hand_y;
		fly3_state = FLY_FLEE;
	}
}

void reset_flies() {
	if (fly1_state == FLY_OFF || fly1_state == FLY_FLEE) {
		fly1_state = FLY_ALIVE;
		fly1_x = 40;
		fly1_y = 40;
	}
	if (fly2_state == FLY_OFF || fly2_state == FLY_FLEE) {
		fly2_state = FLY_ALIVE;
		fly2_x = 20;
		fly2_y = 30;
	}
	if (fly3_state == FLY_OFF || fly3_state == FLY_FLEE) {
		fly3_state = FLY_ALIVE;
		fly3_x = 30;
		fly3_y = 50;
	}
}

// void update_flies() {

// }

// void update_flies_after_break() {

// }
