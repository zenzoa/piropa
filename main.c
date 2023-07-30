#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "clock.h"
#include "save.h"
#include "animation.h"
#include "frog.h"
#include "hand.h"
#include "hud.h"

#include "sprites/backgrounds/field.h"

uint8_t last_sprite;

uint8_t frames = 0;
uint8_t last_update_minutes = 0;
uint8_t last_update_seconds = 0;

uint8_t joypad_value;
uint8_t a_button_pressed = FALSE;
uint8_t b_button_pressed = FALSE;

uint8_t local_frog_x;
uint8_t local_frog_y;

void handle_dpad() {
	SWITCH_ROM(BANK(hand_bank));
	if (joypad_value & J_LEFT) {
		if (joypad_value & J_UP) {
			move_hand_by_frac(-181, -181);
		} else if (joypad_value & J_DOWN) {
			move_hand_by_frac(-181, 181);
		} else {
			move_hand_by_frac(-256, 0);
		}
	} else if (joypad_value & J_RIGHT) {
		if (joypad_value & J_UP) {
			move_hand_by_frac(181, -181);
		} else if (joypad_value & J_DOWN) {
			move_hand_by_frac(181, 181);
		} else {
			move_hand_by_frac(256, 0);
		}
	} else if (joypad_value & J_UP) {
		move_hand_by_frac(0, -256);
	} else if (joypad_value & J_DOWN) {
		move_hand_by_frac(0, 256);
	}
}

void handle_a_button() {
	if (joypad_value & J_A && !a_button_pressed) {
		a_button_pressed = TRUE;
		// some stuff
	} else if (!(joypad_value & J_A)) {
		a_button_pressed = FALSE;
	}
}

void handle_b_button() {
	if (joypad_value & J_B && !b_button_pressed) {
		b_button_pressed = TRUE;
		// some stuff
	} else if (!(joypad_value & J_B)) {
		b_button_pressed = FALSE;
	}
}

void handle_input() {
	joypad_value = joypad();
	handle_dpad();
	handle_a_button();
	handle_b_button();
}

void draw_sprites() {
	last_sprite = 0;

	SWITCH_ROM(BANK(hand_bank));
	draw_hand(&last_sprite, local_frog_x);

	SWITCH_ROM(BANK(frog_bank));
	draw_frog(&last_sprite);
	local_frog_x = frog_x;

	hide_sprites_range(last_sprite, MAX_HARDWARE_SPRITES);
}

void main() {
	DISPLAY_ON;
	SHOW_BKG;
	SHOW_SPRITES;
	SPRITES_8x8;
	OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);

	SWITCH_ROM(BANK(field));
	set_bkg_data(0, field_TILE_COUNT, field_tiles);
	set_bkg_tiles(0, 0, 20, 18, field_map);

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
		handle_input();

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
