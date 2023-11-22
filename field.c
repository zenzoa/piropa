#pragma bank 255

#include <gbdk/platform.h>

#include "shared_variables.h"

#include "sprites/backgrounds/field.h"
#include "sprites/backgrounds/field_night.h"
#include "sprites/backgrounds/clouds.h"
#include "sprites/backgrounds/moon.h"
#include "sprites/backgrounds/basket.h"

static const unsigned char no_moon_tile_map[4] = { 0x16, 0x16, 0x16, 0x16 };
static const unsigned char moon_1_tile_map[4] = { 0x6a, 0x6b, 0x72, 0x73 };
static const unsigned char moon_2_tile_map[4] = { 0x6c, 0x6d, 0x74, 0x75 };
static const unsigned char moon_3_tile_map[4] = { 0x6c, 0x6e, 0x76, 0x77 };
static const unsigned char moon_4_tile_map[4] = { 0x6c, 0x6f, 0x78, 0x79 };
static const unsigned char moon_5_tile_map[4] = { 0x70, 0x71, 0x7a, 0x7b };

static const unsigned char basket_closed_tile_map[3] = { 0xf8, 0xf9, 0xfa };
static const unsigned char basket_open_tile_map[3] = { 0xfb, 0xfc, 0xfd };

static uint8_t moon_in_sky;
static uint8_t sky_anim_counter;
static uint8_t basket_is_open;

void set_basket(uint8_t is_open) BANKED {
	if (is_open != basket_is_open) {
		if (is_open) {
			set_bkg_tiles(13, 8, 3, 1, basket_open_tile_map);
		} else {
			set_bkg_tiles(13, 8, 3, 1, basket_closed_tile_map);
		}
		basket_is_open = is_open;
	}
}

void setup_field_data(void) NONBANKED {
	if (is_night) {
		SWITCH_ROM(BANK(field_night));
		set_bkg_data(0, field_night_TILE_COUNT, field_night_tiles);
		set_bkg_tiles(0, 0, 20, 18, field_night_map);

		SWITCH_ROM(BANK(moon));
		set_bkg_data(0x6a, moon_TILE_COUNT, moon_tiles);

	} else {
		SWITCH_ROM(BANK(field));
		set_bkg_data(0, field_TILE_COUNT, field_tiles);
		set_bkg_tiles(0, 0, 20, 18, field_map);

		SWITCH_ROM(BANK(clouds));
		set_bkg_data(0x70, clouds_TILE_COUNT, clouds_tiles);
	}

	SWITCH_ROM(BANK(basket));
	set_bkg_data(0xf8, basket_TILE_COUNT, basket_tiles);
}

void setup_field(uint8_t hand_has_moon) BANKED {
	if (is_night) {
		if (hand_has_moon) {
			moon_in_sky = FALSE;
			set_bkg_tiles(9, 5, 2, 2, no_moon_tile_map);
		} else if (moon_in_sky) {
			sky_anim_counter = 150;
			set_bkg_tiles(9, 5, 2, 2, moon_4_tile_map);
		} else {
			moon_in_sky = TRUE;
			sky_anim_counter = 0;
			set_bkg_tiles(9, 5, 2, 2, moon_1_tile_map);
		}

	} else {
		moon_in_sky = FALSE;
		sky_anim_counter = 0;
		set_bkg_tiles(6, 5, 3, 1, big_cloud_2_tile_map);
		set_bkg_tiles(8, 4, 2, 1, small_cloud_1_tile_map);
		set_bkg_tiles(12, 5, 2, 1, small_cloud_2_tile_map);
	}

	set_bkg_tiles(13, 8, 3, 1, basket_closed_tile_map);
}

void update_field(void) BANKED {
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
}

void restore_field_tile(uint8_t x, uint8_t y) NONBANKED {
	SWITCH_ROM(BANK(field));
	uint8_t original_tile = field_map[y * 20 + x];
	set_bkg_tile_xy(x, y, original_tile);
}

void grab_moon_from_sky(void) BANKED {
	moon_in_sky = FALSE;
	set_bkg_tiles(9, 5, 2, 2, no_moon_tile_map);
}

void return_moon_to_sky(void) BANKED {
	if (!moon_in_sky) {
		moon_in_sky = TRUE;
		sky_anim_counter = 0;
		set_bkg_tiles(9, 5, 2, 2, moon_1_tile_map);
	}
}
