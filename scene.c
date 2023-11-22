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

static uint8_t is_transitioning;
static uint8_t transition_counter;
static uint8_t transition_frame;
static uint8_t next_scene;
static uint8_t next_is_night;

static uint8_t last_sprite;

static time_t last_time;
static time_t current_time;

void setup_scene(uint8_t new_scene) {
	uint8_t skip_save = last_scene == TITLE && new_scene == TITLE;
	last_scene = (current_scene == TITLE ? FIELD : current_scene);
	current_scene = new_scene;

	switch(current_scene) {
		case TITLE:
			setup_title_data();
			setup_title();
			break;

		case FIELD:
			setup_field_data();
			setup_field(hand_state == HAND_MOON);
			break;

		case POND:
			setup_pond_data();
			setup_pond();
			break;

		case GARDEN:
			setup_garden_data();
			setup_garden();
			break;

		case INFO:
			setup_info_data();
			setup_info();
			break;

		// case INVENTORY:
			// setup_inventory();
			// break;
	}

	if (current_scene == FIELD || current_scene == POND || current_scene == GARDEN) {
		setup_hud_data();
		draw_hud();
		draw_poops();
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

static void update_transition(void) {
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

void transition_to_scene(uint8_t new_scene, uint8_t new_is_night) {
	is_transitioning = TRUE;
	transition_counter = 0;
	transition_frame = 0;
	next_scene = new_scene;
	next_is_night = new_is_night;
}

static void draw_sprites(void) {
	last_sprite = 0;

	switch(current_scene) {
		case TITLE:
			draw_title_sprites(&last_sprite);
			break;

		case FIELD:
		case POND:
		case GARDEN:
			draw_hand(&last_sprite);
			if (current_scene == FIELD || (!is_night && life_stage != EGG && life_stage != DEAD)) {
				draw_frog(&last_sprite);
			}
			draw_bugs(&last_sprite);
			break;
	}

	hide_sprites_range(last_sprite, MAX_HARDWARE_SPRITES);
}

static void update_every_minute(void) {
	update_stats();
	if (is_night && is_sleeping() && energy >= 9) {
		transition_to_scene(FIELD, FALSE);
	}
	respawn_bugs();
	update_plants();
}

void update_scene(void) {
	if (is_transitioning) {
		update_transition();

	} else {
		if ((current_scene == FIELD || current_scene == POND || current_scene == GARDEN)) {
			update_frog();
			update_hand();
			update_poops();

			current_time = clock() / CLOCKS_PER_SEC;
			if (current_time >= last_time + 60) {
				last_time = clock() / CLOCKS_PER_SEC;
				update_every_minute();
				is_time_to_save = TRUE;
			}

			if (is_time_to_save) {
				save_data();
				is_time_to_save = FALSE;
			}
		}

		switch(current_scene) {
			case FIELD:
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
				update_pond();
				if (restore_x > 0 && restore_y > 0) {
					restore_pond_tile(restore_x, restore_y);
					restore_x = 0;
					restore_y = 0;
				}
				break;

			case GARDEN:
				update_garden();
				if (restore_x > 0 && restore_y > 0) {
					restore_garden_tile(restore_x, restore_y);
					draw_plants();
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
		reset_poops();
	}

	setup_frog(reset);

	setup_hand();

	last_time = clock() / CLOCKS_PER_SEC;
}

void reset_data(void) {
	setup_data(TRUE);
	transition_to_scene(FIELD, FALSE);
}
