#include <gbdk/platform.h>

#include "hand.h"

#include "sprites/backgrounds/field.h"
#include "sprites/backgrounds/basket.h"

const unsigned char basket_closed_tile_map[3] = { 0xf1, 0xf2, 0xf3 };
const unsigned char basket_open_tile_map[3] = { 0xf4, 0xf5, 0xf6 };

uint8_t basket_is_open = FALSE;

void set_basket(uint8_t is_open) {
	if (is_open != basket_is_open) {
		if (is_open) {
			set_bkg_tiles(13, 7, 3, 1, basket_open_tile_map);
		} else {
			set_bkg_tiles(13, 7, 3, 1, basket_closed_tile_map);
		}
		basket_is_open = is_open;
	}
}

void setup_field(void) {
	SWITCH_ROM(BANK(field));
	set_bkg_data(0, field_TILE_COUNT, field_tiles);
	set_bkg_tiles(0, 0, 20, 18, field_map);

	SWITCH_ROM(BANK(basket));
	set_bkg_data(0xf1, basket_TILE_COUNT, basket_tiles);
	set_bkg_tiles(13, 7, 3, 1, basket_closed_tile_map);
}

void update_field(void) {
	if (hand_x + 16 >= 112 && hand_x < 136 && hand_y + 16 >= 72 && hand_y < 88) {
		set_basket(TRUE);
	} else {
		set_basket(FALSE);
	}
}
