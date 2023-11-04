#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "hand.h"
#include "frog.h"
#include "hud.h"

#include "title.h"
#include "field.h"
// #include "pond.h"
// #include "garden.h"
// #include "info.h"
// #include "inventory.h"

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

void setup_scene(uint8_t new_scene) {
	current_scene = new_scene;
	switch(current_scene) {
		case TITLE:
			setup_title();
			break;

		case FIELD:
			setup_field();
			draw_hud();
			SWITCH_ROM(BANK(frog_bank));
			redraw_frog();
			break;

		case POND:
			//setup_pond();
			draw_hud();
			SWITCH_ROM(BANK(frog_bank));
			redraw_frog();
			break;

		case GARDEN:
			//setup_garden();
			draw_hud();
			SWITCH_ROM(BANK(frog_bank));
			redraw_frog();
			break;

		case INFO:
			// setup_info();
			break;

		case INVENTORY:
			// setup_inventory();
			break;
	}
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

void restart(void) {
	drop_all(0);
	SWITCH_ROM(BANK(frog_bank));
	setup_frog();
	setup_hand();
	start_transition_to_scene(FIELD, FALSE);
}
