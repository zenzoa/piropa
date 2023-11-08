#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "hud.h"
#include "hand.h"
#include "frog.h"
#include "scene.h"

#include "sprites/backgrounds/garden.h"
#include "sprites/backgrounds/garden_night.h"
#include "sprites/backgrounds/clouds.h"

BANKREF(garden_bank)

uint8_t garden_sky_anim_counter = 0;

void setup_garden_data(void) NONBANKED {
	if (is_night) {
		SWITCH_ROM(BANK(garden_night));
		set_bkg_data(0, garden_night_TILE_COUNT, garden_night_tiles);
		set_bkg_tiles(0, 0, 20, 18, garden_night_map);

	} else {
		SWITCH_ROM(BANK(garden));
		set_bkg_data(0, garden_TILE_COUNT, garden_tiles);
		set_bkg_tiles(0, 0, 20, 18, garden_map);

		SWITCH_ROM(BANK(clouds));
		set_bkg_data(0x70, clouds_TILE_COUNT, clouds_tiles);
	}
}

void setup_garden(void) {
	garden_sky_anim_counter = 0;
	if (is_night) {
	} else {
		set_bkg_tiles(11, 4, 2, 1, small_cloud_1_tile_map);
		set_bkg_tiles(13, 5, 3, 1, big_cloud_2_tile_map);
		set_bkg_tiles(18, 4, 2, 1, small_cloud_2_tile_map);
	}

	if (last_scene == FIELD) {
		hand_x = 0;
		hand_x_frac = hand_x << 8;
	}
}

void update_garden(void) {
	if (is_night) {

	} else {
		garden_sky_anim_counter += 1;
		if (garden_sky_anim_counter > 120) {
			garden_sky_anim_counter = 0;
			set_bkg_tiles(11, 4, 2, 1, small_cloud_1_tile_map);
		} else if (garden_sky_anim_counter > 100) {
			set_bkg_tiles(13, 5, 3, 1, big_cloud_2_tile_map);
		} else if (garden_sky_anim_counter > 80) {
			set_bkg_tiles(18, 4, 2, 1, small_cloud_2_tile_map);
		} else if (garden_sky_anim_counter > 60) {
			set_bkg_tiles(11, 4, 2, 1, small_cloud_2_tile_map);
		} else if (garden_sky_anim_counter > 40) {
			set_bkg_tiles(13, 5, 3, 1, big_cloud_1_tile_map);
		} else if (garden_sky_anim_counter > 20) {
			set_bkg_tiles(18, 4, 2, 1, small_cloud_1_tile_map);
		}
	}
}
