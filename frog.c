#include <gbdk/metasprites.h>

#include "clock.h"
#include "hand.h"
#include "sprites/frog/frog_baby.h"
#include "sprites/frog/frog_child.h"
#include "sprites/frog/frog_teen.h"
#include "sprites/frog/frog_teen_tail.h"
#include "sprites/frog/frog_teen_apple.h"
#include "sprites/frog/frog_normal.h"
#include "sprites/frog/frog_axolotl.h"
#include "sprites/frog/frog_apple.h"
#include "sprites/frog/frog_mushroom.h"
#include "sprites/frog/frog_dragon.h"

#define FROG_SPRITE 46

#define EGG 0
#define BABY 1
#define CHILD 2
#define TEEN 3
#define TEEN_TAIL 4
#define TEEN_APPLE 5
#define ADULT_NORMAL 6
#define ADULT_AXOLOTL 7
#define ADULT_APPLE 8
#define ADULT_MUSHROOM 9
#define ADULT_DRAGON 10

uint8_t frog_evolution = BABY;

#define NORMAL_STATE 0
#define WALK_STATE 2
#define JOY_STATE 4
#define EAT_STATE 6
#define SLEEP_STATE 9
#define BATH_STATE 11
#define PET_STATE 13
#define SAD_STATE 15
#define HUNGRY_STATE 17
#define SLEEPY_STATE 19
#define DIRTY_STATE 21
#define SHY_STATE 23

uint8_t frog_state = NORMAL_STATE;

struct Age {
	uint16_t days;
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
};

struct Age frog_age = { 0, 0, 0, 0 };

uint8_t frog_bank = BANK(frog_baby);
const metasprite_t** frog_metasprites;

uint16_t frog_x = 88 << 8;
uint16_t frog_y = 80 << 8;

uint8_t goal_x = 88;
uint8_t goal_y = 80;

uint8_t long_goal_x = 0;
uint8_t long_goal_y = 0;

uint8_t temp_age = 0; // TEMP

uint8_t frame = 0;
uint8_t flipped = 0;

uint8_t trust = 0;
uint8_t happiness = 0;
uint8_t hunger = 0;
uint8_t sleepiness = 0;
uint8_t dirtiness = 0;

void init_frog();
void update_frog();
void draw_frog(uint8_t *last_used_sprite);
void move_toward_goal();
void set_goal(uint8_t new_goal_x, uint8_t new_goal_y);
void pick_new_long_goal();
void update_age();
void update_animation();
void set_frog_evolution(uint8_t new_evolution);
void set_frog_state(uint8_t new_state);
void get_frog_position(uint8_t *x, uint8_t *y);

/* ========================================================================= */

void init_frog() {
	set_frog_evolution(ADULT_DRAGON);
}

void update_frog() {
	update_age();
	update_animation();

	uint8_t x = frog_x >> 8;
	uint8_t y = frog_y >> 8;

	if (x == long_goal_x && y == long_goal_y) {
		pick_new_long_goal();
	} else if (x == goal_x && y == goal_y) {
		get_hand_position(&goal_x, &goal_y);
		set_goal(goal_x, goal_y);
		if (frog_state == WALK_STATE) {
			set_frog_state(NORMAL_STATE);
		}
	} else if (frog_state != WALK_STATE) {
		set_frog_state(WALK_STATE);
	}
}

void draw_frog(uint8_t *last_used_sprite) {
	uint8_t old_bank = CURRENT_BANK;
	SWITCH_ROM(frog_bank);
	if (flipped == 0) {
		*last_used_sprite += move_metasprite(frog_metasprites[frog_state + frame], FROG_SPRITE, *last_used_sprite, frog_x >> 8, frog_y >> 8);
	} else {
		*last_used_sprite += move_metasprite_vflip(frog_metasprites[frog_state + frame], FROG_SPRITE, *last_used_sprite, frog_x >> 8, frog_y >> 8);
	}
	SWITCH_ROM(old_bank);
	if (frog_state == WALK_STATE) {
		move_toward_goal();
	}
}

uint8_t dist(uint8_t a, uint8_t b) {
	if (a > b) {
		return a - b;
	} else {
		return b - a;
	}
}

void move_toward_goal() {
	uint8_t x = frog_x >> 8;
	uint8_t y = frog_y >> 8;
	uint8_t dx = dist(goal_x, x);
	uint8_t dy = dist(goal_y, y);
	if (dx >= dy) {
		if (x < goal_x) {
			frog_x += 60;
		} else if (x > goal_x) {
			frog_x -= 60;
		}
	} else {
		if (y < goal_y) {
			frog_y += 60;
		} else if (y > goal_y) {
			frog_y -= 60;
		}
	}
}

void set_goal(uint8_t new_goal_x, uint8_t new_goal_y) {
	goal_x = new_goal_x;
	goal_y = new_goal_y;
}

void pick_new_long_goal() {

}

void update_age() {
	uint16_t days = 0;
	uint8_t hours = 0;
	uint8_t minutes = 0;
	uint8_t seconds = 0;
	read_clock(&days, &hours, &minutes, &seconds);
	frog_age.days = days;
	frog_age.hours = hours;
	frog_age.minutes = minutes;
	frog_age.seconds = seconds;
}

void update_animation() {
	frame++;
	if (frog_state == EAT_STATE) {
		if (frame > 2) {
			frame = 1;
		}
	} else if (frame > 1) {
		frame = 0;
	}
}

void set_frog_evolution(uint8_t new_evolution) NONBANKED {
	uint8_t old_bank = CURRENT_BANK;

	frog_evolution = new_evolution;
	// TODO: hide metasprite while using an evolution animation to cover the transition

	switch (frog_evolution) {
		case BABY:
			frog_bank = BANK(frog_baby);
			SWITCH_ROM(frog_bank);
			set_sprite_data(FROG_SPRITE, frog_baby_TILE_COUNT, frog_baby_tiles);
			frog_metasprites = frog_baby_metasprites;
			break;

		case CHILD:
			frog_bank = BANK(frog_child);
			SWITCH_ROM(frog_bank);
			set_sprite_data(FROG_SPRITE, frog_child_TILE_COUNT, frog_child_tiles);
			frog_metasprites = frog_child_metasprites;
			break;

		case TEEN:
			frog_bank = BANK(frog_teen);
			SWITCH_ROM(frog_bank);
			set_sprite_data(FROG_SPRITE, frog_teen_TILE_COUNT, frog_teen_tiles);
			frog_metasprites = frog_teen_metasprites;
			break;

		case TEEN_TAIL:
			frog_bank = BANK(frog_teen_tail);
			SWITCH_ROM(frog_bank);
			set_sprite_data(FROG_SPRITE, frog_teen_tail_TILE_COUNT, frog_teen_tail_tiles);
			frog_metasprites = frog_teen_tail_metasprites;
			break;

		case TEEN_APPLE:
			frog_bank = BANK(frog_teen_apple);
			SWITCH_ROM(frog_bank);
			set_sprite_data(FROG_SPRITE, frog_teen_apple_TILE_COUNT, frog_teen_apple_tiles);
			frog_metasprites = frog_teen_apple_metasprites;
			break;

		case ADULT_NORMAL:
			frog_bank = BANK(frog_normal);
			SWITCH_ROM(frog_bank);
			set_sprite_data(FROG_SPRITE, frog_normal_TILE_COUNT, frog_normal_tiles);
			frog_metasprites = frog_normal_metasprites;
			break;

		case ADULT_AXOLOTL:
			frog_bank = BANK(frog_axolotl);
			SWITCH_ROM(frog_bank);
			set_sprite_data(FROG_SPRITE, frog_axolotl_TILE_COUNT, frog_axolotl_tiles);
			frog_metasprites = frog_axolotl_metasprites;
			break;

		case ADULT_APPLE:
			frog_bank = BANK(frog_apple);
			SWITCH_ROM(frog_bank);
			set_sprite_data(FROG_SPRITE, frog_apple_TILE_COUNT, frog_apple_tiles);
			frog_metasprites = frog_apple_metasprites;
			break;

		case ADULT_MUSHROOM:
			frog_bank = BANK(frog_mushroom);
			SWITCH_ROM(frog_bank);
			set_sprite_data(FROG_SPRITE, frog_mushroom_TILE_COUNT, frog_mushroom_tiles);
			frog_metasprites = frog_mushroom_metasprites;
			break;

		case ADULT_DRAGON:
			frog_bank = BANK(frog_dragon);
			SWITCH_ROM(frog_bank);
			set_sprite_data(FROG_SPRITE, frog_dragon_TILE_COUNT, frog_dragon_tiles);
			frog_metasprites = frog_dragon_metasprites;
			break;
	}

	SWITCH_ROM(old_bank);
}

void set_frog_state(uint8_t new_state) {
	frog_state = new_state;
	frame = 0;
	if (frog_state == WALK_STATE && (frog_x >> 8) > goal_x) {
		flipped = 1;
	} else {
		flipped = 0;
	}
}

void get_frog_position(uint8_t *x, uint8_t *y) {
	*x = (frog_x >> 8);
	*y = (frog_y >> 8);
}