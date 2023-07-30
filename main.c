#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <rand.h>

#include "clock.h"
#include "save.h"
#include "animation.h"
#include "frog.h"
#include "hand.h"
#include "hud.h"
#include "joypad.h"
#include "field.h"

uint8_t last_sprite;

uint8_t frames = 0;
uint8_t last_update_minutes = 0;
uint8_t last_update_seconds = 0;

uint8_t local_frog_x;
uint8_t local_frog_y;

void draw_sprites() {
	last_sprite = 0;

	SWITCH_ROM(BANK(hand_bank));
	draw_hand(&last_sprite, local_frog_x);

	SWITCH_ROM(BANK(frog_bank));
	draw_frog(&last_sprite);

	hide_sprites_range(last_sprite, MAX_HARDWARE_SPRITES);
}

void main() {
	DISPLAY_ON;
	SHOW_BKG;
	SHOW_SPRITES;
	SPRITES_8x8;
	OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);

	initrand(DIV_REG);

	setup_field();

	SWITCH_ROM(BANK(frog_bank));
	setup_frog();

	SWITCH_ROM(BANK(hand_bank));
	setup_hand();

	if (load_data()) {
		read_clock();
		update_stats();
		last_update_minutes = minutes;
		last_update_seconds = seconds;
	} else {
		reset_clock();
	}

	setup_hud();

	while(1) {
		SWITCH_ROM(BANK(frog_bank));
		update_frog();
		local_frog_x = frog_x;

		handle_input();

		update_field();

		draw_sprites();

		frames += 1;
		if (frames >= 60) {
			frames = 0;
			read_clock();
			update_hud_clock();
			draw_hud();
			if (minutes != last_update_minutes && seconds >= last_update_seconds) {
				last_update_minutes = minutes;
				update_stats();
				save_data();
			}
		}

		wait_vbl_done(); // wait for next frame
	}
}
