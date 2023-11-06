#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "hand.h"
#include "frog.h"
#include "hud.h"
#include "save.h"

#include "title.h"
#include "field.h"
// #include "pond.h"
// #include "garden.h"
#include "info.h"
// #include "inventory.h"

uint8_t last_scene;
uint8_t current_scene;
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

#define SPEED_FAST 0
#define SPEED_MEDIUM 1
#define SPEED_SLOW 2
uint8_t game_speed = SPEED_MEDIUM;

void setup_scene(uint8_t new_scene) {
	setup_hud_data();
	SWITCH_ROM(BANK(hud_bank));
	setup_hud();

	last_scene = current_scene;
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
			SWITCH_ROM(BANK(hud_bank));
			draw_hud();
			break;

		case POND:
			//setup_pond();
			SWITCH_ROM(BANK(hud_bank));
			draw_hud();
			break;

		case GARDEN:
			//setup_garden();
			SWITCH_ROM(BANK(hud_bank));
			draw_hud();
			break;

		case INFO:
			SWITCH_ROM(BANK(frog_bank));
			uint8_t temp_love = love;
			uint8_t temp_stomach = stomach;
			uint8_t temp_energy = energy;
			uint8_t temp_age = age;
			uint8_t temp_weight = weight;

			setup_info_data();

			SWITCH_ROM(BANK(info_bank));
			info_love = temp_love;
			info_stomach = temp_stomach;
			info_energy = temp_energy;
			info_age = temp_age;
			info_weight = temp_weight;

			setup_info();

			break;

		case INVENTORY:
			// setup_inventory();
			break;
	}

	save_data();
}

void update_transition(void) {
	transition_counter += 1;
	if (transition_counter >= 8) {
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
				if (is_night) {
					SWITCH_ROM(BANK(frog_bank));
					start_sleep();
				}
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
			draw_hand(&last_sprite);
			SWITCH_ROM(BANK(frog_bank));
			draw_frog(&last_sprite);
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
				break;

			case POND:
				// update_pond();
				break;

			case GARDEN:
				// update_garden();
				break;

			case INFO:
				// update_info();
				break;

			case INVENTORY:
				// update_inventory();
				break;
		}
	}

	draw_sprites();
}

void start_transition_to_scene(uint8_t new_scene, uint8_t new_is_night) {
	is_transitioning = TRUE;
	transition_counter = 0;
	transition_frame = 0;
	next_scene = new_scene;
	next_is_night = new_is_night;
}

void reset_data(void) {
	SWITCH_ROM(BANK(hud_bank));
	medicine_is_held = 0;
	soap_is_held = 0;
	broom_is_held = 0;
	moon_is_held = 0;

	SWITCH_ROM(BANK(field_bank));
	for (uint8_t i = 0; i < MAX_POOPS; i++) {
		poops_x[i] = 0;
		poops_y[i] = 0;
	}

	SWITCH_ROM(BANK(frog_bank));
	setup_frog(TRUE);
	setup_hand();
	start_transition_to_scene(FIELD, FALSE);
}
