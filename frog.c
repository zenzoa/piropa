#include <gbdk/metasprites.h>

#include "clock.h"
#include "sprites/frog_baby.h"
#include "sprites/frog_child.h"
#include "sprites/frog_teen.h"
#include "sprites/frog_teen_tail.h"
#include "sprites/frog_teen_apple.h"
#include "sprites/frog_normal.h"
#include "sprites/frog_axolotl.h"
#include "sprites/frog_apple.h"
#include "sprites/frog_mushroom.h"
#include "sprites/frog_dragon.h"

#define FROG_SPRITE 4

enum Evolution {
	EGG,
	BABY,
	CHILD,
	TEEN,
	TEEN_TAIL,
	TEEN_APPLE,
	ADULT_NORMAL,
	ADULT_AXOLOTL,
	ADULT_APPLE,
	ADULT_MUSHROOM,
	ADULT_DRAGON
};

enum Evolution frog_evolution = BABY;

enum State {
	NORMAL_STATE = 0,
	WALK_STATE = 2,
	JOY_STATE = 4,
	EAT_STATE = 6,
	SLEEP_STATE = 9,
	BATH_STATE = 11,
	PET_STATE = 13,
	SAD_STATE = 15,
	HUNGRY_STATE = 17,
	SLEEPY_STATE = 19,
	DIRTY_STATE = 21,
	SHY_STATE = 23
};

enum State frog_state = NORMAL_STATE;

struct Age {
	uint16_t days;
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
};

struct Age frog_age = { 0, 0, 0, 0 };

uint8_t frog_bank = BANK(frog_baby);
const metasprite_t** frog_metasprites;

uint8_t frog_x = 88;
uint8_t frog_y = 80;

uint8_t temp_age = 0; // TEMP

uint8_t frame = 0;

uint8_t trust = 0;
uint8_t happiness = 0;
uint8_t hunger = 0;
uint8_t sleepiness = 0;
uint8_t dirtiness = 0;

void init_frog();
void update_frog();
void draw_frog(uint8_t *last_used_sprite);
void move_frog(int8_t dx, int8_t dy);
void update_age();
void set_frog_evolution(enum Evolution new_evolution);
void set_frog_state(enum State new_state);

/* ========================================================================= */

void init_frog() {
	set_frog_evolution(BABY);
}

void update_frog() {
	update_age();
	
	/* TEMP code to test states and evolutions */
	temp_age++;
	switch (temp_age) {
		case 10:
			set_frog_state(WALK_STATE);
			break;
			
		case 20:
			set_frog_state(JOY_STATE);
			break;
			
		case 30:
			set_frog_state(EAT_STATE);
			break;
			
		case 40:
			set_frog_state(SLEEP_STATE);
			break;
			
		case 50:
			set_frog_state(BATH_STATE);
			break;
			
		case 60:
			set_frog_state(PET_STATE);
			break;
			
		case 70:
			set_frog_state(SAD_STATE);
			break;
			
		case 80:
			set_frog_state(HUNGRY_STATE);
			break;
			
		case 90:
			set_frog_state(SLEEPY_STATE);
			break;
			
		case 100:
			set_frog_state(DIRTY_STATE);
			break;
			
		case 110:
			set_frog_state(SHY_STATE);
			break;
			
		case 120:
			if (frog_evolution == BABY) {
				set_frog_evolution(CHILD);
			} else if (frog_evolution == CHILD) {
				set_frog_evolution(TEEN);
			} else if (frog_evolution == TEEN) {
				set_frog_evolution(ADULT_NORMAL);
			} else if (frog_evolution == ADULT_NORMAL) {
				set_frog_evolution(ADULT_DRAGON);
			}
			temp_age = 0;
			set_frog_state(NORMAL_STATE);
			break;
	}
	
	frame++;
	if (frog_state == EAT_STATE) {
		if (frame > 2) {
			frame = 1;
		}
	} else if (frame > 1) {
		frame = 0;
	}
}

void draw_frog(uint8_t *last_used_sprite) {
	uint8_t old_bank = CURRENT_BANK;
	SWITCH_ROM(frog_bank);
	*last_used_sprite += move_metasprite(frog_metasprites[frog_state + frame], FROG_SPRITE, *last_used_sprite, frog_x, frog_y);
	SWITCH_ROM(old_bank);
}

void move_frog(int8_t dx, int8_t dy) {
	frog_x += dx;
	frog_y += dy;
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

void set_frog_evolution(enum Evolution new_evolution) NONBANKED {
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

void set_frog_state(enum State new_state) {
	frog_state = new_state;
}

