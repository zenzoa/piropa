#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <rand.h>

#include "common.h"

#include "sprites/bugs_small/fly.h"
#include "sprites/bugs_small/firefly.h"
#include "sprites/bugs_small/butterfly.h"
#include "sprites/bugs_big/dragonfly.h"

#define FLY_VRAM 0xc0
#define DRAGONFLY_VRAM 0xc2
#define FIREFLY_VRAM 0xc6
#define BUTTERFLY_VRAM 0xc8

#define MIN_X 8
#define MAX_X 160
#define MIN_Y 48
#define MAX_Y 120

static uint8_t fly_scene[FLY_COUNT];
static uint8_t fly_x[FLY_COUNT];
static uint8_t fly_y[FLY_COUNT];
static uint8_t fly_flip[FLY_COUNT];
static uint8_t fly_anim_counter[FLY_COUNT];
static uint8_t fly_anim_frame[FLY_COUNT];

static uint8_t dragonfly_scene[FLY_COUNT];
static uint8_t dragonfly_x[DRAGONFLY_COUNT];
static uint8_t dragonfly_y[DRAGONFLY_COUNT];
static uint8_t dragonfly_goal_x[DRAGONFLY_COUNT];
static uint8_t dragonfly_goal_y[DRAGONFLY_COUNT];
static uint8_t dragonfly_flip_x[DRAGONFLY_COUNT];
static uint8_t dragonfly_anim_counter[DRAGONFLY_COUNT];
static uint8_t dragonfly_anim_frame[DRAGONFLY_COUNT];

static uint8_t firefly_scene[FIREFLY_COUNT];
static uint8_t firefly_x[FIREFLY_COUNT];
static uint8_t firefly_y[FIREFLY_COUNT];
static uint8_t firefly_flip[FIREFLY_COUNT];
static uint8_t firefly_flip_y[FIREFLY_COUNT];
static uint8_t firefly_anim_counter[FIREFLY_COUNT];
static uint8_t firefly_anim_frame[FIREFLY_COUNT];

static uint8_t butterfly_scene[BUTTERFLY_COUNT];
static uint8_t butterfly_x[BUTTERFLY_COUNT];
static uint8_t butterfly_y[BUTTERFLY_COUNT];
static uint8_t butterfly_goal_x[BUTTERFLY_COUNT];
static uint8_t butterfly_goal_y[BUTTERFLY_COUNT];
static uint8_t butterfly_goal_plant[BUTTERFLY_COUNT];
static uint8_t butterfly_flip_x[BUTTERFLY_COUNT];
static uint8_t butterfly_flip_y[BUTTERFLY_COUNT];
static uint8_t butterfly_anim_counter[BUTTERFLY_COUNT];
static uint8_t butterfly_anim_frame[BUTTERFLY_COUNT];
static uint8_t butterfly_run_away[BUTTERFLY_COUNT];

static uint8_t hand_is_near;
static uint8_t chance_to_move_left;
static uint8_t chance_to_move_up;

static uint8_t alive_count;

static void spawn_fly(uint8_t i, uint8_t is_setup) {
	if (life_stage == DEAD) { return; }
	fly_alive[i] = TRUE;
	fly_respawn[i] = 0;
	fly_scene[i] = POND;
	if (is_setup) {
		fly_x[i] = MIN_X + (rand() % (MAX_X - MIN_X));
	} else {
		fly_x[i] = rand() < 128 ? 1 : 160;
	}
	fly_y[i] = MIN_Y + (rand() % (MAX_Y - MIN_Y));
	fly_anim_counter[i] = rand() % 12;
	fly_anim_frame[i] = rand() % 2;
}

static void spawn_dragonfly(uint8_t i, uint8_t is_setup) {
	if (life_stage == DEAD) { return; }
	dragonfly_alive[i] = TRUE;
	dragonfly_respawn[i] = 0;
	dragonfly_scene[i] = POND;
	if (is_setup) {
		dragonfly_x[i] = MIN_X + (rand() % (MAX_X - MIN_X));
	} else {
		dragonfly_x[i] = rand() < 128 ? 1 : 160;
	}
	dragonfly_y[i] = MIN_Y + (rand() % (MAX_Y - MIN_Y));
	dragonfly_anim_counter[i] = rand() % 12;
	dragonfly_anim_frame[i] = rand() % 2;
}

static void spawn_firefly(uint8_t i, uint8_t is_setup) {
	if (life_stage == DEAD) { return; }
	firefly_alive[i] = TRUE;
	firefly_respawn[i] = 0;
	firefly_scene[i] = POND;
	if (is_setup) {
		firefly_x[i] = MIN_X + (rand() % (MAX_X - MIN_X));
	} else {
		firefly_x[i] = rand() < 128 ? 1 : 160;
	}
	firefly_y[i] = MIN_Y + (rand() % (MAX_Y - MIN_Y));
	firefly_anim_counter[i] = rand() % 12;
	firefly_anim_frame[i] = rand() % 2;
}

static void spawn_butterfly(uint8_t i, uint8_t is_setup) {
	if (life_stage == DEAD) { return; }
	butterfly_alive[i] = TRUE;
	butterfly_respawn[i] = 0;
	butterfly_scene[i] = GARDEN;
	if (is_setup) {
		butterfly_x[i] = MIN_X + (rand() % (MAX_X - MIN_X));
	} else {
		butterfly_x[i] = rand() < 128 ? 1 : 160;
	}
	butterfly_y[i] = MIN_Y + (rand() % (MAX_Y - MIN_Y));
	butterfly_anim_counter[i] = rand() % 12;
	butterfly_anim_frame[i] = rand() % 2;
	butterfly_goal_x[i] = 0;
	butterfly_goal_y[i] = 0;
	butterfly_goal_plant[i] = 0;
	butterfly_run_away[i] = FALSE;
}

void respawn_bugs(void) BANKED {
	alive_count = 0;
	for (uint8_t i = 0; i < FLY_COUNT; i++) {
		if (fly_alive[i]) {
			alive_count += 1;
		} else if (fly_respawn[i] > 0 && alive_count < FLY_COUNT - 1) {
			fly_respawn[i] -= 1;
			break;
		}
	}

	alive_count = 0;
	for (uint8_t i = 0; i < DRAGONFLY_COUNT; i++) {
		if (dragonfly_alive[i]) {
			alive_count += 1;
		} else if (dragonfly_respawn[i] > 0 && alive_count < DRAGONFLY_COUNT - 1) {
			dragonfly_respawn[i] -= 1;
			break;
		}
	}

	alive_count = 0;
	for (uint8_t i = 0; i < FIREFLY_COUNT; i++) {
		if (firefly_alive[i]) {
			alive_count += 1;
		} else if (firefly_respawn[i] > 0 && alive_count < FIREFLY_COUNT - 1) {
			firefly_respawn[i] -= 1;
			break;
		}
	}

	alive_count = 0;
	for (uint8_t i = 0; i < BUTTERFLY_COUNT; i++) {
		if (butterfly_alive[i]) {
			alive_count += 1;
		} else if (butterfly_respawn[i] > 0 && alive_count < BUTTERFLY_COUNT - 1) {
			butterfly_respawn[i] -= 1;
			break;
		}
	}
}

static void draw_fly(uint8_t x, uint8_t y, uint8_t frame, uint8_t flip) {
	if (flip) {
		draw_banked_sprite_flip(BANK(fly), (uint8_t *) fly_metasprites, frame, FLY_VRAM, GREY_PALETTE, x + 8, y);
	} else {
		draw_banked_sprite(BANK(fly), (uint8_t *) fly_metasprites, frame, FLY_VRAM, GREY_PALETTE, x, y);
	}
}

static void draw_dragonfly(uint8_t x, uint8_t y, uint8_t frame, uint8_t flip) {
	if (flip) {
		draw_banked_sprite_flip(BANK(dragonfly), (uint8_t *) dragonfly_metasprites, frame, DRAGONFLY_VRAM, BROWN_PALETTE, x + 16, y + (frame * 3));
	} else {
		draw_banked_sprite(BANK(dragonfly), (uint8_t *) dragonfly_metasprites, frame, DRAGONFLY_VRAM, BROWN_PALETTE, x, y + (frame * 3));
	}
}

static void draw_firefly(uint8_t x, uint8_t y, uint8_t frame, uint8_t flip) {
	if (flip) {
		draw_banked_sprite_flip(BANK(firefly), (uint8_t *) firefly_metasprites, frame, FIREFLY_VRAM, GLOW_PALETTE, x + 8, y);
	} else {
		draw_banked_sprite(BANK(firefly), (uint8_t *) firefly_metasprites, frame, FIREFLY_VRAM, GLOW_PALETTE, x, y);
	}
}

static void draw_butterfly(uint8_t x, uint8_t y, uint8_t frame, uint8_t flip) {
	if (flip) {
		draw_banked_sprite_flip(BANK(butterfly), (uint8_t *) butterfly_metasprites, frame, BUTTERFLY_VRAM, PINK_PALETTE, x + 8, y);
	} else {
		draw_banked_sprite(BANK(butterfly), (uint8_t *) butterfly_metasprites, frame, BUTTERFLY_VRAM, PINK_PALETTE, x, y);
	}
}

static void update_fly(uint8_t i) {
	fly_anim_counter[i] += 1;
	if (fly_anim_counter[i] >= 12) {
		fly_anim_counter[i] = 0;
		fly_anim_frame[i] = !fly_anim_frame[i];

		if (current_scene == POND && !is_night) {
			hand_is_near = hand_x + 32 >= fly_x[i] && hand_x < fly_x[i] + 32 && hand_y + 32 >= fly_y[i] && hand_y < fly_y[i] + 32;

			chance_to_move_left = 128;
			if (hand_is_near && hand_x > fly_x[i]) {
				chance_to_move_left += 100;
			} else if (hand_is_near && hand_x < fly_x[i]) {
				chance_to_move_left -= 100;
			}

			if (rand() < chance_to_move_left && fly_x[i] > MIN_X) {
				fly_x[i] -= 1;
				fly_flip[i] = FALSE;
			} else if (fly_x[i] < MAX_X) {
				fly_x[i] += 1;
				fly_flip[i] = TRUE;
			}

			chance_to_move_up = 128;
			if (hand_is_near && hand_y > fly_y[i]) {
				chance_to_move_up += 100;
			} else if (hand_is_near && hand_y < fly_y[i]) {
				chance_to_move_up -= 100;
			}

			if (rand() < chance_to_move_up && fly_y[i] > MIN_Y) {
				fly_y[i] -= 1;
			} else if (fly_y[i] < MAX_Y) {
				fly_y[i] += 1;
			}

		} else if (fly_x[i] > 0 && fly_y[i] >= MIN_Y) {
			fly_x[i] -= 1;
			fly_y[i] -= 1;
			fly_flip[i] = FALSE;
		}

		if (fly_x[i] == 0 || fly_x[i] > 168 || fly_y[i] < MIN_Y || fly_y[i] > 144) {
			fly_alive[i] = FALSE;
			fly_respawn[i] = 2 * (game_speed + 1);
		}

	}
}

static void update_dragonfly(uint8_t i) {
	dragonfly_anim_counter[i] += 1;
	if (dragonfly_anim_counter[i] >= 6) {
		dragonfly_anim_counter[i] = 0;
		dragonfly_anim_frame[i] = !dragonfly_anim_frame[i];
	}
	if (dragonfly_anim_counter[i] % 2) {
		if (current_scene == POND && !is_night) {
			if ((dragonfly_x[i] == dragonfly_goal_x[i] || !dragonfly_goal_x[i]) &&
				(dragonfly_y[i] == dragonfly_goal_y[i] || !dragonfly_goal_y[i])) {
					if (rand() < 6) {
						dragonfly_goal_x[i] = MIN_X + (rand() % (MAX_X - MIN_X));
						dragonfly_goal_y[i] = MIN_Y + (rand() % (MAX_Y - MIN_Y));
					}
			} else {
				if (dragonfly_y[i] == dragonfly_goal_y[i] || rand() < 128) {
					if (dragonfly_x[i] < dragonfly_goal_x[i]) {
						dragonfly_x[i] += 1;
						dragonfly_flip_x[i] = TRUE;
					} else if (dragonfly_x[i] > dragonfly_goal_x[i]) {
						dragonfly_x[i] -= 1;
						dragonfly_flip_x[i] = FALSE;
					}
				} else {
					if (dragonfly_y[i] < dragonfly_goal_y[i]) {
						dragonfly_y[i] += 1;
					} else if (dragonfly_y[i] > dragonfly_goal_y[i]) {
						dragonfly_y[i] -= 1;
					}
				}
			}

		} else if (dragonfly_x[i] > 0 && dragonfly_y[i] >= MIN_Y) {
			dragonfly_x[i] -= 1;
			dragonfly_y[i] -= 1;
			dragonfly_flip_x[i] = FALSE;
		}

		if (dragonfly_x[i] == 0 || dragonfly_x[i] > 168 || dragonfly_y[i] < MIN_Y || dragonfly_y[i] > 144) {
			dragonfly_alive[i] = FALSE;
			dragonfly_respawn[i] = 4 * (game_speed + 1);
		}
	}
}

static void update_firefly(uint8_t i) {
	firefly_anim_counter[i] += 1;
	if (firefly_anim_counter[i] >= 8) {
		firefly_anim_counter[i] = 0;
		firefly_anim_frame[i] = !firefly_anim_frame[i];

		if (current_scene == POND && is_night) {
			if (rand() < 6) {
				firefly_flip[i] = !firefly_flip[i];
			}
			if (firefly_x[i] <= MIN_X) {
				firefly_flip[i] = TRUE;
			} else if (firefly_x[i] >= MAX_X) {
				firefly_flip[i] = FALSE;
			}
			if (firefly_flip[i]) {
				firefly_x[i] += 1;
			} else {
				firefly_x[i] -= 1;
			}

			if (rand() < 6) {
				firefly_flip_y[i] = !firefly_flip_y[i];
			}
			if (firefly_y[i] <= MIN_Y) {
				firefly_flip_y[i] = TRUE;
			} else if (firefly_y[i] >= MAX_Y) {
				firefly_flip_y[i] = FALSE;
			}
			if (firefly_flip_y[i]) {
				firefly_y[i] += 1;
			} else {
				firefly_y[i] -= 1;
			}

		} else if (firefly_x[i] > 0 && firefly_y[i] >= MIN_Y) {
			firefly_x[i] -= 1;
			firefly_y[i] -= 1;
			firefly_flip[i] = FALSE;
		}

		if (firefly_x[i] == 0 || firefly_x[i] > 168 || firefly_y[i] < MIN_Y || firefly_y[i] > 144) {
			firefly_alive[i] = FALSE;
			firefly_respawn[i] = 4 * (game_speed + 1);
		}

	}
}

static void update_butterfly(uint8_t i) {
	butterfly_anim_counter[i] += 1;
	uint8_t frame_rate = 12;
	if (butterfly_x[i] == butterfly_goal_x[i] && butterfly_y[i] == butterfly_goal_y[i]) {
		frame_rate = 48;
	} else if (butterfly_run_away[i]) {
		frame_rate = 8;
	}

	if (butterfly_anim_counter[i] >= frame_rate) {
		butterfly_anim_counter[i] = 0;
		butterfly_anim_frame[i] = !butterfly_anim_frame[i];

		if (current_scene == GARDEN && !is_night && !butterfly_run_away[i]) {
			if (butterfly_goal_x[i] && butterfly_goal_y[i]) {
				if (butterfly_y[i] == butterfly_goal_y[i] || rand() < 128) {
					if (butterfly_x[i] < butterfly_goal_x[i]) {
						butterfly_x[i] += 1;
						butterfly_flip_x[i] = TRUE;
					} else if (butterfly_x[i] > butterfly_goal_x[i]) {
						butterfly_x[i] -= 1;
						butterfly_flip_x[i] = FALSE;
					}
				} else {
					if (butterfly_y[i] < butterfly_goal_y[i]) {
						butterfly_y[i] += 1;
					} else if (butterfly_y[i] > butterfly_goal_y[i]) {
						butterfly_y[i] -= 1;
					}
				}
				plant_stage[butterfly_goal_plant[i] - 1] = 4;

			} else {
				if (rand() < 6) {
					butterfly_flip_x[i] = !butterfly_flip_x[i];
				}
				if (butterfly_x[i] <= MIN_X) {
					butterfly_flip_x[i] = TRUE;
				} else if (butterfly_x[i] >= MAX_X) {
					butterfly_flip_x[i] = FALSE;
				}
				if (butterfly_flip_x[i]) {
					butterfly_x[i] += 1;
				} else {
					butterfly_x[i] -= 1;
				}

				if (rand() < 6) {
					butterfly_flip_y[i] = !butterfly_flip_y[i];
				}
				if (butterfly_y[i] <= MIN_Y) {
					butterfly_flip_y[i] = TRUE;
				} else if (butterfly_y[i] >= frog_y - 8) {
					butterfly_flip_y[i] = FALSE;
				}
				if (butterfly_flip_y[i]) {
					butterfly_y[i] += 1;
				} else {
					butterfly_y[i] -= 1;
				}

				uint8_t j = rand() % 3;
				if (plant_stage[j] == 3) {
					plant_stage[j] = 4;
					butterfly_goal_plant[i] = j + 1;
					switch(j) {
						case 0:
							butterfly_goal_x[i] = PLANT_0_X*8 + 11;
							butterfly_goal_y[i] = PLANT_0_Y*8 + 12;
							break;
						case 1:
							butterfly_goal_x[i] = PLANT_1_X*8 + 11;
							butterfly_goal_y[i] = PLANT_1_Y*8 + 12;
							break;
						case 2:
							butterfly_goal_x[i] = PLANT_2_X*8 + 11;
							butterfly_goal_y[i] = PLANT_2_Y*8 + 12;
							break;
					}
				}
			}

		} else if (butterfly_x[i] > 0 && butterfly_y[i] >= MIN_Y) {
			butterfly_x[i] -= 1;
			butterfly_y[i] -= 1;
			butterfly_flip_x[i] = FALSE;
		}

		if (butterfly_x[i] == 0 || butterfly_x[i] > 168 || butterfly_y[i] < MIN_Y || butterfly_y[i] > 144) {
			butterfly_alive[i] = FALSE;
			butterfly_respawn[i] = 4 * (game_speed + 1);
		}

	}
}

void draw_bugs(void) BANKED {
	for (uint8_t i = 0; i < FLY_COUNT; i++) {
		if (fly_alive[i] &&
			fly_scene[i] == current_scene) {
				update_fly(i);
				draw_fly(fly_x[i], fly_y[i], fly_anim_frame[i], fly_flip[i]);
		} else if (i < FLY_COUNT - 1 &&
			!fly_alive[i] && !fly_respawn[i] &&
			current_scene == POND && !is_night) {
				spawn_fly(i, FALSE);
		}
	}

	for (uint8_t i = 0; i < DRAGONFLY_COUNT; i++) {
		if (dragonfly_alive[i] &&
			dragonfly_scene[i] == current_scene) {
				update_dragonfly(i);
				draw_dragonfly(dragonfly_x[i], dragonfly_y[i], dragonfly_anim_frame[i], dragonfly_flip_x[i]);
		} else if (i < DRAGONFLY_COUNT - 1 &&
			!dragonfly_alive[i] && !dragonfly_respawn[i] &&
			current_scene == POND && !is_night) {
				spawn_dragonfly(i, FALSE);
		}
	}

	for (uint8_t i = 0; i < FIREFLY_COUNT; i++) {
		if (firefly_alive[i] &&
			firefly_scene[i] == current_scene) {
				update_firefly(i);
				draw_firefly(firefly_x[i], firefly_y[i], firefly_anim_frame[i], firefly_flip[i]);
		} else if (i < FIREFLY_COUNT - 1 &&
			!firefly_alive[i] && !firefly_respawn[i] &&
			current_scene == POND && is_night) {
				spawn_firefly(i, FALSE);
		}
	}

	for (uint8_t i = 0; i < BUTTERFLY_COUNT; i++) {
		if (butterfly_alive[i] &&
			butterfly_scene[i] == current_scene) {
				update_butterfly(i);
				draw_butterfly(butterfly_x[i], butterfly_y[i], butterfly_anim_frame[i], butterfly_flip_x[i]);
		} else if (i < BUTTERFLY_COUNT - 1 &&
			!butterfly_alive[i] && !butterfly_respawn[i] &&
			current_scene == GARDEN && !is_night) {
				spawn_butterfly(i, FALSE);
		}
	}
}

uint8_t grab_bug(void) BANKED {
	for (uint8_t i = 0; i < FLY_COUNT; i++) {
		if (fly_alive[i] && fly_scene[i] == current_scene &&
			hand_x + 8 >= fly_x[i] && hand_x < fly_x[i] + 8 &&
			hand_y + 8 >= fly_y[i] && hand_y < fly_y[i] + 8) {
				fly_alive[i] = FALSE;
				fly_respawn[i] = 2 * (game_speed + 1);
				return BUG_FLY;
		}
	}

	for (uint8_t i = 0; i < DRAGONFLY_COUNT; i++) {
		if (dragonfly_alive[i] && dragonfly_scene[i] == current_scene &&
			hand_x + 16 >= dragonfly_x[i] && hand_x < dragonfly_x[i] + 16 &&
			hand_y + 8 >= dragonfly_y[i] && hand_y < dragonfly_y[i] + 8) {
				dragonfly_alive[i] = FALSE;
				dragonfly_respawn[i] = 4 * (game_speed + 1);
				return BUG_DRAGONFLY;
		}
	}

	for (uint8_t i = 0; i < FIREFLY_COUNT; i++) {
		if (firefly_alive[i] && firefly_scene[i] == current_scene &&
			hand_x + 8 >= firefly_x[i] && hand_x < firefly_x[i] + 8 &&
			hand_y + 8 >= firefly_y[i] && hand_y < firefly_y[i] + 8) {
				firefly_alive[i] = FALSE;
				firefly_respawn[i] = 4 * (game_speed + 1);
				return BUG_FIREFLY;
		}
	}

	for (uint8_t i = 0; i < BUTTERFLY_COUNT; i++) {
		if (butterfly_alive[i] && butterfly_scene[i] == current_scene &&
			hand_x + 8 >= butterfly_x[i] && hand_x < butterfly_x[i] + 8 &&
			hand_y + 8 >= butterfly_y[i] && hand_y < butterfly_y[i] + 8) {
				if (butterfly_x[i] == butterfly_goal_x[i] && butterfly_y[i] == butterfly_goal_y[i] && butterfly_goal_plant[i]) {
					plant_age[butterfly_goal_plant[i] - 1] = 0;
					plant_stage[butterfly_goal_plant[i] - 1] = 0;
					plant_is_watered[butterfly_goal_plant[i] - 1] = FALSE;
					butterfly_alive[i] = FALSE;
					butterfly_respawn[i] = 4 * (game_speed + 1);
					return BUG_BUTTERFLY;
				} else {
					butterfly_run_away[i] = TRUE;
				}
		}
	}

	return BUG_NONE;
}

void drop_bug(uint8_t bug_type) BANKED {
	switch(bug_type) {
		case BUG_FLY:
			for (uint8_t i = 0; i < FLY_COUNT; i++) {
				if (!fly_alive[i]) {
					fly_alive[i] = TRUE;
					fly_respawn[i] = 0;
					fly_scene[i] = current_scene;
					fly_x[i] = hand_x;
					fly_y[i] = hand_y;
					return;
				}
			}
			break;

		case BUG_DRAGONFLY:
			for (uint8_t i = 0; i < DRAGONFLY_COUNT; i++) {
				if (!dragonfly_alive[i]) {
					dragonfly_alive[i] = TRUE;
					dragonfly_respawn[i] = 0;
					dragonfly_scene[i] = current_scene;
					dragonfly_x[i] = hand_x;
					dragonfly_y[i] = hand_y;
					return;
				}
			}
			break;

		case BUG_FIREFLY:
			for (uint8_t i = 0; i < FIREFLY_COUNT; i++) {
				if (!firefly_alive[i]) {
					firefly_alive[i] = TRUE;
					firefly_respawn[i] = 0;
					firefly_scene[i] = current_scene;
					firefly_x[i] = hand_x;
					firefly_y[i] = hand_y;
					return;
				}
			}
			break;

		case BUG_BUTTERFLY:
			for (uint8_t i = 0; i < BUTTERFLY_COUNT; i++) {
				if (!butterfly_alive[i]) {
					butterfly_alive[i] = TRUE;
					butterfly_respawn[i] = 0;
					butterfly_scene[i] = current_scene;
					butterfly_x[i] = hand_x;
					butterfly_y[i] = hand_y;
					butterfly_goal_x[i] = 0;
					butterfly_goal_y[i] = 0;
					butterfly_goal_plant[i] = 0;
					return;
				}
			}
			break;
	}
}

void setup_bugs(void) BANKED {
	for (uint8_t i = 0; i < FLY_COUNT; i++) {
		if (life_stage == DEAD) {
			fly_alive[i] = FALSE;
		} else if (fly_alive[i] &&
			(fly_scene[i] != current_scene ||
			!(current_scene == POND && !is_night))) {
				fly_alive[i] = FALSE;
		} else if (i < FLY_COUNT - 1 &&
			current_scene == POND && !is_night &&
			!fly_alive[i] && !fly_respawn[i] &&
			alive_count < FLY_COUNT - 1) {
				spawn_fly(i, TRUE);
		}
	}

	for (uint8_t i = 0; i < DRAGONFLY_COUNT; i++) {
		if (life_stage == DEAD) {
			dragonfly_alive[i] = FALSE;
		} else if (dragonfly_alive[i] &&
			(dragonfly_scene[i] != current_scene ||
			!(current_scene == POND && !is_night))) {
				dragonfly_alive[i] = FALSE;
		} else if (i < DRAGONFLY_COUNT - 1 &&
			current_scene == POND && !is_night &&
			!dragonfly_alive[i] && !dragonfly_respawn[i] &&
			alive_count < DRAGONFLY_COUNT - 1) {
				spawn_dragonfly(i, TRUE);
		}
	}

	for (uint8_t i = 0; i < FIREFLY_COUNT; i++) {
		if (life_stage == DEAD) {
			firefly_alive[i] = FALSE;
		} else if (firefly_alive[i] &&
			(firefly_scene[i] != current_scene ||
			!(current_scene == POND && is_night))) {
				firefly_alive[i] = FALSE;
		} else if (i < FIREFLY_COUNT - 1 &&
			current_scene == POND && is_night &&
			!firefly_alive[i] && !firefly_respawn[i] &&
			alive_count < FIREFLY_COUNT - 1) {
				spawn_firefly(i, TRUE);
		}
	}

	for (uint8_t i = 0; i < BUTTERFLY_COUNT; i++) {
		if (life_stage == DEAD) {
			butterfly_alive[i] = FALSE;
		} else if (butterfly_alive[i] &&
			(butterfly_scene[i] != current_scene ||
			!(current_scene == GARDEN && !is_night))) {
				butterfly_alive[i] = FALSE;
		} else if (i < BUTTERFLY_COUNT - 1 &&
			current_scene == GARDEN && !is_night &&
			!butterfly_alive[i] && !butterfly_respawn[i] &&
			alive_count < BUTTERFLY_COUNT - 1) {
				spawn_butterfly(i, TRUE);
		}
	}
}

void setup_bugs_data(void) BANKED {
	set_banked_sprite_data(BANK(fly), FLY_VRAM, fly_TILE_COUNT, fly_tiles);
	set_banked_sprite_data(BANK(dragonfly), DRAGONFLY_VRAM, dragonfly_TILE_COUNT, dragonfly_tiles);
	set_banked_sprite_data(BANK(firefly), FIREFLY_VRAM, firefly_TILE_COUNT, firefly_tiles);
	set_banked_sprite_data(BANK(butterfly), BUTTERFLY_VRAM, butterfly_TILE_COUNT, butterfly_tiles);
}

void reset_bugs(void) BANKED {
	for (uint8_t i = 0; i < FLY_COUNT; i++) {
		fly_alive[i] = FALSE;
		fly_respawn[i] = 0;
	}

	for (uint8_t i = 0; i < DRAGONFLY_COUNT; i++) {
		dragonfly_alive[i] = FALSE;
		dragonfly_respawn[i] = 0;
	}

	for (uint8_t i = 0; i < FIREFLY_COUNT; i++) {
		firefly_alive[i] = FALSE;
		firefly_respawn[i] = 0;
	}

	for (uint8_t i = 0; i < BUTTERFLY_COUNT; i++) {
		butterfly_alive[i] = FALSE;
		butterfly_respawn[i] = 0;
	}
}
