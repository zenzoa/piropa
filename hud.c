#pragma bank 255

#include <gbdk/platform.h>

#include "hand.h"
#include "scene.h"
#include "joypad.h"

#include "sprites/backgrounds/hud.h"

BANKREF(hud_bank)

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
	if (medicine_is_held) {
		set_bkg_tiles(0x01, 0x01, 2, 2, medicine_empty_tile_map);
	} else {
		set_bkg_tiles(0x01, 0x01, 2, 2, medicine_tile_map);
	}

	if (soap_is_held) {
		set_bkg_tiles(0x05, 0x01, 2, 2, soap_empty_tile_map);
	} else {
		set_bkg_tiles(0x05, 0x01, 2, 2, soap_tile_map);
	}

	set_bkg_tiles(0x09, 0x01, 2, 2, stats_tile_map);

	if (broom_is_held) {
		set_bkg_tiles(0x0d, 0x01, 2, 2, broom_empty_tile_map);
	} else {
		set_bkg_tiles(0x0d, 0x01, 2, 2, broom_tile_map);
	}

	if (moon_is_held) {
		set_bkg_tiles(0x11, 0x01, 2, 2, moon_empty_tile_map);
	} else {
		set_bkg_tiles(0x11, 0x01, 2, 2, moon_tile_map);
	}
}

void setup_hud_data(void) NONBANKED {
	SWITCH_ROM(BANK(hud));
	set_bkg_data(0xd0, 40, hud_tiles);
}

void setup_hud(void) {
	if (!is_night) {
		moon_is_held = 0;
	}
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
		moon_is_held = 0;
		set_bkg_tiles(0x11, 0x01, 2, 2, moon_tile_map);
		if (is_night && hand_state == HAND_MOON) {
			start_transition_to_scene(FIELD, FALSE);
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

uint8_t is_hand_over_info(void) {
	return (hand_x >= 68 && hand_x < 100 && hand_y < 48);
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

uint8_t handle_hud_input(uint8_t button_pressed) {
	if (button_pressed != A_BUTTON) {
		return FALSE;
	}

	if (is_hand_over_medicine()) {
		if (hold_medicine()) {
			set_hand_state(HAND_MEDICINE);
		} else {
			drop_all(0);
			set_hand_state(HAND_DEFAULT);
		}

	} else if (is_hand_over_soap()) {
		if (hold_soap()) {
			set_hand_state(HAND_SOAP);
		} else {
			drop_all(0);
			set_hand_state(HAND_DEFAULT);
		}

	} else if (is_hand_over_info()) {
		start_transition_to_scene(INFO, is_night);

	} else if (is_hand_over_broom()) {
		if (hold_broom()) {
			set_hand_state(HAND_BROOM);
		} else {
			drop_all(0);
			set_hand_state(HAND_DEFAULT);
		}

	} else if (is_hand_over_moon()) {
		if (hold_moon()) {
			set_hand_state(HAND_MOON);
		} else {
			drop_all(0);
			set_hand_state(HAND_DEFAULT);
		}

	} else {
		return FALSE;
	}

	return TRUE;
}
