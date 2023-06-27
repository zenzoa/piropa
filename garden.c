#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <rand.h>

#include <gbdk/emu_debug.h>

#include "save.h"

BANKREF(garden_code)

#define HAND_EMPTY 0
#define HAND_HOLD_BLACKBERRY 6
#define HAND_HOLD_BLUEBERRY 7
#define HAND_HOLD_STRAWBERRY 8

const unsigned char odd_leaf_tile_map[2] = { 0xD0, 0xD1 };
const unsigned char even_leaf_tile_map[2] = { 0xD2, 0xD3 };

const unsigned char bud_1_tile_map[2] = { 0xD4, 0xD5 };
const unsigned char bud_2_tile_map[2] = { 0xD6, 0xD7 };
const unsigned char bud_3_tile_map[2] = { 0xD8, 0xD9 };

const unsigned char blueberry_tile_map[4] = { 0xDA, 0xDB, 0xDC, 0xDD };
const unsigned char strawberry_tile_map[4] = { 0xDE, 0xDF, 0xE0, 0xE1 };
const unsigned char blackberry_tile_map[4] = { 0xE2, 0xE3, 0xE4, 0xE5 };

const unsigned char empty_ground_tile_map[2] = { 0x28, 0x28 };
const unsigned char empty_bg_1_tile_map[4] = { 0x12, 0x16, 0x12, 0x1D };
const unsigned char empty_bg_2_tile_map[4] = { 0x0C, 0x0D, 0x16, 0x1D };
const unsigned char empty_bg_3_tile_map[4] = { 0x0C, 0x02, 0x21, 0x1D };

#define PLANT_EMPTY 0
#define PLANT_GROWING_1 1
#define PLANT_GROWING_2 2
#define PLANT_GROWING_3 3
#define PLANT_BLACKBERRY 6
#define PLANT_BLUEBERRY 4
#define PLANT_STRAWBERRY 5
#define PLANT_DYING_1 7
#define PLANT_DYING_2 8
#define PLANT_DYING_3 9
#define PLANT_DYING_4 10

#define TIME_TO_GROW 6

#define PLANT_VRAM 0xD0

uint8_t plant_1_watered = FALSE;
uint8_t plant_1_stage = PLANT_EMPTY;
uint8_t plant_1_sec = 0;
uint8_t plant_1_min = 0;

uint8_t plant_2_watered = FALSE;
uint8_t plant_2_stage = PLANT_EMPTY;
uint8_t plant_2_sec = 0;
uint8_t plant_2_min = 0;

uint8_t plant_3_watered = FALSE;
uint8_t plant_3_stage = PLANT_EMPTY;
uint8_t plant_3_sec = 0;
uint8_t plant_3_min = 0;

#define SPARKLE_VRAM 0xEC

uint8_t sparkle_animation_counter = 0;

uint8_t sparkle_1_sprite_index = 0;
uint8_t sparkle_2_sprite_index = 2;
uint8_t sparkle_3_sprite_index = 80;

const metasprite_t my_sparkle_metasprite0[] = {
	METASPR_ITEM(-4, -4, 0, 0), METASPR_TERM
};

const metasprite_t my_sparkle_metasprite1[] = {
	METASPR_ITEM(-4, -4, 1, 0), METASPR_TERM
};

const metasprite_t my_sparkle_metasprite2[] = {
	METASPR_ITEM(-4, -4, 2, 0), METASPR_TERM
};

const metasprite_t my_sparkle_metasprite3[] = {
	METASPR_ITEM(-4, -4, 3, 0), METASPR_TERM
};

const metasprite_t* const my_sparkle_metasprites[4] = {
	my_sparkle_metasprite0, my_sparkle_metasprite1, my_sparkle_metasprite2, my_sparkle_metasprite3
};

void draw_plant(uint8_t plant_stage, uint8_t x) {
	if (plant_stage == PLANT_GROWING_1) {
		set_bkg_tiles(x, 8, 2, 1, bud_1_tile_map);

	} else if (plant_stage == PLANT_GROWING_2) {
		set_bkg_tiles(x, 7, 2, 1, bud_2_tile_map);
		set_bkg_tiles(x, 8, 2, 1, odd_leaf_tile_map);

	} else if (plant_stage == PLANT_GROWING_3) {
		set_bkg_tiles(x, 6, 2, 1, bud_3_tile_map);
		set_bkg_tiles(x, 7, 2, 1, even_leaf_tile_map);
		set_bkg_tiles(x, 8, 2, 1, odd_leaf_tile_map);

	} else if (plant_stage > PLANT_GROWING_3 && plant_stage < PLANT_DYING_1) {
		set_bkg_tiles(x, 6, 2, 1, odd_leaf_tile_map);
		set_bkg_tiles(x, 7, 2, 1, even_leaf_tile_map);
		set_bkg_tiles(x, 8, 2, 1, odd_leaf_tile_map);

		if (plant_stage == PLANT_BLUEBERRY) {
			set_bkg_tiles(x, 4, 2, 2, blueberry_tile_map);
		} else if (plant_stage == PLANT_STRAWBERRY) {
			set_bkg_tiles(x, 4, 2, 2, strawberry_tile_map);
		} else if (plant_stage == PLANT_BLACKBERRY) {
			set_bkg_tiles(x, 4, 2, 2, blackberry_tile_map);
		}

	} else if (plant_stage == PLANT_DYING_1 || plant_stage == PLANT_DYING_2) {
		set_bkg_tiles(x, 6, 2, 1, odd_leaf_tile_map);
		set_bkg_tiles(x, 7, 2, 1, even_leaf_tile_map);
		set_bkg_tiles(x, 8, 2, 1, odd_leaf_tile_map);
		if (x == 0x06) {
			set_bkg_tiles(x, 4, 2, 2, empty_bg_1_tile_map);
		} else if (x == 0x0A) {
			set_bkg_tiles(x, 4, 2, 2, empty_bg_2_tile_map);
		} else {
			set_bkg_tiles(x, 4, 2, 2, empty_bg_3_tile_map);
		}

	} else if (plant_stage == PLANT_DYING_3) {
		set_bkg_tiles(x, 6, 2, 1, empty_ground_tile_map);
		set_bkg_tiles(x, 7, 2, 1, even_leaf_tile_map);
		set_bkg_tiles(x, 8, 2, 1, odd_leaf_tile_map);

	} else if (plant_stage == PLANT_DYING_4) {
		set_bkg_tiles(x, 7, 2, 1, empty_ground_tile_map);
		set_bkg_tiles(x, 8, 2, 1, odd_leaf_tile_map);

	} else if (plant_stage == PLANT_EMPTY) {
		set_bkg_tiles(x, 8, 2, 1, empty_ground_tile_map);
	}
}

void draw_plants() {
	draw_plant(plant_1_stage, 6);
	draw_plant(plant_2_stage, 10);
	draw_plant(plant_3_stage, 14);
}

void grow_plant(uint8_t *watered, uint8_t *stage) {
	*watered = FALSE;

	if (*stage < PLANT_GROWING_3) {
		*stage += 1;
	} else if (*stage == PLANT_GROWING_3) {
		uint8_t n = rand();
		if (n < 85) {
			*stage = PLANT_BLUEBERRY;
		} else if (n < 170) {
			*stage = PLANT_STRAWBERRY;
		} else {
			*stage = PLANT_BLACKBERRY;
		}
	}

	save_item(DATA_PLANT_1_WATERED, plant_1_watered);
	save_item(DATA_PLANT_1_STAGE, plant_1_stage);
	save_item(DATA_PLANT_2_WATERED, plant_2_watered);
	save_item(DATA_PLANT_2_STAGE, plant_2_stage);
	save_item(DATA_PLANT_3_WATERED, plant_3_watered);
	save_item(DATA_PLANT_3_STAGE, plant_3_stage);
}

void update_plant(uint8_t time_speed, uint8_t *watered, uint8_t *stage, uint8_t *sec, uint8_t *min, uint8_t draw) {
	if (*watered) {
		*sec += 1;
		if (*sec >= 60) {
			*sec = 0;

			if (*min < 255) {
				*min += 1;
				save_item(DATA_PLANT_1_MIN, plant_1_min);
				save_item(DATA_PLANT_2_MIN, plant_2_min);
				save_item(DATA_PLANT_3_MIN, plant_3_min);
			}

			if (*stage <= PLANT_GROWING_3 && *min >= time_speed * TIME_TO_GROW) {
				grow_plant(watered, stage);
				if (draw) {
					draw_plants();
				}
			}
		}
	}

	if (*stage >= PLANT_DYING_1 && *stage < PLANT_DYING_4) {
		*stage += 1;
		if (draw) {
			draw_plants();
		}

	} else if (*stage == PLANT_DYING_4) {
		*stage = 0;
		if (draw) {
			draw_plants();
		}
	}
}

void update_garden(uint8_t time_speed, uint8_t draw) {
	update_plant(time_speed, &plant_1_watered, &plant_1_stage, &plant_1_sec, &plant_1_min, draw);
	update_plant(time_speed, &plant_2_watered, &plant_2_stage, &plant_2_sec, &plant_2_min, draw);
	update_plant(time_speed, &plant_3_watered, &plant_3_stage, &plant_3_sec, &plant_3_min, draw);
}

void update_plant_after_break(uint8_t time_speed, uint8_t *seconds, uint8_t missed_minutes, uint8_t *watered, uint8_t *stage, uint8_t *sec, uint8_t *min) {
	if (*watered) {
		EMU_printf("old age: %d", *min);
		*sec += *seconds;
		if (*sec >= 60) {
			*sec = 0;
			if (*min < 255) {
				*min += 1;
			}
		}
		if (*min + missed_minutes < *min) {
			*min = 255;
		} else {
			*min += missed_minutes;
		}
		EMU_printf("new age: %d", *min);
		if (*min >= time_speed * TIME_TO_GROW) {
			grow_plant(watered, stage);
		}
	}
}

void update_garden_after_break(uint8_t time_speed, uint16_t *days, uint8_t *hours, uint8_t *minutes, uint8_t *seconds) {
	EMU_MESSAGE("UPDATE GARDEN");

	uint8_t missed_minutes = *minutes;
	if (*hours >= 3 || *days >= 1) {
		missed_minutes = 255;
	} else {
		missed_minutes += *hours * 60;
	}

	update_plant_after_break(time_speed, seconds, missed_minutes, &plant_1_watered, &plant_1_stage, &plant_1_sec, &plant_1_min);
	update_plant_after_break(time_speed, seconds, missed_minutes, &plant_2_watered, &plant_2_stage, &plant_2_sec, &plant_2_min);
	update_plant_after_break(time_speed, seconds, missed_minutes, &plant_3_watered, &plant_3_stage, &plant_3_sec, &plant_3_min);
}

void water_plant(uint8_t plant_number) {
	if (plant_number == 1 && !plant_1_watered) {
		plant_1_watered = TRUE;
		plant_1_sec = 0;
		plant_1_min = 0;
		save_item(DATA_PLANT_1_WATERED, plant_1_watered);
		save_item(DATA_PLANT_1_MIN, plant_1_min);

	} else if (plant_number == 2 && !plant_2_watered) {
		plant_2_watered = TRUE;
		plant_2_sec = 0;
		plant_2_min = 0;
		save_item(DATA_PLANT_2_WATERED, plant_2_watered);
		save_item(DATA_PLANT_2_MIN, plant_2_min);

	} else if (plant_number == 3 && !plant_3_watered) {
		plant_3_watered = TRUE;
		plant_3_sec = 0;
		plant_3_min = 0;
		save_item(DATA_PLANT_3_WATERED, plant_3_watered);
		save_item(DATA_PLANT_3_MIN, plant_3_min);
	}
}

uint8_t pick_fruit(uint8_t plant_number) {
	uint8_t new_hand_state = HAND_EMPTY;

	uint8_t* stage = &plant_1_stage;

	switch (plant_number) {
		case 1:
			stage = &plant_1_stage;
			plant_1_watered = FALSE;
			break;

		case 2:
			stage = &plant_2_stage;
			plant_2_watered = FALSE;
			break;

		case 3:
			stage = &plant_3_stage;
			plant_3_watered = FALSE;
			break;
	}

	switch (*stage) {
		case PLANT_BLACKBERRY:
			new_hand_state = HAND_HOLD_BLACKBERRY;
			*stage = PLANT_DYING_1;
			save_item(DATA_PLANT_1_STAGE, PLANT_EMPTY);
			break;

		case PLANT_BLUEBERRY:
			new_hand_state = HAND_HOLD_BLUEBERRY;
			*stage = PLANT_DYING_1;
			save_item(DATA_PLANT_2_STAGE, PLANT_EMPTY);
			break;

		case PLANT_STRAWBERRY:
			new_hand_state = HAND_HOLD_STRAWBERRY;
			*stage = PLANT_DYING_1;
			save_item(DATA_PLANT_3_STAGE, PLANT_EMPTY);
			break;
	}

	draw_plants();
	return new_hand_state;
}

void animate_sparkles() {
	sparkle_animation_counter += 1;
	if (sparkle_animation_counter > 12) {
		sparkle_animation_counter = 0;
	}
	if (sparkle_animation_counter == 4) {
		sparkle_1_sprite_index += 1;
		if (sparkle_1_sprite_index > 3) {
			sparkle_1_sprite_index = 0;
		}
	}
	if (sparkle_animation_counter == 12) {
		sparkle_2_sprite_index += 1;
		if (sparkle_2_sprite_index > 3) {
			sparkle_2_sprite_index = 0;
		}
	}
	if (sparkle_animation_counter == 8) {
		sparkle_3_sprite_index += 1;
		if (sparkle_3_sprite_index > 3) {
			sparkle_3_sprite_index = 0;
		}
	}
}

void draw_garden_sparkles(uint8_t *last_used_sprite) {
	animate_sparkles();

	if (plant_1_watered && plant_1_stage <= PLANT_GROWING_3) {
		uint8_t y = 80;
		if (plant_1_stage == PLANT_GROWING_2) { y -= 8; }
		if (plant_1_stage == PLANT_GROWING_3) { y -= 16; }
		*last_used_sprite += move_metasprite(my_sparkle_metasprites[sparkle_1_sprite_index], SPARKLE_VRAM, *last_used_sprite, 60, y);
	}

	if (plant_2_watered && plant_2_stage <= PLANT_GROWING_3) {
		uint8_t y = 80;
		if (plant_2_stage == PLANT_GROWING_2) { y -= 8; }
		if (plant_2_stage == PLANT_GROWING_3) { y -= 16; }
		*last_used_sprite += move_metasprite(my_sparkle_metasprites[sparkle_2_sprite_index], SPARKLE_VRAM, *last_used_sprite, 92, y);
	}

	if (plant_3_watered && plant_3_stage <= PLANT_GROWING_3) {
		uint8_t y = 80;
		if (plant_3_stage == PLANT_GROWING_2) { y -= 8; }
		if (plant_3_stage == PLANT_GROWING_3) { y -= 16; }
		*last_used_sprite += move_metasprite(my_sparkle_metasprites[sparkle_3_sprite_index], SPARKLE_VRAM, *last_used_sprite, 124, y);
	}
}

void load_garden_data() {
	plant_1_watered = load_item(DATA_PLANT_1_WATERED, plant_1_watered);
	plant_1_stage = load_item(DATA_PLANT_1_STAGE, plant_1_stage);
	plant_1_min = load_item(DATA_PLANT_1_MIN, plant_1_min);

	plant_2_watered = load_item(DATA_PLANT_2_WATERED, plant_2_watered);
	plant_2_stage = load_item(DATA_PLANT_2_STAGE, plant_2_stage);
	plant_2_min = load_item(DATA_PLANT_2_MIN, plant_2_min);

	plant_3_watered = load_item(DATA_PLANT_3_WATERED, plant_3_watered);
	plant_3_stage = load_item(DATA_PLANT_3_STAGE, plant_3_stage);
	plant_3_min = load_item(DATA_PLANT_3_MIN, plant_3_min);
}
