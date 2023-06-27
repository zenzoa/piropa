#pragma bank 255

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <rand.h>

#include <gbdk/emu_debug.h>

#include "save.h"
#include "clock.h"

BANKREF(frog_code)

#define FALSE 0
#define TRUE 1

#define EVO_EGG 0
#define EVO_BABY 1
#define EVO_CHILD 2
#define EVO_TEEN 3
#define EVO_TEEN_TAIL 4
#define EVO_TEEN_APPLE 5
#define EVO_ADULT 6
#define EVO_AXO 7
#define EVO_APPLE 8
#define EVO_MUSH 9
#define EVO_DINO 10

#define FROG_STAND 0
#define FROG_WALK_LEFT 1
#define FROG_WALK_RIGHT 2
#define FROG_HAPPY 3
#define FROG_SAD 4
#define FROG_EAT 5
#define FROG_TICKLED 6
#define FROG_SLEEP 7
#define FROG_WASH 8
#define FROG_EVOLVING 9

#define HAPPY_TIME_TO_DECREASE 1
#define FULL_TIME_TO_DECREASE 2
#define CLEAN_TIME_TO_DECREASE 3
#define ENERGY_TIME_TO_DECREASE 4

#define ENERGY_TIME_TO_INCREASE 1

uint8_t frog_x = 88;
uint8_t frog_y = 84;
uint8_t frog_goal_x = 88;
uint8_t frog_goal_y = 84;

uint8_t frog_evo = EVO_EGG;
uint8_t frog_state = FROG_STAND;

uint8_t frog_evolving = FALSE;

uint8_t frog_move_speed = 8;
uint8_t frog_move_counter = 0;

uint8_t frog_anim_speed = 32;
uint8_t frog_anim_counter = 0;
uint8_t frog_anim_frame = 0;
uint8_t frog_anim_loops = 0;
uint8_t show_emote = FALSE;

uint8_t frog_sec = 0;
uint8_t frog_min = 0;
uint8_t frog_hour = 0;

uint8_t tickles = 0;

uint8_t washes = 0;

uint8_t frog_eating_fruit = 0;
uint8_t frog_eating_fly = 0;
uint8_t fruit_eaten = FALSE;
uint8_t fly_eaten = FALSE;

uint8_t happy = 6;
uint8_t full = 6;
uint8_t clean = 6;
uint8_t energy = 6;

uint8_t happy_timer = 0;
uint8_t full_timer = 0;
uint8_t clean_timer = 0;
uint8_t energy_timer = 0;

void set_state(uint8_t new_state) {
	frog_state = new_state;
	frog_anim_counter = 0;
	frog_anim_frame = 0;
	frog_anim_loops = 0;
	show_emote = FALSE;
}

void frog_rejoice_small() {
	set_state(FROG_HAPPY);
	frog_anim_loops = 1;
}

void frog_rejoice_big() {
	set_state(FROG_HAPPY);
	frog_anim_loops = 3;
	show_emote = TRUE;
}

void frog_refuse() {
	set_state(FROG_SAD);
	frog_anim_loops = 3;
}

void frog_tickle(uint8_t frame) {
	// TODO: don't do this if shy, return something to let hand know what's up, shake head to refuse
	if (frog_state != FROG_TICKLED) {
		set_state(FROG_TICKLED);
	}
	frog_anim_frame = frame;
	frog_anim_counter = 0;
	tickles += 1;
}

void frog_sleep() {
	if (energy < 12) {
		set_state(FROG_SLEEP);
		show_emote = TRUE;
	} else {
		frog_refuse();
	}
}

void frog_wake() {
	if (energy < 12) {
		frog_rejoice_small();
	} else {
		frog_rejoice_big();
	}
}

void frog_start_wash() {
	washes = 0;
	if (clean < 12) {
		set_state(FROG_WASH);
	} else {
		frog_refuse();
	}
}

void frog_stop_wash() {
	if (frog_anim_loops == 0) {
		frog_anim_counter = 0;
		frog_anim_frame = 0;
		frog_anim_loops = 1;
	}
}

uint8_t frog_eat_fruit() {
	if (full < 12) {
		frog_eating_fruit = 1;
		set_state(FROG_HAPPY);
		frog_anim_frame = 1;
		if (!fruit_eaten) {
			fruit_eaten = TRUE;
			save_item(DATA_FRUIT_EATEN, TRUE);
		}
		return TRUE;
	} else {
		frog_refuse();
		return FALSE;
	}
}

void frog_eat_fly() {
	if (full < 12) {
		frog_eating_fly = 1;
		set_state(FROG_HAPPY);
		frog_anim_frame = 1;
		if (!fly_eaten) {
			fly_eaten = TRUE;
			save_item(DATA_FLY_EATEN, TRUE);
		}
	} else {
		frog_refuse();
	}
}

void frog_change_rooms() {
	if (frog_state != FROG_SLEEP) {
		set_state(FROG_STAND);
		frog_anim_loops = 0;
	}
}

void frog_evolve() {
	uint8_t old_evo = frog_evo;

	switch (frog_evo) {
		case EVO_EGG:
			if (frog_min >= 1 || frog_hour >= 1) {
				frog_evo = EVO_BABY;
			}
			break;

		case EVO_BABY:
			if (frog_min >= 1 || frog_hour >= 1) {
				frog_evo = EVO_CHILD;
			}
			break;

		case EVO_CHILD:
			if (frog_min >= 1 || frog_hour >= 1) {
				if (fruit_eaten && !fly_eaten) {
					frog_evo = EVO_TEEN_APPLE;
				} else if (fly_eaten && !fruit_eaten) {
					frog_evo = EVO_TEEN_TAIL;
				} else {
					frog_evo = EVO_TEEN;
				}
			}
			break;

		case EVO_TEEN_APPLE:
			if (frog_min >= 1 || frog_hour >= 1) {
				frog_evo = EVO_APPLE;
			}
			break;

		case EVO_TEEN_TAIL:
			if (frog_min >= 1 || frog_hour >= 1) {
				frog_evo = EVO_AXO;
			}
			break;

		case EVO_TEEN:
			if (frog_min >= 1 || frog_hour >= 1) {
				frog_evo = EVO_ADULT;
			}
			break;
	}

	if (old_evo != frog_evo) {
		save_item(DATA_FROG_EVO, frog_evo);
		frog_sec = 0;
		frog_min = 0;
		save_item(DATA_FROG_MIN, frog_min);
		frog_hour = 0;
		save_item(DATA_FROG_HOUR, frog_hour);
		frog_state = FROG_EVOLVING;
	}
}

void move_frog(uint8_t x, uint8_t y) {
	if (frog_state != FROG_SLEEP) {
		frog_x = x;
		frog_y = y;
	}
}

void set_goal(uint8_t x, uint8_t y) {
	if (frog_state != FROG_SLEEP) {
		frog_goal_x = x;
		frog_goal_y = y;
	}
}

void set_random_goal() {
	uint8_t x = 24 + rand() / 2; // 24 to 148
	uint8_t y = 56 + rand() / 5; // 56 to 104
	set_goal(x, y);
}

void frog_emote() {
	if (full <= 4 || clean <= 4 || energy <= 4 || happy <= 4) {
		set_state(FROG_SAD);
	} else if (happy >= 12) {
		set_state(FROG_HAPPY);
	} else {
		set_state(FROG_STAND);
	}
	frog_anim_loops = 3;
	show_emote = TRUE;
}

void animate_frog(uint8_t wandering) {
	if (frog_evo != EVO_EGG && frog_state <= FROG_WALK_RIGHT && (frog_x != frog_goal_x || frog_y != frog_goal_y)) {
		frog_move_counter += 1;
		if (frog_move_counter > frog_move_speed) {
			frog_move_counter = 0;
			if (frog_goal_x > frog_x) {
				if (frog_state != FROG_WALK_RIGHT) {
					set_state(FROG_WALK_RIGHT);
				}
				if (frog_goal_x >= frog_x + 2) {
					frog_x += 2;
				} else {
					frog_x += (frog_goal_x - frog_x);
				}
			} else if (frog_goal_x < frog_x) {
				if (frog_state != FROG_WALK_LEFT) {
					set_state(FROG_WALK_LEFT);
				}
				if (frog_goal_x <= frog_x - 2) {
					frog_x -= 2;
				} else {
					frog_x -= (frog_x - frog_goal_x);
				}
			}
			if (frog_goal_y > frog_y) {
				frog_y += 1;
			} else if (frog_goal_y < frog_y) {
				frog_y -= 1;
			}
		}
		if (frog_x == frog_goal_x && frog_y == frog_goal_y) {
			frog_emote();
		}
	}

	frog_anim_counter += 1;
	if (frog_anim_counter > frog_anim_speed) {
		frog_anim_counter = 0;
		frog_anim_frame += 1;
		if (frog_anim_frame >= 2) {
			frog_anim_frame = 0;

			if (frog_anim_loops > 0) {
				frog_anim_loops -= 1;
				if (frog_anim_loops == 0) {
					if (frog_state == FROG_EVOLVING) {
						frog_rejoice_big();

					} else if (frog_state == FROG_WASH && washes >= 4) {
						if (clean < 12 - 6) {
							clean += 6;
							frog_rejoice_small();
						} else {
							clean = 12;
							frog_rejoice_big();
						}

					} else if (frog_state != FROG_STAND) {
						set_state(FROG_STAND);
					}
				}
			}
		}

		if (frog_state == FROG_TICKLED && frog_anim_frame == 0) {
			if (tickles >= 4) {
				if (happy < 12 - 3) {
					happy += 3;
					frog_rejoice_small();
				} else {
					happy = 12;
					frog_rejoice_big();
				}
			} else {
				set_state(FROG_STAND);
			}
			tickles = 0;
		}

		if (frog_state == FROG_WASH) {
			washes += 1;
		}

		if (frog_eating_fruit) {
			frog_eating_fruit += 1;
		}
		if (frog_eating_fruit == 2 || frog_eating_fruit == 5 || frog_eating_fruit == 8) {
			set_state(FROG_EAT);
		} else if (frog_eating_fruit == 4 || frog_eating_fruit == 7) {
			set_state(FROG_HAPPY);
			frog_anim_frame = 1;
		} else if (frog_eating_fruit >= 10) {
			frog_eating_fruit = 0;
			if (full < 12 - 6) {
				full += 6;
				frog_rejoice_small();
			} else {
				full = 12;
				frog_rejoice_big();
			}
		}

		if (frog_eating_fly) {
			frog_eating_fly += 1;
		}
		if (frog_eating_fly == 2) {
			set_state(FROG_EAT);
		} else if (frog_eating_fly >= 8) {
			frog_eating_fly = 0;
			if (full < 12 - 2) {
				full += 2;
				frog_rejoice_small();
			} else {
				full = 12;
				frog_rejoice_big();
			}
		}

		if (frog_evo != EVO_EGG && wandering && !frog_anim_loops && frog_state == FROG_STAND && frog_x == frog_goal_x && frog_y == frog_goal_y) {
			if (rand() < 25) {
				set_random_goal();
			} else {
				frog_anim_loops = 3;
			}
		}
	}
}

void update_frog(uint8_t time_speed) {
	frog_sec += 1;
	if (frog_sec >= 60) {
		frog_sec = 0;
		frog_min += 1;
		save_item(DATA_FROG_MIN, frog_min);
		EMU_MESSAGE("RESET CLOCK");
		reset_clock();
		if (frog_min >= 60) {
			frog_min = 0;
			frog_hour += 1;
			save_item(DATA_FROG_HOUR, frog_hour);
		}

		if (frog_state <= FROG_WALK_RIGHT) {
			frog_evolve();
		}

		if (frog_evo == EVO_EGG) {
			return;
		}

		happy_timer += 1;
		save_item(DATA_HAPPY_TIMER, happy_timer);
		if (happy_timer >= time_speed * HAPPY_TIME_TO_DECREASE) {
			happy_timer = 0;
			if (happy > 0) {
				happy -= 1;
				save_item(DATA_HAPPY, happy);
			}
		}

		full_timer += 1;
		save_item(DATA_FULL_TIMER, full_timer);
		if (full_timer >= time_speed * FULL_TIME_TO_DECREASE) {
			full_timer = 0;
			if (full > 0) {
				full -= 1;
				save_item(DATA_FULL, full);
			}
		}

		clean_timer += 1;
		save_item(DATA_CLEAN_TIMER, clean_timer);
		if (clean_timer >= time_speed * CLEAN_TIME_TO_DECREASE) {
			clean_timer = 0;
			if (clean > 0) {
				clean -= 1;
				save_item(DATA_CLEAN, clean);
			}
		}

		energy_timer += 1;
		save_item(DATA_ENERGY_TIMER, energy_timer);
		if (frog_state == FROG_SLEEP && energy_timer >= time_speed * ENERGY_TIME_TO_INCREASE) {
			energy_timer = 0;
			if (energy < 12) {
				energy += 1;
				save_item(DATA_ENERGY, energy);
			}
		} else if (frog_state != FROG_SLEEP && energy_timer >= time_speed * ENERGY_TIME_TO_DECREASE) {
			energy_timer = 0;
			if (energy > 0) {
				energy -= 1;
				save_item(DATA_ENERGY, energy);
			}
		}
	}
}

void update_frog_after_break(uint8_t time_speed, uint16_t *days, uint8_t *hours, uint8_t *minutes, uint8_t *seconds) {
	EMU_MESSAGE("UPDATE FROG");
	EMU_printf("old age: %d : %d : %d", frog_hour, frog_min, frog_sec);

	uint16_t missed_minutes = *minutes + (*hours * 60);
	uint16_t total_hours = frog_hour + *hours;

	frog_sec = *seconds;

	frog_min += *minutes;
	if (frog_min >= 60) {
		frog_min -= 60;
		total_hours += 1;
	}

	if (*days < 10) {
		missed_minutes += *days * 1440;
		total_hours += *days * 24;
	} else {
		missed_minutes += 1440;
		total_hours += 240;
	}

	if (total_hours < 255) {
		frog_hour = (uint8_t) total_hours;
	} else {
		frog_hour = 255;
	}

	EMU_printf("new age: %d : %d : %d", frog_hour, frog_min, frog_sec);

	EMU_printf("missed minutes: %d", missed_minutes);

	uint8_t full_rate = time_speed * FULL_TIME_TO_DECREASE;
	uint8_t full_decrease = missed_minutes / full_rate;
	full_timer = missed_minutes % full_rate;
	if (full_timer >= full_rate) {
		full_timer -= full_rate;
		full_decrease += 1;
	}
	if (full_decrease < full) {
		full -= full_decrease;
	} else {
		full = 0;
	}
	EMU_printf("full decrease: %d", full_decrease);
	EMU_printf("full: %d", full);
	EMU_printf("full timer: %d", full_timer);

	uint8_t clean_rate = time_speed * CLEAN_TIME_TO_DECREASE;
	uint8_t clean_decrease = missed_minutes / clean_rate;
	clean_timer = missed_minutes % clean_rate;
	if (clean_timer >= clean_rate) {
		clean_timer -= clean_rate;
		clean_decrease += 1;
	}
	if (clean_decrease < clean) {
		clean -= clean_decrease;
	} else {
		clean = 0;
	}
	EMU_printf("clean decrease: %d", clean_decrease);
	EMU_printf("clean: %d", clean);
	EMU_printf("clean timer: %d", clean_timer);

	uint8_t energy_rate = time_speed * ENERGY_TIME_TO_DECREASE;
	uint8_t energy_decrease = missed_minutes / energy_rate;
	energy_timer = missed_minutes % energy_rate;
	if (energy_timer >= energy_rate) {
		energy_timer -= energy_rate;
		energy_decrease += 1;
	}
	if (energy_decrease < energy) {
		energy -= energy_decrease;
	} else {
		energy = 0;
	}
	EMU_printf("energy decrease: %d", energy_decrease);
	EMU_printf("energy: %d", energy);
	EMU_printf("energy timer: %d", energy_timer);

	uint8_t happy_rate = time_speed * HAPPY_TIME_TO_DECREASE;
	uint8_t happy_decrease = missed_minutes / happy_rate;
	happy_timer = missed_minutes % happy_rate;
	if (happy_timer >= happy_rate) {
		happy_timer -= happy_rate;
		happy_decrease += 1;
	}
	if (happy_decrease < happy) {
		happy -= happy_decrease;
	} else {
		happy = 0;
	}
	EMU_printf("happy decrease: %d", happy_decrease);
	EMU_printf("happy: %d", happy);
	EMU_printf("happy timer: %d", happy_timer);

	// if too long, frog is dead
	// otherwise calc stat decreases
	// figure out if it would have evolved, how many times, and which ones

}

void load_frog_data() {
	frog_evo = load_item(DATA_FROG_EVO, frog_evo);
	frog_min = load_item(DATA_FROG_MIN, frog_min);
	frog_hour = load_item(DATA_FROG_HOUR, frog_hour);

	happy = load_item(DATA_HAPPY, happy);
	full = load_item(DATA_FULL, full);
	clean = load_item(DATA_CLEAN, clean);
	energy = load_item(DATA_ENERGY, energy);

	happy_timer = load_item(DATA_HAPPY_TIMER, happy_timer);
	full_timer = load_item(DATA_FULL_TIMER, full_timer);
	clean_timer = load_item(DATA_CLEAN_TIMER, clean_timer);
	energy_timer = load_item(DATA_ENERGY_TIMER, energy_timer);

	fruit_eaten = load_item(DATA_FRUIT_EATEN, fruit_eaten);
	fly_eaten = load_item(DATA_FLY_EATEN, fly_eaten);
}
