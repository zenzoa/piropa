#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <time.h>

#include <stdio.h>
#include <gbdk/emu_debug.h>

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

uint8_t current_scene;
uint8_t last_scene;
#define TITLE 0
#define FIELD 1
#define POND 2
#define GARDEN 3
#define INFO 4
#define INVENTORY 5

uint8_t is_night;

uint8_t is_transitioning = FALSE;
uint8_t transition_counter = 0;
uint8_t transition_frame = 0;
uint8_t next_scene;
uint8_t next_is_night;

uint8_t last_sprite;

uint8_t restore_x;
uint8_t restore_y;

#define SPEED_FAST 0
#define SPEED_MEDIUM 1
#define SPEED_SLOW 2
uint8_t game_speed = SPEED_MEDIUM;

const unsigned char big_cloud_1_tile_map[3] = { 0x70, 0x71, 0x72 };
const unsigned char big_cloud_2_tile_map[3] = { 0x73, 0x74, 0x75 };
const unsigned char small_cloud_1_tile_map[2] = { 0x70, 0x72 };
const unsigned char small_cloud_2_tile_map[2] = { 0x73, 0x75 };

time_t last_time = 0;
time_t current_time = 0;

void setup_scene(uint8_t new_scene) {
	setup_hud_data();

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
			setup_field();
			SWITCH_ROM(BANK(poop_bank));
			draw_poops();
			SWITCH_ROM(BANK(hud_bank));
			draw_hud();
			SWITCH_ROM(BANK(bugs_bank));
			setup_bugs();
			break;

		case POND:
			setup_pond_data();
			SWITCH_ROM(BANK(pond_bank));
			setup_pond();
			SWITCH_ROM(BANK(poop_bank));
			draw_poops();
			SWITCH_ROM(BANK(hud_bank));
			draw_hud();
			SWITCH_ROM(BANK(bugs_bank));
			setup_bugs();
			break;

		case GARDEN:
			setup_garden_data();
			SWITCH_ROM(BANK(garden_bank));
			setup_garden();
			SWITCH_ROM(BANK(poop_bank));
			draw_poops();
			SWITCH_ROM(BANK(hud_bank));
			draw_hud();
			SWITCH_ROM(BANK(bugs_bank));
			setup_bugs();
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

void update_scene(void) {
	if (is_transitioning) {
		update_transition();

	} else {
		switch(current_scene) {
			case FIELD:
				SWITCH_ROM(BANK(field_bank));
				update_field();
				if (restore_x > 0 && restore_y > 0) {
					EMU_printf("");
					EMU_printf("RESTORE tile at %d, %d", restore_x, restore_y);
					restore_field_tile(restore_x, restore_y);
					restore_x = 0;
					restore_y = 0;
				}
				break;

			case POND:
				SWITCH_ROM(BANK(pond_bank));
				update_pond();
				if (restore_x > 0 && restore_y > 0) {
					EMU_printf("");
					EMU_printf("RESTORE tile at %d, %d", restore_x, restore_y);
					restore_pond_tile(restore_x, restore_y);
					restore_x = 0;
					restore_y = 0;
				}
				break;

			case GARDEN:
				SWITCH_ROM(BANK(garden_bank));
				update_garden();
				if (restore_x > 0 && restore_y > 0) {
					EMU_printf("");
					EMU_printf("RESTORE tile at %d, %d", restore_x, restore_y);
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

void reset_data(void) {
	SWITCH_ROM(BANK(poop_bank));
	reset_poops();

	SWITCH_ROM(BANK(frog_bank));
	setup_frog(TRUE);
	SWITCH_ROM(BANK(hand_bank));
	setup_hand();
	start_transition_to_scene(FIELD, FALSE);

	last_time = clock() / CLOCKS_PER_SEC;
}
