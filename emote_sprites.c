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
#include "sprites/misc_16x8/bath.h"

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

#define EMOTE_TILE_COUNT 2

const metasprite_t emote_metasprite0[] = {
	METASPR_ITEM(0, 0, 0, S_PAL(0)),
	METASPR_TERM
};

const metasprite_t emote_metasprite1[] = {
	METASPR_ITEM(0, 0, 1, S_PAL(0)),
	METASPR_TERM
};

const metasprite_t* const emote_metasprites[2] = {
	emote_metasprite0, emote_metasprite1
};

#define EMOTE_VRAM_1 0x40
#define EMOTE_VRAM_2 0x42
uint8_t emote_vram = EMOTE_VRAM_1;

#define DIRT_VRAM 0xc0
uint8_t dirt_anim_counter = 0;
uint8_t dirt_frame = 0;

#define BATH_VRAM 0xc4
uint8_t bath_anim_counter = 0;
uint8_t bath_frame = 0;

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
			SWITCH_ROM(BANK(emote_sun));
			set_sprite_data(emote_vram, EMOTE_TILE_COUNT, emote_sun_tiles);
			break;

		case EMOTE_SAD:
			SWITCH_ROM(BANK(emote_sad));
			set_sprite_data(emote_vram, EMOTE_TILE_COUNT, emote_sad_tiles);
			break;

		case EMOTE_ANGRY:
			SWITCH_ROM(BANK(emote_angry));
			set_sprite_data(emote_vram, EMOTE_TILE_COUNT, emote_angry_tiles);
			break;

		case EMOTE_BUBBLES:
			SWITCH_ROM(BANK(emote_bubbles));
			set_sprite_data(emote_vram, EMOTE_TILE_COUNT, emote_bubbles_tiles);
			break;

		case EMOTE_SPARKLE:
			SWITCH_ROM(BANK(emote_sparkle));
			set_sprite_data(emote_vram, EMOTE_TILE_COUNT, emote_sparkle_tiles);
			break;

		case EMOTE_HEART:
			SWITCH_ROM(BANK(emote_heart));
			set_sprite_data(emote_vram, EMOTE_TILE_COUNT, emote_heart_tiles);
			break;

		case EMOTE_HEARTBREAK:
			SWITCH_ROM(BANK(emote_heartbreak));
			set_sprite_data(emote_vram, EMOTE_TILE_COUNT, emote_heartbreak_tiles);
			break;

		case EMOTE_SLEEP:
			SWITCH_ROM(BANK(emote_sleep));
			set_sprite_data(emote_vram, EMOTE_TILE_COUNT, emote_sleep_tiles);
			break;

		case EMOTE_SKULL:
			SWITCH_ROM(BANK(emote_skull));
			set_sprite_data(emote_vram, EMOTE_TILE_COUNT, emote_skull_tiles);
			break;

		case EMOTE_HEAL:
			SWITCH_ROM(BANK(emote_heal));
			set_sprite_data(emote_vram, EMOTE_TILE_COUNT, emote_heal_tiles);
			break;

	}

	SWITCH_ROM(saved_bank);
}

void draw_emote_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite) {
	*last_sprite += move_metasprite_ex(emote_metasprites[frame], emote_vram, 0, *last_sprite, x, y);
}

void setup_emote_sprites(void) {
	uint8_t saved_bank = _current_bank;

	SWITCH_ROM(BANK(dirt));
	set_sprite_data(DIRT_VRAM, dirt_TILE_COUNT, dirt_tiles);

	SWITCH_ROM(BANK(bath));
	set_sprite_data(BATH_VRAM, bath_TILE_COUNT, bath_tiles);

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

void draw_bath_sprite(uint8_t x, uint8_t y, int8_t y_offset, uint8_t *last_sprite) {
	uint8_t saved_bank = _current_bank;

	bath_anim_counter += 1;
	if (bath_anim_counter > 24) {
		bath_anim_counter = 0;
		bath_frame = !bath_frame;
	}

	SWITCH_ROM(BANK(bath));
	*last_sprite += move_metasprite_ex(bath_metasprites[bath_frame], BATH_VRAM, 0, *last_sprite, x + 8, y + y_offset);
	*last_sprite += move_metasprite_ex(bath_metasprites[!bath_frame], BATH_VRAM, 0, *last_sprite, x + 8, y + 18);

	SWITCH_ROM(saved_bank);
}
