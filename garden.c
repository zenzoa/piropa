#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "sprites/backgrounds/garden.h"
#include "sprites/backgrounds/garden_night.h"
#include "sprites/backgrounds/clouds.h"
#include "cloud_tile_maps.h"
#include "sprites/backgrounds/plants.h"

BANKREF(garden_bank)

#define PLANT_COUNT 3
uint8_t plant_counter[PLANT_COUNT];
uint8_t plant_stage[PLANT_COUNT];
uint8_t plant_is_watered[PLANT_COUNT];

const unsigned char plant_0_tile_map[4] = { 0x06, 0x06, 0x50, 0x51 };
const unsigned char plant_1_tile_map[4] = { 0x53, 0x54, 0x50, 0x52 };
const unsigned char plant_2_tile_map[4] = { 0x55, 0x56, 0x50, 0x52 };
const unsigned char plant_3_tile_map[4] = { 0x57, 0x58, 0x50, 0x52 };

uint8_t garden_sky_anim_counter = 0;

void draw_plants(void) {
	switch(plant_stage[0]) {
		case 0:
			set_bkg_tiles(6, 11, 2, 2, plant_0_tile_map);
			break;
		case 1:
			set_bkg_tiles(6, 11, 2, 2, plant_1_tile_map);
			break;
		case 2:
			set_bkg_tiles(6, 11, 2, 2, plant_2_tile_map);
			break;
		case 3:
			set_bkg_tiles(6, 11, 2, 2, plant_3_tile_map);
			break;
	}
	switch(plant_stage[1]) {
		case 0:
			set_bkg_tiles(10, 11, 2, 2, plant_0_tile_map);
			break;
		case 1:
			set_bkg_tiles(10, 11, 2, 2, plant_1_tile_map);
			break;
		case 2:
			set_bkg_tiles(10, 11, 2, 2, plant_2_tile_map);
			break;
		case 3:
			set_bkg_tiles(10, 11, 2, 2, plant_3_tile_map);
			break;
	}
	switch(plant_stage[2]) {
		case 0:
			set_bkg_tiles(14, 11, 2, 2, plant_0_tile_map);
			break;
		case 1:
			set_bkg_tiles(14, 11, 2, 2, plant_1_tile_map);
			break;
		case 2:
			set_bkg_tiles(14, 11, 2, 2, plant_2_tile_map);
			break;
		case 3:
			set_bkg_tiles(14, 11, 2, 2, plant_3_tile_map);
			break;
	}
}

void update_plants(uint8_t game_speed) {
	uint8_t redraw = FALSE;

	for (uint8_t i = 0; i < PLANT_COUNT; i++) {
		if (plant_is_watered[i]) {
			plant_counter[i] += 1;
			if (plant_counter[i] >= 1 + (game_speed * 2)) {
				plant_is_watered[i] = FALSE;
				if (plant_stage[i] < 3) {
					plant_stage[i] += 1;
					redraw = TRUE;
				}
			}
		}
	}

	if (redraw) {
		draw_plants();
	}
}

void setup_garden_data(uint8_t is_night) NONBANKED {
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

	SWITCH_ROM(BANK(plants));
	set_bkg_data(0x50, plants_TILE_COUNT, plants_tiles);
}

void setup_garden(uint8_t is_night) {
	if (!is_night) {
		garden_sky_anim_counter = 0;
		set_bkg_tiles(11, 4, 2, 1, small_cloud_1_tile_map);
		set_bkg_tiles(13, 5, 3, 1, big_cloud_2_tile_map);
		set_bkg_tiles(18, 4, 2, 1, small_cloud_2_tile_map);
	}

	draw_plants();
}

void update_garden(uint8_t is_night) {
	if (!is_night) {
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

void restore_garden_tile(uint8_t x, uint8_t y) NONBANKED {
	SWITCH_ROM(BANK(garden));
	uint8_t original_tile = garden_map[y * 20 + x];
	set_bkg_tile_xy(x, y, original_tile);
}
