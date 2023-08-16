#include <gbdk/platform.h>

#include "frog.h"
#include "hud.h"

typedef struct save_slot_t {
	uint16_t save_flag;

	uint8_t hud_hours_0;
	uint8_t hud_minutes_0;
	uint8_t hud_seconds_0;

	uint16_t age;
	uint8_t stage;
	uint8_t personality;

	uint8_t fullness;
	uint16_t last_fullness_decrease;

	uint8_t happiness;
	uint16_t last_happiness_decrease;

	uint8_t cleanliness;
	uint16_t last_cleanliness_decrease;

	uint8_t care_mistakes;
	uint16_t empty_fullness_time;
	uint16_t empty_happiness_time;
	uint16_t empty_cleanliness_time;

	uint8_t sickness_counter;
	uint16_t last_sickness_increase;

	uint8_t friendship_points;
	uint16_t last_friendship_increase;

	uint8_t friendship_level;

	uint8_t vegetarian;
	uint8_t carnivore;
} save_slot_t;

save_slot_t AT(0xA000) save_slot;

const uint16_t SAVE_FLAG_VALUE = 0xACAB;

void save_data(void) {
	ENABLE_RAM;
	SWITCH_RAM(0);

	save_slot.save_flag = SAVE_FLAG_VALUE;
	save_slot.hud_hours_0 = hud_hours_0;
	save_slot.hud_minutes_0 = hud_minutes_0;
	save_slot.hud_seconds_0 = hud_seconds_0;

	SWITCH_ROM(BANK(frog_bank));

	save_slot.age = age;
	save_slot.stage = stage;
	save_slot.personality = personality;

	save_slot.fullness = fullness;
	save_slot.last_fullness_decrease = last_fullness_decrease;

	save_slot.happiness = happiness;
	save_slot.last_happiness_decrease = last_happiness_decrease;

	save_slot.cleanliness = cleanliness;
	save_slot.last_cleanliness_decrease = last_cleanliness_decrease;

	save_slot.care_mistakes = care_mistakes;
	save_slot.empty_fullness_time = empty_fullness_time;
	save_slot.empty_happiness_time = empty_happiness_time;
	save_slot.empty_cleanliness_time = empty_cleanliness_time;

	save_slot.sickness_counter = sickness_counter;
	save_slot.last_sickness_increase = last_sickness_increase;

	save_slot.friendship_points = friendship_points;
	save_slot.last_friendship_increase = last_friendship_increase;

	save_slot.friendship_level = friendship_level;

	save_slot.vegetarian = vegetarian;
	save_slot.carnivore = carnivore;

	DISABLE_RAM;
}

uint8_t load_data(void) {
	uint8_t was_load_successful = FALSE;

	ENABLE_RAM;
	SWITCH_RAM(0);

	if (save_slot.save_flag == SAVE_FLAG_VALUE) {

		hud_hours_0 = save_slot.hud_hours_0;
		hud_minutes_0 = save_slot.hud_minutes_0;
		hud_seconds_0 = save_slot.hud_seconds_0;

		SWITCH_ROM(BANK(frog_bank));

		age = save_slot.age;
		stage = save_slot.stage;
		personality = save_slot.personality;

		fullness = save_slot.fullness;
		last_fullness_decrease = save_slot.last_fullness_decrease;

		happiness = save_slot.happiness;
		last_happiness_decrease = save_slot.last_happiness_decrease;

		cleanliness = save_slot.cleanliness;
		last_cleanliness_decrease = save_slot.last_cleanliness_decrease;

		care_mistakes = save_slot.care_mistakes;
		empty_fullness_time = save_slot.empty_fullness_time;
		empty_happiness_time = save_slot.empty_happiness_time;
		empty_cleanliness_time = save_slot.empty_cleanliness_time;

		sickness_counter = save_slot.sickness_counter;
		last_sickness_increase = save_slot.last_sickness_increase;

		friendship_points = save_slot.friendship_points;
		last_friendship_increase = save_slot.last_friendship_increase;

		friendship_level = save_slot.friendship_level;

		vegetarian = save_slot.vegetarian;
		carnivore = save_slot.carnivore;

		was_load_successful = TRUE;

	}

	DISABLE_RAM;
	return was_load_successful;

}
