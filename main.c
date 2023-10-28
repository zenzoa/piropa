#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <rand.h>
#include <time.h>

#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "clock.h"
#include "save.h"
#include "animation.h"
#include "frog.h"
#include "hand.h"
#include "hud.h"
#include "joypad.h"
#include "scene.h"

uint8_t last_sprite;

uint8_t frames = 0;
uint8_t last_update_minutes = 0;
uint8_t last_update_seconds = 0;

time_t last_time = 0;
time_t current_time = 0;

void draw_sprites(void) {
	last_sprite = 0;

	draw_hand(&last_sprite);

	SWITCH_ROM(BANK(frog_bank));
	draw_frog(&last_sprite);

	hide_sprites_range(last_sprite, MAX_HARDWARE_SPRITES);
}

void main(void) {
	DISPLAY_ON;
	SHOW_BKG;
	SHOW_SPRITES;
	SPRITES_8x8;
	OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);

	initrand(DIV_REG);

	setup_scene(FIELD);

	SWITCH_ROM(BANK(frog_bank));
	setup_frog();

	setup_hand();

	setup_hud();

	last_time = clock() / CLOCKS_PER_SEC;

	while(1) {
		SWITCH_ROM(BANK(frog_bank));
		update_frog();
		update_hand();

		handle_input();

		update_scene();

		draw_sprites();

		current_time = clock() / CLOCKS_PER_SEC;
		if (current_time >= last_time + 60) {
			last_time = clock() / CLOCKS_PER_SEC;
			SWITCH_ROM(BANK(frog_bank));
			update_stats();
		}

		vsync(); // wait for next frame
	}
}
