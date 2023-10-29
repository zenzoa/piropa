#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "sprites/misc_8x8/emote_sun.h"
#include "sprites/misc_8x8/emote_sad.h"
#include "sprites/misc_8x8/emote_angry.h"
#include "sprites/misc_8x8/emote_bubbles.h"
#include "sprites/misc_8x8/emote_sparkle.h"
#include "sprites/misc_8x8/emote_heart.h"
#include "sprites/misc_8x8/emote_heartbreak.h"
#include "sprites/misc_8x8/emote_sleep.h"
#include "sprites/misc_8x8/emote_skull.h"
#include "sprites/misc_8x8/emote_heal.h"

#include "sprites/misc_16x8/dirt.h"

#define EMOTE_NONE 0
#define EMOTE_SUN 1
#define EMOTE_SAD 2
#define EMOTE_ANGRY 3
#define EMOTE_BUBBLES 4
#define EMOTE_SPARKLE 5
#define EMOTE_HEART 6
#define EMOTE_HEARTBREAK 7
#define EMOTE_SLEEP 8
#define EMOTE_SKULL 9
#define EMOTE_HEAL 10

uint8_t emote_sprite_bank;
metasprite_t** emote_metasprites;

#define EMOTE_VRAM_1 0x40
#define EMOTE_VRAM_2 0x42
uint8_t emote_vram = EMOTE_VRAM_1;

#define DIRT_VRAM 0xc0
uint8_t dirt_anim_counter = 0;
uint8_t dirt_frame = 0;

void swap_emote_vram(void) {
	if (emote_vram == EMOTE_VRAM_1) {
		emote_vram = EMOTE_VRAM_2;
	} else {
		emote_vram = EMOTE_VRAM_1;
	}
}

void set_emote_sprite_data(uint8_t emote) {
	uint8_t saved_bank = _current_bank;

	switch(emote) {

		case EMOTE_SUN:
			emote_sprite_bank = BANK(emote_sun);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_sun_TILE_COUNT, emote_sun_tiles);
			emote_metasprites = emote_sun_metasprites;
			break;

		case EMOTE_SAD:
			emote_sprite_bank = BANK(emote_sad);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_sad_TILE_COUNT, emote_sad_tiles);
			emote_metasprites = emote_sad_metasprites;
			break;

		case EMOTE_ANGRY:
			emote_sprite_bank = BANK(emote_angry);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_angry_TILE_COUNT, emote_angry_tiles);
			emote_metasprites = emote_angry_metasprites;
			break;

		case EMOTE_BUBBLES:
			emote_sprite_bank = BANK(emote_bubbles);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_bubbles_TILE_COUNT, emote_bubbles_tiles);
			emote_metasprites = emote_bubbles_metasprites;
			break;

		case EMOTE_SPARKLE:
			emote_sprite_bank = BANK(emote_sparkle);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_sparkle_TILE_COUNT, emote_sparkle_tiles);
			emote_metasprites = emote_sparkle_metasprites;
			break;

		case EMOTE_HEART:
			emote_sprite_bank = BANK(emote_heart);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_heart_TILE_COUNT, emote_heart_tiles);
			emote_metasprites = emote_heart_metasprites;
			break;

		case EMOTE_HEARTBREAK:
			emote_sprite_bank = BANK(emote_heartbreak);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_heartbreak_TILE_COUNT, emote_heartbreak_tiles);
			emote_metasprites = emote_heartbreak_metasprites;
			break;

		case EMOTE_SLEEP:
			emote_sprite_bank = BANK(emote_sleep);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_sleep_TILE_COUNT, emote_sleep_tiles);
			emote_metasprites = emote_sleep_metasprites;
			break;

		case EMOTE_SKULL:
			emote_sprite_bank = BANK(emote_skull);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_skull_TILE_COUNT, emote_skull_tiles);
			emote_metasprites = emote_skull_metasprites;
			break;

		case EMOTE_HEAL:
			emote_sprite_bank = BANK(emote_heal);
			SWITCH_ROM(emote_sprite_bank);
			set_sprite_data(emote_vram, emote_heal_TILE_COUNT, emote_heal_tiles);
			emote_metasprites = emote_heal_metasprites;
			break;

	}

	SWITCH_ROM(saved_bank);
}

void draw_emote_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite) {
	uint8_t saved_bank = _current_bank;

	SWITCH_ROM(emote_sprite_bank);
	*last_sprite += move_metasprite_ex(emote_metasprites[frame], emote_vram, 0, *last_sprite, x, y);

	SWITCH_ROM(saved_bank);
}

void setup_dirt_sprite(void) {
	uint8_t saved_bank = _current_bank;

	SWITCH_ROM(BANK(dirt));
	set_sprite_data(DIRT_VRAM, dirt_TILE_COUNT, dirt_tiles);

	SWITCH_ROM(saved_bank);
}

void draw_dirt_sprite(uint8_t x, uint8_t y, uint8_t *last_sprite) {
	uint8_t saved_bank = _current_bank;

	dirt_anim_counter += 1;
	if (dirt_anim_counter > 24) {
		dirt_anim_counter = 0;
		dirt_frame = !dirt_frame;
	}

	SWITCH_ROM(BANK(dirt));
	*last_sprite += move_metasprite_ex(dirt_metasprites[dirt_frame], DIRT_VRAM, 0, *last_sprite, x + 8, y + 18);

	SWITCH_ROM(saved_bank);
}
