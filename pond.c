#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "hud.h"
#include "hand.h"
#include "frog.h"
#include "scene.h"

#include "sprites/backgrounds/pond.h"
#include "sprites/backgrounds/pond_night.h"
#include "sprites/backgrounds/clouds.h"

BANKREF(pond_bank)

uint8_t pond_sky_anim_counter = 0;

void setup_pond_data(void) NONBANKED {
	if (is_night) {
		SWITCH_ROM(BANK(pond_night));
		set_bkg_data(0, pond_night_TILE_COUNT, pond_night_tiles);
		set_bkg_tiles(0, 0, 20, 18, pond_night_map);

	} else {
		SWITCH_ROM(BANK(pond));
		set_bkg_data(0, pond_TILE_COUNT, pond_tiles);
		set_bkg_tiles(0, 0, 20, 18, pond_map);

		SWITCH_ROM(BANK(clouds));
		set_bkg_data(0x70, clouds_TILE_COUNT, clouds_tiles);
	}
}

void setup_pond(void) {
	pond_sky_anim_counter = 0;
	if (is_night) {
	} else {
		set_bkg_tiles(0, 5, 3, 1, big_cloud_2_tile_map);
		set_bkg_tiles(3, 6, 2, 1, small_cloud_1_tile_map);
		set_bkg_tiles(11, 4, 2, 1, small_cloud_2_tile_map);
	}

	if (last_scene == FIELD) {
		hand_x = 160;
		hand_x_frac = hand_x << 8;
	}
}

void update_pond(void) {
	if (is_night) {

	} else {
		pond_sky_anim_counter += 1;
		if (pond_sky_anim_counter > 120) {
			pond_sky_anim_counter = 0;
			set_bkg_tiles(0, 5, 3, 1, big_cloud_2_tile_map);
		} else if (pond_sky_anim_counter > 100) {
			set_bkg_tiles(3, 6, 2, 1, small_cloud_1_tile_map);
		} else if (pond_sky_anim_counter > 80) {
			set_bkg_tiles(11, 4, 2, 1, small_cloud_2_tile_map);
		} else if (pond_sky_anim_counter > 60) {
			set_bkg_tiles(0, 5, 3, 1, big_cloud_1_tile_map);
		} else if (pond_sky_anim_counter > 40) {
			set_bkg_tiles(3, 6, 2, 1, small_cloud_2_tile_map);
		} else if (pond_sky_anim_counter > 20) {
			set_bkg_tiles(11, 4, 2, 1, small_cloud_1_tile_map);
		}
	}
}

void restore_pond_tile(uint8_t x, uint8_t y) NONBANKED {
	SWITCH_ROM(BANK(pond));
	uint8_t original_tile = pond_map[y * 20 + x];
	set_bkg_tile_xy(x, y, original_tile);
}
