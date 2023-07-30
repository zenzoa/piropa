#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <rand.h>

#include "clock.h"
#include "animation.h"
#include "frog_sprites.h"
#include "emote_sprites.h"

#include "sprites/misc_16x8/dirt.h"

BANKREF(frog_bank)

uint8_t frog_x;
uint8_t frog_y;

uint8_t goal_x;
uint8_t goal_y;

uint8_t fullness;
uint16_t last_fullness_decrease; // age (in mins)
#define TIME_TO_FULLNESS_DECREASE 1 //60
#define MAX_FULLNESS 12

uint8_t happiness;
uint16_t last_happiness_decrease; // age (in mins)
#define TIME_TO_HAPPINESS_DECREASE 1 //60
#define MAX_HAPPINESS 12

uint8_t cleanliness;
uint16_t last_cleanliness_decrease; // age (in mins)
#define TIME_TO_CLEANLINESS_DECREASE 720
#define MAX_CLEANLINESS 12

uint8_t care_mistakes;
uint16_t empty_fullness_time; // age (in mins)
uint16_t empty_happiness_time; // age (in mins)
uint16_t empty_cleanliness_time; // age (in mins)
#define TIME_TO_CARE_MISTAKE 60

uint8_t sickness_counter;
uint16_t last_sickness_increase; // age (in mins)
#define TIME_TO_SICKNESS_INCREASE 60
#define MAX_SICKNESS 12

uint8_t friendship_points;
uint16_t last_friendship_increase; // age (in mins)
#define TIME_TO_FRIENDSHIP_INCREASE 60
#define FRIENDSHIP_POINTS_PER_LEVEL 6

uint8_t friendship_level;
#define POINTS_PER_FRIENDSHIP_LEVEL 6
#define MAX_FRIENDSHIP 10

uint8_t vegetarian;
uint8_t carnivore;

uint16_t age; // in minutes
#define AGE_TADPOLE 1
#define AGE_POLLIWOG 61
#define AGE_FROGLET 1501
#define AGE_ADULT 4381
#define AGE_SPECIAL_ADULT 8701
#define AGE_DEATH 20160
#define AGE_SPECIAL_DEATH 30240

uint8_t stage;
uint8_t face;
uint8_t emote;

uint8_t personality;
#define PERSONALITY_NORMAL 0
#define PERSONALITY_SHY 1
#define PERSONALITY_FRIENDLY 2
#define PERSONALITY_ANGRY 3

uint8_t state;
uint8_t prev_state;
#define STATE_STAND 0
#define STATE_WALK 1
#define STATE_SLEEP 2
#define STATE_RETREAT 3
#define STATE_EAT 4
#define STATE_BATH 5
#define STATE_PET 6
#define STATE_HEAL 7
#define STATE_HAPPY 8
#define STATE_HUNGRY 9
#define STATE_DIRTY 10
#define STATE_SAD 11
#define STATE_SICK 12
#define STATE_GROW 13
#define STATE_FRIENDSHIP 14
#define STATE_DEAD 15

animation_t frog_anim;
animation_t emote_anim;

void care_mistake() {
	care_mistakes++;
}

void die_of_sickness() {
	state = STATE_DEAD;
}

void die_of_old_age() {
	state = STATE_DEAD;
}

void friendship_level_up() {
	friendship_level++;
	state = STATE_FRIENDSHIP;
}

void update_stats() {
	// update age
	uint16_t temp_days = (days <= 44) ? days : 44;
	age = (temp_days * 1440) + (hours * 60) + minutes;

	uint8_t d;

	// update fullness
	if (age - last_fullness_decrease >= TIME_TO_FULLNESS_DECREASE) {
		d = (age - last_fullness_decrease) / TIME_TO_FULLNESS_DECREASE;
		last_fullness_decrease = age;
		if (d > fullness) {
			if (fullness > 0) {
				empty_fullness_time = age - ((d - fullness) * TIME_TO_FULLNESS_DECREASE);
			}
			fullness = 0;
		} else {
			fullness -= d;
			if (fullness == 0) {
				empty_fullness_time = age;
			}
		}
	}

	// update happiness
	if (age - last_happiness_decrease >= TIME_TO_HAPPINESS_DECREASE) {
		d = (age - last_happiness_decrease) / TIME_TO_HAPPINESS_DECREASE;
		last_happiness_decrease = age;
		if (d > happiness) {
			if (happiness > 0) {
				empty_happiness_time = age - ((d - happiness) * TIME_TO_HAPPINESS_DECREASE);
			}
			happiness = 0;
		} else {
			happiness -= d;
			if (happiness == 0) {
				empty_happiness_time = age;
			}
		}
	}

	// update cleanliness
	if (age - last_cleanliness_decrease >= TIME_TO_CLEANLINESS_DECREASE) {
		d = (age - last_cleanliness_decrease) / TIME_TO_CLEANLINESS_DECREASE;
		last_cleanliness_decrease = age;
		if (d > cleanliness) {
			if (cleanliness > 0) {
				empty_cleanliness_time = age - ((d - cleanliness) * TIME_TO_CLEANLINESS_DECREASE);
			}
			cleanliness = 0;
		} else {
			cleanliness -= d;
			if (cleanliness == 0) {
				empty_cleanliness_time = age;
			}
		}
	}

	// check for care mistakes
	if (age - empty_fullness_time >= TIME_TO_CARE_MISTAKE) {
		care_mistake();
	}
	if (age - empty_happiness_time >= TIME_TO_CARE_MISTAKE) {
		care_mistake();
	}
	if (age - empty_cleanliness_time >= TIME_TO_CARE_MISTAKE) {
		care_mistake();
	}

	// update sickness counter
	if (state == STATE_SICK && age - last_sickness_increase >= TIME_TO_SICKNESS_INCREASE) {
		d = (age - last_sickness_increase) / TIME_TO_SICKNESS_INCREASE;
		last_sickness_increase = age;
		sickness_counter += d;
		if (sickness_counter >= MAX_SICKNESS) {
			die_of_sickness();
		}
	}

	// update friendship points
	if (friendship_level < MAX_FRIENDSHIP) {
		if (age - last_friendship_increase >= TIME_TO_FRIENDSHIP_INCREASE) {
			d = (age - last_friendship_increase) / TIME_TO_FRIENDSHIP_INCREASE;
			friendship_points += d;
			if (friendship_points >= POINTS_PER_FRIENDSHIP_LEVEL) {
				friendship_points = 0;
				friendship_level_up();
			}
		}
	}
}

void setup_frog() {
	frog_x = 100;
	frog_y = 100;

	frog_anim = new_animation(32, 2, 0);
	emote_anim = new_animation(32, 2, 0);
	emote_anim.ticks = 24;

	stage = STAGE_NORM;
	face = FACE_HAPPY;
	emote = EMOTE_LOVE;

	fullness = 8;
	happiness = 4;

	set_frog_sprite_data(stage, face);
	set_emote_sprite_data(emote);
}

void draw_frog(uint8_t *last_sprite) {
	update_animation(&frog_anim);
	update_animation(&emote_anim);

	draw_frog_sprite(frog_x, frog_y, frog_anim.frame, last_sprite);

	if (emote != EMOTE_NONE) {
		draw_emote_sprite(frog_x + 32, frog_y, emote_anim.frame, last_sprite);
	}
}
