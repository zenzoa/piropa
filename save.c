#pragma bank 255

#include <gbdk/platform.h>

#include "shared_variables.h"

BANKREF(save_bank)

typedef struct save_slot_t {
	uint16_t save_flag_start;

	uint8_t game_speed;
	uint8_t is_night;

	uint16_t age;
	uint8_t age_part;
	uint8_t stage;
	uint8_t life_stage;

	uint8_t stomach;
	uint8_t bowels;
	uint8_t weight;
	uint8_t hygiene;
	uint8_t energy;
	uint8_t love;
	uint8_t medicine;
	uint8_t health;
	uint8_t sickness;

	uint8_t poop_count;
	uint8_t poops_scene[MAX_POOPS];
	uint8_t poops_x[MAX_POOPS];
	uint8_t poops_y[MAX_POOPS];

	uint8_t fly_alive[FLY_COUNT];
	uint8_t fly_respawn[FLY_COUNT];
	uint8_t dragonfly_alive[DRAGONFLY_COUNT];
	uint8_t dragonfly_respawn[DRAGONFLY_COUNT];
	uint8_t firefly_alive[FIREFLY_COUNT];
	uint8_t firefly_respawn[FIREFLY_COUNT];
	uint8_t butterfly_alive[BUTTERFLY_COUNT];
	uint8_t butterfly_respawn[BUTTERFLY_COUNT];

	uint8_t plant_age[PLANT_COUNT];
	uint8_t plant_stage[PLANT_COUNT];
	uint8_t plant_is_watered[PLANT_COUNT];

	uint16_t save_flag_end;

} save_slot_t;

save_slot_t AT(0xA000) save_slots[2];

const uint16_t SAVE_FLAG_VALUE_1 = 0xACAB;
const uint16_t SAVE_FLAG_VALUE_2 = 0xBABA;
uint8_t last_flag = 0;

void save_data_to_slot(uint8_t i) {
	save_slots[i].save_flag_start = last_flag ? SAVE_FLAG_VALUE_1 : SAVE_FLAG_VALUE_2;

	save_slots[i].game_speed = game_speed;
	save_slots[i].is_night = is_night;

	save_slots[i].age = age;
	save_slots[i].age_part = age_part;
	save_slots[i].stage = stage;
	save_slots[i].life_stage = life_stage;

	save_slots[i].stomach = stomach;
	save_slots[i].bowels = bowels;
	save_slots[i].weight = weight;
	save_slots[i].hygiene = hygiene;
	save_slots[i].energy = energy;
	save_slots[i].love = love;
	save_slots[i].medicine = medicine;
	save_slots[i].health = health;
	save_slots[i].sickness = sickness;

	save_slots[i].poop_count = poop_count;
	for (uint8_t j = 0; j < MAX_POOPS; j++) {
		save_slots[i].poops_scene[j] = poops_scene[j];
		save_slots[i].poops_x[j] = poops_x[j];
		save_slots[i].poops_y[j] = poops_y[j];
	}

	for (uint8_t j = 0; j < FLY_COUNT; j++) {
		save_slots[i].fly_alive[j] = fly_alive[j];
		save_slots[i].fly_respawn[j] = fly_respawn[j];
	}
	for (uint8_t j = 0; j < DRAGONFLY_COUNT; j++) {
		save_slots[i].dragonfly_alive[j] = dragonfly_alive[j];
		save_slots[i].dragonfly_respawn[j] = dragonfly_respawn[j];
	}
	for (uint8_t j = 0; j < FIREFLY_COUNT; j++) {
		save_slots[i].firefly_alive[j] = firefly_alive[j];
		save_slots[i].firefly_respawn[j] = firefly_respawn[j];
	}
	for (uint8_t j = 0; j < BUTTERFLY_COUNT; j++) {
		save_slots[i].butterfly_alive[j] = butterfly_alive[j];
		save_slots[i].butterfly_respawn[j] = butterfly_respawn[j];
	}

	for (uint8_t j = 0; j < PLANT_COUNT; j++) {
		save_slots[i].plant_age[j] = plant_age[j];
		save_slots[i].plant_stage[j] = plant_stage[j];
		save_slots[i].plant_is_watered[j] = plant_is_watered[j];
	}

	save_slots[i].save_flag_end = last_flag ? SAVE_FLAG_VALUE_1 : SAVE_FLAG_VALUE_2;
}

void save_data(void) {
	ENABLE_RAM;
	SWITCH_RAM(0);

	save_data_to_slot(0);
	save_data_to_slot(1);

	DISABLE_RAM;
	has_save = TRUE;
}

uint8_t load_data_from_slot(uint8_t i) {
	if (save_slots[i].save_flag_start == save_slots[i].save_flag_end &&
		(save_slots[i].save_flag_start == SAVE_FLAG_VALUE_1 || save_slots[i].save_flag_start == SAVE_FLAG_VALUE_2)
	) {

		game_speed = save_slots[i].game_speed;
		is_night = save_slots[i].is_night;

		age = save_slots[i].age;
		age_part = save_slots[i].age_part;
		stage = save_slots[i].stage;
		life_stage = save_slots[i].life_stage;

		stomach = save_slots[i].stomach;
		bowels = save_slots[i].bowels;
		weight = save_slots[i].weight;
		hygiene = save_slots[i].hygiene;
		energy = save_slots[i].energy;
		love = save_slots[i].love;
		medicine = save_slots[i].medicine;
		health = save_slots[i].health;
		sickness = save_slots[i].sickness;

		poop_count = save_slots[i].poop_count;
		for (uint8_t j = 0; j < MAX_POOPS; j++) {
			poops_scene[j] = save_slots[i].poops_scene[j];
			poops_x[j] = save_slots[i].poops_x[j];
			poops_y[j] = save_slots[i].poops_y[j];
		}

		for (uint8_t j = 0; j < FLY_COUNT; j++) {
			fly_alive[j] = save_slots[i].fly_alive[j];
			fly_respawn[j] = save_slots[i].fly_respawn[j];
		}
		for (uint8_t j = 0; j < DRAGONFLY_COUNT; j++) {
			dragonfly_alive[j] = save_slots[i].dragonfly_alive[j];
			dragonfly_respawn[j] = save_slots[i].dragonfly_respawn[j];
		}
		for (uint8_t j = 0; j < FIREFLY_COUNT; j++) {
			firefly_alive[j] = save_slots[i].firefly_alive[j];
			firefly_respawn[j] = save_slots[i].firefly_respawn[j];
		}
		for (uint8_t j = 0; j < BUTTERFLY_COUNT; j++) {
			butterfly_alive[j] = save_slots[i].butterfly_alive[j];
			butterfly_respawn[j] = save_slots[i].butterfly_respawn[j];
		}

		for (uint8_t j = 0; j < PLANT_COUNT; j++) {
			plant_age[j] = save_slots[i].plant_age[j];
			plant_stage[j] = save_slots[i].plant_stage[j];
			plant_is_watered[j] = save_slots[i].plant_is_watered[j];
		}

		return TRUE;

	} else {
		return FALSE;
	}
}

void load_data(void) {
	has_save = FALSE;

	ENABLE_RAM;
	SWITCH_RAM(0);

	has_save = load_data_from_slot(0) || load_data_from_slot(1);

	DISABLE_RAM;
}
