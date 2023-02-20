#include <gb/gb.h>
#include <gb/metasprites.h>
#include <stdio.h>

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

#define BABY 0
#define CHILD 25
#define TEEN 50
#define TEEN_TAIL 75
#define TEEN_APPLE 100
#define ADULT_NORMAL 125
#define ADULT_AXOLOTL 150
#define ADULT_APPLE 175
#define ADULT_MUSHROOM 200
#define ADULT_DINOSAUR 225

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

uint8_t evolution = ADULT_NORMAL;
uint8_t state = NORMAL_STATE;

uint8_t x_pos = 0;
uint8_t y_pos = 0;

uint8_t age = 0;
uint8_t frame = 0;
uint8_t animation_counter = 0;
uint8_t animation_speed = 32;

uint8_t trust = 0;

uint8_t happiness = 0;
uint8_t hunger = 0;
uint8_t sleepiness = 0;
uint8_t dirtiness = 0;

void check_clock(void);
void set_frog_evolution(uint8_t new_evolution);
void set_frog_state(uint8_t new_state);
void draw_frog(void);
void move_frog(uint8_t new_x, uint8_t new_y);
void animate_frog(void);
void update_frog(void);

void main(void) {
	DISPLAY_ON;
	SHOW_SPRITES;
	SPRITES_8x8;
	
	ENABLE_RAM;
	volatile uint8_t * const rtc_register = (volatile uint8_t * const)0xA000;
	SWITCH_RAM(0xB);
	*rtc_register = 0x18;
	SWITCH_RAM(0xC);
	*rtc_register = 0b10000001;
	DISABLE_RAM;
	
	set_frog_evolution(BABY);
	move_frog(88, 80);
	
    while(1) {
    	update_frog();
		animate_frog();

		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}

void check_clock(void) {
	/* MBC3 RTC: https://gbdev.io/pandocs/MBC3.html */
	/* Thanks to CasualPokePlayer and NanoCodeBug for help with this! */
	
	ENABLE_RAM;
	
	volatile uint8_t * const latch_clock = (volatile uint8_t * const)0x6000;
	*latch_clock = 0;
	*latch_clock = 1;
	
	volatile uint8_t * const rtc_register = (volatile uint8_t * const)0xA000;
	SWITCH_RAM(0x8);
	uint8_t seconds = *rtc_register;
	SWITCH_RAM(0x9);
	uint8_t minutes = *rtc_register;
	SWITCH_RAM(0xA);
	uint8_t hours = *rtc_register;
	SWITCH_RAM(0xB);
	uint16_t days = *rtc_register;
	SWITCH_RAM(0xC);
	// bit 0 is the most significant bit of the day register
	// day is a total of 9 bits or 511 days
	if (*rtc_register & 0x01) {
		days |= 0x0100;
	}
	// day overflow bit set
	if (*rtc_register & 0b10000000) {
		days += 512;
	}
	
	printf("%d %d %d %d\n", days, hours, minutes, seconds);
	
	DISABLE_RAM;
}

void set_frog_evolution(uint8_t new_evolution) {
	evolution = new_evolution;
	hide_metasprite(frog_dragon_metasprites[state + frame], 0);
	
	if (evolution == BABY) {
		SWITCH_ROM(BANK(frog_baby));
		set_sprite_data(0, frog_baby_TILE_COUNT, frog_baby_tiles);
		
	} else if (evolution == CHILD) {
		SWITCH_ROM(BANK(frog_child));
		set_sprite_data(0, frog_child_TILE_COUNT, frog_child_tiles);
		
	} else if (evolution == TEEN) {
		SWITCH_ROM(BANK(frog_teen));
		set_sprite_data(0, frog_teen_TILE_COUNT, frog_teen_tiles);
		
	} else if (evolution == TEEN_TAIL) {
		SWITCH_ROM(BANK(frog_teen_tail));
		set_sprite_data(0, frog_teen_tail_TILE_COUNT, frog_teen_tail_tiles);
		
	} else if (evolution == TEEN_APPLE) {
		SWITCH_ROM(BANK(frog_teen_apple));
		set_sprite_data(0, frog_teen_apple_TILE_COUNT, frog_teen_apple_tiles);
		
	} else if (evolution == ADULT_NORMAL) {
		SWITCH_ROM(BANK(frog_normal));
		set_sprite_data(0, frog_normal_TILE_COUNT, frog_normal_tiles);
		
	} else if (evolution == ADULT_AXOLOTL) {
		SWITCH_ROM(BANK(frog_axolotl));
		set_sprite_data(0, frog_axolotl_TILE_COUNT, frog_axolotl_tiles);
		
	} else if (evolution == ADULT_APPLE) {
		SWITCH_ROM(BANK(frog_apple));
		set_sprite_data(0, frog_apple_TILE_COUNT, frog_apple_tiles);
		
	} else if (evolution == ADULT_MUSHROOM) {
		SWITCH_ROM(BANK(frog_mushroom));
		set_sprite_data(0, frog_mushroom_TILE_COUNT, frog_mushroom_tiles);
		
	} else if (evolution == ADULT_DINOSAUR) {
		SWITCH_ROM(BANK(frog_dragon));
		set_sprite_data(0, frog_dragon_TILE_COUNT, frog_dragon_tiles);
	}
}

void set_frog_state(uint8_t new_state) {
	state = new_state;
}

void draw_frog() {
	hide_metasprite(frog_dragon_metasprites[state + frame], 0);
	
	if (evolution == BABY) {
		move_metasprite(frog_baby_metasprites[state + frame], 0, 0, x_pos, y_pos);
		
	} else if (evolution == CHILD) {
		move_metasprite(frog_child_metasprites[state + frame], 0, 0, x_pos, y_pos);
		
	} else if (evolution == TEEN) {
		move_metasprite(frog_teen_metasprites[state + frame], 0, 0, x_pos, y_pos);
		
	} else if (evolution == TEEN_TAIL) {
		move_metasprite(frog_teen_tail_metasprites[state + frame], 0, 0, x_pos, y_pos);
		
	} else if (evolution == TEEN_APPLE) {
		move_metasprite(frog_teen_apple_metasprites[state + frame], 0, 0, x_pos, y_pos);
		
	} else if (evolution == ADULT_NORMAL) {
		move_metasprite(frog_normal_metasprites[state + frame], 0, 0, x_pos, y_pos);
		
	} else if (evolution == ADULT_AXOLOTL) {
		move_metasprite(frog_axolotl_metasprites[state + frame], 0, 0, x_pos, y_pos);
		
	} else if (evolution == ADULT_APPLE) {
		move_metasprite(frog_apple_metasprites[state + frame], 0, 0, x_pos, y_pos);
		
	} else if (evolution == ADULT_MUSHROOM) {
		move_metasprite(frog_mushroom_metasprites[state + frame], 0, 0, x_pos, y_pos);
		
	} else if (evolution == ADULT_DINOSAUR) {
		move_metasprite(frog_dragon_metasprites[state + frame], 0, 0, x_pos, y_pos);
	}
}

void move_frog(uint8_t new_x, uint8_t new_y) {
	x_pos = new_x;
	y_pos = new_y;
	draw_frog();
}

void animate_frog(void) {
	if (animation_counter >= animation_speed) {
		check_clock();
		age++;
		if (age == 10) {
			set_frog_state(WALK_STATE);
		} else if (age == 20) {
			set_frog_state(JOY_STATE);
		} else if (age == 30) {
			set_frog_state(EAT_STATE);
		} else if (age == 40) {
			set_frog_state(SLEEP_STATE);
		} else if (age == 50) {
			set_frog_state(BATH_STATE);
		} else if (age == 60) {
			set_frog_state(PET_STATE);
		} else if (age == 70) {
			set_frog_state(SAD_STATE);
		} else if (age == 80) {
			set_frog_state(HUNGRY_STATE);
		} else if (age == 90) {
			set_frog_state(SLEEPY_STATE);
		} else if (age == 100) {
			set_frog_state(DIRTY_STATE);
		} else if (age == 110) {
			set_frog_state(SHY_STATE);
		} else if (age == 120) {
			if (evolution == BABY) {
				set_frog_evolution(CHILD);
			} else if (evolution == CHILD) {
				set_frog_evolution(TEEN);
			} else if (evolution == TEEN) {
				set_frog_evolution(ADULT_NORMAL);
			} else if (evolution == ADULT_NORMAL) {
				set_frog_evolution(ADULT_DINOSAUR);
			}
			age = 0;
			set_frog_state(NORMAL_STATE);
		}
		frame++;
		if ((state != EAT_STATE && frame > 1) || (state == EAT_STATE && frame > 2)) { frame = 0; }
		draw_frog();
		animation_counter = 0;
	}
	animation_counter++;
}

void update_frog() {
	
}
