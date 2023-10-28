#include <gbdk/platform.h>

#include "hand.h"

#include "sprites/backgrounds/field.h"
#include "sprites/backgrounds/clouds.h"
#include "sprites/backgrounds/basket.h"
#include "sprites/backgrounds/poo.h"

#define CLOUDS_VRAM 0x70
#define BASKET_VRAM 0xf8
#define POO_VRAM 0xfe

const unsigned char big_cloud_1_tile_map[3] = { 0x70, 0x71, 0x72 };
const unsigned char big_cloud_2_tile_map[3] = { 0x73, 0x74, 0x75 };

const unsigned char small_cloud_1_tile_map[2] = { 0x70, 0x72 };
const unsigned char small_cloud_2_tile_map[2] = { 0x73, 0x75 };

const unsigned char basket_closed_tile_map[3] = { 0xf8, 0xf9, 0xfa };
const unsigned char basket_open_tile_map[3] = { 0xfb, 0xfc, 0xfd };

uint8_t cloud_anim_counter = 0;
uint8_t basket_is_open = FALSE;

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

void update_poops(uint8_t poops_x[6], uint8_t poops_y[6], uint8_t max_poops) {
	SWITCH_ROM(BANK(field));
	set_bkg_tiles(0, 0, 20, 18, field_map);
	for (uint8_t i = 0; i < max_poops; i++) {
		if (poops_x[i] > 0 || poops_y[i] > 0) {
			set_bkg_tile_xy(poops_x[i], poops_y[i], POO_VRAM);
		}
	}
}

void setup_field(void) {
	SWITCH_ROM(BANK(field));
	set_bkg_data(0, field_TILE_COUNT, field_tiles);
	set_bkg_tiles(0, 0, 20, 18, field_map);

	SWITCH_ROM(BANK(clouds));
	set_bkg_data(CLOUDS_VRAM, clouds_TILE_COUNT, clouds_tiles);
	set_bkg_tiles(6, 5, 3, 1, big_cloud_2_tile_map);
	set_bkg_tiles(8, 4, 2, 1, small_cloud_1_tile_map);
	set_bkg_tiles(12, 5, 2, 1, small_cloud_2_tile_map);

	SWITCH_ROM(BANK(basket));
	set_bkg_data(BASKET_VRAM, basket_TILE_COUNT, basket_tiles);
	set_bkg_tiles(13, 8, 3, 1, basket_closed_tile_map);

	SWITCH_ROM(BANK(poo));
	set_bkg_data(POO_VRAM, poo_TILE_COUNT, poo_tiles);
}

void update_field(void) {
	cloud_anim_counter += 1;
	if (cloud_anim_counter > 120) {
		cloud_anim_counter = 0;
		set_bkg_tiles(6, 5, 3, 1, big_cloud_2_tile_map);
	} else if (cloud_anim_counter > 100) {
		set_bkg_tiles(8, 4, 2, 1, small_cloud_1_tile_map);
	} else if (cloud_anim_counter > 80) {
		set_bkg_tiles(12, 5, 2, 1, small_cloud_2_tile_map);
	} else if (cloud_anim_counter > 60) {
		set_bkg_tiles(6, 5, 3, 1, big_cloud_1_tile_map);
	} else if (cloud_anim_counter > 40) {
		set_bkg_tiles(8, 4, 2, 1, small_cloud_2_tile_map);
	} else if (cloud_anim_counter > 20) {
		set_bkg_tiles(12, 5, 2, 1, small_cloud_1_tile_map);
	}

	if (hand_x + 16 >= 120 && hand_x < 136 && hand_y + 16 >= 80 && hand_y < 96) {
		set_basket(TRUE);
	} else {
		set_basket(FALSE);
	}
}
