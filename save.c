#include <gbdk/platform.h>

#include "frog.h"

typedef struct save_slot_t {
	uint16_t save_flag;

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
	uint8_t poops;

} save_slot_t;

save_slot_t AT(0xA000) save_slot;

const uint16_t SAVE_FLAG_VALUE = 0xACAB;

void save_data(void) {
	ENABLE_RAM;
	SWITCH_RAM(0);

	save_slot.save_flag = SAVE_FLAG_VALUE;

	SWITCH_ROM(BANK(frog_bank));

	save_slot.life_stage = life_stage;
	save_slot.stomach = stomach;
	save_slot.bowels = bowels;
	save_slot.weight = weight;
	save_slot.hygiene = hygiene;
	save_slot.energy = energy;
	save_slot.love = love;
	save_slot.medicine = medicine;
	save_slot.health = health;
	save_slot.sickness = sickness;
	save_slot.poops = poops;

	DISABLE_RAM;
}

uint8_t load_data(void) {
	uint8_t was_load_successful = FALSE;

	ENABLE_RAM;
	SWITCH_RAM(0);

	if (save_slot.save_flag == SAVE_FLAG_VALUE) {

		SWITCH_ROM(BANK(frog_bank));

		life_stage = save_slot.life_stage;
		stomach = save_slot.stomach;
		bowels = save_slot.bowels;
		weight = save_slot.weight;
		hygiene = save_slot.hygiene;
		energy = save_slot.energy;
		love = save_slot.love;
		medicine = save_slot.medicine;
		health = save_slot.health;
		sickness = save_slot.sickness;
		poops = save_slot.poops;

		was_load_successful = TRUE;

	}

	DISABLE_RAM;
	return was_load_successful;

}
