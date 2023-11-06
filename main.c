#include <gbdk/platform.h>
#include <rand.h>
#include <time.h>

#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "clock.h"
#include "save.h"
#include "frog.h"
#include "hand.h"
#include "joypad.h"
#include "scene.h"

uint8_t frames = 0;
uint8_t last_update_minutes = 0;
uint8_t last_update_seconds = 0;

time_t last_time = 0;
time_t current_time = 0;

void main(void) {
	DISPLAY_ON;
	SHOW_BKG;
	SHOW_SPRITES;
	SPRITES_8x8;
	OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);

	initrand(DIV_REG);

	load_data();
	SWITCH_ROM(BANK(frog_bank));
	setup_frog(!has_save);

	setup_hand();

	setup_scene(TITLE);

	last_time = clock() / CLOCKS_PER_SEC;

	while(1) {
		if (!is_transitioning && (current_scene == FIELD || current_scene == POND || current_scene == GARDEN)) {
			SWITCH_ROM(BANK(frog_bank));
			update_frog();
			update_hand();

			current_time = clock() / CLOCKS_PER_SEC;
			if (current_time >= last_time + 60) {
				last_time = clock() / CLOCKS_PER_SEC;
				update_stats();
			}
		}

		handle_input();

		update_scene();

		vsync(); // wait for next frame
	}
}
