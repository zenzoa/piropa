#include <gbdk/platform.h>

#include "hand.h"
#include "scene.h"
#include "field.h"

#include "sprites/backgrounds/hud.h"

#define HUD_VRAM 0xd0

const unsigned char medicine_tile_map[4] = { 0xd0, 0xd1, 0xda, 0xdb };
const unsigned char medicine_empty_tile_map[4] = { 0xe4, 0xe5, 0xee, 0xef };

const unsigned char soap_tile_map[4] = { 0xd2, 0xd3, 0xdc, 0xdd };
const unsigned char soap_empty_tile_map[4] = { 0xe6, 0xe7, 0xf0, 0xf1 };

const unsigned char stats_tile_map[4] = { 0xd4, 0xd5, 0xde, 0xdf };
const unsigned char stats_empty_tile_map[4] = { 0xe8, 0xe9, 0xf2, 0xf3 };

const unsigned char broom_tile_map[4] = { 0xd6, 0xd7, 0xe0, 0xe1 };
const unsigned char broom_empty_tile_map[4] = { 0xea, 0xeb, 0xf4, 0xf5 };

const unsigned char moon_tile_map[4] = { 0xd8, 0xd9, 0xe2, 0xe3 };
const unsigned char moon_empty_tile_map[4] = { 0xec, 0xed, 0xf6, 0xf7 };

uint8_t medicine_is_held = 0;
uint8_t soap_is_held = 0;
uint8_t broom_is_held = 0;
uint8_t moon_is_held = 0;

void draw_hud(void) {
	set_bkg_tiles(0x01, 0x01, 2, 2, medicine_tile_map);
	set_bkg_tiles(0x05, 0x01, 2, 2, soap_tile_map);
	set_bkg_tiles(0x09, 0x01, 2, 2, stats_tile_map);
	set_bkg_tiles(0x0d, 0x01, 2, 2, broom_tile_map);
	if (moon_is_held) {
		set_bkg_tiles(0x11, 0x01, 2, 2, moon_empty_tile_map);
	} else {
		set_bkg_tiles(0x11, 0x01, 2, 2, moon_tile_map);
	}
}

void setup_hud(void) {
	SWITCH_ROM(BANK(hud));
	set_bkg_data(HUD_VRAM, 40, hud_tiles);

	if (!is_night) {
		moon_is_held = 0;
	}

	draw_hud();
}

void drop_all(uint8_t except) {
	if (except != 1) {
		medicine_is_held = 0;
		set_bkg_tiles(0x01, 0x01, 2, 2, medicine_tile_map);
	}
	if (except != 2) {
		soap_is_held = 0;
		set_bkg_tiles(0x05, 0x01, 2, 2, soap_tile_map);
	}
	if (except != 3) {
		broom_is_held = 0;
		set_bkg_tiles(0x0d, 0x01, 2, 2, broom_tile_map);
	}
	if (except != 4) {
		if (is_night && current_scene == FIELD) {
			return_moon_to_sky();
		} else if (!is_night) {
			moon_is_held = 0;
			set_bkg_tiles(0x11, 0x01, 2, 2, moon_tile_map);
		}
	}
}

uint8_t is_hand_over_medicine(void) {
	return (hand_x < 36 && hand_y < 48);
}

uint8_t hold_medicine(void) {
	if (medicine_is_held) {
		return FALSE;
	} else {
		drop_all(1);
		medicine_is_held = 1;
		set_bkg_tiles(0x01, 0x01, 2, 2, medicine_empty_tile_map);
		return TRUE;
	}
}

uint8_t is_hand_over_soap(void) {
	return (hand_x >= 36 && hand_x < 68 && hand_y < 48);
}

uint8_t hold_soap(void) {
	if (soap_is_held) {
		return FALSE;
	} else {
		drop_all(2);
		soap_is_held = 1;
		set_bkg_tiles(0x05, 0x01, 2, 2, soap_empty_tile_map);
		return TRUE;
	}
}

uint8_t is_hand_over_broom(void) {
	return (hand_x >= 100 && hand_x < 132 && hand_y < 48);
}

uint8_t hold_broom(void) {
	if (broom_is_held) {
		return FALSE;
	} else {
		drop_all(3);
		broom_is_held = 1;
		set_bkg_tiles(0x0d, 0x01, 2, 2, broom_empty_tile_map);
		return TRUE;
	}
}

uint8_t is_hand_over_moon(void) {
	return (hand_x >= 132 && hand_y < 48);
}

uint8_t hold_moon(void) {
	if (moon_is_held) {
		return FALSE;
	} else {
		drop_all(4);
		moon_is_held = 1;
		set_bkg_tiles(0x11, 0x01, 2, 2, moon_empty_tile_map);
		return TRUE;
	}
}
