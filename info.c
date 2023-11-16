#pragma bank 255

#include <gbdk/platform.h>

#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "frog.h"
#include "scene.h"
#include "joypad.h"

#include "sprites/backgrounds/info.h"
#include "sprites/backgrounds/numbers.h"
#include "sprites/backgrounds/lilypads.h"
#include "sprites/backgrounds/speed_icons.h"

const unsigned char lilypad_full_tile_map[4] = { 0x40, 0x41, 0x44, 0x45 };
const unsigned char lilypad_half_tile_map[4] = { 0x42, 0x43, 0x46, 0x47 };

const unsigned char speed_fast_tile_map[4] = { 0x50, 0x51, 0x56, 0x57 };
const unsigned char speed_medium_tile_map[4] = { 0x52, 0x53, 0x58, 0x59 };
const unsigned char speed_slow_tile_map[4] = { 0x54, 0x55, 0x5a, 0x5b };

const unsigned char speed_fast_selected_tile_map[4] = { 0x5c, 0x5d, 0x62, 0x63 };
const unsigned char speed_medium_selected_tile_map[4] = { 0x5e, 0x5f, 0x64, 0x65 };
const unsigned char speed_slow_selected_tile_map[4] = { 0x60, 0x61, 0x66, 0x67 };

BANKREF(info_bank)

void draw_stat(uint8_t value, uint8_t y) {
	switch(value) {
		case 0:
			break;
		case 1:
			set_bkg_tiles(0x06, y, 2, 2, lilypad_full_tile_map);
			break;
		case 2:
			set_bkg_tiles(0x06, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x08, y, 2, 2, lilypad_half_tile_map);
			break;
		case 3:
			set_bkg_tiles(0x06, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x08, y, 2, 2, lilypad_full_tile_map);
			break;
		case 4:
			set_bkg_tiles(0x06, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x08, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x0A, y, 2, 2, lilypad_half_tile_map);
			break;
		case 5:
			set_bkg_tiles(0x06, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x08, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x0A, y, 2, 2, lilypad_full_tile_map);
			break;
		case 6:
			set_bkg_tiles(0x06, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x08, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x0A, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x0C, y, 2, 2, lilypad_half_tile_map);
			break;
		case 7:
			set_bkg_tiles(0x06, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x08, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x0A, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x0C, y, 2, 2, lilypad_full_tile_map);
			break;
		case 8:
			set_bkg_tiles(0x06, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x08, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x0A, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x0C, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x0E, y, 2, 2, lilypad_half_tile_map);
			break;
		default:
			set_bkg_tiles(0x06, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x08, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x0A, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x0C, y, 2, 2, lilypad_full_tile_map);
			set_bkg_tiles(0x0E, y, 2, 2, lilypad_full_tile_map);
			break;
	}
}

void draw_number(uint8_t value, uint8_t x) {
	uint8_t hundreds_place = value / 100;
	uint8_t tens_place = (value % 100) / 10;
	uint8_t ones_place = (value % 100) % 10;
	if (hundreds_place > 0) {
		set_bkg_tile_xy(x, 0x0e, 0x30 + hundreds_place);
		set_bkg_tile_xy(x + 1, 0x0e, 0x30 + tens_place);
		set_bkg_tile_xy(x + 2, 0x0e, 0x30 + ones_place);
	} else if (tens_place > 0) {
		set_bkg_tile_xy(x, 0x0e, 0x30 + tens_place);
		set_bkg_tile_xy(x + 1, 0x0e, 0x30 + ones_place);
	} else {
		set_bkg_tile_xy(x, 0x0e, 0x30 + ones_place);
	}
}

void draw_speed(void) {
	EMU_printf("");
	EMU_printf("speed: %d", game_speed);
	if (game_speed == SPEED_SLOW) {
		set_bkg_tiles(0x07, 0x10, 2, 2, speed_slow_selected_tile_map);
	} else {
		set_bkg_tiles(0x07, 0x10, 2, 2, speed_slow_tile_map);
	}

	if (game_speed == SPEED_FAST) {
		set_bkg_tiles(0x0B, 0x10, 2, 2, speed_fast_selected_tile_map);
	} else {
		set_bkg_tiles(0x0B, 0x10, 2, 2, speed_fast_tile_map);
	}

	if (game_speed == SPEED_MEDIUM) {
		set_bkg_tiles(0x09, 0x10, 2, 2, speed_medium_selected_tile_map);
	} else {
		set_bkg_tiles(0x09, 0x10, 2, 2, speed_medium_tile_map);
	}
}

void setup_info_data(void) NONBANKED {
	SWITCH_ROM(BANK(info));
	set_bkg_data(0, info_TILE_COUNT, info_tiles);
	set_bkg_tiles(0, 0, 20, 18, info_map);

	SWITCH_ROM(BANK(numbers));
	set_bkg_data(0x30, numbers_TILE_COUNT, numbers_tiles);

	SWITCH_ROM(BANK(lilypads));
	set_bkg_data(0x40, lilypads_TILE_COUNT, lilypads_tiles);

	SWITCH_ROM(BANK(speed_icons));
	set_bkg_data(0x50, speed_icons_TILE_COUNT, speed_icons_tiles);
}

void setup_info(void) {
	draw_stat(love, 0x05);
	draw_stat(stomach, 0x08);
	draw_stat(energy, 0x0B);

	draw_number(age, 0x06);
	draw_number(weight, 0x0e);

	draw_speed();
}

void handle_info_input(uint8_t button_pressed) {
	switch(button_pressed) {
		case A_BUTTON:
			start_transition_to_scene(last_scene, is_night);
			break;

		case B_BUTTON:
			start_transition_to_scene(last_scene, is_night);
			break;

		case LEFT_BUTTON:
			if (game_speed == SPEED_FAST) {
				game_speed = SPEED_MEDIUM;
			} else if (game_speed == SPEED_MEDIUM) {
				game_speed = SPEED_SLOW;
			}
			draw_speed();
			break;

		case RIGHT_BUTTON:
			if (game_speed == SPEED_SLOW) {
				game_speed = SPEED_MEDIUM;
			} else if (game_speed == SPEED_MEDIUM) {
				game_speed = SPEED_FAST;
			}
			draw_speed();
			break;
	}
}
