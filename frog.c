#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <rand.h>

#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "save.h"
#include "scene.h"
#include "field.h"
#include "animation.h"
#include "frog_sprites.h"
#include "emote_sprites.h"

BANKREF(frog_bank)

uint8_t frog_x;
uint8_t frog_y;

uint8_t goal_x;
uint8_t goal_y;

uint16_t age;
uint8_t age_part;

uint8_t life_stage;
#define EGG 0
#define TADPOLE 1
#define FROGLET 2
#define TEEN 3
#define ADULT 4
#define DEAD 5

uint8_t mood;
#define MOOD_NEUTRAL 0
#define MOOD_HAPPY 1
#define MOOD_HUNGRY 2
#define MOOD_TIRED 3
#define MOOD_LONELY 4
#define MOOD_SICK 5

uint8_t action;
#define ACTION_STAND 0
#define ACTION_EMOTE 1
#define ACTION_WALK 2
#define ACTION_EAT 3
#define ACTION_REFUSE 4
#define ACTION_ENJOY 5
#define ACTION_YAWN 6
#define ACTION_SLEEP 7
#define ACTION_WAKE 8
#define ACTION_WASH 9
#define ACTION_CLEAN 10
#define ACTION_PET 11
#define ACTION_LOVE 12
#define ACTION_MEDICATE 13
#define ACTION_POOP 14

uint8_t stomach;
uint8_t bowels;
uint8_t weight;
uint8_t hygiene;
uint8_t energy;
uint8_t love;
uint8_t medicine;
uint8_t health;
uint8_t sickness;

uint8_t poops;

uint8_t night_timer = 0;

uint8_t stage;
uint8_t anim;
uint8_t emote;

animation_t frog_anim;
animation_t emote_anim;
uint8_t anim_complete = 0;

uint8_t pet_loops = 0;
uint8_t wash_loops = 0;

uint8_t is_evolving = FALSE;
uint8_t evolution_counter = 0;
uint8_t evolution_frame = 0;
uint8_t next_stage;

void start_action(uint8_t new_action);
void set_stage(uint8_t new_stage);
void start_evolution(uint8_t new_stage);

void die_badly(void) {
	start_evolution(STAGE_DEAD_BAD);
}

void die_well(void) {
	start_evolution(STAGE_DEAD_GOOD);
}

void update_mood(void) {
	if (sickness > 0) {
		mood = MOOD_SICK;
		EMU_printf("MOOD: SICK");
	} else if (stomach <= energy && stomach <= love && stomach < 3) {
		mood = MOOD_HUNGRY;
		EMU_printf("MOOD: HUNGRY");
	} else if (energy <= stomach && energy <= love && energy < 3) {
		mood = MOOD_TIRED;
		EMU_printf("MOOD: TIRED");
	} else if (love <= energy && love <= stomach && love < 3) {
		mood = MOOD_LONELY;
		EMU_printf("MOOD: LONELY");
	} else if (stomach > 5 && energy > 5 && love > 5) {
		mood = MOOD_HAPPY;
		EMU_printf("MOOD: HAPPY");
	} else {
		mood = MOOD_NEUTRAL;
		EMU_printf("MOOD: NEUTRAL");
	}
}

void update_stomach(void) {
	if (stomach > 0) {
		stomach -= 1;
		bowels += 1;
	}
	if (stomach == 0) {
		if (weight > 0) {
			weight -= 1;
		}
	} else if (stomach > 9) {
		if (weight < 99) {
			weight += 1;
		}
		stomach = 9;
	}
}

uint8_t check_bowels(void) {
	if (bowels > 3) {
		if (poops < 6) {
			start_action(ACTION_POOP);
		}
		bowels = 0;
		return TRUE;
	} else {
		return FALSE;
	}
}

void update_weight(void) {
	if (weight == 0) {
		die_badly();
	} else if (life_stage == TADPOLE && (weight < 5 || weight > 10)) {
		if (health > 0) {
			health -= 1;
		}
	} else if (life_stage == FROGLET && (weight < 10 || weight > 20)) {
		if (health > 0) {
			health -= 1;
		}
	} else if (life_stage == TEEN && (weight < 20 || weight > 40)) {
		if (health > 0) {
			health -= 1;
		}
	} else if (life_stage == ADULT && (weight < 40 || weight > 80)) {
		if (health > 0) {
			health -= 1;
		}
	}
	if (weight > 99) {
		weight = 99;
	}
}

void update_hygiene(void) {
	for (uint8_t i = 0; i < poops; i++) {
		if (hygiene > 0) {
			hygiene -= 1;
		}
	}
	if (hygiene == 0) {
		if (health > 0) {
			health -= 1;
		}
	} else if (hygiene > 9) {
		hygiene = 9;
	}
}

void update_energy(void) {
	if (is_night) {
		energy += 2;
	} else {
		if (energy > 0) {
			energy -= 1;
		}
	}
	if (energy == 0) {
		if (health > 0) {
			health -= 1;
		}
	} else if (energy > 9) {
		energy = 9;
	}
}

void update_love(void) {
	if (love > 0 && !is_night) {
		love -= 1;
	}
	if (love > 9) {
		love = 9;
	}
}

void update_medicine(void) {
	if (medicine > 0) {
		medicine -= 1;
		health += 1;
	} else if (medicine > 9) {
		if (health > 0) {
			health -= 3;
		}
		medicine = 9;
	}
}

void update_health(void) {
	if (health == 0) {
		sickness += 1;
	}
}

void update_sickness(void) {
	if (sickness > 3) {
		die_badly();
	}
}

void update_stats(void) {
	age_part += 1;
	if (age_part >= ((2 * game_speed) + 1)) {
		age_part = 0;

		age += 1;

		if (life_stage == EGG || life_stage == DEAD) { return; }

		if (is_night) {
			night_timer += 1;
		}

		if (!is_night || night_timer >= 10) {
			night_timer = 0;
			update_stomach();
			update_weight();
			update_hygiene();
			update_love();
			update_medicine();
			update_health();
			update_sickness();
		}

		update_energy();

		EMU_printf("");
		EMU_printf("age: %d", age);
		EMU_printf("stomach: %d", stomach);
		EMU_printf("bowels: %d", bowels);
		EMU_printf("weight: %d", weight);
		EMU_printf("hygiene: %d", hygiene);
		EMU_printf("energy: %d", energy);
		EMU_printf("love: %d", love);
		EMU_printf("medicine: %d", medicine);
		EMU_printf("health: %d", health);
		EMU_printf("sickness: %d", sickness);
		EMU_printf("poops: %d", poops);

		update_mood();

	} else {
		EMU_printf("partial age: %d", age_part);
	}

	save_data();
}

void end_feed_fly(void) {
	stomach += 1;
	update_mood();
}

void end_feed_dragonfly(void) {
	stomach += 3;
	update_mood();
}

void end_feed_butterfly(void) {
	stomach += 1;
	love += 3;
	update_mood();
}

void end_feed_firefly(void) {
	stomach += 1;
	energy += 3;
	update_mood();
}

void start_wash(void) {
	if (action == ACTION_STAND || action == ACTION_EMOTE || action == ACTION_WALK) {
		start_action(ACTION_WASH);
	} else if (action == ACTION_WASH) {
		wash_loops += frog_anim.loop;
		frog_anim.loop = 0;
	}
}

void end_wash(void) {
	wash_loops += frog_anim.loop;
	if (wash_loops >= 3) {
		hygiene += 3;
		update_mood();
		start_action(ACTION_CLEAN);
	} else {
		start_action(ACTION_STAND);
	}
}

void start_pet(void) {
	if (action == ACTION_STAND || action == ACTION_EMOTE || action == ACTION_WALK) {
		start_action(ACTION_PET);
	} else if (action == ACTION_PET) {
		pet_loops += frog_anim.loop;
		frog_anim.loop = 0;
	}
}

void end_pet(void) {
	pet_loops += frog_anim.loop;
	if (pet_loops >= 3) {
		love += 1;
		update_mood();
		start_action(ACTION_ENJOY);
	} else {
		start_action(ACTION_STAND);
	}
}

void start_medicate(void) {
	start_action(ACTION_MEDICATE);
}

void end_medicate(void) {
	medicine += 3;
	sickness = 0;
	if (love > 0) {
		love -= 1;
	}
	update_mood();
}

void start_sleep(void) {
	if (life_stage != EGG && life_stage != DEAD) {
		night_timer = 0;
		frog_x = 76;
		frog_y = 120;
		start_action(ACTION_YAWN);
	}
}

void draw_frog(uint8_t *last_sprite) {
	anim_complete = update_animation(&frog_anim);
	update_animation(&emote_anim);

	if (!is_evolving && life_stage != EGG && life_stage != DEAD) {

		if (emote != EMOTE_NONE) {
			int8_t y_offset = -8;
			if (life_stage == TADPOLE || stage == STAGE_DINO) {
				y_offset -= 1;
			} else if (life_stage == FROGLET) {
				y_offset += 4;
			} else if (life_stage == TEEN) {
				y_offset += 2;
			}
			draw_emote_sprite(frog_x + 12, frog_y + y_offset, emote_anim.frame, last_sprite);
		}

		if (action == ACTION_WASH) {
			int8_t y_offset = frog_anim.frame;
			if (life_stage == TADPOLE || stage == STAGE_DINO) {
				y_offset -= 4;
			} else if (stage == STAGE_AXO) {
				y_offset -= 2;
			} else if (life_stage == FROGLET) {
				y_offset += 4;
			} else if (life_stage == TEEN) {
				y_offset += 2;
			}
			draw_bath_sprite(frog_x, frog_y, y_offset, last_sprite);

		} else if (hygiene == 0) {
			draw_dirt_sprite(frog_x, frog_y, last_sprite);
		}

	}

	draw_frog_sprite(frog_x, frog_y, frog_anim.frame, last_sprite);
}

void random_goal(void) {
	uint8_t zone = rand();

	if (zone < 32) {
		goal_x = 32;
		goal_y = 86;
	} else if (zone < 64) {
		goal_x = 66;
		goal_y = 82;
	} else if (zone < 96) {
		goal_x = 124;
		goal_y = 86;
	} else if (zone < 128) {
		goal_x = 40;
		goal_y = 102;
	} else if (zone < 160) {
		goal_x = 104;
		goal_y = 102;
	} else if (zone < 192) {
		goal_x = 24;
		goal_y = 124;
	} else if (zone < 224) {
		goal_x = 80;
		goal_y = 108;
	} else {
		goal_x = 120;
		goal_y = 124;
	}
}

void move_toward_goal(void) {
	uint8_t move_x = FALSE;
	uint8_t move_y = FALSE;
	if (goal_x != frog_x && goal_y != frog_y) {
		if (rand() < 128) {
			move_x = TRUE;
		} else {
			move_y = TRUE;
		}
	} else if (goal_x != frog_x) {
		move_x = TRUE;
	} else if (goal_y != frog_y) {
		move_y = TRUE;
	}

	if (move_x) {
		if (goal_x == frog_x + 1 || goal_x == frog_x - 1) {
			frog_x = goal_x;
		} else if (goal_x < frog_x) {
			frog_x -= 2;
		} else if (goal_x > frog_x) {
			frog_x += 2;
		}
	}

	if (move_y) {
		if (goal_y == frog_y + 1 || goal_y == frog_y - 1) {
			frog_y = goal_y;
		} else if (goal_y < frog_y) {
			frog_y -= 2;
		} else if (goal_y > frog_y) {
			frog_y += 2;
		}
	}
}

void start_action(uint8_t new_action) {
	if (life_stage == EGG || life_stage == DEAD) { return; }

	switch(new_action) {
		case ACTION_STAND:
			emote = EMOTE_NONE;
			switch(mood) {
				case MOOD_NEUTRAL:
					anim = ANIM_NEUTRAL;
					break;
				case MOOD_HAPPY:
					anim = ANIM_HAPPY;
					break;
				case MOOD_HUNGRY:
					anim = ANIM_SAD;
					break;
				case MOOD_TIRED:
					anim = ANIM_SAD;
					break;
				case MOOD_LONELY:
					anim = ANIM_SAD;
					break;
				case MOOD_SICK:
					anim = ANIM_SAD;
					emote = EMOTE_SKULL;
					emote_anim = new_animation(32, 2, 0);
					break;
			}
			frog_anim = new_animation(32, 2, 0);
			break;

		case ACTION_EMOTE:
			switch(mood) {
				case MOOD_NEUTRAL:
					anim = ANIM_NEUTRAL;
					emote = EMOTE_NONE;
					break;
				case MOOD_HAPPY:
					anim = ANIM_LAUGH;
					emote = EMOTE_SUN;
					break;
				case MOOD_HUNGRY:
					anim = ANIM_ANGRY;
					emote = EMOTE_ANGRY;
					break;
				case MOOD_TIRED:
					anim = ANIM_YAWN;
					emote = EMOTE_BUBBLES;
					break;
				case MOOD_LONELY:
					anim = ANIM_STRESSED;
					emote = EMOTE_HEARTBREAK;
					break;
				case MOOD_SICK:
					anim = ANIM_STRESSED;
					emote = EMOTE_SKULL;
					break;
			}
			frog_anim = new_animation(32, 2, 3);
			emote_anim = new_animation(32, 2, 3);
			break;

		case ACTION_WALK:
			random_goal();
			if (goal_x < frog_x) {
				anim = ANIM_WALK_LEFT;
			} else {
				anim = ANIM_WALK_RIGHT;
			}
			frog_anim = new_animation(24, 2, 0);
			emote = EMOTE_NONE;
			break;

		case ACTION_EAT:
			anim = ANIM_EAT;
			emote = EMOTE_NONE;
			frog_anim = new_animation(24, 3, 3);
			break;

		case ACTION_REFUSE:
			anim = ANIM_SAD;
			emote = EMOTE_SAD;
			frog_anim = new_animation(32, 2, 3);
			emote_anim = new_animation(32, 2, 3);
			break;

		case ACTION_ENJOY:
			anim = ANIM_LAUGH;
			emote = EMOTE_SUN;
			frog_anim = new_animation(32, 2, 3);
			emote_anim = new_animation(32, 2, 3);
			break;

		case ACTION_YAWN:
			anim = ANIM_YAWN;
			emote = EMOTE_BUBBLES;
			frog_anim = new_animation(64, 2, 1);
			emote_anim = new_animation(64, 2, 1);
			break;

		case ACTION_SLEEP:
			anim = ANIM_SLEEP;
			emote = EMOTE_SLEEP;
			frog_anim = new_animation(48, 2, 0);
			emote_anim = new_animation(48, 2, 0);
			break;

		case ACTION_WAKE:
			anim = ANIM_YAWN;
			emote = EMOTE_BUBBLES;
			frog_anim = new_animation(64, 2, 1);
			emote_anim = new_animation(64, 2, 1);
			break;

		case ACTION_WASH:
			anim = ANIM_HAPPY;
			emote = EMOTE_NONE;
			frog_anim = new_animation(32, 2, 2);
			wash_loops = 0;
			break;

		case ACTION_CLEAN:
			anim = ANIM_LAUGH;
			emote = EMOTE_SPARKLE;
			frog_anim = new_animation(32, 2, 3);
			emote_anim = new_animation(32, 2, 3);
			break;

		case ACTION_PET:
			anim = ANIM_HAPPY;
			emote = EMOTE_NONE;
			frog_anim = new_animation(32, 2, 2);
			pet_loops = 0;
			break;

		case ACTION_LOVE:
			anim = ANIM_LAUGH;
			emote = EMOTE_HEART;
			frog_anim = new_animation(32, 2, 3);
			break;

		case ACTION_MEDICATE:
			anim = ANIM_STRESSED;
			emote = EMOTE_HEAL;
			frog_anim = new_animation(32, 2, 3);
			emote_anim = new_animation(32, 2, 3);
			break;

		case ACTION_POOP:
			anim = ANIM_HAPPY;
			emote = EMOTE_NONE;
			frog_anim = new_animation(64, 2, 1);
			break;
	}

	swap_frog_vram();
	set_frog_sprite_data(stage, anim);

	if (emote == EMOTE_NONE && medicine > 0) {
		emote = EMOTE_HEAL;
	}

	if (emote != EMOTE_NONE) {
		swap_emote_vram();
		set_emote_sprite_data(emote);
	}

	action = new_action;
	anim_complete = 0;

	EMU_printf("");
	EMU_printf("ACTION: %d", action);
}

void set_stage(uint8_t new_stage) {
	stage = new_stage;

	EMU_printf("");
	EMU_printf("STAGE: %d", stage);

	switch(stage) {
		case STAGE_EGG:
			life_stage = EGG;
			break;

		case STAGE_TADPOLE:
			life_stage = TADPOLE;
			break;

		case STAGE_FROGLET:
			life_stage = FROGLET;
			break;

		case STAGE_TEEN_NORM:
		case STAGE_TEEN_TAIL:
		case STAGE_TEEN_BW:
			life_stage = TEEN;
			break;

		case STAGE_NORM:
		case STAGE_MUSH:
		case STAGE_AXO:
		case STAGE_DINO:
		case STAGE_APPLE:
		case STAGE_PANDA:
			life_stage = ADULT;
			break;

		case STAGE_DEAD_GOOD:
		case STAGE_DEAD_BAD:
			life_stage = DEAD;
			break;
	}

	if (life_stage == EGG || life_stage == DEAD) {
		swap_frog_vram();
		set_frog_sprite_data(stage, anim);
		frog_anim = new_animation(32, 2, 0);
		frog_x = 72;
		frog_y = 78;

	} else {
		start_action(ACTION_ENJOY);
	}

	save_data();
}

void start_evolution(uint8_t new_stage) {
	is_evolving = TRUE;
	evolution_counter = 0;
	evolution_frame = 0;
	next_stage = new_stage;
}

void update_evolution(void) {
	evolution_counter += 1;
	if (evolution_counter >= 8) {
		evolution_counter = 0;
		evolution_frame += 1;
		switch(evolution_frame) {
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
				break;
			case 9:
			case 15:
				BGP_REG = DMG_PALETTE(DMG_BLACK, DMG_BLACK, DMG_BLACK, DMG_BLACK);
				break;
			case 4:
			case 8:
			case 10:
			case 14:
			case 16:
			case 20:
				BGP_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_DARK_GRAY, DMG_DARK_GRAY, DMG_DARK_GRAY);
				break;
			case 5:
			case 7:
			case 11:
			case 13:
			case 17:
			case 19:
				BGP_REG = DMG_PALETTE(DMG_LITE_GRAY, DMG_LITE_GRAY, DMG_LITE_GRAY, DMG_LITE_GRAY);
				break;
			case 6:
			case 12:
			case 18:
				BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_WHITE, DMG_WHITE, DMG_WHITE);
				break;
			case 21:
				BGP_REG = DMG_PALETTE(DMG_BLACK, DMG_BLACK, DMG_BLACK, DMG_BLACK);
				set_stage(next_stage);
				break;
			case 22:
				BGP_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK, DMG_BLACK);
				OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK);
				break;
			case 23:
				BGP_REG = DMG_PALETTE(DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK);
				OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
				break;
			case 24:
				BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
				OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
				is_evolving = FALSE;
				break;
		}
	}
}

void evolve(void) {
	if (life_stage == EGG) {
		start_evolution(STAGE_TADPOLE);

	} else if (life_stage == TADPOLE) {
		start_evolution(STAGE_FROGLET);

	} else if (life_stage == FROGLET) {
		uint8_t n = rand();
		if (n < 85) {
			start_evolution(STAGE_TEEN_NORM);
		} else if (n < 170) {
			start_evolution(STAGE_TEEN_TAIL);
		} else {
			start_evolution(STAGE_TEEN_BW);
		}

	} else if (life_stage == TEEN) {
		uint8_t n = rand();
		if (n < 42) {
			start_evolution(STAGE_NORM);
		} else if (n < 85) {
			start_evolution(STAGE_MUSH);
		} else if (n < 128) {
			start_evolution(STAGE_AXO);
		} else if (n < 170) {
			start_evolution(STAGE_DINO);
		} else if (n < 212) {
			start_evolution(STAGE_APPLE);
		} else {
			start_evolution(STAGE_PANDA);
		}

	} else if (life_stage == ADULT) {
		die_well();
	}
}

uint8_t is_time_to_evolve(void) {
	return (
		(life_stage == EGG && age >= 1) ||
		(life_stage == TADPOLE && age >= 3) ||
		(life_stage == FROGLET && age >= 6) ||
		(life_stage == TEEN && age >= 10) ||
		(life_stage == ADULT && age >= 15)
	);
}

void setup_frog(uint8_t reset) {
	if (!reset) {
		anim = ANIM_NEUTRAL;
		set_frog_sprite_data(stage, anim);
		if (life_stage == EGG || life_stage == DEAD) {
			frog_anim = new_animation(32, 2, 0);
			frog_x = 72;
			frog_y = 78;
		} else {
			frog_x = 66;
			frog_y = 82;
		}
	}

	goal_x = frog_x;
	goal_y = frog_y;

	if (reset) {
		age = 0;
		age_part = 0;
		stomach = 9;
		bowels = 0;
		weight = 5;
		hygiene = 9;
		energy = 9;
		love = 5;
		medicine = 0;
		health = 9;
		poops = 0;
	}
	update_mood();

	setup_emote_sprites();

	if (reset) {
		set_stage(STAGE_EGG);
	} else if (is_night) {
		set_frog_sprite_data(stage, ANIM_SLEEP);
		set_emote_sprite_data(EMOTE_SLEEP);
		start_action(ACTION_SLEEP);
	} else {
		set_frog_sprite_data(stage, ANIM_NEUTRAL);
		start_action(ACTION_STAND);
	}
}

void update_frog(void) {
	if (is_evolving) {
		update_evolution();

	} else {
		switch(life_stage) {
			case EGG:
				if (is_time_to_evolve()) {
					evolve();
				}
				break;

			case DEAD:
				break;

			default:
				switch(action) {
					case ACTION_STAND:
						if (frog_anim.frame == 0 && frog_anim.ticks == 0) {
							if (is_time_to_evolve()) {
								evolve();
							} else if (current_scene != FIELD || !check_bowels()) {
								uint8_t n = rand();
								if (n < 25 && current_scene == FIELD) {
									start_action(ACTION_WALK);
								} else if (n < 50) {
									start_action(ACTION_EMOTE);
								}
							}
						}
						break;

					case ACTION_EMOTE:
						if (anim_complete) {
							start_action(ACTION_STAND);
						}
						break;

					case ACTION_WALK:
						if (frog_anim.ticks == 6 || frog_anim.ticks == 18) {
							move_toward_goal();
							if (frog_x == goal_x && frog_y == goal_y) {
								start_action(ACTION_STAND);
							}
						}
						break;

					case ACTION_EAT:
						if (anim_complete) {
							start_action(ACTION_STAND);
						}
						break;

					case ACTION_REFUSE:
						if (anim_complete) {
							start_action(ACTION_STAND);
						}
						break;

					case ACTION_ENJOY:
						if (anim_complete) {
							start_action(ACTION_STAND);
						}
						break;

					case ACTION_YAWN:
						if (anim_complete) {
							start_action(ACTION_SLEEP);
						}
						break;

					case ACTION_SLEEP:
						if (!is_night) {
							start_action(ACTION_WAKE);
						}
						break;

					case ACTION_WAKE:
						if (anim_complete) {
							start_action(ACTION_STAND);
						}
						break;

					case ACTION_WASH:
						if (anim_complete) {
							end_wash();
						}
						break;

					case ACTION_CLEAN:
						if (anim_complete) {
							start_action(ACTION_STAND);
						}
						break;

					case ACTION_PET:
						if (anim_complete) {
							end_pet();
						}
						break;

					case ACTION_LOVE:
						if (anim_complete) {
							start_action(ACTION_STAND);
						}
						break;

					case ACTION_MEDICATE:
						if (anim_complete) {
							end_medicate();
							start_action(ACTION_STAND);
						}
						break;

					case ACTION_POOP:
						if (anim_complete) {
							if (current_scene == FIELD) {
								poops += 1;
								SWITCH_ROM(BANK(field_bank));
								add_poop(frog_x / 8, frog_y / 8);
							}
							start_action(ACTION_STAND);
						}
						break;

				}
		}
	}
}
