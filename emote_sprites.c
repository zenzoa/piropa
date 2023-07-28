#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "sprites/misc_8x8/emote_happy.h"
#include "sprites/misc_8x8/emote_sad.h"
#include "sprites/misc_8x8/emote_scared.h"
#include "sprites/misc_8x8/emote_angry.h"
#include "sprites/misc_8x8/emote_sleep.h"
#include "sprites/misc_8x8/emote_sick.h"
#include "sprites/misc_8x8/emote_love.h"

#define EMOTE_NONE 0
#define EMOTE_HAPPY 1
#define EMOTE_SAD 2
#define EMOTE_SCARED 3
#define EMOTE_ANGRY 4
#define EMOTE_SLEEP 5
#define EMOTE_SICK 6
#define EMOTE_LOVE 7

uint8_t emote_sprite_bank;
metasprite_t** emote_metasprites;

#define EMOTE_VRAM_1 0x30
#define EMOTE_VRAM_2 0x32
uint8_t emote_vram = EMOTE_VRAM_1;

void swap_emote_vram() {
	if (emote_vram == EMOTE_VRAM_1) {
		emote_vram = EMOTE_VRAM_2;
	} else {
		emote_vram = EMOTE_VRAM_1;
	}
}

void set_emote_sprite_data(uint8_t emote) {
	uint8_t saved_bank = _current_bank;

	switch(emote) {

		case EMOTE_HAPPY:
			emote_sprite_bank = BANK(emote_happy);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_happy_TILE_COUNT, emote_happy_tiles);
			emote_metasprites = emote_happy_metasprites;
			break;

		case EMOTE_SAD:
			emote_sprite_bank = BANK(emote_sad);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_sad_TILE_COUNT, emote_sad_tiles);
			emote_metasprites = emote_sad_metasprites;
			break;

		case EMOTE_SCARED:
			emote_sprite_bank = BANK(emote_scared);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_scared_TILE_COUNT, emote_scared_tiles);
			emote_metasprites = emote_scared_metasprites;
			break;

		case EMOTE_ANGRY:
			emote_sprite_bank = BANK(emote_angry);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_angry_TILE_COUNT, emote_angry_tiles);
			emote_metasprites = emote_angry_metasprites;
			break;

		case EMOTE_SLEEP:
			emote_sprite_bank = BANK(emote_sleep);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_sleep_TILE_COUNT, emote_sleep_tiles);
			emote_metasprites = emote_sleep_metasprites;
			break;

		case EMOTE_SICK:
			emote_sprite_bank = BANK(emote_sick);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_sick_TILE_COUNT, emote_sick_tiles);
			emote_metasprites = emote_sick_metasprites;
			break;

		case EMOTE_LOVE:
			emote_sprite_bank = BANK(emote_love);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_love_TILE_COUNT, emote_love_tiles);
			emote_metasprites = emote_love_metasprites;
			break;

	}

	SWITCH_ROM(saved_bank);
}

void draw_emote_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite) {
	uint8_t saved_bank = _current_bank;

	SWITCH_ROM(emote_sprite_bank);
	*last_sprite += move_metasprite(emote_metasprites[frame], emote_vram, *last_sprite, x, y);

	SWITCH_ROM(saved_bank);
}
