#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "clock.h"
#include "frog.h"
#include "hand.h"
#include "sprites/background/bg_main.h"

uint8_t joypad_current = 0;
uint8_t button_pressed = 0;

uint8_t animation_counter = 0;
uint8_t animation_speed = 32;

void read_joypad();
void draw_sprites();
uint8_t is_hand_on_frog();

/* ========================================================================= */

void main(void) {
	DISPLAY_ON;
	SHOW_BKG;
	SHOW_SPRITES;
	SPRITES_8x8;
	OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);

	// TODO: read save data and update frog based on time that has passed
	reset_clock(); // do this when new frog is born

	uint8_t old_bank = CURRENT_BANK;
	SWITCH_ROM(BANK(bg_main));
	set_bkg_data(0, bg_main_TILE_COUNT, bg_main_tiles);
	set_bkg_tiles(0, 0, 20, 18, bg_main_map);
	SWITCH_ROM(old_bank);

	init_hand();
	init_frog();

	while(1) {
		read_joypad();

		if (animation_counter >= animation_speed) {
			update_frog();
			animation_counter = 0;
		}
		animation_counter++;

		draw_sprites();

		wait_vbl_done(); // wait for next frame
	}
}

void read_joypad() {
	joypad_current = joypad();

	if (joypad_current & J_LEFT) {
		if (joypad_current & J_UP) {
			move_hand(-181, -181); // sqrt(1/2) -> Q8.8
		} else if (joypad_current & J_DOWN) {
			move_hand(-181, 181);
		} else {
			move_hand(-256, 0); // 1 -> Q8.8
		}
	} else if (joypad_current & J_RIGHT) {
		if (joypad_current & J_UP) {
			move_hand(181, -181);
		} else if (joypad_current & J_DOWN) {
			move_hand(181, 181);
		} else {
			move_hand(256, 0);
		}
	} else {
		if (joypad_current & J_UP) {
			move_hand(0, -256);
		} else if (joypad_current & J_DOWN) {
			move_hand(0, 256);
		}
	}

	if (joypad_current & J_A && button_pressed == 0) {
		button_pressed = 1;

		uint8_t x = 0;
		uint8_t y = 0;
		get_hand_position(&x, &y);

		// menu
		if (y > 132) {
			// jar
			if (x <= 40) {
				if (hand_type == JAR_EMPTY || hand_type == JAR_FULL || hand_type == JAR_2_3 || hand_type == JAR_1_3) {
					set_hand_type(DEFAULT_HAND);
				} else {
					set_hand_type(JAR_EMPTY);
					// TODO: replace icon with outline
				}
			}
			// soap
			else if (x > 40 && x <= 72) {
				if (hand_type == HOLD_SOAP) {
					set_hand_type(DEFAULT_HAND);
				} else {
					set_hand_type(HOLD_SOAP);
					// TODO: replace icon with outline
				}
			}
			// moon
			else if (x > 72 && x <= 104) {
				if (hand_type == HOLD_MOON) {
					set_hand_type(DEFAULT_HAND);
				} else {
					set_hand_type(HOLD_MOON);
					// TODO: replace icon with outline
				}
			}
			// food
			else if (x <= 136) {
				// TODO: check contents and fill hand with next item in list
			}
			// time
			else {
				// TODO: open clock screen
			}

		} else if (is_hand_on_frog()) {
			switch (hand_type) {
				case DEFAULT_HAND:
					set_hand_type(TICKLE_1);
					// tickle frog
					break;

				case TICKLE_1:
					set_hand_type(TICKLE_2);
					// tickle frog
					break;

				case TICKLE_2:
					set_hand_type(TICKLE_1);
					// tickle frog
					break;

				case JAR_FULL:
					// animate pouring
					// make frog sad (and wet)
					break;

				case JAR_2_3:
					// animate pouring
					// make frog sad (and wet)
					break;

				case JAR_1_3:
					// animate pouring
					// make frog sad (and wet)
					break;

				case JAR_EMPTY:
					// animate pouring... nothing
					// confused frog reaction?
					break;

				case HOLD_SOAP:
					// bathe frog
					break;

				case HOLD_MOON:
					// frog reacts... happily? shyly? depends on how sleepy? do we need a confused reaction?
					break;

				case HOLD_STRAWBERRY:
					// drop beside frog and animate eating it (hide hand while this happens)
					break;

				case HOLD_BLUEBERRY:
					// drop beside frog and animate eating it (hide hand while this happens)
					break;

				case HOLD_BLACKBERRY:
					// drop beside frog and animate eating it (hide hand while this happens)
					break;
			}

		} else if (hand_type == TICKLE_1 || hand_type == TICKLE_2) {
			set_hand_type(DEFAULT_HAND);
		}

	} else if (!(joypad_current & J_A)) {
		button_pressed = 0;
	}
}

void draw_sprites() {
	uint8_t frog_x = 0;
	uint8_t frog_y = 0;
	get_frog_position(&frog_x, &frog_y);

	uint8_t last_used_sprite = 0;
	draw_hand(&last_used_sprite, frog_x);
	draw_frog(&last_used_sprite);
	hide_sprites_range(last_used_sprite, MAX_HARDWARE_SPRITES);
}

uint8_t is_hand_on_frog() {
	uint8_t hand_x = 0;
	uint8_t hand_y = 0;
	uint8_t frog_x = 0;
	uint8_t frog_y = 0;
	get_hand_position(&hand_x, &hand_y);
	get_frog_position(&frog_x, &frog_y);
	if (hand_x + 8 > frog_x - 16 && hand_x - 8 < frog_x + 16 && hand_y + 8 > frog_y - 16 && hand_y - 8 < frog_y + 16) {
		return 1;
	} else {
		return 0;
	}
}
