#pragma bank 255

#include <gbdk/platform.h>

#include "hand.h"
#include "scene.h"
#include "joypad.h"
#include "common.h"
#include "audio.h"

#include "sprites/backgrounds/hud.h"

static const unsigned char medicine_tile_map[4] = { 0xd0, 0xd1, 0xda, 0xdb };
static const unsigned char medicine_empty_tile_map[4] = { 0xe4, 0xe5, 0xee, 0xef };

static const unsigned char soap_tile_map[4] = { 0xd2, 0xd3, 0xdc, 0xdd };
static const unsigned char soap_empty_tile_map[4] = { 0xe6, 0xe7, 0xf0, 0xf1 };

static const unsigned char stats_tile_map[4] = { 0xd4, 0xd5, 0xde, 0xdf };
static const unsigned char stats_empty_tile_map[4] = { 0xe8, 0xe9, 0xf2, 0xf3 };

static const unsigned char broom_tile_map[4] = { 0xd6, 0xd7, 0xe0, 0xe1 };
static const unsigned char broom_empty_tile_map[4] = { 0xea, 0xeb, 0xf4, 0xf5 };

static const unsigned char moon_tile_map[4] = { 0xd8, 0xd9, 0xe2, 0xe3 };
static const unsigned char moon_empty_tile_map[4] = { 0xec, 0xed, 0xf6, 0xf7 };

void draw_hud(void) BANKED {
	if (hand_state == HAND_MEDICINE) {
		set_bkg_tiles(0x01, 0x01, 2, 2, medicine_empty_tile_map);
	} else {
		set_bkg_tiles(0x01, 0x01, 2, 2, medicine_tile_map);
	}

	if (hand_state == HAND_SOAP) {
		set_bkg_tiles(0x05, 0x01, 2, 2, soap_empty_tile_map);
	} else {
		set_bkg_tiles(0x05, 0x01, 2, 2, soap_tile_map);
	}

	set_bkg_tiles(0x09, 0x01, 2, 2, stats_tile_map);

	if (hand_state == HAND_BROOM) {
		set_bkg_tiles(0x0d, 0x01, 2, 2, broom_empty_tile_map);
	} else {
		set_bkg_tiles(0x0d, 0x01, 2, 2, broom_tile_map);
	}

	if (hand_state == HAND_MOON || is_night) {
		set_bkg_tiles(0x11, 0x01, 2, 2, moon_empty_tile_map);
	} else {
		set_bkg_tiles(0x11, 0x01, 2, 2, moon_tile_map);
	}
}

void setup_hud_data(void) BANKED {
	set_banked_bkg_data(BANK(hud), 0xd0, 40, hud_tiles);
}

void drop_all(uint8_t except) BANKED {
	if (except != 1) {
		set_bkg_tiles(0x01, 0x01, 2, 2, medicine_tile_map);
	}
	if (except != 2) {
		set_bkg_tiles(0x05, 0x01, 2, 2, soap_tile_map);
	}
	if (except != 3) {
		set_bkg_tiles(0x0d, 0x01, 2, 2, broom_tile_map);
	}
	if (except != 4 && hand_state == HAND_MOON) {
		set_bkg_tiles(0x11, 0x01, 2, 2, moon_tile_map);
		if (is_night) {
			transition_to_scene(FIELD, FALSE);
		}
	}
}

static void hold_medicine(void) {
	if (hand_state == HAND_MEDICINE) {
		drop_all(0);
		set_hand_state(HAND_DEFAULT);
	} else {
		drop_all(1);
		set_bkg_tiles(0x01, 0x01, 2, 2, medicine_empty_tile_map);
		set_hand_state(HAND_MEDICINE);
	}
}

static void hold_soap(void) {
	if (hand_state == HAND_SOAP) {
		drop_all(0);
		set_hand_state(HAND_DEFAULT);
	} else {
		drop_all(2);
		set_bkg_tiles(0x05, 0x01, 2, 2, soap_empty_tile_map);
		set_hand_state(HAND_SOAP);
	}
}

static void hold_broom(void) {
	if (hand_state == HAND_BROOM) {
		drop_all(0);
		set_hand_state(HAND_DEFAULT);
	} else {
		drop_all(3);
		set_bkg_tiles(0x0d, 0x01, 2, 2, broom_empty_tile_map);
		set_hand_state(HAND_BROOM);
	}
}

static void hold_moon(void) {
	if (hand_state == HAND_MOON) {
		drop_all(0);
		set_hand_state(HAND_DEFAULT);
	} else {
		drop_all(4);
		set_bkg_tiles(0x11, 0x01, 2, 2, moon_empty_tile_map);
		set_hand_state(HAND_MOON);
	}
}

static uint8_t is_hand_over_medicine(void) {
	return (hand_x < 36 && hand_y < 48);
}

static uint8_t is_hand_over_soap(void) {
	return (hand_x >= 36 && hand_x < 68 && hand_y < 48);
}

static uint8_t is_hand_over_info(void) {
	return (hand_x >= 68 && hand_x < 100 && hand_y < 48);
}

static uint8_t is_hand_over_broom(void) {
	return (hand_x >= 100 && hand_x < 132 && hand_y < 48);
}

static uint8_t is_hand_over_moon(void) {
	return (hand_x >= 132 && hand_y < 48);
}

uint8_t handle_hud_input(uint8_t button_pressed) BANKED {
	if (button_pressed != A_BUTTON) {
		return FALSE;
	}

	if (is_hand_over_medicine()) {
		hold_medicine();

	} else if (is_hand_over_soap()) {
		hold_soap();

	} else if (is_hand_over_info()) {
		drop_all(0);
		transition_to_scene(INFO, is_night);

	} else if (is_hand_over_broom()) {
		hold_broom();

	} else if (is_hand_over_moon() && !is_night) {
		hold_moon();

	} else {
		return FALSE;
	}

	play_sfx(SFX_TAP);

	return TRUE;
}
