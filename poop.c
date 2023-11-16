#pragma bank 255

#include <gbdk/platform.h>

#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "frog.h"
#include "scene.h"

#include "sprites/backgrounds/poo.h"

BANKREF(poop_bank)

#define POOP_VRAM 0xfe
#define MAX_POOPS 6
uint8_t poop_count = 0;
uint8_t poops_to_add = 0;
uint8_t poops_scene[MAX_POOPS];
uint8_t poops_x[MAX_POOPS];
uint8_t poops_y[MAX_POOPS];

void setup_poop_data(void) NONBANKED {
	SWITCH_ROM(BANK(poo));
	set_bkg_data(POOP_VRAM, poo_TILE_COUNT, poo_tiles);
}

void reset_poops(void) {
	poop_count = 0;
	for (uint8_t i = 0; i < MAX_POOPS; i++) {
		poops_scene[i] = 0;
		poops_x[i] = 0;
		poops_y[i] = 0;
	}
}

void draw_poops(void) {
	for (uint8_t i = 0; i < MAX_POOPS; i++) {
		if (poops_scene[i] == current_scene && (poops_x[i] > 0 || poops_y[i] > 0)) {
			set_bkg_tile_xy(poops_x[i], poops_y[i], POOP_VRAM);
		}
	}
}

uint8_t is_poop_at(uint8_t x, uint8_t y) {
	for (uint8_t i = 0; i < MAX_POOPS; i++) {
		if (poops_scene[i] == current_scene && poops_x[i] == x && poops_y[i] == y) {
			return TRUE;
		}
	}
	return FALSE;
}

void add_poop_at(uint8_t i, uint8_t x, uint8_t y) {
	if (current_scene == POND || current_scene == GARDEN) {
		poops_scene[i] = current_scene;
	} else {
		poops_scene[i] = FIELD;
	}
	poops_x[i] = x;
	poops_y[i] = y;
	poop_count += 1;
	EMU_printf("");
	EMU_printf("POOP at %d %d", x, y);
	draw_poops();
}

void add_poop(uint8_t x, uint8_t y) {
	for (uint8_t i = 0; i < MAX_POOPS; i++) {
		if (poops_x[i] == 0 && poops_y[i] == 0) {
			if (!is_poop_at(x - 1, y)) {
				add_poop_at(i, x - 1, y);
			} else if (!is_poop_at(x + 2, y)) {
				add_poop_at(i, x + 2, y);
			} else if (!is_poop_at(x, y + 1)) {
				add_poop_at(i, x, y + 1);
			} else if (!is_poop_at(x + 1, y + 1)) {
				add_poop_at(i, x + 1, y + 1);
			} else if (!is_poop_at(x - 1, y + 1)) {
				add_poop_at(i, x - 1, y + 1);
			} else if (!is_poop_at(x + 2, y + 1)) {
				add_poop_at(i, x + 2, y + 1);
			} else if (!is_poop_at(x + 1, y)) {
				add_poop_at(i, x + 1, y);
			} else if (!is_poop_at(x, y)) {
				add_poop_at(i, x, y);
			}
			break;
		}
	}
}

void clean_poop_at(uint8_t x, uint8_t y) NONBANKED {
	for (uint8_t i = 0; i < MAX_POOPS; i++) {
		if (poops_scene[i] == current_scene &&
			(poops_x[i] == x || poops_x[i] == x + 1 || poops_x[i] == x - 1) &&
			(poops_y[i] == y || poops_y[i] == y + 1 || poops_y[i] == y - 1)) {
				if (poop_count > 0) {
					poop_count -= 1;
				}
				restore_x = poops_x[i];
				restore_y = poops_y[i];
				EMU_printf("");
				EMU_printf("CLEAN poop at %d, %d", poops_x[i], poops_y[i]);
				poops_x[i] = 0;
				poops_y[i] = 0;
		}
	}
}

void update_poops(void) {
	if (poops_to_add > 0) {
		for (uint8_t i = 0; i < poops_to_add; i++) {
			add_poop(frog_x / 8, frog_y / 8);
		}
		poops_to_add = 0;
	}
}
