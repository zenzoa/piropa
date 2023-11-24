#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "common.h"

#include "sprites/backgrounds/pond.h"
#include "sprites/backgrounds/pond_night.h"
#include "sprites/backgrounds/clouds.h"

static uint8_t pond_sky_anim_counter;

void setup_pond(void) BANKED {
	if (is_night) {
		set_banked_bkg_data(BANK(pond_night), 0, pond_night_TILE_COUNT, pond_night_tiles);
		set_banked_bkg_tiles(BANK(pond_night), 0, 0, 20, 18, pond_night_map);

	} else {
		set_banked_bkg_data(BANK(pond), 0, pond_TILE_COUNT, pond_tiles);
		set_banked_bkg_tiles(BANK(pond), 0, 0, 20, 18, pond_map);

		set_banked_bkg_data(BANK(clouds), 0x70, clouds_TILE_COUNT, clouds_tiles);

		pond_sky_anim_counter = 0;
		set_bkg_tiles(0, 5, 3, 1, big_cloud_2_tile_map);
		set_bkg_tiles(3, 6, 2, 1, small_cloud_1_tile_map);
		set_bkg_tiles(11, 4, 2, 1, small_cloud_2_tile_map);
	}
}

void update_pond(void) BANKED {
	if (!is_night) {
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

void restore_pond_tile(uint8_t x, uint8_t y) BANKED {
	restore_banked_bkg_tile_xy(BANK(pond), x, y, pond_map);
}
