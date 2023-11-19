#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <rand.h>

#include "shared_variables.h"

#include "sprites/misc_8x8/fly.h"
#include "sprites/misc_8x8/firefly.h"
#include "sprites/misc_8x8/butterfly.h"
#include "sprites/misc_16x8/dragonfly.h"

BANKREF(bugs_bank)

#define BUG_NONE 0
#define BUG_FLY 1
#define BUG_DRAGONFLY 2
#define BUG_FIREFLY 3
#define BUG_BUTTERFLY 4

#define FLY_VRAM 0xc8
#define DRAGONFLY_VRAM 0xca
#define FIREFLY_VRAM 0xce
#define BUTTERFLY_VRAM 0xbe

#define MIN_X 8
#define MAX_X 160
#define MIN_Y 48
#define MAX_Y 120

#define FLY_COUNT 5
uint8_t fly_alive[FLY_COUNT];
uint8_t fly_scene[FLY_COUNT];
uint8_t fly_x[FLY_COUNT];
uint8_t fly_y[FLY_COUNT];
uint8_t fly_flip[FLY_COUNT];
uint8_t fly_anim_counter[FLY_COUNT];
uint8_t fly_anim_frame[FLY_COUNT];
uint8_t fly_respawn[FLY_COUNT];

#define DRAGONFLY_COUNT 1
uint8_t dragonfly_alive[DRAGONFLY_COUNT];
uint8_t dragonfly_scene[FLY_COUNT];
uint8_t dragonfly_x[DRAGONFLY_COUNT];
uint8_t dragonfly_y[DRAGONFLY_COUNT];
uint8_t dragonfly_goal_x[DRAGONFLY_COUNT];
uint8_t dragonfly_goal_y[DRAGONFLY_COUNT];
uint8_t dragonfly_flip_x[DRAGONFLY_COUNT];
uint8_t dragonfly_anim_counter[DRAGONFLY_COUNT];
uint8_t dragonfly_anim_frame[DRAGONFLY_COUNT];
uint8_t dragonfly_respawn[DRAGONFLY_COUNT];

#define FIREFLY_COUNT 3
uint8_t firefly_alive[FIREFLY_COUNT];
uint8_t firefly_scene[FIREFLY_COUNT];
uint8_t firefly_x[FIREFLY_COUNT];
uint8_t firefly_y[FIREFLY_COUNT];
uint8_t firefly_flip[FIREFLY_COUNT];
uint8_t firefly_flip_y[FIREFLY_COUNT];
uint8_t firefly_anim_counter[FIREFLY_COUNT];
uint8_t firefly_anim_frame[FIREFLY_COUNT];
uint8_t firefly_respawn[FIREFLY_COUNT];

#define BUTTERFLY_COUNT 3
uint8_t butterfly_alive[BUTTERFLY_COUNT];
uint8_t butterfly_scene[BUTTERFLY_COUNT];
uint8_t butterfly_x[BUTTERFLY_COUNT];
uint8_t butterfly_y[BUTTERFLY_COUNT];
uint8_t butterfly_goal_x[BUTTERFLY_COUNT];
uint8_t butterfly_goal_y[BUTTERFLY_COUNT];
uint8_t butterfly_goal_plant[BUTTERFLY_COUNT];
uint8_t butterfly_flip_x[BUTTERFLY_COUNT];
uint8_t butterfly_flip_y[BUTTERFLY_COUNT];
uint8_t butterfly_anim_counter[BUTTERFLY_COUNT];
uint8_t butterfly_anim_frame[BUTTERFLY_COUNT];
uint8_t butterfly_respawn[BUTTERFLY_COUNT];

uint8_t hand_is_near;
uint8_t chance_to_move_left;
uint8_t chance_to_move_up;

void spawn_fly(uint8_t i, uint8_t is_setup) {
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

void spawn_dragonfly(uint8_t i, uint8_t is_setup) {
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

void spawn_firefly(uint8_t i, uint8_t is_setup) {
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

void spawn_butterfly(uint8_t i, uint8_t is_setup) {
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
}

void respawn_bugs(void) {
	for (uint8_t i = 0; i < FLY_COUNT; i++) {
		if (!fly_alive[i] && fly_respawn[i] > 0) {
			fly_respawn[i] -= 1;
			break;
		}
	}
	for (uint8_t i = 0; i < DRAGONFLY_COUNT; i++) {
		if (!dragonfly_alive[i] && dragonfly_respawn[i] > 0) {
			dragonfly_respawn[i] -= 1;
			break;
		}
	}
	for (uint8_t i = 0; i < FIREFLY_COUNT; i++) {
		if (!firefly_alive[i] && firefly_respawn[i] > 0) {
			firefly_respawn[i] -= 1;
			break;
		}
	}
	for (uint8_t i = 0; i < BUTTERFLY_COUNT; i++) {
		if (!butterfly_alive[i] && butterfly_respawn[i] > 0) {
			butterfly_respawn[i] -= 1;
			break;
		}
	}
}

void draw_fly(uint8_t *last_sprite, uint8_t x, uint8_t y, uint8_t frame, uint8_t flip) NONBANKED {
	uint8_t prev_bank = _current_bank;
	SWITCH_ROM(BANK(fly));
	if (flip) {
		*last_sprite += move_metasprite_flipx(
			fly_metasprites[frame],
			FLY_VRAM, 0, *last_sprite, x + 8, y);
	} else {
		*last_sprite += move_metasprite_ex(
			fly_metasprites[frame],
			FLY_VRAM, 0, *last_sprite, x, y);
	}
	SWITCH_ROM(prev_bank);
}

void draw_dragonfly(uint8_t *last_sprite, uint8_t x, uint8_t y, uint8_t frame, uint8_t flip) NONBANKED {
	uint8_t prev_bank = _current_bank;
	SWITCH_ROM(BANK(dragonfly));
	if (flip) {
		*last_sprite += move_metasprite_flipx(
			dragonfly_metasprites[frame],
			DRAGONFLY_VRAM, 0, *last_sprite, x + 16, y + (frame * 3));
	} else {
		*last_sprite += move_metasprite_ex(
			dragonfly_metasprites[frame],
			DRAGONFLY_VRAM, 0, *last_sprite, x, y + (frame * 3));
	}
	SWITCH_ROM(prev_bank);
}

void draw_firefly(uint8_t *last_sprite, uint8_t x, uint8_t y, uint8_t frame, uint8_t flip) NONBANKED {
	uint8_t prev_bank = _current_bank;
	SWITCH_ROM(BANK(firefly));
	if (flip) {
		*last_sprite += move_metasprite_flipx(
			firefly_metasprites[frame],
			FIREFLY_VRAM, 0, *last_sprite, x + 8, y);
	} else {
		*last_sprite += move_metasprite_ex(
			firefly_metasprites[frame],
			FIREFLY_VRAM, 0, *last_sprite, x, y);
	}
	SWITCH_ROM(prev_bank);
}

void draw_butterfly(uint8_t *last_sprite, uint8_t x, uint8_t y, uint8_t frame, uint8_t flip) NONBANKED {
	uint8_t prev_bank = _current_bank;
	SWITCH_ROM(BANK(butterfly));
	if (flip) {
		*last_sprite += move_metasprite_flipx(
			butterfly_metasprites[frame],
			BUTTERFLY_VRAM, 0, *last_sprite, x + 8, y);
	} else {
		*last_sprite += move_metasprite_ex(
			butterfly_metasprites[frame],
			BUTTERFLY_VRAM, 0, *last_sprite, x, y);
	}
	SWITCH_ROM(prev_bank);
}

void update_fly(uint8_t i) {
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

void update_dragonfly(uint8_t i) {
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

void update_firefly(uint8_t i) {
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

void update_butterfly(uint8_t i) {
	butterfly_anim_counter[i] += 1;
	uint8_t frame_rate = (butterfly_x[i] == butterfly_goal_x[i] && butterfly_y[i] == butterfly_goal_y[i]) ? 48 : 12;
	if (butterfly_anim_counter[i] >= frame_rate) {
		butterfly_anim_counter[i] = 0;
		butterfly_anim_frame[i] = !butterfly_anim_frame[i];

		if (current_scene == GARDEN && !is_night) {
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

void draw_bugs(uint8_t *last_sprite) {
	for (uint8_t i = 0; i < FLY_COUNT; i++) {
		if (fly_alive[i] &&
			fly_scene[i] == current_scene) {
				update_fly(i);
				draw_fly(last_sprite, fly_x[i], fly_y[i], fly_anim_frame[i], fly_flip[i]);
		} else if (!fly_alive[i] && !fly_respawn[i] &&
			current_scene == POND && !is_night) {
				spawn_fly(i, FALSE);
		}
	}

	for (uint8_t i = 0; i < DRAGONFLY_COUNT; i++) {
		if (dragonfly_alive[i] &&
			dragonfly_scene[i] == current_scene) {
				update_dragonfly(i);
				draw_dragonfly(last_sprite, dragonfly_x[i], dragonfly_y[i], dragonfly_anim_frame[i], dragonfly_flip_x[i]);
		} else if (!dragonfly_alive[i] && !dragonfly_respawn[i] &&
			current_scene == POND && !is_night) {
				spawn_dragonfly(i, FALSE);
		}
	}

	for (uint8_t i = 0; i < FIREFLY_COUNT; i++) {
		if (firefly_alive[i] &&
			firefly_scene[i] == current_scene) {
				update_firefly(i);
				draw_firefly(last_sprite, firefly_x[i], firefly_y[i], firefly_anim_frame[i], firefly_flip[i]);
		} else if (!firefly_alive[i] && !firefly_respawn[i] &&
			current_scene == POND && is_night) {
				spawn_firefly(i, FALSE);
		}
	}

	for (uint8_t i = 0; i < BUTTERFLY_COUNT; i++) {
		if (butterfly_alive[i] &&
			butterfly_scene[i] == current_scene) {
				update_butterfly(i);
				draw_butterfly(last_sprite, butterfly_x[i], butterfly_y[i], butterfly_anim_frame[i], butterfly_flip_x[i]);
		} else if (!butterfly_alive[i] && !butterfly_respawn[i] &&
			current_scene == GARDEN && !is_night) {
				spawn_butterfly(i, FALSE);
		}
	}
}

uint8_t grab_bug(void) {
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
			butterfly_x[i] == butterfly_goal_x[i] && butterfly_y[i] == butterfly_goal_y[i] && butterfly_goal_plant[i] &&
			hand_x + 8 >= butterfly_x[i] && hand_x < butterfly_x[i] + 8 &&
			hand_y + 8 >= butterfly_y[i] && hand_y < butterfly_y[i] + 8) {
				plant_age[butterfly_goal_plant[i] - 1] = 0;
				plant_stage[butterfly_goal_plant[i] - 1] = 0;
				plant_is_watered[butterfly_goal_plant[i] - 1] = FALSE;
				butterfly_alive[i] = FALSE;
				butterfly_respawn[i] = 4 * (game_speed + 1);
				return BUG_BUTTERFLY;
		}
	}

	return BUG_NONE;
}

void drop_bug(uint8_t bug_type) {
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

void setup_bugs(void) {
	for (uint8_t i = 0; i < FLY_COUNT; i++) {
		if (fly_alive[i] &&
			(fly_scene[i] != current_scene ||
			!(current_scene == POND && !is_night))) {
				fly_alive[i] = FALSE;
		} else if (current_scene == POND && !is_night &&
			!fly_alive[i] && !fly_respawn[i]) {
				spawn_fly(i, TRUE);
		}
	}

	for (uint8_t i = 0; i < DRAGONFLY_COUNT; i++) {
		if (dragonfly_alive[i] &&
			(dragonfly_scene[i] != current_scene ||
			!(current_scene == POND && !is_night))) {
				dragonfly_alive[i] = FALSE;
		} else if (current_scene == POND && !is_night &&
			!dragonfly_alive[i] && !dragonfly_respawn[i]) {
				spawn_dragonfly(i, TRUE);
		}
	}

	for (uint8_t i = 0; i < FIREFLY_COUNT; i++) {
		if (firefly_alive[i] &&
			(firefly_scene[i] != current_scene ||
			!(current_scene == POND && is_night))) {
				firefly_alive[i] = FALSE;
		} else if (current_scene == POND && is_night &&
			!firefly_alive[i] && !firefly_respawn[i]) {
				spawn_firefly(i, TRUE);
		}
	}

	for (uint8_t i = 0; i < BUTTERFLY_COUNT; i++) {
		if (butterfly_alive[i] &&
			(butterfly_scene[i] != current_scene ||
			!(current_scene == GARDEN && !is_night))) {
				butterfly_alive[i] = FALSE;
		} else if (current_scene == GARDEN && !is_night &&
			!butterfly_alive[i] && !butterfly_respawn[i]) {
				spawn_butterfly(i, TRUE);
		}
	}
}

void setup_bugs_data(void) NONBANKED {
	SWITCH_ROM(BANK(fly));
	set_sprite_data(FLY_VRAM, fly_TILE_COUNT, fly_tiles);

	SWITCH_ROM(BANK(dragonfly));
	set_sprite_data(DRAGONFLY_VRAM, dragonfly_TILE_COUNT, dragonfly_tiles);

	SWITCH_ROM(BANK(firefly));
	set_sprite_data(FIREFLY_VRAM, firefly_TILE_COUNT, firefly_tiles);

	SWITCH_ROM(BANK(butterfly));
	set_sprite_data(BUTTERFLY_VRAM, butterfly_TILE_COUNT, butterfly_tiles);
}
