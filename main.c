#include <gbdk/platform.h>
#include <rand.h>
#include <time.h>

#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "save.h"
#include "frog.h"
#include "hand.h"
#include "bugs.h"
#include "poop.h"
#include "joypad.h"
#include "scene.h"

void main(void) {
	DISPLAY_ON;
	SHOW_BKG;
	SHOW_SPRITES;
	SPRITES_8x8;
	OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);

	SWITCH_ROM(BANK(bugs_bank));
	setup_bugs_data();

	SWITCH_ROM(BANK(poop_bank));
	setup_poop_data();

	load_data();
	setup_scene(TITLE);

	SWITCH_ROM(BANK(frog_bank));
	setup_frog(!has_save);

	SWITCH_ROM(BANK(hand_bank));
	setup_hand();

	last_time = clock() / CLOCKS_PER_SEC;

	while(1) {
		if (!is_transitioning && (current_scene == FIELD || current_scene == POND || current_scene == GARDEN)) {
			SWITCH_ROM(BANK(frog_bank));
			update_frog();

			SWITCH_ROM(BANK(hand_bank));
			update_hand();

			SWITCH_ROM(BANK(poop_bank));
			update_poops();

			current_time = clock() / CLOCKS_PER_SEC;
			if (current_time >= last_time + 60) {
				last_time = clock() / CLOCKS_PER_SEC;
				SWITCH_ROM(BANK(frog_bank));
				update_stats();
				SWITCH_ROM(BANK(bugs_bank));
				respawn_bugs();
			}
		}

		handle_input();

		update_scene();

		vsync(); // wait for next frame
	}
}
