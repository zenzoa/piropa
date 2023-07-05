#include <gbdk/platform.h>

#define SAVE_DATA_COUNT 35

const uint16_t SAVED_FLAG = 'a';

typedef struct SaveDataLocations {
	uint16_t* flag_addr; // Pointer to RAM where we set the "did we save this item?" flag
	uint16_t* RAM_addr;  // Pointer to RAM memory address where we save the data itself
} SaveDataLocations;

const SaveDataLocations save_data_locations[SAVE_DATA_COUNT] = {
	{ 0xA000, 0xA002 }, // time_speed

	{ 0xA004, 0xA006 }, // is_night

	{ 0xA008, 0xA00A }, // jar_fullness

	{ 0xA00C, 0xA00E }, // next_fruit
	{ 0xA010, 0xA012 }, // num_blackberries
	{ 0xA014, 0xA016 }, // num_blueberries
	{ 0xA018, 0xA01A }, // num_strawberries

	{ 0xA01C, 0xA01E }, // frog_evo
	{ 0xA020, 0xA022 }, // frog_min
	{ 0xA024, 0xA026 }, // frog_hour

	{ 0xA028, 0xA02A }, // happy
	{ 0xA02C, 0xA02E }, // full
	{ 0xA030, 0xA032 }, // clean
	{ 0xA034, 0xA036 }, // energy

	{ 0xA038, 0xA03A }, // happy_timer
	{ 0xA03C, 0xA03E }, // full_timer
	{ 0xA040, 0xA042 }, // clean_timer
	{ 0xA044, 0xA046 }, // energy_timer

	{ 0xA048, 0xA04A }, // fruit_eaten
	{ 0xA04C, 0xA04E }, // fly_eaten

	{ 0xA050, 0xA052 }, // plant_1_watered
	{ 0xA054, 0xA056 }, // plant_1_stage
	{ 0xA058, 0xA05A }, // plant_1_min

	{ 0xA05C, 0xA05E }, // plant_2_watered
	{ 0xA060, 0xA062 }, // plant_2_stage
	{ 0xA064, 0xA066 }, // plant_2_min

	{ 0xA068, 0xA06A }, // plant_3_watered
	{ 0xA06C, 0xA06E }, // plant_3_stage
	{ 0xA070, 0xA072 }, // plant_3_min

	{ 0xA074, 0xA076 }, // fly1_state
	{ 0xA078, 0xA07A }, // fly1_respawn

	{ 0xA07C, 0xA07E }, // fly2_state
	{ 0xA080, 0xA082 }, // fly2_respawn

	{ 0xA084, 0xA086 }, // fly3_state
	{ 0xA088, 0xA08A }, // fly3_respawn
};

void save_item(uint8_t item_id, uint8_t item_value) {
	ENABLE_RAM;
	SWITCH_RAM(0);

	save_data_locations[item_id].flag_addr[0] = SAVED_FLAG;
	save_data_locations[item_id].RAM_addr[0] = item_value;

	DISABLE_RAM;
}

uint8_t load_item(uint8_t item_id, uint8_t default_value) {
	uint8_t item_value = default_value;

	ENABLE_RAM;
	SWITCH_RAM(0);

	if (save_data_locations[item_id].flag_addr[0] == SAVED_FLAG) {
		item_value = save_data_locations[item_id].RAM_addr[0];
	}

	DISABLE_RAM;

	return item_value;
}

void reset_all_items() {
	ENABLE_RAM;
	SWITCH_RAM(0);

	uint8_t i = 0;
	while (i < SAVE_DATA_COUNT) {
		save_data_locations[i].flag_addr[0] = 0;
		i += 1;
	}

	DISABLE_RAM;
}

uint8_t check_for_save() {
	ENABLE_RAM;
	SWITCH_RAM(0);
	if (save_data_locations[0].flag_addr[0] == SAVED_FLAG) {
		DISABLE_RAM;
		return 1;
	} else {
		DISABLE_RAM;
		return 0;
	}
}
