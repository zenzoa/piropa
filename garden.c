#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "shared_variables.h"

#include "sprites/backgrounds/garden.h"
#include "sprites/backgrounds/garden_night.h"
#include "sprites/backgrounds/clouds.h"
#include "sprites/backgrounds/plants.h"
#include "cloud_tile_maps.h"

BANKREF(garden_bank)

uint8_t plant_anim_counter[PLANT_COUNT];
uint8_t plant_anim_frame[PLANT_COUNT];

const unsigned char plant_0_tile_map[4] = { 0x06, 0x06, 0x50, 0x51 };
const unsigned char plant_1_tile_map[4] = { 0x53, 0x54, 0x50, 0x52 };
const unsigned char plant_2_tile_map[4] = { 0x55, 0x56, 0x50, 0x52 };
const unsigned char plant_3_tile_map[4] = { 0x57, 0x58, 0x50, 0x52 };

const unsigned char plant_watered_0_tile_map[2] = { 0x59, 0x5a };
const unsigned char plant_watered_1_tile_map[2] = { 0x5b, 0x5c };
const unsigned char plant_watered_2_tile_map[2] = { 0x5d, 0x5e };

uint8_t garden_sky_anim_counter = 0;

void draw_plants(void) {
	switch(plant_stage[0]) {
		case 0:
			set_bkg_tiles(PLANT_0_X, PLANT_0_Y, 2, 2, plant_0_tile_map);
			break;
		case 1:
			set_bkg_tiles(PLANT_0_X, PLANT_0_Y, 2, 2, plant_1_tile_map);
			break;
		case 2:
			set_bkg_tiles(PLANT_0_X, PLANT_0_Y, 2, 2, plant_2_tile_map);
			break;
		default:
			set_bkg_tiles(PLANT_0_X, PLANT_0_Y, 2, 2, plant_3_tile_map);
	}
	switch(plant_stage[1]) {
		case 0:
			set_bkg_tiles(PLANT_1_X, PLANT_1_Y, 2, 2, plant_0_tile_map);
			break;
		case 1:
			set_bkg_tiles(PLANT_1_X, PLANT_1_Y, 2, 2, plant_1_tile_map);
			break;
		case 2:
			set_bkg_tiles(PLANT_1_X, PLANT_1_Y, 2, 2, plant_2_tile_map);
			break;
		default:
			set_bkg_tiles(PLANT_1_X, PLANT_1_Y, 2, 2, plant_3_tile_map);
	}
	switch(plant_stage[2]) {
		case 0:
			set_bkg_tiles(PLANT_2_X, PLANT_2_Y, 2, 2, plant_0_tile_map);
			break;
		case 1:
			set_bkg_tiles(PLANT_2_X, PLANT_2_Y, 2, 2, plant_1_tile_map);
			break;
		case 2:
			set_bkg_tiles(PLANT_2_X, PLANT_2_Y, 2, 2, plant_2_tile_map);
			break;
		default:
			set_bkg_tiles(PLANT_2_X, PLANT_2_Y, 2, 2, plant_3_tile_map);
	}
}

void update_plants(void) {
	uint8_t redraw = FALSE;

	for (uint8_t i = 0; i < PLANT_COUNT; i++) {
		if (plant_is_watered[i]) {
			plant_age[i] += 1;
			if (plant_age[i] >= 2 * (game_speed + 1)) {
				plant_age[i] = 0;
				plant_is_watered[i] = FALSE;
				if (plant_stage[i] < 3) {
					plant_stage[i] += 1;
					redraw = TRUE;
				}
			}
		}
	}

	if (redraw && current_scene == GARDEN) {
		draw_plants();
	}
}

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

	SWITCH_ROM(BANK(plants));
	set_bkg_data(0x50, plants_TILE_COUNT, plants_tiles);
}

void setup_garden(void) {
	if (!is_night) {
		garden_sky_anim_counter = 0;
		set_bkg_tiles(11, 4, 2, 1, small_cloud_1_tile_map);
		set_bkg_tiles(13, 5, 3, 1, big_cloud_2_tile_map);
		set_bkg_tiles(18, 4, 2, 1, small_cloud_2_tile_map);
	}

	for (uint8_t i = 0; i < PLANT_COUNT; i++) {
		if (plant_stage[i] > 3) {
			plant_stage[i] = 3;
			plant_anim_counter[i] = i;
		}
	}

	draw_plants();
}

void update_garden(void) {
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

	for (uint8_t i = 0; i < PLANT_COUNT; i++) {
		if (plant_is_watered[i]) {
			plant_anim_counter[i] += 1;
			if (plant_anim_counter[i] > 16) {
				plant_anim_counter[i] = 0;
				plant_anim_frame[i] += 1;

				uint8_t plant_x = i == 0 ? PLANT_0_X : (i == 1 ? PLANT_1_X : PLANT_2_X);
				uint8_t plant_y = i == 0 ? PLANT_0_Y : (i == 1 ? PLANT_1_Y : PLANT_2_Y);

				if (plant_anim_frame[i] == 1) {
					set_bkg_tiles(plant_x, plant_y + 1, 2, 1, plant_watered_0_tile_map);
				} else if (plant_anim_frame[i] == 2) {
					set_bkg_tiles(plant_x, plant_y + 1, 2, 1, plant_watered_1_tile_map);
				} else {
					set_bkg_tiles(plant_x, plant_y + 1, 2, 1, plant_watered_2_tile_map);
					plant_anim_frame[i] = 0;
				}
			}
		}
	}

	if (watering_plant > 0) {
		plant_is_watered[watering_plant - 1] = TRUE;
		watering_plant = 0;
	}
}

void restore_garden_tile(uint8_t x, uint8_t y) NONBANKED {
	SWITCH_ROM(BANK(garden));
	uint8_t original_tile = garden_map[y * 20 + x];
	set_bkg_tile_xy(x, y, original_tile);
}
