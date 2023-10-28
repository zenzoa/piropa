#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <rand.h>

#include <stdio.h>
#include <gbdk/emu_debug.h>

#include "scene.h"
#include "field.h"
#include "animation.h"
#include "frog_sprites.h"
#include "emote_sprites.h"

#include "sprites/misc_16x8/dirt.h"

BANKREF(frog_bank)

uint8_t frog_x;
uint8_t frog_y;

uint8_t goal_x;
uint8_t goal_y;

uint8_t life_stage;
#define EGG 0
#define TADPOLE 1
#define FROGLET 2
#define TEEN 3
#define ADULT 4
#define DEAD_BAD 5
#define DEAD_GOOD 6

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
uint8_t poops_x[6];
uint8_t poops_y[6];
#define MAX_POOPS 6

uint8_t stage;
uint8_t anim;
uint8_t emote;

animation_t frog_anim;
animation_t emote_anim;
uint8_t anim_complete = 0;

void die_badly(void) {
	life_stage = DEAD_BAD;
}

void die_well(void) {
	life_stage = DEAD_GOOD;
}

void place_poop(void) {
	for (uint8_t i = 0; i < MAX_POOPS; i++) {
		if (poops_x[i] == 0 && poops_y[i] == 0) {
			poops_x[i] = frog_x / 8;
			poops_y[i] = frog_y / 8;
			if (current_scene == FIELD) {
				update_poops(poops_x, poops_y, MAX_POOPS);
			}
			break;
		}
	}
}

void clean_poop(uint8_t x, uint8_t y) {
	for (uint8_t i = 0; i < MAX_POOPS; i++) {
		if (poops_x[i] == x && poops_y[i] == y) {
			poops_x[i] = 0;
			poops_y[i] = 0;
			if (poops > 0) {
				poops -= 1;
			}
			update_poops(poops_x, poops_y, MAX_POOPS);
			break;
		}
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
		weight += 1;
		stomach = 9;
	}
}

void update_bowels(void) {
	if (bowels > 3) {
		if (poops < MAX_POOPS) {
			poops += 1;
			place_poop();
		}
		bowels = 0;
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
	if (time_of_day == DAY) {
		if (energy > 0) {
			energy -= 1;
		}
	} else {
		energy += 2;
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
	if (time_of_day == DAY && love > 0) {
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

void update_stats(void) {
	update_stomach();
	update_weight();
	update_hygiene();
	update_energy();
	update_love();
	update_medicine();
	update_health();
	update_sickness();

	EMU_printf("");
	EMU_printf("stomach: %hd", stomach);
	EMU_printf("weight: %hd", weight);
	EMU_printf("hygiene: %hd", hygiene);
	EMU_printf("energy: %hd", energy);
	EMU_printf("love: %hd", love);
	EMU_printf("medicine: %hd", medicine);
	EMU_printf("health: %hd", health);
	EMU_printf("sickness: %hd", sickness);

	update_mood();
}

void feed_fly(void) {
	stomach += 1;
}

void feed_dragonfly(void) {
	stomach += 3;
}

void feed_butterfly(void) {
	stomach += 1;
	love += 3;
}

void feed_firefly(void) {
	stomach += 1;
	energy += 3;
}

void wash(void) {
	hygiene += 3;
}

void pet(void) {
	love += 1;
}

void medicate(void) {
	medicine += 3;
	sickness = 0;
	if (love > 0) {
		love -= 1;
	}
}

void draw_frog(uint8_t *last_sprite) {
	anim_complete = update_animation(&frog_anim);
	update_animation(&emote_anim);

	draw_frog_sprite(frog_x, frog_y, frog_anim.frame, last_sprite);

	if (emote != EMOTE_NONE) {
		draw_emote_sprite(frog_x + 12, frog_y - 8, emote_anim.frame, last_sprite);
	}

	// if (hygiene == 0) {
	// 	draw_dirt_sprite();
	// }
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
			frog_anim = new_animation(48, 2, 1);
			emote_anim = new_animation(48, 2, 1);
			break;

		case ACTION_SLEEP:
			anim = ANIM_SLEEP;
			emote = EMOTE_SLEEP;
			frog_anim = new_animation(32, 2, 0);
			emote_anim = new_animation(32, 2, 0);
			break;

		case ACTION_WAKE:
			anim = ANIM_YAWN;
			emote = EMOTE_BUBBLES;
			frog_anim = new_animation(48, 2, 1);
			emote_anim = new_animation(48, 2, 1);
			break;

		case ACTION_WASH:
			anim = ANIM_HAPPY;
			emote = EMOTE_NONE;
			frog_anim = new_animation(32, 2, 0);
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
			frog_anim = new_animation(32, 2, 0);
			break;

		case ACTION_LOVE:
			anim = ANIM_LAUGH;
			emote = EMOTE_HEART;
			frog_anim = new_animation(32, 2, 3);
			break;

		case ACTION_MEDICATE:
			anim = ANIM_STRESSED;
			emote = EMOTE_NONE;
			frog_anim = new_animation(32, 2, 3);
			break;

		case ACTION_POOP:
			anim = ANIM_HAPPY;
			emote = EMOTE_NONE;
			frog_anim = new_animation(64, 2, 1);
			break;
	}

	swap_frog_vram();
	set_frog_sprite_data(stage, anim);

	if (medicine > 0) {
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

void setup_frog(void) {
	frog_x = 66;
	frog_y = 82;

	goal_x = frog_x;
	goal_y = frog_y;

	life_stage = ADULT;

	stomach = 9;
	bowels = 0;
	weight = 5;
	hygiene = 9;
	energy = 9;
	love = 0;
	medicine = 0;
	health = 9;
	poops = 0;
	update_mood();

	stage = STAGE_NORM;
	start_action(ACTION_STAND);

	set_frog_sprite_data(stage, anim);
	set_emote_sprite_data(emote);
}

void update_frog(void) {
	switch(life_stage) {
		case EGG:
			// once old enough, evolve into next stage
			break;
		case DEAD_BAD:
			break;
		case DEAD_GOOD:
			break;
		default:
			switch(action) {
				case ACTION_STAND:
					// if it's nighttime -> ACTION_YAWN
					if (frog_anim.frame == 0 && frog_anim.ticks == 0) {
						uint8_t n = rand();
						if (n < 25) {
							start_action(ACTION_WALK);
						} else if (n < 50) {
							start_action(ACTION_EMOTE);
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
						EMU_printf("");
						EMU_printf("move toward goal %d %d to %d %d", frog_x, frog_y, goal_x, goal_y);
						move_toward_goal();
						if (frog_x == goal_x && frog_y == goal_y) {
							EMU_printf("");
							EMU_printf("REACH GOAL");
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
					// if it's daytime
					if (anim_complete) {
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
						start_action(ACTION_CLEAN);
					}
					break;

				case ACTION_CLEAN:
					if (anim_complete) {
						start_action(ACTION_STAND);
					}
					break;

				case ACTION_PET:
					if (anim_complete) {
						start_action(ACTION_STAND);
					}
					break;

				case ACTION_LOVE:
					if (anim_complete) {
						start_action(ACTION_STAND);
					}
					break;

				case ACTION_MEDICATE:
					if (anim_complete) {
						start_action(ACTION_STAND);
					}
					break;

				case ACTION_POOP:
					if (anim_complete) {
						start_action(ACTION_STAND);
					}
					break;

			}
	}
}
