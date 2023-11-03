#include <gbdk/platform.h>

#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "hand.h"
#include "frog.h"
#include "hud.h"
#include "field.h"

uint8_t current_scene;
#define TITLE_SCREEN 0
#define CLOCK_SCREEN 1
#define INVENTORY 2
#define FIELD 3
#define POND 4
#define GARDEN 5

uint8_t is_night;

uint8_t is_transitioning = FALSE;
uint8_t transition_counter = 0;
uint8_t transition_frame = 0;
uint8_t next_scene;
uint8_t next_is_night;

void setup_scene(uint8_t new_scene) {
	current_scene = new_scene;
	switch(current_scene) {
		case FIELD:
			setup_field();
			break;
	}
	draw_hud();
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

void update_scene(void) {
	if (is_transitioning) {
		update_transition();

	} else {
		switch(current_scene) {
			case FIELD:
				update_field();
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
