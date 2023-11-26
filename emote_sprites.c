#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "common.h"

#include "sprites/emotes/emote_sun.h"
#include "sprites/emotes/emote_sad.h"
#include "sprites/emotes/emote_angry.h"
#include "sprites/emotes/emote_bubbles.h"
#include "sprites/emotes/emote_sparkle.h"
#include "sprites/emotes/emote_heart.h"
#include "sprites/emotes/emote_heartbreak.h"
#include "sprites/emotes/emote_sleep.h"
#include "sprites/emotes/emote_skull.h"
#include "sprites/emotes/emote_heal.h"
#include "sprites/emotes/dirt.h"
#include "sprites/emotes/bath.h"
#include "sprites/emotes/watering_can.h"

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

#define EMOTE_TILE_COUNT 4

static const metasprite_t emote_metasprite0[] = {
	METASPR_ITEM(0, 0, 0, S_PAL(0)),
	METASPR_ITEM(0, 8, 1, S_PAL(0)),
	METASPR_TERM
};

static const metasprite_t emote_metasprite1[] = {
	METASPR_ITEM(0, 0, 2, S_PAL(0)),
	METASPR_ITEM(0, 8, 3, S_PAL(0)),
	METASPR_TERM
};

static const metasprite_t* const emote_metasprites[2] = {
	emote_metasprite0, emote_metasprite1
};

#define EMOTE_VRAM_1 0xa0
#define EMOTE_VRAM_2 0xa4
static uint8_t emote_vram = EMOTE_VRAM_1;

#define DIRT_VRAM 0xa8
static uint8_t dirt_anim_counter = 0;
static uint8_t dirt_frame = 0;

#define BATH_VRAM 0xac
static uint8_t bath_anim_counter = 0;
static uint8_t bath_frame = 0;

#define WATERING_CAN_VRAM 0xb0
static uint8_t watering_anim_counter = 0;
static uint8_t watering_frame = 0;

static void swap_emote_vram(void) {
	if (emote_vram == EMOTE_VRAM_1) {
		emote_vram = EMOTE_VRAM_2;
	} else {
		emote_vram = EMOTE_VRAM_1;
	}
}

void set_emote_sprite_data(uint8_t emote) {
	swap_emote_vram();
	switch(emote) {
		case EMOTE_SUN:
			set_banked_sprite_data(BANK(emote_sun), emote_vram, emote_sun_TILE_COUNT, emote_sun_tiles);
			break;

		case EMOTE_SAD:
			set_banked_sprite_data(BANK(emote_sad), emote_vram, emote_sad_TILE_COUNT, emote_sad_tiles);
			break;

		case EMOTE_ANGRY:
			set_banked_sprite_data(BANK(emote_angry), emote_vram, emote_angry_TILE_COUNT, emote_angry_tiles);
			break;

		case EMOTE_BUBBLES:
			set_banked_sprite_data(BANK(emote_bubbles), emote_vram, emote_bubbles_TILE_COUNT, emote_bubbles_tiles);
			break;

		case EMOTE_SPARKLE:
			set_banked_sprite_data(BANK(emote_sparkle), emote_vram, emote_sparkle_TILE_COUNT, emote_sparkle_tiles);
			break;

		case EMOTE_HEART:
			set_banked_sprite_data(BANK(emote_heart), emote_vram, emote_heart_TILE_COUNT, emote_heart_tiles);
			break;

		case EMOTE_HEARTBREAK:
			set_banked_sprite_data(BANK(emote_heartbreak), emote_vram, emote_heartbreak_TILE_COUNT, emote_heartbreak_tiles);
			break;

		case EMOTE_SLEEP:
			set_banked_sprite_data(BANK(emote_sleep), emote_vram, emote_sleep_TILE_COUNT, emote_sleep_tiles);
			break;

		case EMOTE_SKULL:
			set_banked_sprite_data(BANK(emote_skull), emote_vram, emote_skull_TILE_COUNT, emote_skull_tiles);
			break;

		case EMOTE_HEAL:
			set_banked_sprite_data(BANK(emote_heal), emote_vram, emote_heal_TILE_COUNT, emote_heal_tiles);
			break;
	}
}

void draw_emote_sprite(uint8_t x, uint8_t y, uint8_t frame) {
	last_sprite += move_metasprite_ex(emote_metasprites[frame], emote_vram, GREY_PALETTE, last_sprite, x, y);
}

void setup_emote_sprites(void) {
	set_banked_sprite_data(BANK(dirt), DIRT_VRAM, dirt_TILE_COUNT, dirt_tiles);
	set_banked_sprite_data(BANK(bath), BATH_VRAM, bath_TILE_COUNT, bath_tiles);
	set_banked_sprite_data(BANK(watering_can), WATERING_CAN_VRAM, watering_can_TILE_COUNT, watering_can_tiles);
}

void draw_dirt_sprite(uint8_t x, uint8_t y) {
	dirt_anim_counter += 1;
	if (dirt_anim_counter > 24) {
		dirt_anim_counter = 0;
		dirt_frame = !dirt_frame;
	}
	draw_banked_sprite(BANK(dirt), emote_metasprites, dirt_frame, DIRT_VRAM, BROWN_PALETTE, x + 8, y + 18);
}

void draw_bath_sprite(uint8_t x, uint8_t y, int8_t y_offset) {
	bath_anim_counter += 1;
	if (bath_anim_counter > 24) {
		bath_anim_counter = 0;
		bath_frame = !bath_frame;
	}
	draw_banked_sprite(BANK(bath), emote_metasprites, bath_frame, BATH_VRAM, BLUE_PALETTE, x + 8, y + y_offset);
	draw_banked_sprite(BANK(bath), emote_metasprites, bath_frame, BATH_VRAM, BLUE_PALETTE, x + 8, y + 18);
}

void draw_watering_sprite(uint8_t x, uint8_t y) {
	watering_anim_counter += 1;
	if (watering_anim_counter > 16) {
		watering_anim_counter = 0;
		watering_frame = !watering_frame;
	}
	draw_banked_sprite(BANK(watering_can), emote_metasprites, watering_frame, WATERING_CAN_VRAM, GREY_PALETTE, x + 16, y + 12);
}
