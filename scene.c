#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <time.h>

#include "hand.h"
#include "frog.h"
#include "bugs.h"
#include "poop.h"
#include "hud.h"
#include "save.h"

#include "title.h"
#include "field.h"
#include "pond.h"
#include "garden.h"
#include "info.h"
// #include "inventory.h"

#include "shared_variables.h"

uint8_t is_transitioning = FALSE;
uint8_t transition_counter = 0;
uint8_t transition_frame = 0;
uint8_t next_scene;
uint8_t next_is_night;

uint8_t last_sprite;

time_t last_time = 0;
time_t current_time = 0;

void setup_scene(uint8_t new_scene) {
	uint8_t skip_save = last_scene == TITLE && new_scene == TITLE;
	last_scene = (current_scene == TITLE ? FIELD : current_scene);
	current_scene = new_scene;

	switch(current_scene) {
		case TITLE:
			setup_title_data();
			SWITCH_ROM(BANK(title_bank));
			setup_title();
			break;

		case FIELD:
			setup_field_data();
			SWITCH_ROM(BANK(field_bank));
			setup_field(hand_state == HAND_MOON);
			break;

		case POND:
			setup_pond_data();
			SWITCH_ROM(BANK(pond_bank));
			setup_pond();
			break;

		case GARDEN:
			setup_garden_data();
			SWITCH_ROM(BANK(garden_bank));
			setup_garden();
			break;

		case INFO:
			setup_info_data();
			SWITCH_ROM(BANK(info_bank));
			setup_info();
			break;

		// case INVENTORY:
			// setup_inventory();
			// break;
	}

	if (current_scene == FIELD || current_scene == POND || current_scene == GARDEN) {
		setup_hud_data();
		SWITCH_ROM(BANK(hud_bank));
		draw_hud();
		SWITCH_ROM(BANK(poop_bank));
		draw_poops();
		SWITCH_ROM(BANK(bugs_bank));
		setup_bugs();
	}

	if ((current_scene == FIELD && last_scene == POND) || (current_scene == GARDEN && last_scene == FIELD)) {
		hand_x = 12;
		hand_x_frac = hand_x << 8;
	} else if ((current_scene == POND && last_scene == FIELD) || (current_scene == FIELD && last_scene == GARDEN)) {
		hand_x = 148;
		hand_x_frac = hand_x << 8;
	}

	if (!skip_save) {
		save_data();
	}
}

void update_transition(void) {
	transition_counter += 1;
	if (transition_counter >= 4) {
		transition_counter = 0;
		transition_frame += 1;

		switch(transition_frame) {
			case 1:
				BGP_REG = DMG_PALETTE(DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK);
				OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
				break;

			case 2:
				BGP_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK, DMG_BLACK);
				OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK);
				break;

			case 3:
				BGP_REG = DMG_PALETTE(DMG_BLACK, DMG_BLACK, DMG_BLACK, DMG_BLACK);
				OBP0_REG = DMG_PALETTE(DMG_BLACK, DMG_BLACK, DMG_BLACK, DMG_BLACK);
				is_night = next_is_night;
				setup_scene(next_scene);
				SWITCH_ROM(BANK(frog_bank));
				place_in_scene();
				break;

			case 4:
				BGP_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK, DMG_BLACK);
				OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK);
				break;

			case 5:
				BGP_REG = DMG_PALETTE(DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK);
				OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
				break;

			case 6:
				BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
				OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
				is_transitioning = FALSE;
				break;
		}
	}
}

void start_transition_to_scene(uint8_t new_scene, uint8_t new_is_night) {
	is_transitioning = TRUE;
	transition_counter = 0;
	transition_frame = 0;
	next_scene = new_scene;
	next_is_night = new_is_night;
}

void draw_sprites(void) {
	last_sprite = 0;

	switch(current_scene) {
		case TITLE:
			SWITCH_ROM(BANK(title_bank));
			draw_title_sprites(&last_sprite);
			break;

		case FIELD:
		case POND:
		case GARDEN:
			SWITCH_ROM(BANK(hand_bank));
			draw_hand(&last_sprite);
			SWITCH_ROM(BANK(frog_bank));
			if (current_scene == FIELD || (!is_night && life_stage != EGG && life_stage != DEAD)) {
				draw_frog(&last_sprite);
			}
			SWITCH_ROM(BANK(bugs_bank));
			draw_bugs(&last_sprite);
			break;
	}

	hide_sprites_range(last_sprite, MAX_HARDWARE_SPRITES);
}

void update_every_minute(void) {
	SWITCH_ROM(BANK(frog_bank));
	update_stats();
	if (is_night && action == ACTION_SLEEP && energy >= 9) {
		start_transition_to_scene(FIELD, FALSE);
	}

	SWITCH_ROM(BANK(bugs_bank));
	respawn_bugs();

	SWITCH_ROM(BANK(garden_bank));
	update_plants(game_speed);
}

void update_scene(void) {
	if (is_transitioning) {
		update_transition();

	} else {
		if ((current_scene == FIELD || current_scene == POND || current_scene == GARDEN)) {
			SWITCH_ROM(BANK(frog_bank));
			update_frog();

			SWITCH_ROM(BANK(hand_bank));
			update_hand();

			SWITCH_ROM(BANK(poop_bank));
			update_poops();

			current_time = clock() / CLOCKS_PER_SEC;
			if (current_time >= last_time + 60) {
				last_time = clock() / CLOCKS_PER_SEC;
				update_every_minute();
			}
		}

		switch(current_scene) {
			case FIELD:
				SWITCH_ROM(BANK(field_bank));
				update_field();
				if (hand_x + 16 >= 120 && hand_x < 136 && hand_y + 16 >= 80 && hand_y < 96) {
					set_basket(TRUE);
				} else {
					set_basket(FALSE);
				}
				if (restore_x > 0 && restore_y > 0) {
					restore_field_tile(restore_x, restore_y);
					restore_x = 0;
					restore_y = 0;
				}
				break;

			case POND:
				SWITCH_ROM(BANK(pond_bank));
				update_pond();
				if (restore_x > 0 && restore_y > 0) {
					restore_pond_tile(restore_x, restore_y);
					restore_x = 0;
					restore_y = 0;
				}
				break;

			case GARDEN:
				SWITCH_ROM(BANK(garden_bank));
				update_garden();
				if (restore_x > 0 && restore_y > 0) {
					restore_garden_tile(restore_x, restore_y);
					restore_x = 0;
					restore_y = 0;
				}
				break;

			// case INVENTORY:
				// update_inventory();
				// break;
		}
	}

	draw_sprites();
}

void setup_data(uint8_t reset) {
	setup_bugs_data();

	setup_poop_data();
	if (reset) {
		SWITCH_ROM(BANK(poop_bank));
		reset_poops();
	}

	SWITCH_ROM(BANK(frog_bank));
	setup_frog(reset);

	SWITCH_ROM(BANK(hand_bank));
	setup_hand();

	last_time = clock() / CLOCKS_PER_SEC;
}

void reset_data(void) {
	setup_data(TRUE);
	start_transition_to_scene(FIELD, FALSE);
}
