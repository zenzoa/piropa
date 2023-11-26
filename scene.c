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
#include "inventory.h"
#include "credits.h"

#include "colors.h"
#include "common.h"

static uint8_t is_transitioning;
static uint8_t transition_counter;
static uint8_t transition_frame;
static uint8_t next_scene;
static uint8_t next_is_night;

static time_t last_time;
static time_t current_time;

static void draw_sprites(void);

void setup_scene(uint8_t new_scene) {
	uint8_t on_start = current_scene == 255;
	uint8_t skip_save = on_start || current_scene == CREDITS || new_scene == CREDITS;

	if (!on_start && current_scene != CREDITS && new_scene != CREDITS) {
		last_scene = current_scene;
	}

	current_scene = on_start ? TITLE : new_scene;

	switch(current_scene) {
		case TITLE:
			setup_title();
			break;

		case FIELD:
			setup_field(hand_state == HAND_MOON);
			break;

		case POND:
			setup_pond();
			break;

		case GARDEN:
			setup_garden();
			break;

		case INFO:
			setup_info();
			break;

		case INVENTORY:
			setup_inventory();
			break;

		case CREDITS:
			setup_credits();
			break;
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

	draw_sprites();
}

static void update_transition(void) {
	transition_counter += 1;
	if (transition_counter >= 4) {
		transition_counter = 0;
		transition_frame += 1;

		switch(transition_frame) {
			case 1:
				set_bkg_colors(1);
				set_sprite_colors(1);
				break;

			case 2:
				set_bkg_colors(2);
				set_sprite_colors(2);
				break;

			case 3:
				set_bkg_colors(3);
				set_sprite_colors(3);
				is_night = next_is_night;
				setup_scene(next_scene);
				place_in_scene();
				break;

			case 4:
				set_bkg_colors(2);
				set_sprite_colors(2);
				break;

			case 5:
				set_bkg_colors(1);
				set_sprite_colors(1);
				break;

			case 6:
				set_bkg_colors(0);
				set_sprite_colors(0);
				is_transitioning = FALSE;
				break;
		}
	}
}

void transition_to_scene(uint8_t new_scene, uint8_t new_is_night) {
	is_transitioning = TRUE;
	transition_counter = 0;
	transition_frame = current_scene == 255 ? 2 : 0;
	next_scene = new_scene;
	next_is_night = new_is_night;
}

static void draw_sprites(void) {
	last_sprite = 0;

	switch(current_scene) {
		case TITLE:
			draw_title_sprites();
			break;

		case FIELD:
		case POND:
		case GARDEN:
			draw_hand();
			if (current_scene == FIELD || (!is_night && life_stage != EGG && life_stage != DEAD)) {
				draw_frog();
			}
			draw_bugs();
			break;

		case INVENTORY:
			draw_inventory_sprites();
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
				if (is_hand_over_basket()) {
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
		}
	}

	draw_sprites();
}

void setup_data(uint8_t reset) {
	setup_bugs_data();

	setup_poop_data();

	setup_frog(reset);

	setup_hand();

	last_time = clock() / CLOCKS_PER_SEC;
}

void reset_data(void) {
	reset_bugs();
	reset_plants();
	reset_poops();
	reset_inventory();
	setup_data(TRUE);
	transition_to_scene(FIELD, FALSE);
}
