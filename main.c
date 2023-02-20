#include <gbdk/platform.h>
#include <gbdk/far_ptr.h>
#include <gbdk/metasprites.h>

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

enum Evolution my_evolution = BABY;

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

enum State my_state = NORMAL_STATE;

struct Age {
	uint16_t days;
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
};

struct Age my_age = { 0, 0, 0, 0 };

uint8_t frog_bank = BANK(frog_baby);
metasprite_t** frog_metasprites;

uint8_t x_pos = 0;
uint8_t y_pos = 0;

uint8_t temp_age = 0; // TEMP

uint8_t frame = 0;
uint8_t animation_counter = 0;
uint8_t animation_speed = 32;

uint8_t trust = 0;
uint8_t happiness = 0;
uint8_t hunger = 0;
uint8_t sleepiness = 0;
uint8_t dirtiness = 0;

void read_clock(struct Age *age);
void reset_clock();
void update_age();
void set_frog_evolution(enum Evolution new_evolution);
void set_frog_state(enum State new_state);
void draw_frog();
void move_frog(uint8_t new_x, uint8_t new_y);
void update_frog();

void main(void) {
	DISPLAY_ON;
	SHOW_SPRITES;
	SPRITES_8x8;
	
	// TODO: read save data and update frog based on time that has passed
	reset_clock(); // do this when new frog is born
	
	set_frog_evolution(BABY);
	move_frog(88, 80);
	
    while(1) {
		if (animation_counter >= animation_speed) {
			update_frog();
			animation_counter = 0;
		}
		animation_counter++;

		wait_vbl_done(); // wait for next frame
    }
}

void read_clock(struct Age *age) {
	/* MBC3 RTC: https://gbdev.io/pandocs/MBC3.html */
	/* Thanks to CasualPokePlayer and NanoCodeBug for help with this! */
	
	ENABLE_RAM;
	
	volatile uint8_t * const latch_clock = (volatile uint8_t * const)0x6000;
	*latch_clock = 0;
	*latch_clock = 1;
	
	volatile uint8_t * const rtc_register = (volatile uint8_t * const)0xA000;
	SWITCH_RAM(0x8);
	age->seconds = *rtc_register;
	SWITCH_RAM(0x9);
	age->minutes = *rtc_register;
	SWITCH_RAM(0xA);
	age->hours = *rtc_register;
	SWITCH_RAM(0xB);
	age->days = *rtc_register;
	SWITCH_RAM(0xC);
	// bit 0 is the most significant bit of the day register
	// day is a total of 9 bits or 511 days
	if (*rtc_register & 0x01) {
		age->days |= 0x0100;
	}
	// day overflow bit set
	if (*rtc_register & 0b10000000) {
		age->days += 512;
	}
	
	DISABLE_RAM;
}

void reset_clock() {
	ENABLE_RAM;
	
	volatile uint8_t * const rtc_register = (volatile uint8_t * const)0xA000;
	SWITCH_RAM(0x8);
	*rtc_register = 0;
	SWITCH_RAM(0x9);
	*rtc_register = 0;
	SWITCH_RAM(0xA);
	*rtc_register = 0;
	SWITCH_RAM(0xB);
	*rtc_register = 0;
	SWITCH_RAM(0xC);
	*rtc_register = 0;
	
	DISABLE_RAM;
}

void update_age() {
	read_clock(&my_age);
}

void set_frog_evolution(enum Evolution new_evolution) NONBANKED {
	uint8_t old_bank = CURRENT_BANK;
	
	my_evolution = new_evolution;
	// TODO: hide metasprite while using an evolution animation to cover the transition
	
	switch (my_evolution) {
		case BABY:
			frog_bank = BANK(frog_baby);
			SWITCH_ROM(frog_bank);
			set_sprite_data(0, frog_baby_TILE_COUNT, frog_baby_tiles);
			frog_metasprites = frog_baby_metasprites;
			break;
			
		case CHILD:
			frog_bank = BANK(frog_child);
			SWITCH_ROM(frog_bank);
			set_sprite_data(0, frog_child_TILE_COUNT, frog_child_tiles);
			frog_metasprites = frog_child_metasprites;
			break;
			
		case TEEN:
			frog_bank = BANK(frog_teen);
			SWITCH_ROM(frog_bank);
			set_sprite_data(0, frog_teen_TILE_COUNT, frog_teen_tiles);
			frog_metasprites = frog_teen_metasprites;
			break;
		
		case TEEN_TAIL:
			frog_bank = BANK(frog_teen_tail);
			SWITCH_ROM(frog_bank);
			set_sprite_data(0, frog_teen_tail_TILE_COUNT, frog_teen_tail_tiles);
			frog_metasprites = frog_teen_tail_metasprites;
			break;
		
		case TEEN_APPLE:
			frog_bank = BANK(frog_teen_apple);
			SWITCH_ROM(frog_bank);
			set_sprite_data(0, frog_teen_apple_TILE_COUNT, frog_teen_apple_tiles);
			frog_metasprites = frog_teen_apple_metasprites;
			break;
		
		case ADULT_NORMAL:
			frog_bank = BANK(frog_normal);
			SWITCH_ROM(frog_bank);
			set_sprite_data(0, frog_normal_TILE_COUNT, frog_normal_tiles);
			frog_metasprites = frog_normal_metasprites;
			break;
		
		case ADULT_AXOLOTL:
			frog_bank = BANK(frog_axolotl);
			SWITCH_ROM(frog_bank);
			set_sprite_data(0, frog_axolotl_TILE_COUNT, frog_axolotl_tiles);
			frog_metasprites = frog_axolotl_metasprites;
			break;
			
		case ADULT_APPLE:
			frog_bank = BANK(frog_apple);
			SWITCH_ROM(frog_bank);
			set_sprite_data(0, frog_apple_TILE_COUNT, frog_apple_tiles);
			frog_metasprites = frog_apple_metasprites;
			break;
		
		case ADULT_MUSHROOM:
			frog_bank = BANK(frog_mushroom);
			SWITCH_ROM(frog_bank);
			set_sprite_data(0, frog_mushroom_TILE_COUNT, frog_mushroom_tiles);
			frog_metasprites = frog_mushroom_metasprites;
			break;
		
		case ADULT_DRAGON:
			frog_bank = BANK(frog_dragon);
			SWITCH_ROM(frog_bank);
			set_sprite_data(0, frog_dragon_TILE_COUNT, frog_dragon_tiles);
			frog_metasprites = frog_dragon_metasprites;
			break;
	}
	
	SWITCH_ROM(old_bank);
}

void set_frog_state(enum State new_state) {
	my_state = new_state;
}

void draw_frog() {
	uint8_t old_bank = CURRENT_BANK;
	uint8_t last_used_sprite = 0;
	SWITCH_ROM(frog_bank);
	last_used_sprite = move_metasprite(frog_metasprites[my_state + frame], 0, 0, x_pos, y_pos);
	hide_sprites_range(last_used_sprite, MAX_HARDWARE_SPRITES);
	SWITCH_ROM(old_bank);
}

void move_frog(uint8_t new_x, uint8_t new_y) {
	x_pos = new_x;
	y_pos = new_y;
	draw_frog();
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
			if (my_evolution == BABY) {
				set_frog_evolution(CHILD);
			} else if (my_evolution == CHILD) {
				set_frog_evolution(TEEN);
			} else if (my_evolution == TEEN) {
				set_frog_evolution(ADULT_NORMAL);
			} else if (my_evolution == ADULT_NORMAL) {
				set_frog_evolution(ADULT_DRAGON);
			}
			temp_age = 0;
			set_frog_state(NORMAL_STATE);
			break;
	}
	
	frame++;
	if (my_state == EAT_STATE) {
		if (frame > 2) {
			frame = 1;
		}
	} else if (frame > 1) {
		frame = 0;
	}
	
	draw_frog();
}
