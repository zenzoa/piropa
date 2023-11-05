#pragma bank 255

#include <gbdk/platform.h>

#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "hud.h"
#include "hand.h"
#include "frog.h"
#include "scene.h"

#include "sprites/backgrounds/field.h"
#include "sprites/backgrounds/field_night.h"
#include "sprites/backgrounds/clouds.h"
#include "sprites/backgrounds/moon.h"
#include "sprites/backgrounds/basket.h"
#include "sprites/backgrounds/poo.h"

BANKREF(field_bank)

const unsigned char big_cloud_1_tile_map[3] = { 0x70, 0x71, 0x72 };
const unsigned char big_cloud_2_tile_map[3] = { 0x73, 0x74, 0x75 };

const unsigned char small_cloud_1_tile_map[2] = { 0x70, 0x72 };
const unsigned char small_cloud_2_tile_map[2] = { 0x73, 0x75 };

const unsigned char no_moon_tile_map[4] = { 0x15, 0x15, 0x15, 0x15 };
const unsigned char moon_1_tile_map[4] = { 0x60, 0x61, 0x68, 0x69 };
const unsigned char moon_2_tile_map[4] = { 0x62, 0x63, 0x6a, 0x6b };
const unsigned char moon_3_tile_map[4] = { 0x62, 0x64, 0x6c, 0x6d };
const unsigned char moon_4_tile_map[4] = { 0x62, 0x65, 0x6e, 0x6f };
const unsigned char moon_5_tile_map[4] = { 0x66, 0x67, 0x70, 0x71 };

const unsigned char basket_closed_tile_map[3] = { 0xf8, 0xf9, 0xfa };
const unsigned char basket_open_tile_map[3] = { 0xfb, 0xfc, 0xfd };

uint8_t moon_in_sky = TRUE;
uint8_t sky_anim_counter = 0;
uint8_t basket_is_open = FALSE;

#define MAX_POOPS 6
uint8_t poops_x[MAX_POOPS];
uint8_t poops_y[MAX_POOPS];

void set_basket(uint8_t is_open) {
	if (is_open != basket_is_open) {
		if (is_open) {
			set_bkg_tiles(13, 8, 3, 1, basket_open_tile_map);
		} else {
			set_bkg_tiles(13, 8, 3, 1, basket_closed_tile_map);
		}
		basket_is_open = is_open;
	}
}

void draw_poops(void) {
	for (uint8_t i = 0; i < MAX_POOPS; i++) {
		if (poops_x[i] > 0 || poops_y[i] > 0) {
			set_bkg_tile_xy(poops_x[i], poops_y[i], 0xfe);
		}
	}
}

void setup_field_data(void) NONBANKED {
	if (is_night) {
		SWITCH_ROM(BANK(field_night));
		set_bkg_data(0, field_night_TILE_COUNT, field_night_tiles);
		set_bkg_tiles(0, 0, 20, 18, field_night_map);

		SWITCH_ROM(BANK(moon));
		set_bkg_data(0x60, moon_TILE_COUNT, moon_tiles);

	} else {
		SWITCH_ROM(BANK(field));
		set_bkg_data(0, field_TILE_COUNT, field_tiles);
		set_bkg_tiles(0, 0, 20, 18, field_map);

		SWITCH_ROM(BANK(clouds));
		set_bkg_data(0x70, clouds_TILE_COUNT, clouds_tiles);
	}

	SWITCH_ROM(BANK(basket));
	set_bkg_data(0xf8, basket_TILE_COUNT, basket_tiles);

	SWITCH_ROM(BANK(poo));
	set_bkg_data(0xfe, poo_TILE_COUNT, poo_tiles);
}

void setup_field(void) {
	if (is_night) {
		moon_in_sky = TRUE;
		sky_anim_counter = 0;
		set_bkg_tiles(9, 5, 2, 2, moon_1_tile_map);

	} else {
		sky_anim_counter = 0;
		set_bkg_tiles(6, 5, 3, 1, big_cloud_2_tile_map);
		set_bkg_tiles(8, 4, 2, 1, small_cloud_1_tile_map);
		set_bkg_tiles(12, 5, 2, 1, small_cloud_2_tile_map);
	}

	set_bkg_tiles(13, 8, 3, 1, basket_closed_tile_map);

	draw_poops();
}

void update_field(void) {
	if (is_night) {
		if (moon_in_sky) {
			sky_anim_counter += 1;
			if (sky_anim_counter > 240) {
				sky_anim_counter = 144;
			} else if (sky_anim_counter > 192) {
				set_bkg_tiles(9, 5, 2, 2, moon_5_tile_map);
			} else if (sky_anim_counter > 144) {
				set_bkg_tiles(9, 5, 2, 2, moon_4_tile_map);
			} else if (sky_anim_counter > 96) {
				set_bkg_tiles(9, 5, 2, 2, moon_3_tile_map);
			} else if (sky_anim_counter > 48) {
				set_bkg_tiles(9, 5, 2, 2, moon_2_tile_map);
			}
		}

	} else {
		sky_anim_counter += 1;
		if (sky_anim_counter > 120) {
			sky_anim_counter = 0;
			set_bkg_tiles(6, 5, 3, 1, big_cloud_2_tile_map);
		} else if (sky_anim_counter > 100) {
			set_bkg_tiles(8, 4, 2, 1, small_cloud_1_tile_map);
		} else if (sky_anim_counter > 80) {
			set_bkg_tiles(12, 5, 2, 1, small_cloud_2_tile_map);
		} else if (sky_anim_counter > 60) {
			set_bkg_tiles(6, 5, 3, 1, big_cloud_1_tile_map);
		} else if (sky_anim_counter > 40) {
			set_bkg_tiles(8, 4, 2, 1, small_cloud_2_tile_map);
		} else if (sky_anim_counter > 20) {
			set_bkg_tiles(12, 5, 2, 1, small_cloud_1_tile_map);
		}
	}

	if (hand_x + 16 >= 120 && hand_x < 136 && hand_y + 16 >= 80 && hand_y < 96) {
		set_basket(TRUE);
	} else {
		set_basket(FALSE);
	}
}

void grab_moon_from_sky(void) {
	moon_in_sky = FALSE;
	set_bkg_tiles(9, 5, 2, 2, no_moon_tile_map);
}

void return_moon_to_sky(void) {
	if (!moon_in_sky) {
		moon_in_sky = TRUE;
		sky_anim_counter = 0;
		set_bkg_tiles(9, 5, 2, 2, moon_1_tile_map);
	}
}

uint8_t is_poop_at(uint8_t x, uint8_t y) {
	for (uint8_t i = 0; i < MAX_POOPS; i++) {
		if (poops_x[i] == x && poops_y[i] == y) {
			return TRUE;
		}
	}
	return FALSE;
}

void clean_poop_at(uint8_t x, uint8_t y) {
	if (current_scene == FIELD) {
		for (uint8_t i = 0; i < MAX_POOPS; i++) {
			if ((poops_x[i] == x || poops_x[i] == x + 1 || poops_x[i] == x - 1) &&
				(poops_y[i] == y || poops_y[i] == y + 1 || poops_y[i] == y - 1)
				) {
					SWITCH_ROM(BANK(frog_bank));
					if (poops > 0) {
						poops -= 1;
					}

					SWITCH_ROM(BANK(field));
					uint8_t original_tile = field_map[poops_y[i] * 20 + poops_x[i]];
					set_bkg_tile_xy(poops_x[i], poops_y[i], original_tile);

					poops_x[i] = 0;
					poops_y[i] = 0;
			}
		}
	}
}

void add_poop(uint8_t x, uint8_t y) {
	for (uint8_t i = 0; i < MAX_POOPS; i++) {
		if (poops_x[i] == 0 && poops_y[i] == 0) {
			if (!is_poop_at(x - 1, y + 1)) {
				poops_x[i] = x - 1;
				poops_y[i] = y + 1;
			} else if (!is_poop_at(x + 2, y + 1)) {
				poops_x[i] = x + 2;
				poops_y[i] = y + 1;
			} else if (!is_poop_at(x - 1, y)) {
				poops_x[i] = x - 1;
				poops_y[i] = y;
			} else if (!is_poop_at(x + 2, y)) {
				poops_x[i] = x + 2;
				poops_y[i] = y;
			} else if (!is_poop_at(x, y + 1)) {
				poops_x[i] = x;
				poops_y[i] = y + 1;
			} else if (!is_poop_at(x + 1, y + 1)) {
				poops_x[i] = x + 1;
				poops_y[i] = y + 1;
			} else if (!is_poop_at(x, y)) {
				poops_x[i] = x;
				poops_y[i] = y;
			} else if (!is_poop_at(x + 1, y)) {
				poops_x[i] = x + 1;
				poops_y[i] = y;
			}
			EMU_printf("");
			EMU_printf("POOP at %d %d", poops_x[i], poops_y[i]);
			draw_poops();
			break;
		}
	}
}
