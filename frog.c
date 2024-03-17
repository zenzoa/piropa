#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <rand.h>

#include "common.h"
#include "audio.h"
#include "colors.h"
#include "save.h"
#include "bugs.h"
#include "animation.h"
#include "frog_sprites.h"
#include "emote_sprites.h"

static uint8_t goal_x;
static uint8_t goal_y;

#define MOOD_NEUTRAL 0
#define MOOD_HAPPY 1
#define MOOD_HUNGRY 2
#define MOOD_TIRED 3
#define MOOD_LONELY 4
#define MOOD_SICK 5
static uint8_t mood;

#define ACTION_STAND 0
#define ACTION_EMOTE 1
#define ACTION_WALK 2
#define ACTION_BITE 3
#define ACTION_EAT 4
#define ACTION_REFUSE 5
#define ACTION_ENJOY 6
#define ACTION_YAWN 7
#define ACTION_SLEEP 8
#define ACTION_WAKE 9
#define ACTION_WASH 10
#define ACTION_CLEAN 11
#define ACTION_PET 12
#define ACTION_LOVE 13
#define ACTION_MEDICATE 14
#define ACTION_POOP 15
#define ACTION_WATERING 16
static uint8_t action;

static uint8_t night_timer;

static animation_t frog_anim;
static animation_t emote_anim;
static uint8_t anim_complete;

static uint8_t pet_loops;
static uint8_t wash_loops;

static uint8_t evolution_counter;
static uint8_t evolution_frame;
static uint8_t next_stage;

static void start_action(uint8_t new_action);
static void set_stage(uint8_t new_stage);
static void start_evolution(uint8_t new_stage);

#define FROG_VRAM_1 0x0
#define FROG_VRAM_2 0x20
static uint8_t frog_vram = FROG_VRAM_1;

static sprite_data_t frog_sprite;

static uint8_t frog_palette = GREEN_PALETTE;

static void swap_frog_vram(void) {
	if (frog_vram == FROG_VRAM_1) {
		frog_vram = FROG_VRAM_2;
	} else {
		frog_vram = FROG_VRAM_1;
	}
}

static void update_frog_sprite_data(void) {
	frog_sprite = frog_sprite_table[stage][anim];
	swap_frog_vram();
	set_banked_sprite_data(frog_sprite.bank, frog_vram, frog_sprite.tile_count, frog_sprite.tiles);
}

uint8_t is_sleeping(void) BANKED {
	return action == ACTION_SLEEP;
}

static void die_badly(void) {
	death_anim_start = TRUE;
	good_death = FALSE;
}

static void die_well(void) {
	death_anim_start = TRUE;
	good_death = TRUE;
}

static void update_mood(void) {
	if (sickness > 0) {
		mood = MOOD_SICK;
	} else if (stomach <= energy && stomach <= love && stomach < 3) {
		mood = MOOD_HUNGRY;
	} else if (energy <= stomach && energy <= love && energy < 3) {
		mood = MOOD_TIRED;
	} else if (love <= energy && love <= stomach && love < 3) {
		mood = MOOD_LONELY;
	} else if (stomach > 5 && energy > 5 && love > 5) {
		mood = MOOD_HAPPY;
	} else {
		mood = MOOD_NEUTRAL;
	}
}

static void update_stomach(void) {
	if (stomach > 0) {
		stomach -= 1;
		bowels += 1;
	}
	if (stomach == 0) {
		if (weight > 0) {
			weight -= 1;
		}
	} else if (stomach > 9) {
		stomach = 9;
	}
}

static uint8_t check_bowels(void) {
	if (bowels > 3) {
		bowels = 0;
		if (poop_count < 6) {
			start_action(ACTION_POOP);
		}
		return TRUE;
	} else {
		return FALSE;
	}
}

static void update_weight(void) {
	if (weight == 0) {
		die_badly();
	} else if (life_stage == TADPOLE && weight > 5 && health > 0) {
		health -= 1;
	} else if (life_stage == FROGLET && weight > 10 && health > 0) {
		health -= 1;
	} else if (life_stage == TEEN && weight > 20 && health > 0) {
		health -= 1;
	} else if (life_stage == ADULT && weight > 40 && health > 0) {
		health -= 1;
	}
	if (weight > 99) {
		weight = 99;
	}
}

static void update_hygiene(void) {
	for (uint8_t i = 0; i < poop_count; i++) {
		if (hygiene > 0) {
			hygiene -= 1;
		}
	}
	if (hygiene == 0 && health > 0) {
		health -= 1;
	} else if (hygiene > 9) {
		hygiene = 9;
	}
}

static void update_energy(void) {
	if (is_night) {
		energy += 2;
	} else if (energy > 0) {
		energy -= 1;
	}
	if (energy == 0 && health > 0) {
		health -= 1;
	} else if (energy > 9) {
		energy = 9;
	}
}

static void update_love(void) {
	if (love > 0 && !is_night) {
		love -= 1;
	} else if (love > 9) {
		love = 9;
	}
}

static void update_medicine(void) {
	if (medicine > 0) {
		medicine -= 1;
	} else if (medicine > 9) {
		medicine = 9;
	}
}

static void update_health(void) {
	if (health == 0) {
		sickness += 1;
	}
}

static void update_sickness(void) {
	if (sickness > 3) {
		die_badly();
	}
}

void update_stats(void) BANKED {
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

		update_mood();

	}

	is_time_to_save = TRUE;
}

void start_feed(uint8_t bug_type) BANKED {
	switch(bug_type) {
		case BUG_FLY:
			stomach += 1;
			break;
		case BUG_DRAGONFLY:
			stomach += 3;
			if (num_dragonflies_eaten < 255) { num_dragonflies_eaten += 1; }
			break;
		case BUG_FIREFLY:
			stomach += 3;
			energy += 3;
			if (num_fireflies_eaten < 255) { num_fireflies_eaten += 1; }
			break;
		case BUG_BUTTERFLY:
			stomach = 9;
			love = 9;
			if (num_butterflies_eaten < 255) { num_butterflies_eaten += 1; }
			break;
		case BUG_CICADA:
			stomach = 9;
			if (weight < 200) {
				weight += 2;
			}
			if (num_cicadas_eaten < 255) { num_cicadas_eaten += 1; }
			break;
	}
	if (stomach > 9 && weight < 200) {
		weight += (stomach - 9);
	}
	update_mood();
	start_action(ACTION_BITE);
	is_time_to_save = TRUE;
}

void start_wash(void) BANKED {
	if (action == ACTION_STAND || action == ACTION_EMOTE || action == ACTION_WALK) {
		play_sfx(SFX_WASH);
		start_action(ACTION_WASH);
	} else if (action == ACTION_WASH) {
		if (frog_anim.loop > 0) { play_sfx(SFX_WASH); }
		wash_loops += frog_anim.loop;
		frog_anim.loop = 0;
	}
}

static void end_wash(void) {
	wash_loops += frog_anim.loop;
	if (wash_loops >= 3) {
		hygiene += 3;
		update_mood();
		start_action(ACTION_CLEAN);
	} else {
		start_action(ACTION_STAND);
	}
	is_time_to_save = TRUE;
}

void start_pet(void) BANKED {
	if (action == ACTION_STAND || action == ACTION_EMOTE || action == ACTION_WALK) {
		play_sfx(SFX_PET);
		start_action(ACTION_PET);
	} else if (action == ACTION_PET) {
		if (frog_anim.loop > 0) { play_sfx(SFX_PET); }
		pet_loops += frog_anim.loop;
		frog_anim.loop = 0;
	}
}

static void end_pet(void) {
	pet_loops += frog_anim.loop;
	if (pet_loops >= 3) {
		love += pet_loops / 3;
		update_mood();
		start_action(ACTION_ENJOY);
	} else {
		start_action(ACTION_STAND);
	}
	is_time_to_save = TRUE;
}

void start_medicate(void) BANKED {
	if (sickness == 0) {
		if (love > 0) {
			love -= 1;
		}
		start_action(ACTION_REFUSE);
	} else {
		medicine += 1;
		health += 1;
		sickness = 0;
		update_mood();
		start_action(ACTION_MEDICATE);
	}
	is_time_to_save = TRUE;
}

void start_sleep(void) BANKED {
	if (life_stage != EGG && life_stage != DEAD) {
		night_timer = 0;
		frog_x = 76;
		frog_y = 120;
		start_action(ACTION_YAWN);
	}
}

void start_walk_to_plant(uint8_t plant_number) BANKED {
	switch(plant_number) {
		case 0:
			goal_x = PLANT_0_X * 8 - 16;
			goal_y = PLANT_0_Y * 8 + 10;
			break;
		case 1:
			goal_x = PLANT_1_X * 8 - 16;
			goal_y = PLANT_1_Y * 8 + 10;
			break;
		case 2:
			goal_x = PLANT_2_X * 8 - 16;
			goal_y = PLANT_2_Y * 8 + 10;
			break;
	}
	start_action(ACTION_WALK);
}

void place_in_scene(void) BANKED {
	if (life_stage != EGG && life_stage != DEAD) {
		switch(current_scene) {
			case FIELD:
				if (is_night) {
					if (action == ACTION_SLEEP) {
						frog_x = 76;
						frog_y = 120;
					} else {
						start_sleep();
					}
				} else if (last_scene == POND) {
					frog_x = 12;
					frog_y = 100;
				} else if (last_scene == GARDEN) {
					frog_x = 132;
					frog_y = 100;
				}
				break;

			case POND:
				if (!is_night) {
					frog_x = 128;
					frog_y = 128;
				}
				break;

			case GARDEN:
				if (!is_night) {
					frog_x = 16;
					frog_y = 128;
				}
				break;
		}

		goal_x = frog_x;
		goal_y = frog_y;
	}
}

void draw_frog(void) BANKED {
	if (death_anim_complete) {
		death_anim_complete = FALSE;
		if (good_death) {
			set_stage(STAGE_DEAD_GOOD);
		} else {
			set_stage(STAGE_DEAD_BAD);
		}
	}

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
			draw_emote_sprite(frog_x + 8, frog_y + y_offset, emote_anim.frame);
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
			draw_bath_sprite(frog_x, frog_y, y_offset);

		} else if (action == ACTION_WATERING) {
			draw_watering_sprite(frog_x, frog_y);

		} else if (hygiene == 0) {
			draw_dirt_sprite(frog_x, frog_y);
		}
	}

	if (stage == STAGE_TEEN_BW || stage == STAGE_PANDA || stage == STAGE_APPLE || stage == STAGE_MUSH) {
		frog_palette = BROWN_PALETTE;
	} else if (stage == STAGE_AXO) {
		frog_palette = PINK_PALETTE;
	} else {
		frog_palette = GREEN_PALETTE;
	}

	if (anim == ANIM_WALK_RIGHT) {
		draw_banked_sprite_flip(frog_sprite.bank, frog_sprite.metasprites, frog_anim.frame, frog_vram, frog_palette, frog_x + 32, frog_y);
	} else {
		draw_banked_sprite(frog_sprite.bank, frog_sprite.metasprites, frog_anim.frame, frog_vram, frog_palette, frog_x, frog_y);
	}
}

static void random_goal(void) {
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

static void move_toward_goal(void) {
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

static void start_action(uint8_t new_action) {
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
					play_sfx(SFX_HAPPY);
					anim = ANIM_LAUGH;
					emote = EMOTE_SUN;
					break;
				case MOOD_HUNGRY:
					play_sfx(SFX_SAD);
					anim = ANIM_ANGRY;
					emote = EMOTE_ANGRY;
					break;
				case MOOD_TIRED:
					play_sfx(SFX_SAD);
					anim = ANIM_YAWN;
					emote = EMOTE_BUBBLES;
					break;
				case MOOD_LONELY:
					play_sfx(SFX_SAD);
					anim = ANIM_STRESSED;
					emote = EMOTE_HEARTBREAK;
					break;
				case MOOD_SICK:
					play_sfx(SFX_SAD);
					anim = ANIM_STRESSED;
					emote = EMOTE_SKULL;
					break;
			}
			frog_anim = new_animation(32, 2, 3);
			emote_anim = new_animation(32, 2, 3);
			break;

		case ACTION_WALK:
			if (current_scene == FIELD) {
				random_goal();
			}
			if (goal_x < frog_x) {
				anim = ANIM_WALK_LEFT;
			} else {
				anim = ANIM_WALK_RIGHT;
			}
			frog_anim = new_animation(24, 2, 0);
			emote = EMOTE_NONE;
			break;

		case ACTION_BITE:
			play_sfx(SFX_CHOMP);
			anim = ANIM_YAWN;
			emote = EMOTE_NONE;
			frog_anim = new_animation(24, 2, 1);
			frog_anim.frame = 1;
			break;

		case ACTION_EAT:
			anim = ANIM_EAT;
			emote = EMOTE_NONE;
			frog_anim = new_animation(24, 2, 3);
			break;

		case ACTION_REFUSE:
			play_sfx(SFX_SAD);
			anim = ANIM_SAD;
			emote = EMOTE_SAD;
			frog_anim = new_animation(32, 2, 3);
			emote_anim = new_animation(32, 2, 3);
			break;

		case ACTION_ENJOY:
			play_sfx(SFX_HAPPY);
			anim = ANIM_LAUGH;
			emote = EMOTE_SUN;
			frog_anim = new_animation(32, 2, 3);
			emote_anim = new_animation(32, 2, 3);
			break;

		case ACTION_YAWN:
			play_sfx(SFX_MEEP3);
			anim = ANIM_YAWN;
			emote = EMOTE_BUBBLES;
			frog_anim = new_animation(64, 2, 1);
			emote_anim = new_animation(64, 2, 1);
			break;

		case ACTION_SLEEP:
			if (current_scene == FIELD) { play_sfx(SFX_MEEP3); }
			anim = ANIM_SLEEP;
			emote = EMOTE_SLEEP;
			frog_anim = new_animation(48, 2, 0);
			emote_anim = new_animation(48, 2, 0);
			break;

		case ACTION_WAKE:
			play_sfx(SFX_MEEP3);
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
			play_sfx(SFX_HAPPY);
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
			play_sfx(SFX_HAPPY);
			anim = ANIM_LAUGH;
			emote = EMOTE_HEART;
			frog_anim = new_animation(32, 2, 3);
			break;

		case ACTION_MEDICATE:
			play_sfx(SFX_MEDS);
			anim = ANIM_STRESSED;
			emote = EMOTE_HEAL;
			frog_anim = new_animation(32, 2, 3);
			emote_anim = new_animation(32, 2, 3);
			break;

		case ACTION_POOP:
			play_sfx(SFX_MEEP2);
			anim = ANIM_HAPPY;
			emote = EMOTE_NONE;
			frog_anim = new_animation(64, 2, 1);
			break;

		case ACTION_WATERING:
			play_sfx(SFX_WASH);
			anim = ANIM_WALK_RIGHT;
			emote = EMOTE_NONE;
			frog_anim = new_animation(24, 1, 6);
			break;
	}

	update_frog_sprite_data();

	if (emote == EMOTE_NONE && medicine > 0) {
		emote = EMOTE_HEAL;
	}

	if (emote != EMOTE_NONE) {
		set_emote_sprite_data(emote);
	}

	action = new_action;
	anim_complete = 0;
}

static void set_stage(uint8_t new_stage) {
	stage = new_stage;

	switch(stage) {
		case STAGE_EGG:
			life_stage = EGG;
			break;

		case STAGE_TADPOLE:
			life_stage = TADPOLE;
			break;

		case STAGE_FROGLET:
			life_stage = FROGLET;
			if (weight < 5) {
				weight = 5;
			}
			break;

		case STAGE_TEEN_NORM:
		case STAGE_TEEN_TAIL:
		case STAGE_TEEN_BW:
			life_stage = TEEN;
			if (weight < 10) {
				weight = 10;
			}
			break;

		case STAGE_NORM:
		case STAGE_MUSH:
		case STAGE_AXO:
		case STAGE_DINO:
		case STAGE_APPLE:
		case STAGE_PANDA:
			life_stage = ADULT;
			if (weight < 20) {
				weight = 20;
			}
			break;

		case STAGE_DEAD_GOOD:
		case STAGE_DEAD_BAD:
			life_stage = DEAD;
			break;
	}

	if (life_stage == EGG || life_stage == DEAD) {
		update_frog_sprite_data();
		frog_anim = new_animation(32, 2, 0);
		frog_x = 72;
		frog_y = 78;

	} else {
		start_action(ACTION_ENJOY);
	}

	if (life_stage != EGG) {
		is_time_to_save = TRUE;
	}
}

static void start_evolution(uint8_t new_stage) {
	is_evolving = TRUE;
	evolution_counter = 0;
	evolution_frame = 0;
	next_stage = new_stage;
	play_sfx(SFX_EVOLVE);
}

static void update_evolution(void) {
	evolution_counter += 1;
	if (evolution_counter >= 8) {
		evolution_counter = 0;
		evolution_frame += 1;
		switch(evolution_frame) {
			case 1:
				set_bkg_colors(1);
				set_sprite_colors(1);
				break;
			case 2:
				set_bkg_colors(2);
				set_sprite_colors(2);
				break;
			case 3:
				set_bkg_colors(3);
				set_sprite_colors(3);
				break;
			case 9:
			case 15:
				play_sfx(SFX_EVOLVE);
				set_bkg_colors(3);
				break;
			case 4:
			case 8:
			case 10:
			case 14:
			case 16:
			case 20:
				set_bkg_colors(4);
				break;
			case 5:
			case 7:
			case 11:
			case 13:
			case 17:
			case 19:
				set_bkg_colors(5);
				break;
			case 6:
			case 12:
			case 18:
				set_bkg_colors(6);
				break;
			case 21:
				set_bkg_colors(3);
				set_stage(next_stage);
				break;
			case 22:
				set_bkg_colors(2);
				set_sprite_colors(2);
				break;
			case 23:
				set_bkg_colors(1);
				set_sprite_colors(1);
				break;
			case 24:
				set_bkg_colors(0);
				set_sprite_colors(0);
				is_evolving = FALSE;
				if (life_stage == DEAD) {
					play_music(DEATH_MUSIC);
				}
				break;
		}
	}
}

static void adjust_stats_at_evolution(void) {
	if (stomach > 1) {
		stomach = stomach >> 1;
	}
	if (hygiene > 1) {
		hygiene = hygiene >> 1;
	}
	if (love > 1) {
		love = love >> 1;
	}
	if (health > 1) {
		health = health >> 1;
	}
}

static void evolve(void) {
	if (life_stage == EGG) {
		start_evolution(STAGE_TADPOLE);
		adjust_stats_at_evolution();

	} else if (life_stage == TADPOLE) {
		start_evolution(STAGE_FROGLET);
		adjust_stats_at_evolution();

	} else if (life_stage == FROGLET) {
		if (num_fireflies_eaten >= 4) {
			start_evolution(STAGE_TEEN_BW);
		} else if (num_dragonflies_eaten >= 2) {
			start_evolution(STAGE_TEEN_TAIL);
		} else {
			start_evolution(STAGE_TEEN_NORM);
		}
		adjust_stats_at_evolution();

	} else if (life_stage == TEEN) {
		switch (stage) {
			case STAGE_TEEN_NORM:
				if (num_butterflies_eaten >= 4) {
					start_evolution(STAGE_MUSH);
				} else {
					start_evolution(STAGE_NORM);
				}
				break;

			case STAGE_TEEN_TAIL:
				if (weight >= 20) {
					start_evolution(STAGE_DINO);
				} else if (num_dragonflies_eaten >= 4) {
					start_evolution(STAGE_AXO);
				} else {
					start_evolution(STAGE_NORM);
				}
				break;

			case STAGE_TEEN_BW:
				if (num_dragonflies_eaten == 0 && num_cicadas_eaten == 0 && num_butterflies_eaten == 0) {
					start_evolution(STAGE_PANDA);
				} else {
					start_evolution(STAGE_APPLE);
				}
				break;

			default:
				start_evolution(STAGE_NORM);
		}
		adjust_stats_at_evolution();

	} else if (life_stage == ADULT) {
		die_well();
	}
}

static uint8_t is_time_to_evolve(void) {
	return (
		(life_stage == EGG && age >= 1) ||
		(life_stage == TADPOLE && age >= 4) ||
		(life_stage == FROGLET && age >= 9) ||
		(life_stage == TEEN && age >= 16) ||
		(life_stage == ADULT && age >= 25)
	);
}

void setup_frog(uint8_t reset) BANKED {
	if (!reset) {
		anim = ANIM_NEUTRAL;
		update_frog_sprite_data();
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
		weight = 1;
		hygiene = 9;
		energy = 9;
		love = 9;
		medicine = 0;
		health = 9;
		sickness = 0;
		num_dragonflies_eaten = 0;
		num_fireflies_eaten = 0;
		num_butterflies_eaten = 0;
		num_cicadas_eaten = 0;
	}
	update_mood();

	setup_emote_sprites();

	if (reset) {
		set_stage(STAGE_EGG);
	} else if (is_night) {
		anim = ANIM_SLEEP;
		update_frog_sprite_data();
		set_emote_sprite_data(EMOTE_SLEEP);
		start_action(ACTION_SLEEP);
	} else {
		anim = ANIM_NEUTRAL;
		update_frog_sprite_data();
		start_action(ACTION_STAND);
	}
}

void update_frog(void) BANKED {
	if (is_evolving) {
		update_evolution();

	} else {
		switch(life_stage) {
			case EGG:
				if (is_time_to_evolve() && !is_night && current_scene == FIELD) {
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

							} else if (current_scene == GARDEN && frog_x != 16 && frog_y != 128) {
								goal_x = 16;
								goal_y = 128;
								start_action(ACTION_WALK);

							} else if (!check_bowels()) {
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
								if (current_scene == GARDEN && frog_y < 128) {
									if (frog_x == PLANT_0_X * 8 - 16) {
										watering_plant = 1;
									} else if (frog_x == 64) {
										watering_plant = 2;
									} else {
										watering_plant = 3;
									}
									start_action(ACTION_WATERING);
								} else {
									start_action(ACTION_STAND);
								}
							}
						}
						break;

					case ACTION_BITE:
						if (anim_complete) {
							start_action(ACTION_EAT);
						}

					case ACTION_EAT:
						if (anim_complete) {
							start_action(ACTION_ENJOY);
						} else if (frog_anim.frame == 0) {
							play_sfx(SFX_EAT);
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
						} else if (frog_anim.frame == 0) {
							play_sfx(SFX_MEEP1);
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
							start_action(ACTION_STAND);
						}
						break;

					case ACTION_POOP:
						if (anim_complete) {
							poops_to_add += 1;
							start_action(ACTION_STAND);
						}
						break;

					case ACTION_WATERING:
						if (anim_complete) {
							start_action(ACTION_ENJOY);
						}
						break;

				}
		}
	}
}
