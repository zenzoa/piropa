#include <gbdk/platform.h>

#include "frog.h"
#include "hud.h"

typedef struct save_slot_t {
	uint16_t signature;
	uint8_t hud_hours_0;
	uint8_t hud_minutes_0;
	uint8_t hud_seconds_0;
	uint16_t age;
	uint8_t fullness;
	uint8_t happiness;
} save_slot_t;

save_slot_t AT(0xA000) save_slot;

void save_data() {
	ENABLE_RAM;
	SWITCH_RAM(0);

	save_slot.signature = 0xACAB;
	save_slot.hud_hours_0 = hud_hours_0;
	save_slot.hud_minutes_0 = hud_minutes_0;
	save_slot.hud_seconds_0 = hud_seconds_0;

	SWITCH_ROM(BANK(frog_bank));
	save_slot.age = age;
	save_slot.fullness = fullness;
	save_slot.happiness = happiness;

	DISABLE_RAM;
}

uint8_t load_data() {
	ENABLE_RAM;
	SWITCH_RAM(0);

	uint8_t result = (save_slot.signature == 0xACAB);
	if (result) {

		hud_hours_0 = save_slot.hud_hours_0;
		hud_minutes_0 = save_slot.hud_minutes_0;
		hud_seconds_0 = save_slot.hud_seconds_0;

		SWITCH_ROM(BANK(frog_bank));
		age = save_slot.age;
		fullness = save_slot.fullness;
		happiness = save_slot.happiness;

	}

	DISABLE_RAM;

	return result;
}
