/* =============== */
/*     IMPORTS     */
/* =============== */

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <time.h>
#include <rand.h>

#include <gbdk/emu_debug.h>

#include "clock.h"
#include "frog.h"
#include "pond.h"
#include "garden.h"

#include "save.h"

/* FIELD */

#include "sprites/background/bg_field.h"
#include "sprites/background/bg_field_night.h"
#include "sprites/misc_16x16/moon.h"
#include "sprites/misc_8x8/moon_sleep.h"

/* POND */

#include "sprites/background/bg_pond.h"
#include "sprites/background/bg_pond_night.h"
#include "sprites/background/pond_sparkle.h"
#include "sprites/misc_8x8/fly.h"

/* GARDEN */

#include "sprites/background/bg_garden.h"
#include "sprites/background/bg_garden_night.h"
#include "sprites/background/plant.h"

#include "sprites/misc_8x8/sparkle.h"

/* STATS */

#include "sprites/background/bg_stats.h"
#include "sprites/background/speed_pause.h"
#include "sprites/background/speed_slow.h"
#include "sprites/background/speed_normal.h"
#include "sprites/background/speed_fast.h"

/* MENU */

#include "sprites/background/menu_jar_full.h"
#include "sprites/background/menu_jar_2_3.h"
#include "sprites/background/menu_jar_1_3.h"
#include "sprites/background/menu_jar_empty.h"
#include "sprites/background/menu_jar_outline.h"

#include "sprites/background/menu_soap.h"
#include "sprites/background/menu_soap_outline.h"

#include "sprites/background/menu_moon.h"
#include "sprites/background/menu_moon_outline.h"

#include "sprites/background/menu_fruit_blackberry.h"
#include "sprites/background/menu_fruit_blueberry.h"
#include "sprites/background/menu_fruit_strawberry.h"
#include "sprites/background/menu_fruit_outline.h"

#include "sprites/background/fruit_count_1.h"
#include "sprites/background/fruit_count_2.h"
#include "sprites/background/fruit_count_3.h"
#include "sprites/background/fruit_count_4.h"
#include "sprites/background/fruit_count_5.h"
#include "sprites/background/fruit_count_6.h"

#include "sprites/background/menu_stats.h"

/* HAND */

#include "sprites/hand/hand_normal.h"
#include "sprites/hand/hand_tickle_1.h"
#include "sprites/hand/hand_tickle_2.h"
#include "sprites/hand/hand_jar_empty.h"
#include "sprites/hand/hand_jar_empty_tip.h"
#include "sprites/hand/hand_jar_full.h"
#include "sprites/hand/hand_jar_full_tip.h"
#include "sprites/hand/hand_jar_2_3.h"
#include "sprites/hand/hand_jar_2_3_tip.h"
#include "sprites/hand/hand_jar_1_3.h"
#include "sprites/hand/hand_jar_1_3_tip.h"
#include "sprites/hand/hand_soap.h"
#include "sprites/hand/hand_moon.h"
#include "sprites/hand/hand_blackberry.h"
#include "sprites/hand/hand_blueberry.h"
#include "sprites/hand/hand_strawberry.h"
#include "sprites/hand/hand_fly.h"

#include "sprites/hand/fruit_blackberry_1.h"
#include "sprites/hand/fruit_blackberry_2.h"
#include "sprites/hand/fruit_blackberry_3.h"
#include "sprites/hand/fruit_blueberry_1.h"
#include "sprites/hand/fruit_blueberry_2.h"
#include "sprites/hand/fruit_blueberry_3.h"
#include "sprites/hand/fruit_strawberry_1.h"
#include "sprites/hand/fruit_strawberry_2.h"
#include "sprites/hand/fruit_strawberry_3.h"

/* FROG */

#include "sprites/misc_16x16/egg.h"

#include "sprites/frog_baby/frog_baby_stand.h"
#include "sprites/frog_baby/frog_baby_walk_left.h"
#include "sprites/frog_baby/frog_baby_walk_right.h"
#include "sprites/frog_baby/frog_baby_happy.h"
#include "sprites/frog_baby/frog_baby_sad.h"
#include "sprites/frog_baby/frog_baby_eat.h"
#include "sprites/frog_baby/frog_baby_tickled.h"
#include "sprites/frog_baby/frog_baby_sleep.h"
#include "sprites/frog_baby/frog_baby_wash.h"

#include "sprites/frog_child/frog_child_stand.h"
#include "sprites/frog_child/frog_child_walk_left.h"
#include "sprites/frog_child/frog_child_walk_right.h"
#include "sprites/frog_child/frog_child_happy.h"
#include "sprites/frog_child/frog_child_sad.h"
#include "sprites/frog_child/frog_child_eat.h"
#include "sprites/frog_child/frog_child_tickled.h"
#include "sprites/frog_child/frog_child_sleep.h"
#include "sprites/frog_child/frog_child_wash.h"

#include "sprites/frog_teen/frog_teen_stand.h"
#include "sprites/frog_teen/frog_teen_walk_left.h"
#include "sprites/frog_teen/frog_teen_walk_right.h"
#include "sprites/frog_teen/frog_teen_happy.h"
#include "sprites/frog_teen/frog_teen_sad.h"
#include "sprites/frog_teen/frog_teen_eat.h"
#include "sprites/frog_teen/frog_teen_tickled.h"
#include "sprites/frog_teen/frog_teen_sleep.h"
#include "sprites/frog_teen/frog_teen_wash.h"

#include "sprites/frog_teen_tail/frog_teen_tail_stand.h"
#include "sprites/frog_teen_tail/frog_teen_tail_walk_left.h"
#include "sprites/frog_teen_tail/frog_teen_tail_walk_right.h"
#include "sprites/frog_teen_tail/frog_teen_tail_happy.h"
#include "sprites/frog_teen_tail/frog_teen_tail_sad.h"
#include "sprites/frog_teen_tail/frog_teen_tail_eat.h"
#include "sprites/frog_teen_tail/frog_teen_tail_tickled.h"
#include "sprites/frog_teen_tail/frog_teen_tail_sleep.h"
#include "sprites/frog_teen_tail/frog_teen_tail_wash.h"

#include "sprites/frog_teen_apple/frog_teen_apple_stand.h"
#include "sprites/frog_teen_apple/frog_teen_apple_walk_left.h"
#include "sprites/frog_teen_apple/frog_teen_apple_walk_right.h"
#include "sprites/frog_teen_apple/frog_teen_apple_happy.h"
#include "sprites/frog_teen_apple/frog_teen_apple_sad.h"
#include "sprites/frog_teen_apple/frog_teen_apple_eat.h"
#include "sprites/frog_teen_apple/frog_teen_apple_tickled.h"
#include "sprites/frog_teen_apple/frog_teen_apple_sleep.h"
#include "sprites/frog_teen_apple/frog_teen_apple_wash.h"

#include "sprites/frog_adult/frog_adult_stand.h"
#include "sprites/frog_adult/frog_adult_walk_left.h"
#include "sprites/frog_adult/frog_adult_walk_right.h"
#include "sprites/frog_adult/frog_adult_happy.h"
#include "sprites/frog_adult/frog_adult_sad.h"
#include "sprites/frog_adult/frog_adult_eat.h"
#include "sprites/frog_adult/frog_adult_tickled.h"
#include "sprites/frog_adult/frog_adult_sleep.h"
#include "sprites/frog_adult/frog_adult_wash.h"

#include "sprites/frog_axo/frog_axo_stand.h"
#include "sprites/frog_axo/frog_axo_walk_left.h"
#include "sprites/frog_axo/frog_axo_walk_right.h"
#include "sprites/frog_axo/frog_axo_happy.h"
#include "sprites/frog_axo/frog_axo_sad.h"
#include "sprites/frog_axo/frog_axo_eat.h"
#include "sprites/frog_axo/frog_axo_tickled.h"
#include "sprites/frog_axo/frog_axo_sleep.h"
#include "sprites/frog_axo/frog_axo_wash.h"

#include "sprites/frog_apple/frog_apple_stand.h"
#include "sprites/frog_apple/frog_apple_walk_left.h"
#include "sprites/frog_apple/frog_apple_walk_right.h"
#include "sprites/frog_apple/frog_apple_happy.h"
#include "sprites/frog_apple/frog_apple_sad.h"
#include "sprites/frog_apple/frog_apple_eat.h"
#include "sprites/frog_apple/frog_apple_tickled.h"
#include "sprites/frog_apple/frog_apple_sleep.h"
#include "sprites/frog_apple/frog_apple_wash.h"

#include "sprites/frog_mush/frog_mush_stand.h"
#include "sprites/frog_mush/frog_mush_walk_left.h"
#include "sprites/frog_mush/frog_mush_walk_right.h"
#include "sprites/frog_mush/frog_mush_happy.h"
#include "sprites/frog_mush/frog_mush_sad.h"
#include "sprites/frog_mush/frog_mush_eat.h"
#include "sprites/frog_mush/frog_mush_tickled.h"
#include "sprites/frog_mush/frog_mush_sleep.h"
#include "sprites/frog_mush/frog_mush_wash.h"

#include "sprites/frog_dino/frog_dino_stand.h"
#include "sprites/frog_dino/frog_dino_walk_left.h"
#include "sprites/frog_dino/frog_dino_walk_right.h"
#include "sprites/frog_dino/frog_dino_happy.h"
#include "sprites/frog_dino/frog_dino_sad.h"
#include "sprites/frog_dino/frog_dino_eat.h"
#include "sprites/frog_dino/frog_dino_tickled.h"
#include "sprites/frog_dino/frog_dino_sleep.h"
#include "sprites/frog_dino/frog_dino_wash.h"

#include "sprites/misc_8x8/emote_happy.h"
#include "sprites/misc_8x8/emote_sad.h"
#include "sprites/misc_8x8/emote_hungry.h"
#include "sprites/misc_8x8/emote_tired.h"
#include "sprites/misc_8x8/emote_dirty.h"
#include "sprites/misc_8x8/emote_sleep.h"
#include "sprites/misc_8x8/dirt.h"

/* ================= */
/*     VARIABLES     */
/* ================= */

#define FALSE 0
#define TRUE 1

uint8_t a_button_pressed = FALSE;
uint8_t b_button_pressed = FALSE;

uint8_t last_used_sprite = 0;

/* SPEED */

#define SPEED_PAUSE 0
#define SPEED_SLOW 10
#define SPEED_NORMAL 2
#define SPEED_FAST 1
uint8_t time_speed = SPEED_NORMAL;

const unsigned char speed_pause_tile_map[6] = { 0x50, 0x51, 0x52, 0x53, 0x54, 0x55 };
const unsigned char speed_pause_inactive_tile_map[6] = { 0x20, 0x21, 0x22, 0x2E, 0x2F, 0x30 };

const unsigned char speed_slow_tile_map[6] = { 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B };
const unsigned char speed_slow_inactive_tile_map[6] = { 0x23, 0x24, 0x25, 0x31, 0x32, 0x33 };

const unsigned char speed_normal_tile_map[6] = { 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61 };
const unsigned char speed_normal_inactive_tile_map[6] = { 0x26, 0x27, 0x28, 0x34, 0x35, 0x36 };

const unsigned char speed_fast_tile_map[6] = { 0x62, 0x63, 0x64, 0x65, 0x66, 0x67 };
const unsigned char speed_fast_inactive_tile_map[6] = { 0x29, 0x2A, 0x22, 0x37, 0x38, 0x30 };

/* MOON */

#define MOON_VRAM 0xF0
#define MOON_SLEEP_VRAM 0xCE

uint8_t moon_animation_counter = 0;
uint8_t moon_sprite_index = 0;

/* STATS */

const unsigned char empty_dot_tile_map[4] = { 0x0A, 0x0B, 0x10, 0x11 };
const unsigned char full_dot_tile_map[4] = { 0x08, 0x09, 0x0E, 0x0F };

/* SCREEN */

#define SCREEN_NONE 0
#define SCREEN_SPLASH 1
#define SCREEN_FIELD 2
#define SCREEN_POND 3
#define SCREEN_GARDEN 4
#define SCREEN_STATS 5
uint8_t prev_screen = SCREEN_FIELD;
uint8_t current_screen = SCREEN_FIELD;
uint8_t next_screen = SCREEN_NONE;
uint8_t switching_screens = FALSE;
uint8_t switching_screens_counter = 0;
uint8_t switching_screens_step = 0;

uint8_t is_night = FALSE;

/* MENU */

const unsigned char menu_jar_tile_map[4] = { 0x70, 0x71, 0x72, 0x73 };
const unsigned char menu_soap_tile_map[4] = { 0x74, 0x75, 0x76, 0x77 };
const unsigned char menu_moon_tile_map[4] = { 0x78, 0x79, 0x7A, 0x7B };
const unsigned char menu_fruit_tile_map[4] = { 0x7C, 0x7D, 0x7E, 0x7F };
const unsigned char menu_stats_tile_map[4] = { 0x6C, 0x6D, 0x6E, 0x6F };

/* FRUIT */

#define FRUIT_COUNT_VRAM 0xFF

#define FRUIT_NONE 0
#define FRUIT_BLACKBERRY 1
#define FRUIT_BLUEBERRY 2
#define FRUIT_STRAWBERRY 3
uint8_t next_fruit = FRUIT_NONE;

uint8_t num_blackberries = 0;
uint8_t num_blueberries = 0;
uint8_t num_strawberries = 0;

/* HAND */

uint8_t hand_x = 100;
uint8_t hand_y = 68;
uint16_t hand_x_fractional = 100 << 8;
uint16_t hand_y_fractional = 68 << 8;
#define HAND_WIDTH 16
#define HAND_HEIGHT 16

#define HAND_VRAM_1 0
#define HAND_VRAM_2 46
uint8_t hand_vram = HAND_VRAM_1;
uint8_t hand_sprite_bank;
metasprite_t** hand_metasprites;

#define HAND_EMPTY 0
#define HAND_TICKLE 1
#define HAND_HOLD_JAR 2
#define HAND_TIP_JAR 3
#define HAND_HOLD_SOAP 4
#define HAND_HOLD_MOON 5
#define HAND_HOLD_BLACKBERRY 6
#define HAND_HOLD_BLUEBERRY 7
#define HAND_HOLD_STRAWBERRY 8
#define HAND_FEED_BLACKBERRY 9
#define HAND_FEED_BLUEBERRY 10
#define HAND_FEED_STRAWBERRY 11
#define HAND_HOLD_FLY 12
uint8_t hand_state = HAND_EMPTY;

uint8_t hand_frame = 0;
uint8_t hand_anim_counter = 0;

uint8_t jar_fullness = 0; // 0-3

/* FROG */

#define FROG_VRAM_1 96
#define FROG_VRAM_2 144

#define EMOTE_SLEEP_VRAM 0xC0
#define EMOTE_HAPPY_VRAM 0xC2
#define EMOTE_SAD_VRAM 0xC4
#define EMOTE_HUNGRY_VRAM 0xC6
#define EMOTE_TIRED_VRAM 0xC8
#define EMOTE_DIRTY_VRAM 0xCA
#define DIRT_VRAM 0xBC

uint8_t current_frog_state;
uint8_t current_frog_evo;

uint8_t frog_vram = 0;
uint8_t frog_sprite_bank;
metasprite_t** frog_metasprites;

/* FUNCTIONS */

void release_fruit(uint8_t fruit_type);
void go_screen(uint8_t new_screen);

/* ============ */
/*     FROG     */
/* ============ */

void set_frog_state_stand() {
	switch (current_frog_evo) {
		case EVO_BABY:
			frog_sprite_bank = BANK(frog_baby_stand);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_baby_stand_TILE_COUNT, frog_baby_stand_tiles);
			frog_metasprites = frog_baby_stand_metasprites;
			break;

		case EVO_CHILD:
			frog_sprite_bank = BANK(frog_child_stand);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_child_stand_TILE_COUNT, frog_child_stand_tiles);
			frog_metasprites = frog_child_stand_metasprites;
			break;

		case EVO_TEEN:
			frog_sprite_bank = BANK(frog_teen_stand);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_stand_TILE_COUNT, frog_teen_stand_tiles);
			frog_metasprites = frog_teen_stand_metasprites;
			break;

		case EVO_TEEN_TAIL:
			frog_sprite_bank = BANK(frog_teen_tail_stand);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_tail_stand_TILE_COUNT, frog_teen_tail_stand_tiles);
			frog_metasprites = frog_teen_tail_stand_metasprites;
			break;

		case EVO_TEEN_APPLE:
			frog_sprite_bank = BANK(frog_teen_apple_stand);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_apple_stand_TILE_COUNT, frog_teen_apple_stand_tiles);
			frog_metasprites = frog_teen_apple_stand_metasprites;
			break;

		case EVO_ADULT:
			frog_sprite_bank = BANK(frog_adult_stand);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_adult_stand_TILE_COUNT, frog_adult_stand_tiles);
			frog_metasprites = frog_adult_stand_metasprites;
			break;

		case EVO_AXO:
			frog_sprite_bank = BANK(frog_axo_stand);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_axo_stand_TILE_COUNT, frog_axo_stand_tiles);
			frog_metasprites = frog_axo_stand_metasprites;
			break;

		case EVO_APPLE:
			frog_sprite_bank = BANK(frog_apple_stand);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_apple_stand_TILE_COUNT, frog_apple_stand_tiles);
			frog_metasprites = frog_apple_stand_metasprites;
			break;

		case EVO_MUSH:
			frog_sprite_bank = BANK(frog_mush_stand);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_mush_stand_TILE_COUNT, frog_mush_stand_tiles);
			frog_metasprites = frog_mush_stand_metasprites;
			break;

		case EVO_DINO:
			frog_sprite_bank = BANK(frog_dino_stand);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_dino_stand_TILE_COUNT, frog_dino_stand_tiles);
			frog_metasprites = frog_dino_stand_metasprites;
			break;
	}
}

void set_frog_state_walk_left() {
	switch (current_frog_evo) {
		case EVO_BABY:
			frog_sprite_bank = BANK(frog_baby_walk_left);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_baby_walk_left_TILE_COUNT, frog_baby_walk_left_tiles);
			frog_metasprites = frog_baby_walk_left_metasprites;
			break;

		case EVO_CHILD:
			frog_sprite_bank = BANK(frog_child_walk_left);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_child_walk_left_TILE_COUNT, frog_child_walk_left_tiles);
			frog_metasprites = frog_child_walk_left_metasprites;
			break;

		case EVO_TEEN:
			frog_sprite_bank = BANK(frog_teen_walk_left);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_walk_left_TILE_COUNT, frog_teen_walk_left_tiles);
			frog_metasprites = frog_teen_walk_left_metasprites;
			break;

		case EVO_TEEN_TAIL:
			frog_sprite_bank = BANK(frog_teen_tail_walk_left);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_tail_walk_left_TILE_COUNT, frog_teen_tail_walk_left_tiles);
			frog_metasprites = frog_teen_tail_walk_left_metasprites;
			break;

		case EVO_TEEN_APPLE:
			frog_sprite_bank = BANK(frog_teen_apple_walk_left);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_apple_walk_left_TILE_COUNT, frog_teen_apple_walk_left_tiles);
			frog_metasprites = frog_teen_apple_walk_left_metasprites;
			break;

		case EVO_ADULT:
			frog_sprite_bank = BANK(frog_adult_walk_left);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_adult_walk_left_TILE_COUNT, frog_adult_walk_left_tiles);
			frog_metasprites = frog_adult_walk_left_metasprites;
			break;

		case EVO_AXO:
			frog_sprite_bank = BANK(frog_axo_walk_left);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_axo_walk_left_TILE_COUNT, frog_axo_walk_left_tiles);
			frog_metasprites = frog_axo_walk_left_metasprites;
			break;

		case EVO_APPLE:
			frog_sprite_bank = BANK(frog_apple_walk_left);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_apple_walk_left_TILE_COUNT, frog_apple_walk_left_tiles);
			frog_metasprites = frog_apple_walk_left_metasprites;
			break;

		case EVO_MUSH:
			frog_sprite_bank = BANK(frog_mush_walk_left);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_mush_walk_left_TILE_COUNT, frog_mush_walk_left_tiles);
			frog_metasprites = frog_mush_walk_left_metasprites;
			break;

		case EVO_DINO:
			frog_sprite_bank = BANK(frog_dino_walk_left);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_dino_walk_left_TILE_COUNT, frog_dino_walk_left_tiles);
			frog_metasprites = frog_dino_walk_left_metasprites;
			break;
	}
}

void set_frog_state_walk_right() {
	switch (current_frog_evo) {
		case EVO_BABY:
			frog_sprite_bank = BANK(frog_baby_walk_right);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_baby_walk_right_TILE_COUNT, frog_baby_walk_right_tiles);
			frog_metasprites = frog_baby_walk_right_metasprites;
			break;

		case EVO_CHILD:
			frog_sprite_bank = BANK(frog_child_walk_right);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_child_walk_right_TILE_COUNT, frog_child_walk_right_tiles);
			frog_metasprites = frog_child_walk_right_metasprites;
			break;

		case EVO_TEEN:
			frog_sprite_bank = BANK(frog_teen_walk_right);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_walk_right_TILE_COUNT, frog_teen_walk_right_tiles);
			frog_metasprites = frog_teen_walk_right_metasprites;
			break;

		case EVO_TEEN_TAIL:
			frog_sprite_bank = BANK(frog_teen_tail_walk_right);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_tail_walk_right_TILE_COUNT, frog_teen_tail_walk_right_tiles);
			frog_metasprites = frog_teen_tail_walk_right_metasprites;
			break;

		case EVO_TEEN_APPLE:
			frog_sprite_bank = BANK(frog_teen_apple_walk_right);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_apple_walk_right_TILE_COUNT, frog_teen_apple_walk_right_tiles);
			frog_metasprites = frog_teen_apple_walk_right_metasprites;
			break;

		case EVO_ADULT:
			frog_sprite_bank = BANK(frog_adult_walk_right);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_adult_walk_right_TILE_COUNT, frog_adult_walk_right_tiles);
			frog_metasprites = frog_adult_walk_right_metasprites;
			break;

		case EVO_AXO:
			frog_sprite_bank = BANK(frog_axo_walk_right);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_axo_walk_right_TILE_COUNT, frog_axo_walk_right_tiles);
			frog_metasprites = frog_axo_walk_right_metasprites;
			break;

		case EVO_APPLE:
			frog_sprite_bank = BANK(frog_apple_walk_right);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_apple_walk_right_TILE_COUNT, frog_apple_walk_right_tiles);
			frog_metasprites = frog_apple_walk_right_metasprites;
			break;

		case EVO_MUSH:
			frog_sprite_bank = BANK(frog_mush_walk_right);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_mush_walk_right_TILE_COUNT, frog_mush_walk_right_tiles);
			frog_metasprites = frog_mush_walk_right_metasprites;
			break;

		case EVO_DINO:
			frog_sprite_bank = BANK(frog_dino_walk_right);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_dino_walk_right_TILE_COUNT, frog_dino_walk_right_tiles);
			frog_metasprites = frog_dino_walk_right_metasprites;
			break;
	}
}

void set_frog_state_happy() {
	switch (current_frog_evo) {
		case EVO_BABY:
			frog_sprite_bank = BANK(frog_baby_happy);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_baby_happy_TILE_COUNT, frog_baby_happy_tiles);
			frog_metasprites = frog_baby_happy_metasprites;
			break;

		case EVO_CHILD:
			frog_sprite_bank = BANK(frog_child_happy);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_child_happy_TILE_COUNT, frog_child_happy_tiles);
			frog_metasprites = frog_child_happy_metasprites;
			break;

		case EVO_TEEN:
			frog_sprite_bank = BANK(frog_teen_happy);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_happy_TILE_COUNT, frog_teen_happy_tiles);
			frog_metasprites = frog_teen_happy_metasprites;
			break;

		case EVO_TEEN_TAIL:
			frog_sprite_bank = BANK(frog_teen_tail_happy);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_tail_happy_TILE_COUNT, frog_teen_tail_happy_tiles);
			frog_metasprites = frog_teen_tail_happy_metasprites;
			break;

		case EVO_TEEN_APPLE:
			frog_sprite_bank = BANK(frog_teen_apple_happy);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_apple_happy_TILE_COUNT, frog_teen_apple_happy_tiles);
			frog_metasprites = frog_teen_apple_happy_metasprites;
			break;

		case EVO_ADULT:
			frog_sprite_bank = BANK(frog_adult_happy);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_adult_happy_TILE_COUNT, frog_adult_happy_tiles);
			frog_metasprites = frog_adult_happy_metasprites;
			break;

		case EVO_AXO:
			frog_sprite_bank = BANK(frog_axo_happy);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_axo_happy_TILE_COUNT, frog_axo_happy_tiles);
			frog_metasprites = frog_axo_happy_metasprites;
			break;

		case EVO_APPLE:
			frog_sprite_bank = BANK(frog_apple_happy);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_apple_happy_TILE_COUNT, frog_apple_happy_tiles);
			frog_metasprites = frog_apple_happy_metasprites;
			break;

		case EVO_MUSH:
			frog_sprite_bank = BANK(frog_mush_happy);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_mush_happy_TILE_COUNT, frog_mush_happy_tiles);
			frog_metasprites = frog_mush_happy_metasprites;
			break;

		case EVO_DINO:
			frog_sprite_bank = BANK(frog_dino_happy);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_dino_happy_TILE_COUNT, frog_dino_happy_tiles);
			frog_metasprites = frog_dino_happy_metasprites;
			break;
	}
}

void set_frog_state_sad() {
	switch (current_frog_evo) {
		case EVO_BABY:
			frog_sprite_bank = BANK(frog_baby_sad);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_baby_sad_TILE_COUNT, frog_baby_sad_tiles);
			frog_metasprites = frog_baby_sad_metasprites;
			break;

		case EVO_CHILD:
			frog_sprite_bank = BANK(frog_child_sad);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_child_sad_TILE_COUNT, frog_child_sad_tiles);
			frog_metasprites = frog_child_sad_metasprites;
			break;

		case EVO_TEEN:
			frog_sprite_bank = BANK(frog_teen_sad);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_sad_TILE_COUNT, frog_teen_sad_tiles);
			frog_metasprites = frog_teen_sad_metasprites;
			break;

		case EVO_TEEN_TAIL:
			frog_sprite_bank = BANK(frog_teen_tail_sad);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_tail_sad_TILE_COUNT, frog_teen_tail_sad_tiles);
			frog_metasprites = frog_teen_tail_sad_metasprites;
			break;

		case EVO_TEEN_APPLE:
			frog_sprite_bank = BANK(frog_teen_apple_sad);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_apple_sad_TILE_COUNT, frog_teen_apple_sad_tiles);
			frog_metasprites = frog_teen_apple_sad_metasprites;
			break;

		case EVO_ADULT:
			frog_sprite_bank = BANK(frog_adult_sad);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_adult_sad_TILE_COUNT, frog_adult_sad_tiles);
			frog_metasprites = frog_adult_sad_metasprites;
			break;

		case EVO_AXO:
			frog_sprite_bank = BANK(frog_axo_sad);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_axo_sad_TILE_COUNT, frog_axo_sad_tiles);
			frog_metasprites = frog_axo_sad_metasprites;
			break;

		case EVO_APPLE:
			frog_sprite_bank = BANK(frog_apple_sad);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_apple_sad_TILE_COUNT, frog_apple_sad_tiles);
			frog_metasprites = frog_apple_sad_metasprites;
			break;

		case EVO_MUSH:
			frog_sprite_bank = BANK(frog_mush_sad);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_mush_sad_TILE_COUNT, frog_mush_sad_tiles);
			frog_metasprites = frog_mush_sad_metasprites;
			break;

		case EVO_DINO:
			frog_sprite_bank = BANK(frog_dino_sad);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_dino_sad_TILE_COUNT, frog_dino_sad_tiles);
			frog_metasprites = frog_dino_sad_metasprites;
			break;
	}
}

void set_frog_state_eat() {
	switch (current_frog_evo) {
		case EVO_BABY:
			frog_sprite_bank = BANK(frog_baby_eat);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_baby_eat_TILE_COUNT, frog_baby_eat_tiles);
			frog_metasprites = frog_baby_eat_metasprites;
			break;

		case EVO_CHILD:
			frog_sprite_bank = BANK(frog_child_eat);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_child_eat_TILE_COUNT, frog_child_eat_tiles);
			frog_metasprites = frog_child_eat_metasprites;
			break;

		case EVO_TEEN:
			frog_sprite_bank = BANK(frog_teen_eat);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_eat_TILE_COUNT, frog_teen_eat_tiles);
			frog_metasprites = frog_teen_eat_metasprites;
			break;

		case EVO_TEEN_TAIL:
			frog_sprite_bank = BANK(frog_teen_tail_eat);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_tail_eat_TILE_COUNT, frog_teen_tail_eat_tiles);
			frog_metasprites = frog_teen_tail_eat_metasprites;
			break;

		case EVO_TEEN_APPLE:
			frog_sprite_bank = BANK(frog_teen_apple_eat);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_apple_eat_TILE_COUNT, frog_teen_apple_eat_tiles);
			frog_metasprites = frog_teen_apple_eat_metasprites;
			break;

		case EVO_ADULT:
			frog_sprite_bank = BANK(frog_adult_eat);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_adult_eat_TILE_COUNT, frog_adult_eat_tiles);
			frog_metasprites = frog_adult_eat_metasprites;
			break;

		case EVO_AXO:
			frog_sprite_bank = BANK(frog_axo_eat);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_axo_eat_TILE_COUNT, frog_axo_eat_tiles);
			frog_metasprites = frog_axo_eat_metasprites;
			break;

		case EVO_APPLE:
			frog_sprite_bank = BANK(frog_apple_eat);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_apple_eat_TILE_COUNT, frog_apple_eat_tiles);
			frog_metasprites = frog_apple_eat_metasprites;
			break;

		case EVO_MUSH:
			frog_sprite_bank = BANK(frog_mush_eat);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_mush_eat_TILE_COUNT, frog_mush_eat_tiles);
			frog_metasprites = frog_mush_eat_metasprites;
			break;

		case EVO_DINO:
			frog_sprite_bank = BANK(frog_dino_eat);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_dino_eat_TILE_COUNT, frog_dino_eat_tiles);
			frog_metasprites = frog_dino_eat_metasprites;
			break;
	}
}

void set_frog_state_tickled() {
	switch (current_frog_evo) {
		case EVO_BABY:
			frog_sprite_bank = BANK(frog_baby_tickled);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_baby_tickled_TILE_COUNT, frog_baby_tickled_tiles);
			frog_metasprites = frog_baby_tickled_metasprites;
			break;

		case EVO_CHILD:
			frog_sprite_bank = BANK(frog_child_tickled);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_child_tickled_TILE_COUNT, frog_child_tickled_tiles);
			frog_metasprites = frog_child_tickled_metasprites;
			break;

		case EVO_TEEN:
			frog_sprite_bank = BANK(frog_teen_tickled);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_tickled_TILE_COUNT, frog_teen_tickled_tiles);
			frog_metasprites = frog_teen_tickled_metasprites;
			break;

		case EVO_TEEN_TAIL:
			frog_sprite_bank = BANK(frog_teen_tail_tickled);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_tail_tickled_TILE_COUNT, frog_teen_tail_tickled_tiles);
			frog_metasprites = frog_teen_tail_tickled_metasprites;
			break;

		case EVO_TEEN_APPLE:
			frog_sprite_bank = BANK(frog_teen_apple_tickled);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_apple_tickled_TILE_COUNT, frog_teen_apple_tickled_tiles);
			frog_metasprites = frog_teen_apple_tickled_metasprites;
			break;

		case EVO_ADULT:
			frog_sprite_bank = BANK(frog_adult_tickled);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_adult_tickled_TILE_COUNT, frog_adult_tickled_tiles);
			frog_metasprites = frog_adult_tickled_metasprites;
			break;

		case EVO_AXO:
			frog_sprite_bank = BANK(frog_axo_tickled);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_axo_tickled_TILE_COUNT, frog_axo_tickled_tiles);
			frog_metasprites = frog_axo_tickled_metasprites;
			break;

		case EVO_APPLE:
			frog_sprite_bank = BANK(frog_apple_tickled);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_apple_tickled_TILE_COUNT, frog_apple_tickled_tiles);
			frog_metasprites = frog_apple_tickled_metasprites;
			break;

		case EVO_MUSH:
			frog_sprite_bank = BANK(frog_mush_tickled);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_mush_tickled_TILE_COUNT, frog_mush_tickled_tiles);
			frog_metasprites = frog_mush_tickled_metasprites;
			break;

		case EVO_DINO:
			frog_sprite_bank = BANK(frog_dino_tickled);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_dino_tickled_TILE_COUNT, frog_dino_tickled_tiles);
			frog_metasprites = frog_dino_tickled_metasprites;
			break;
	}
}

void set_frog_state_sleep() {
	switch (current_frog_evo) {
		case EVO_BABY:
			frog_sprite_bank = BANK(frog_baby_sleep);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_baby_sleep_TILE_COUNT, frog_baby_sleep_tiles);
			frog_metasprites = frog_baby_sleep_metasprites;
			break;

		case EVO_CHILD:
			frog_sprite_bank = BANK(frog_child_sleep);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_child_sleep_TILE_COUNT, frog_child_sleep_tiles);
			frog_metasprites = frog_child_sleep_metasprites;
			break;

		case EVO_TEEN:
			frog_sprite_bank = BANK(frog_teen_sleep);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_sleep_TILE_COUNT, frog_teen_sleep_tiles);
			frog_metasprites = frog_teen_sleep_metasprites;
			break;

		case EVO_TEEN_TAIL:
			frog_sprite_bank = BANK(frog_teen_tail_sleep);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_tail_sleep_TILE_COUNT, frog_teen_tail_sleep_tiles);
			frog_metasprites = frog_teen_tail_sleep_metasprites;
			break;

		case EVO_TEEN_APPLE:
			frog_sprite_bank = BANK(frog_teen_apple_sleep);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_apple_sleep_TILE_COUNT, frog_teen_apple_sleep_tiles);
			frog_metasprites = frog_teen_apple_sleep_metasprites;
			break;

		case EVO_ADULT:
			frog_sprite_bank = BANK(frog_adult_sleep);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_adult_sleep_TILE_COUNT, frog_adult_sleep_tiles);
			frog_metasprites = frog_adult_sleep_metasprites;
			break;

		case EVO_AXO:
			frog_sprite_bank = BANK(frog_axo_sleep);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_axo_sleep_TILE_COUNT, frog_axo_sleep_tiles);
			frog_metasprites = frog_axo_sleep_metasprites;
			break;

		case EVO_APPLE:
			frog_sprite_bank = BANK(frog_apple_sleep);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_apple_sleep_TILE_COUNT, frog_apple_sleep_tiles);
			frog_metasprites = frog_apple_sleep_metasprites;
			break;

		case EVO_MUSH:
			frog_sprite_bank = BANK(frog_mush_sleep);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_mush_sleep_TILE_COUNT, frog_mush_sleep_tiles);
			frog_metasprites = frog_mush_sleep_metasprites;
			break;

		case EVO_DINO:
			frog_sprite_bank = BANK(frog_dino_sleep);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_dino_sleep_TILE_COUNT, frog_dino_sleep_tiles);
			frog_metasprites = frog_dino_sleep_metasprites;
			break;
	}
}

void set_frog_state_wash() {
	switch (current_frog_evo) {
		case EVO_BABY:
			frog_sprite_bank = BANK(frog_baby_wash);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_baby_wash_TILE_COUNT, frog_baby_wash_tiles);
			frog_metasprites = frog_baby_wash_metasprites;
			break;

		case EVO_CHILD:
			frog_sprite_bank = BANK(frog_child_wash);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_child_wash_TILE_COUNT, frog_child_wash_tiles);
			frog_metasprites = frog_child_wash_metasprites;
			break;

		case EVO_TEEN:
			frog_sprite_bank = BANK(frog_teen_wash);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_wash_TILE_COUNT, frog_teen_wash_tiles);
			frog_metasprites = frog_teen_wash_metasprites;
			break;

		case EVO_TEEN_TAIL:
			frog_sprite_bank = BANK(frog_teen_tail_wash);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_tail_wash_TILE_COUNT, frog_teen_tail_wash_tiles);
			frog_metasprites = frog_teen_tail_wash_metasprites;
			break;

		case EVO_TEEN_APPLE:
			frog_sprite_bank = BANK(frog_teen_apple_wash);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_teen_apple_wash_TILE_COUNT, frog_teen_apple_wash_tiles);
			frog_metasprites = frog_teen_apple_wash_metasprites;
			break;

		case EVO_ADULT:
			frog_sprite_bank = BANK(frog_adult_wash);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_adult_wash_TILE_COUNT, frog_adult_wash_tiles);
			frog_metasprites = frog_adult_wash_metasprites;
			break;

		case EVO_AXO:
			frog_sprite_bank = BANK(frog_axo_wash);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_axo_wash_TILE_COUNT, frog_axo_wash_tiles);
			frog_metasprites = frog_axo_wash_metasprites;
			break;

		case EVO_APPLE:
			frog_sprite_bank = BANK(frog_apple_wash);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_apple_wash_TILE_COUNT, frog_apple_wash_tiles);
			frog_metasprites = frog_apple_wash_metasprites;
			break;

		case EVO_MUSH:
			frog_sprite_bank = BANK(frog_mush_wash);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_mush_wash_TILE_COUNT, frog_mush_wash_tiles);
			frog_metasprites = frog_mush_wash_metasprites;
			break;

		case EVO_DINO:
			frog_sprite_bank = BANK(frog_dino_wash);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, frog_dino_wash_TILE_COUNT, frog_dino_wash_tiles);
			frog_metasprites = frog_dino_wash_metasprites;
			break;
	}
}

void set_frog_egg() {
	frog_sprite_bank = BANK(egg);
	SWITCH_ROM(frog_sprite_bank);
	set_sprite_data(frog_vram, egg_TILE_COUNT, egg_tiles);
	frog_metasprites = egg_metasprites;
}

void set_frog_state(uint8_t new_state) {
	current_frog_state = new_state;

	if (frog_vram == FROG_VRAM_1) {
		frog_vram = FROG_VRAM_2;
	} else {
		frog_vram = FROG_VRAM_1;
	}

	if (current_frog_state == FROG_EVOLVING) {
		SWITCH_ROM(BANK(frog_code));
		frog_anim_speed = 24;
		if (current_frog_evo != EVO_EGG) {
			set_frog_state_stand();
		} else {
			set_frog_egg();
			return;
		}

	} else if (current_frog_evo == EVO_EGG) {
		set_frog_egg();
		SWITCH_ROM(BANK(frog_code));
		frog_anim_speed = 32;
		return;

	} else {

		switch (current_frog_state) {
			case FROG_STAND:
				set_frog_state_stand();
				SWITCH_ROM(BANK(frog_code));
				frog_anim_speed = 32;
				break;

			case FROG_WALK_LEFT:
				set_frog_state_walk_left();
				SWITCH_ROM(BANK(frog_code));
				frog_anim_speed = 24;
				break;

			case FROG_WALK_RIGHT:
				set_frog_state_walk_right();
				SWITCH_ROM(BANK(frog_code));
				frog_anim_speed = 24;
				break;

			case FROG_HAPPY:
				set_frog_state_happy();
				SWITCH_ROM(BANK(frog_code));
				frog_anim_speed = 32;
				break;

			case FROG_SAD:
				set_frog_state_sad();
				SWITCH_ROM(BANK(frog_code));
				frog_anim_speed = 40;
				break;

			case FROG_EAT:
				set_frog_state_eat();
				SWITCH_ROM(BANK(frog_code));
				frog_anim_speed = 24;
				break;

			case FROG_TICKLED:
				set_frog_state_tickled();
				SWITCH_ROM(BANK(frog_code));
				frog_anim_speed = 32;
				break;

			case FROG_SLEEP:
				set_frog_state_sleep();
				SWITCH_ROM(BANK(frog_code));
				frog_anim_speed = 56;
				break;

			case FROG_WASH:
				set_frog_state_wash();
				SWITCH_ROM(BANK(frog_code));
				frog_anim_speed = 24;
				break;
		}

	}

	hide_sprites_range(frog_vram, MAX_HARDWARE_SPRITES);
}

void draw_frog() {
	SWITCH_ROM(BANK(frog_code));
	uint8_t x = frog_x;
	uint8_t y = frog_y;
	uint8_t anim_frame = frog_anim_frame;
	current_frog_evo = frog_evo;
	if (current_frog_state != frog_state) {
		set_frog_state(frog_state);
	}

	SWITCH_ROM(BANK(frog_code));

	if (frog_state == FROG_EVOLVING) {
		if (frog_anim_frame == 1) {
			BGP_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_DARK_GRAY, DMG_DARK_GRAY, DMG_DARK_GRAY);
		} else {
			BGP_REG = DMG_PALETTE(DMG_LITE_GRAY, DMG_LITE_GRAY, DMG_LITE_GRAY, DMG_LITE_GRAY);
			if (frog_anim_speed > 16) {
				frog_anim_speed -= 2;
			}
		}
		if (frog_anim_loops == 2) {
			HIDE_SPRITES;
		}
	}

	if (show_emote) {
		if (frog_state == FROG_HAPPY) {
			SWITCH_ROM(BANK(emote_happy));
			last_used_sprite += move_metasprite(emote_happy_metasprites[anim_frame], EMOTE_HAPPY_VRAM, last_used_sprite, x - 12, y - 12);
		} else if (frog_state == FROG_SAD) {
			if (full <= 4) {
				SWITCH_ROM(BANK(emote_hungry));
				last_used_sprite += move_metasprite(emote_hungry_metasprites[anim_frame], EMOTE_HUNGRY_VRAM, last_used_sprite, x - 20, y + 12);
			} else if (clean <= 4) {
				SWITCH_ROM(BANK(emote_dirty));
				last_used_sprite += move_metasprite(emote_dirty_metasprites[anim_frame], EMOTE_DIRTY_VRAM, last_used_sprite, x - 12, y - 4);
			} else if (energy <= 4) {
				SWITCH_ROM(BANK(emote_tired));
				last_used_sprite += move_metasprite(emote_tired_metasprites[anim_frame], EMOTE_TIRED_VRAM, last_used_sprite, x - 12, y - 4);
			} else if (happy <= 4) {
				SWITCH_ROM(BANK(emote_sad));
				last_used_sprite += move_metasprite(emote_sad_metasprites[anim_frame], EMOTE_SAD_VRAM, last_used_sprite, x - 12, y - 4);
			}
		} else if (frog_state == FROG_SLEEP) {
			SWITCH_ROM(BANK(emote_sleep));
			last_used_sprite += move_metasprite(emote_sleep_metasprites[!anim_frame], EMOTE_SLEEP_VRAM, last_used_sprite, x - 12, y - 12);
		}
	}

	if (clean <= 4 && current_frog_state != FROG_EVOLVING) {
		SWITCH_ROM(BANK(dirt));
		last_used_sprite += move_metasprite(dirt_metasprites[0 + anim_frame], DIRT_VRAM, last_used_sprite, x - 4, y + 12);
		last_used_sprite += move_metasprite(dirt_metasprites[2 + anim_frame], DIRT_VRAM, last_used_sprite, x - 12, y + 12);
		last_used_sprite += move_metasprite_hflip(dirt_metasprites[0 + anim_frame], DIRT_VRAM, last_used_sprite, x + 12, y + 12);
	}

	SWITCH_ROM(frog_sprite_bank);
	last_used_sprite += move_metasprite(frog_metasprites[anim_frame], frog_vram, last_used_sprite, x, y);
}

void setup_frog() {
	SWITCH_ROM(BANK(frog_code));
	current_frog_evo = frog_evo;
	current_frog_state = frog_state;
	set_frog_state(current_frog_state);

	SWITCH_ROM(BANK(emote_sleep));
	set_sprite_data(EMOTE_SLEEP_VRAM, emote_sleep_TILE_COUNT, emote_sleep_tiles);

	SWITCH_ROM(BANK(emote_happy));
	set_sprite_data(EMOTE_HAPPY_VRAM, emote_happy_TILE_COUNT, emote_happy_tiles);

	SWITCH_ROM(BANK(emote_sad));
	set_sprite_data(EMOTE_SAD_VRAM, emote_sad_TILE_COUNT, emote_sad_tiles);

	SWITCH_ROM(BANK(emote_hungry));
	set_sprite_data(EMOTE_HUNGRY_VRAM, emote_hungry_TILE_COUNT, emote_hungry_tiles);

	SWITCH_ROM(BANK(emote_tired));
	set_sprite_data(EMOTE_TIRED_VRAM, emote_tired_TILE_COUNT, emote_tired_tiles);

	SWITCH_ROM(BANK(emote_dirty));
	set_sprite_data(EMOTE_DIRTY_VRAM, emote_dirty_TILE_COUNT, emote_dirty_tiles);

	SWITCH_ROM(BANK(dirt));
	set_sprite_data(DIRT_VRAM, dirt_TILE_COUNT, dirt_tiles);
}

/* ============ */
/*     HAND     */
/* ============ */

void set_hand_state(uint8_t new_hand_state) {
	if (hand_vram == HAND_VRAM_1) {
		hand_vram = HAND_VRAM_2;
	} else {
		hand_vram = HAND_VRAM_1;
	}

	switch (new_hand_state) {
		case HAND_EMPTY:
			hand_sprite_bank = BANK(hand_normal);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_normal_TILE_COUNT, hand_normal_tiles);
			hand_metasprites = hand_normal_metasprites;
			break;

		case HAND_TICKLE:
			if (hand_state != HAND_TICKLE) {
				hand_frame = 0;
			}
			if (hand_frame == 0) {
				hand_frame = 1;
				hand_sprite_bank = BANK(hand_tickle_1);
				SWITCH_ROM(hand_sprite_bank);
				set_sprite_data(hand_vram, hand_tickle_1_TILE_COUNT, hand_tickle_1_tiles);
				hand_metasprites = hand_tickle_1_metasprites;
			} else {
				hand_frame = 0;
				hand_sprite_bank = BANK(hand_tickle_2);
				SWITCH_ROM(hand_sprite_bank);
				set_sprite_data(hand_vram, hand_tickle_2_TILE_COUNT, hand_tickle_2_tiles);
				hand_metasprites = hand_tickle_2_metasprites;
			}
			break;

		case HAND_HOLD_JAR:
			switch (jar_fullness) {
				case 0:
					hand_sprite_bank = BANK(hand_jar_empty);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, hand_jar_empty_TILE_COUNT, hand_jar_empty_tiles);
					hand_metasprites = hand_jar_empty_metasprites;
					break;

				case 1:
					hand_sprite_bank = BANK(hand_jar_1_3);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, hand_jar_1_3_TILE_COUNT, hand_jar_1_3_tiles);
					hand_metasprites = hand_jar_1_3_metasprites;
					break;

				case 2:
					hand_sprite_bank = BANK(hand_jar_2_3);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, hand_jar_2_3_TILE_COUNT, hand_jar_2_3_tiles);
					hand_metasprites = hand_jar_2_3_metasprites;
					break;

				case 3:
					hand_sprite_bank = BANK(hand_jar_full);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, hand_jar_full_TILE_COUNT, hand_jar_full_tiles);
					hand_metasprites = hand_jar_full_metasprites;
					break;
			}
			break;

		case HAND_TIP_JAR:
			if (hand_state != HAND_TIP_JAR) {
				hand_anim_counter = 0;
			}
			switch (jar_fullness) {
				case 0:
					hand_sprite_bank = BANK(hand_jar_empty_tip);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, hand_jar_empty_tip_TILE_COUNT, hand_jar_empty_tip_tiles);
					hand_metasprites = hand_jar_empty_tip_metasprites;
					break;

				case 1:
					hand_sprite_bank = BANK(hand_jar_1_3_tip);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, hand_jar_1_3_tip_TILE_COUNT, hand_jar_1_3_tip_tiles);
					hand_metasprites = hand_jar_1_3_tip_metasprites;
					break;

				case 2:
					hand_sprite_bank = BANK(hand_jar_2_3_tip);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, hand_jar_2_3_tip_TILE_COUNT, hand_jar_2_3_tip_tiles);
					hand_metasprites = hand_jar_2_3_tip_metasprites;
					break;

				case 3:
					hand_sprite_bank = BANK(hand_jar_full_tip);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, hand_jar_full_tip_TILE_COUNT, hand_jar_full_tip_tiles);
					hand_metasprites = hand_jar_full_tip_metasprites;
					break;
			}
			break;

		case HAND_HOLD_SOAP:
			hand_sprite_bank = BANK(hand_soap);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_soap_TILE_COUNT, hand_soap_tiles);
			hand_metasprites = hand_soap_metasprites;
			break;

		case HAND_HOLD_MOON:
			hand_sprite_bank = BANK(hand_moon);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_moon_TILE_COUNT, hand_moon_tiles);
			hand_metasprites = hand_moon_metasprites;
			break;

		case HAND_HOLD_BLACKBERRY:
			hand_sprite_bank = BANK(hand_blackberry);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_blackberry_TILE_COUNT, hand_blackberry_tiles);
			hand_metasprites = hand_blackberry_metasprites;
			break;

		case HAND_HOLD_BLUEBERRY:
			hand_sprite_bank = BANK(hand_blueberry);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_blueberry_TILE_COUNT, hand_blueberry_tiles);
			hand_metasprites = hand_blueberry_metasprites;
			break;

		case HAND_HOLD_STRAWBERRY:
			hand_sprite_bank = BANK(hand_strawberry);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_strawberry_TILE_COUNT, hand_strawberry_tiles);
			hand_metasprites = hand_strawberry_metasprites;
			break;

		case HAND_FEED_BLACKBERRY:
			if (hand_state != HAND_FEED_BLACKBERRY) {
				hand_frame = 0;
				hand_anim_counter = 0;
			}
			switch (hand_frame) {
				case 0:
					hand_sprite_bank = BANK(fruit_blackberry_1);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, fruit_blackberry_1_TILE_COUNT, fruit_blackberry_1_tiles);
					hand_metasprites = fruit_blackberry_1_metasprites;
					break;

				case 1:
					hand_sprite_bank = BANK(fruit_blackberry_2);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, fruit_blackberry_2_TILE_COUNT, fruit_blackberry_2_tiles);
					hand_metasprites = fruit_blackberry_2_metasprites;
					break;

				case 2:
					hand_sprite_bank = BANK(fruit_blackberry_3);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, fruit_blackberry_3_TILE_COUNT, fruit_blackberry_3_tiles);
					hand_metasprites = fruit_blackberry_3_metasprites;
					break;
			}
			break;

		case HAND_FEED_BLUEBERRY:
			if (hand_state != HAND_FEED_BLUEBERRY) {
				hand_frame = 0;
				hand_anim_counter = 0;
			}
			switch (hand_frame) {
				case 0:
					hand_sprite_bank = BANK(fruit_blueberry_1);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, fruit_blueberry_1_TILE_COUNT, fruit_blueberry_1_tiles);
					hand_metasprites = fruit_blueberry_1_metasprites;
					break;

				case 1:
					hand_sprite_bank = BANK(fruit_blueberry_2);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, fruit_blueberry_2_TILE_COUNT, fruit_blueberry_2_tiles);
					hand_metasprites = fruit_blueberry_2_metasprites;
					break;

				case 2:
					hand_sprite_bank = BANK(fruit_blueberry_3);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, fruit_blueberry_3_TILE_COUNT, fruit_blueberry_3_tiles);
					hand_metasprites = fruit_blueberry_3_metasprites;
					break;
			}
			break;

		case HAND_FEED_STRAWBERRY:
			if (hand_state != HAND_FEED_STRAWBERRY) {
				hand_frame = 0;
				hand_anim_counter = 0;
			}
			switch (hand_frame) {
				case 0:
					hand_sprite_bank = BANK(fruit_strawberry_1);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, fruit_strawberry_1_TILE_COUNT, fruit_strawberry_1_tiles);
					hand_metasprites = fruit_strawberry_1_metasprites;
					break;

				case 1:
					hand_sprite_bank = BANK(fruit_strawberry_2);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, fruit_strawberry_2_TILE_COUNT, fruit_strawberry_2_tiles);
					hand_metasprites = fruit_strawberry_2_metasprites;
					break;

				case 2:
					hand_sprite_bank = BANK(fruit_strawberry_3);
					SWITCH_ROM(hand_sprite_bank);
					set_sprite_data(hand_vram, fruit_strawberry_3_TILE_COUNT, fruit_strawberry_3_tiles);
					hand_metasprites = fruit_strawberry_3_metasprites;
					break;
			}
			break;

		case HAND_HOLD_FLY:
			hand_sprite_bank = BANK(hand_fly);
			SWITCH_ROM(hand_sprite_bank);
			set_sprite_data(hand_vram, hand_fly_TILE_COUNT, hand_fly_tiles);
			hand_metasprites = hand_fly_metasprites;
			break;
	}

	hand_state = new_hand_state;
}

void animate_jar() {
	hand_anim_counter += 1;
	if (hand_anim_counter > 52) {
		hand_anim_counter = 0;
		if (current_screen == SCREEN_POND) {
			jar_fullness = 3;
			set_hand_state(HAND_HOLD_JAR);
			save_item(DATA_JAR_FULLNESS, jar_fullness);
		} else if (hand_state == HAND_TIP_JAR) {
			if (jar_fullness > 0) {
				jar_fullness -= 1;
			}
			set_hand_state(HAND_HOLD_JAR);
			save_item(DATA_JAR_FULLNESS, jar_fullness);
		}
	}
}

void draw_hand() {
	switch (hand_state) {
		case HAND_TIP_JAR:
			animate_jar();
			break;
	}

	uint8_t frog_left = frog_x - 16; // adjust for pivot to find left edge
	uint8_t hand_left = hand_x - 12;

	uint8_t hand_offset = 0;
	uint8_t frog_mod = frog_left % 8;
	uint8_t hand_mod = hand_left % 8;
	if (frog_mod > hand_mod) {
		hand_offset = (hand_mod + 8) - frog_mod;
	} else {
		hand_offset = hand_mod - frog_mod;
	}
	hand_left -= hand_offset;

	SWITCH_ROM(hand_sprite_bank);
	last_used_sprite += move_metasprite(hand_metasprites[hand_offset], hand_vram, last_used_sprite, hand_left + 12, hand_y);
}

uint8_t hand_intersects(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
	if (hand_x - 12 <= x + w && hand_x + 4 >= x && hand_y - 8 <= y + h && hand_y + 8 >= y) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void move_hand(int16_t dx_fractional, int16_t dy_fractional) {
	hand_x_fractional += dx_fractional;
	hand_y_fractional += dy_fractional;

	if (hand_y_fractional < 6144) { // 24 -> Q8.8
		hand_y_fractional = 6144;
	} else if (hand_y_fractional > 38912) { // 152 -> Q8.8
		hand_y_fractional = 38912;
	}

	if (hand_x_fractional < 3072) { // 12 -> Q8.8
		switch (current_screen) {
			case SCREEN_FIELD:
				hand_x_fractional = 44032;
				go_screen(SCREEN_POND);
				break;
			case SCREEN_GARDEN:
				hand_x_fractional = 44032;
				go_screen(SCREEN_FIELD);
				break;
			default:
				hand_x_fractional = 3072;
		}
	} else if (hand_x_fractional > 44032) { // 172 -> Q8.8
		switch (current_screen) {
			case SCREEN_POND:
				hand_x_fractional = 3072;
				go_screen(SCREEN_FIELD);
				break;
			case SCREEN_FIELD:
				hand_x_fractional = 3072;
				go_screen(SCREEN_GARDEN);
				break;
			default:
				hand_x_fractional = 44032;
		}
	}

	hand_x = hand_x_fractional >> 8;
	hand_y = hand_y_fractional >> 8;
}

void release_item() {
	switch (hand_state) {
		case HAND_HOLD_BLACKBERRY:
			release_fruit(FRUIT_BLACKBERRY);
			break;

		case HAND_HOLD_BLUEBERRY:
			release_fruit(FRUIT_BLUEBERRY);
			break;

		case HAND_HOLD_STRAWBERRY:
			release_fruit(FRUIT_STRAWBERRY);
			break;

		case HAND_HOLD_FLY:
			release_fly(hand_x, hand_y);
			break;
	}
}

/* ============ */
/*     MENU     */
/* ============ */

void get_next_fruit(uint8_t last_fruit) {
	switch (last_fruit) {
		case FRUIT_BLACKBERRY:
			if (num_blueberries > 0) {
				next_fruit = FRUIT_BLUEBERRY;
			} else if (num_strawberries > 0) {
				next_fruit = FRUIT_STRAWBERRY;
			} else if (num_blackberries > 0) {
				next_fruit = FRUIT_BLACKBERRY;
			} else {
				next_fruit = FRUIT_NONE;
			}
			break;

		case FRUIT_BLUEBERRY:
			if (num_strawberries > 0) {
				next_fruit = FRUIT_STRAWBERRY;
			} else if (num_blackberries > 0) {
				next_fruit = FRUIT_BLACKBERRY;
			} else if (num_blueberries > 0) {
				next_fruit = FRUIT_BLUEBERRY;
			} else {
				next_fruit = FRUIT_NONE;
			}
			break;

		case FRUIT_STRAWBERRY:
			if (num_blackberries > 0) {
				next_fruit = FRUIT_BLACKBERRY;
			} else if (num_blueberries > 0) {
				next_fruit = FRUIT_BLUEBERRY;
			} else if (num_strawberries > 0) {
				next_fruit = FRUIT_STRAWBERRY;
			} else {
				next_fruit = FRUIT_NONE;
			}
			break;
	}
}

void release_fruit(uint8_t fruit_type) {
	switch (fruit_type) {
		case FRUIT_BLACKBERRY:
			num_blackberries += 1;
			next_fruit = FRUIT_BLACKBERRY;
			break;

		case FRUIT_BLUEBERRY:
			num_blueberries += 1;
			next_fruit = FRUIT_BLUEBERRY;
			break;

		case FRUIT_STRAWBERRY:
			num_strawberries += 1;
			next_fruit = FRUIT_STRAWBERRY;
			break;
	}
}

void draw_menu_jar() {
	if (hand_state == HAND_HOLD_JAR) {
		SWITCH_ROM(BANK(menu_jar_outline));
		set_bkg_data(0x70, menu_jar_outline_TILE_COUNT, menu_jar_outline_tiles);
		set_bkg_tiles(1, 15, 2, 2, menu_jar_tile_map);
	} else {
		switch (jar_fullness) {
			case 0:
				SWITCH_ROM(BANK(menu_jar_empty));
				set_bkg_data(0x70, menu_jar_empty_TILE_COUNT, menu_jar_empty_tiles);
				set_bkg_tiles(1, 15, 2, 2, menu_jar_tile_map);
				break;

			case 1:
				SWITCH_ROM(BANK(menu_jar_1_3));
				set_bkg_data(0x70, menu_jar_1_3_TILE_COUNT, menu_jar_1_3_tiles);
				set_bkg_tiles(1, 15, 2, 2, menu_jar_tile_map);
				break;

			case 2:
				SWITCH_ROM(BANK(menu_jar_2_3));
				set_bkg_data(0x70, menu_jar_2_3_TILE_COUNT, menu_jar_2_3_tiles);
				set_bkg_tiles(1, 15, 2, 2, menu_jar_tile_map);
				break;

			case 3:
				SWITCH_ROM(BANK(menu_jar_full));
				set_bkg_data(0x70, menu_jar_full_TILE_COUNT, menu_jar_full_tiles);
				set_bkg_tiles(1, 15, 2, 2, menu_jar_tile_map);
				break;
		}
	}
}

void draw_menu_soap() {
	if (hand_state == HAND_HOLD_SOAP) {
		SWITCH_ROM(BANK(menu_soap_outline));
		set_bkg_data(0x74, menu_soap_outline_TILE_COUNT, menu_soap_outline_tiles);
		set_bkg_tiles(5, 15, 2, 2, menu_soap_tile_map);
	} else {
		SWITCH_ROM(BANK(menu_soap));
		set_bkg_data(0x74, menu_soap_TILE_COUNT, menu_soap_tiles);
		set_bkg_tiles(5, 15, 2, 2, menu_soap_tile_map);
	}
}

void draw_menu_moon() {
	if (hand_state == HAND_HOLD_MOON || is_night) {
		SWITCH_ROM(BANK(menu_moon_outline));
		set_bkg_data(0x78, menu_moon_outline_TILE_COUNT, menu_moon_outline_tiles);
		set_bkg_tiles(9, 15, 2, 2, menu_moon_tile_map);
	} else {
		SWITCH_ROM(BANK(menu_moon));
		set_bkg_data(0x78, menu_moon_TILE_COUNT, menu_moon_tiles);
		set_bkg_tiles(9, 15, 2, 2, menu_moon_tile_map);
	}
}

void draw_menu_fruit() {
	switch (next_fruit) {
		case FRUIT_NONE:
			SWITCH_ROM(BANK(menu_fruit_outline));
			set_bkg_data(0x7C, menu_fruit_outline_TILE_COUNT, menu_fruit_outline_tiles);
			set_bkg_tiles(13, 15, 2, 2, menu_fruit_tile_map);
			break;

		case FRUIT_BLACKBERRY:
			SWITCH_ROM(BANK(menu_fruit_blackberry));
			set_bkg_data(0x7C, menu_fruit_blackberry_TILE_COUNT, menu_fruit_blackberry_tiles);
			set_bkg_tiles(13, 15, 2, 2, menu_fruit_tile_map);
			break;

		case FRUIT_BLUEBERRY:
			SWITCH_ROM(BANK(menu_fruit_blueberry));
			set_bkg_data(0x7C, menu_fruit_blueberry_TILE_COUNT, menu_fruit_blueberry_tiles);
			set_bkg_tiles(13, 15, 2, 2, menu_fruit_tile_map);
			break;

		case FRUIT_STRAWBERRY:
			SWITCH_ROM(BANK(menu_fruit_strawberry));
			set_bkg_data(0x7C, menu_fruit_strawberry_TILE_COUNT, menu_fruit_strawberry_tiles);
			set_bkg_tiles(13, 15, 2, 2, menu_fruit_tile_map);
			break;
	}

	switch (num_blackberries + num_blueberries + num_strawberries) {
		case 2:
			SWITCH_ROM(BANK(fruit_count_2));
			set_bkg_data(FRUIT_COUNT_VRAM, 1, fruit_count_2_tiles);
			set_bkg_tile_xy(0x0F, 0x11, FRUIT_COUNT_VRAM);
			break;

		case 3:
			SWITCH_ROM(BANK(fruit_count_3));
			set_bkg_data(FRUIT_COUNT_VRAM, 1, fruit_count_3_tiles);
			set_bkg_tile_xy(0x0F, 0x11, FRUIT_COUNT_VRAM);
			break;

		case 4:
			SWITCH_ROM(BANK(fruit_count_4));
			set_bkg_data(FRUIT_COUNT_VRAM, 1, fruit_count_4_tiles);
			set_bkg_tile_xy(0x0F, 0x11, FRUIT_COUNT_VRAM);
			break;

		case 5:
			SWITCH_ROM(BANK(fruit_count_5));
			set_bkg_data(FRUIT_COUNT_VRAM, 1, fruit_count_5_tiles);
			set_bkg_tile_xy(0x0F, 0x11, FRUIT_COUNT_VRAM);
			break;

		case 6:
			SWITCH_ROM(BANK(fruit_count_6));
			set_bkg_data(FRUIT_COUNT_VRAM, 1, fruit_count_6_tiles);
			set_bkg_tile_xy(0x0F, 0x11, FRUIT_COUNT_VRAM);
			break;

		default:
			SWITCH_ROM(BANK(fruit_count_1));
			set_bkg_data(FRUIT_COUNT_VRAM, 1, fruit_count_1_tiles);
			set_bkg_tile_xy(0x0F, 0x11, FRUIT_COUNT_VRAM);
	}
}

void draw_menu_stats() {
	SWITCH_ROM(BANK(menu_stats));
	set_bkg_data(0x6C, menu_stats_TILE_COUNT, menu_stats_tiles);
	set_bkg_tiles(17, 15, 2, 2, menu_stats_tile_map);
}

void draw_menu() {
	draw_menu_jar();
	draw_menu_soap();
	draw_menu_moon();
	draw_menu_fruit();
	draw_menu_stats();
}

/* ============= */
/*     FIELD     */
/* ============= */

void put_moon_in_sky() {
	moon_sprite_index = 0;

	SWITCH_ROM(BANK(moon));
	set_sprite_data(MOON_VRAM, moon_TILE_COUNT, moon_tiles);

	SWITCH_ROM(BANK(moon_sleep));
	set_sprite_data(MOON_SLEEP_VRAM, moon_sleep_TILE_COUNT, moon_sleep_tiles);
}

void draw_field() {
	if (is_night) {
		moon_animation_counter += 1;
		if (moon_animation_counter > 52) {
			moon_animation_counter = 0;
			moon_sprite_index += 1;
			if (moon_sprite_index > 4) {
				moon_sprite_index = 3;
			}
		}

		SWITCH_ROM(BANK(moon));
		last_used_sprite += move_metasprite(moon_metasprites[moon_sprite_index], MOON_VRAM, last_used_sprite, 88, 32);

		if (moon_sprite_index >= 3) {
			SWITCH_ROM(BANK(moon_sleep));
			last_used_sprite += move_metasprite(moon_sleep_metasprites[moon_sprite_index - 3], MOON_SLEEP_VRAM, last_used_sprite, 100, 22);
		}
	}
}

void draw_field_bg() {
	if (is_night) {
		SWITCH_ROM(BANK(bg_field_night));
		set_bkg_data(0, bg_field_night_TILE_COUNT, bg_field_night_tiles);
		set_bkg_tiles(0, 0, 20, 18, bg_field_night_map);

	} else {
		SWITCH_ROM(BANK(bg_field));
		set_bkg_data(0, bg_field_TILE_COUNT, bg_field_tiles);
		set_bkg_tiles(0, 0, 20, 18, bg_field_map);
	}
}

/* ============ */
/*     POND     */
/* ============ */

void draw_pond_bg() {
	if (is_night) {
		SWITCH_ROM(BANK(bg_pond_night));
		set_bkg_data(0, bg_pond_night_TILE_COUNT, bg_pond_night_tiles);
		set_bkg_tiles(0, 0, 20, 18, bg_pond_night_map);
	} else {
		SWITCH_ROM(BANK(bg_pond));
		set_bkg_data(0, bg_pond_TILE_COUNT, bg_pond_tiles);
		set_bkg_tiles(0, 0, 20, 18, bg_pond_map);
	}

	SWITCH_ROM(BANK(pond_sparkle));
	set_sprite_data(POND_SPARKLE_VRAM, pond_sparkle_TILE_COUNT, pond_sparkle_tiles);

	SWITCH_ROM(BANK(fly));
	set_sprite_data(FLY_VRAM, fly_TILE_COUNT, fly_tiles);
}

/* ============== */
/*     GARDEN     */
/* ============== */

void draw_garden_bg() {
	if (is_night) {
		SWITCH_ROM(BANK(bg_garden_night));
		set_bkg_data(0, bg_garden_night_TILE_COUNT, bg_garden_night_tiles);
		set_bkg_tiles(0, 0, 20, 18, bg_garden_night_map);

	} else {
		SWITCH_ROM(BANK(bg_garden));
		set_bkg_data(0, bg_garden_TILE_COUNT, bg_garden_tiles);
		set_bkg_tiles(0, 0, 20, 18, bg_garden_map);
	}

	SWITCH_ROM(BANK(sparkle));
	set_sprite_data(SPARKLE_VRAM, sparkle_TILE_COUNT, sparkle_tiles);

	SWITCH_ROM(BANK(plant));
	set_bkg_data(PLANT_VRAM, plant_TILE_COUNT, plant_tiles);

	SWITCH_ROM(BANK(garden_code));
	draw_plants();
}

/* ============= */
/*     STATS     */
/* ============= */

void draw_stat(uint8_t y, uint8_t value) {
	uint8_t i = 0;
	uint8_t x = 0;
	while (i < 6) {
		x = 5 + (i * 2);
		if ((i + 1) * 2 <= value + 1) {
			set_bkg_tiles(x, y, 2, 2, full_dot_tile_map);
		} else {
			set_bkg_tiles(x, y, 2, 2, empty_dot_tile_map);
		}
		i++;
	}
}

void draw_stats() {
	SWITCH_ROM(BANK(frog_code));
	draw_stat(2, happy);
	draw_stat(5, full);
	draw_stat(8, clean);
	draw_stat(11, energy);
}

void draw_speed_buttons() {
	if (time_speed == SPEED_PAUSE) {
		set_bkg_tiles(3, 14, 3, 2, speed_pause_tile_map);
	} else {
		set_bkg_tiles(3, 14, 3, 2, speed_pause_inactive_tile_map);
	}

	if (time_speed == SPEED_SLOW) {
		set_bkg_tiles(6, 14, 3, 2, speed_slow_tile_map);
	} else {
		set_bkg_tiles(6, 14, 3, 2, speed_slow_inactive_tile_map);
	}

	if (time_speed == SPEED_NORMAL) {
		set_bkg_tiles(9, 14, 3, 2, speed_normal_tile_map);
	} else {
		set_bkg_tiles(9, 14, 3, 2, speed_normal_inactive_tile_map);
	}

	if (time_speed == SPEED_FAST) {
		set_bkg_tiles(12, 14, 3, 2, speed_fast_tile_map);
	} else {
		set_bkg_tiles(12, 14, 3, 2, speed_fast_inactive_tile_map);
	}
}

void draw_stats_bg() {
	SWITCH_ROM(BANK(bg_stats));
	set_bkg_data(0, bg_stats_TILE_COUNT, bg_stats_tiles);
	set_bkg_tiles(0, 0, 20, 18, bg_stats_map);

	SWITCH_ROM(BANK(speed_pause));
	set_bkg_data(0x50, speed_pause_TILE_COUNT, speed_pause_tiles);

	SWITCH_ROM(BANK(speed_slow));
	set_bkg_data(0x56, speed_slow_TILE_COUNT, speed_slow_tiles);

	SWITCH_ROM(BANK(speed_normal));
	set_bkg_data(0x5C, speed_normal_TILE_COUNT, speed_normal_tiles);

	SWITCH_ROM(BANK(speed_fast));
	set_bkg_data(0x62, speed_fast_TILE_COUNT, speed_fast_tiles);

	draw_stats();
	draw_speed_buttons();
}

/* ============== */
/*     SCREEN     */
/* ============== */

void set_screen(uint8_t new_screen) {
	prev_screen = current_screen;
	current_screen = new_screen;

	switch (new_screen) {
		case SCREEN_FIELD:
			draw_field_bg();
			draw_menu();
			if (prev_screen == SCREEN_POND) {
				SWITCH_ROM(BANK(frog_code));
				move_frog(1, 84);
				set_random_goal();
			} else if (prev_screen == SCREEN_GARDEN) {
				SWITCH_ROM(BANK(frog_code));
				move_frog(175, 84);
				set_random_goal();
			}
			break;

		case SCREEN_POND:
			draw_pond_bg();
			draw_menu();
			if (prev_screen == SCREEN_FIELD) {
				SWITCH_ROM(BANK(frog_code));
				move_frog(175, 84);
				set_goal(144, 84);
			}
			break;

		case SCREEN_GARDEN:
			draw_garden_bg();
			draw_menu();
			if (prev_screen == SCREEN_FIELD) {
				SWITCH_ROM(BANK(frog_code));
				move_frog(1, 84);
				set_goal(30, 84);
			}
			break;

		case SCREEN_STATS:
			draw_stats_bg();
			break;
	}

	if (prev_screen != new_screen) {
		SWITCH_ROM(BANK(frog_code));
		frog_change_rooms();
		SWITCH_ROM(BANK(pond_code));
		reset_flies();
	}
}

void update_screen_switch() {
	switching_screens_counter += 1;
	if (switching_screens_counter >= 4) {
		switching_screens_counter = 0;
		switching_screens_step += 1;
		switch (switching_screens_step) {
			case 1:
				BGP_REG = DMG_PALETTE(DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK);
				break;
			case 2:
				BGP_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK, DMG_BLACK);
				break;
			case 3:
				BGP_REG = DMG_PALETTE(DMG_BLACK, DMG_BLACK, DMG_BLACK, DMG_BLACK);
				set_screen(next_screen);
				break;
			case 4:
				BGP_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK, DMG_BLACK);
				break;
			case 5:
				BGP_REG = DMG_PALETTE(DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK);
				break;
			case 6:
				BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
				switching_screens = FALSE;
				break;
		}
	}
}

void go_screen(uint8_t new_screen) {
	next_screen = new_screen;
	switching_screens = TRUE;
	switching_screens_counter = 0;
	switching_screens_step = 0;
	hide_sprites_range(0, MAX_HARDWARE_SPRITES);
}

/* ============== */
/*     JOYPAD     */
/* ============== */

void press_dpad(uint8_t joypad_value) {
	if (joypad_value & J_LEFT) {
		if (joypad_value & J_UP) {
			move_hand(-181, -181);
		} else if (joypad_value & J_DOWN) {
			move_hand(-181, 181);
		} else {
			move_hand(-256, 0);
		}
	} else if (joypad_value & J_RIGHT) {
		if (joypad_value & J_UP) {
			move_hand(181, -181);
		} else if (joypad_value & J_DOWN) {
			move_hand(181, 181);
		} else {
			move_hand(256, 0);
		}
	} else if (joypad_value & J_UP) {
		move_hand(0, -256);
	} else if (joypad_value & J_DOWN) {
		move_hand(0, 256);
	}
}

void tap_menu() {
	release_item();

	if (hand_intersects(12, 116, 24, 32)) {
		if (hand_state == HAND_HOLD_JAR) {
			set_hand_state(HAND_EMPTY);
		} else {
			set_hand_state(HAND_HOLD_JAR);
		}

	} else if (hand_intersects(44, 116, 24, 32)) {
		if (hand_state == HAND_HOLD_SOAP) {
			set_hand_state(HAND_EMPTY);
		} else {
			set_hand_state(HAND_HOLD_SOAP);
		}

	} else if (hand_intersects(76, 116, 24, 32)) {
		if (hand_state == HAND_HOLD_MOON) {
			set_hand_state(HAND_EMPTY);
		} else {
			set_hand_state(HAND_HOLD_MOON);
		}

	} else if (hand_intersects(108, 116, 24, 32)) {
		if (hand_state == HAND_HOLD_BLACKBERRY || hand_state == HAND_HOLD_BLUEBERRY || hand_state == HAND_HOLD_STRAWBERRY) {
			set_hand_state(HAND_EMPTY);
		} else {
			switch (next_fruit) {
				case FRUIT_BLACKBERRY:
					if (num_blackberries > 0) {
						num_blackberries -= 1;
						set_hand_state(HAND_HOLD_BLACKBERRY);
					}
					break;

				case FRUIT_BLUEBERRY:
					if (num_blueberries > 0) {
						num_blueberries -= 1;
						set_hand_state(HAND_HOLD_BLUEBERRY);
					}
					break;

				case FRUIT_STRAWBERRY:
					if (num_strawberries > 0) {
						num_strawberries -= 1;
						set_hand_state(HAND_HOLD_STRAWBERRY);
					}
					break;
			}
			get_next_fruit(next_fruit);
			save_item(DATA_NEXT_FRUIT, next_fruit);
			save_item(DATA_NUM_BLACKBERRIES, num_blackberries);
			save_item(DATA_NUM_BLUEBERRIES, num_blueberries);
			save_item(DATA_NUM_STRAWBERRIES, num_strawberries);
		}

	} else if (hand_intersects(140, 116, 24, 32)) {
		set_hand_state(HAND_EMPTY);
		prev_screen = current_screen;
		go_screen(SCREEN_STATS);
	}

	draw_menu();
}

void tap_frog() {
	SWITCH_ROM(BANK(frog_code));
	if (frog_evo == EVO_EGG) {
		return;
	}

	switch (hand_state) {
		case HAND_EMPTY:
			set_hand_state(HAND_TICKLE);
			SWITCH_ROM(BANK(frog_code));
			frog_tickle(hand_frame);
			break;

		case HAND_TICKLE:
			set_hand_state(HAND_TICKLE);
			SWITCH_ROM(BANK(frog_code));
			frog_tickle(hand_frame);
			break;

		case HAND_HOLD_SOAP:
			SWITCH_ROM(BANK(frog_code));
			frog_start_wash();
			break;

		case HAND_HOLD_BLACKBERRY:
			SWITCH_ROM(BANK(frog_code));
			if (frog_eat_fruit()) {
				set_hand_state(HAND_FEED_BLACKBERRY);
			}
			break;

		case HAND_HOLD_BLUEBERRY:
			SWITCH_ROM(BANK(frog_code));
			if (frog_eat_fruit()) {
				set_hand_state(HAND_FEED_BLUEBERRY);
			}
			break;

		case HAND_HOLD_STRAWBERRY:
			SWITCH_ROM(BANK(frog_code));
			if (frog_eat_fruit()) {
				set_hand_state(HAND_FEED_STRAWBERRY);
			}
			break;

		case HAND_HOLD_FLY:
			SWITCH_ROM(BANK(frog_code));
			frog_eat_fly();
			break;
	}

	if (hand_state == HAND_FEED_BLACKBERRY || hand_state == HAND_FEED_BLUEBERRY || hand_state == HAND_FEED_STRAWBERRY) {
		hand_x = frog_x + 16;
		hand_y = frog_y - 8;
		hand_x_fractional = hand_x << 8;
		hand_y_fractional = hand_y << 8;
	}
}

void tap_field() {
	if (!is_night && hand_state == HAND_HOLD_MOON && hand_y < 56) {
		set_hand_state(HAND_EMPTY);
		is_night = TRUE;
		put_moon_in_sky();
		go_screen(current_screen);
		SWITCH_ROM(BANK(frog_code));
		frog_sleep();
		save_item(DATA_IS_NIGHT, is_night);

	} else if (is_night && hand_state == HAND_EMPTY && hand_intersects(80, 24, 16, 16)) {
		set_hand_state(HAND_HOLD_MOON);
		is_night = FALSE;
		go_screen(current_screen);
		SWITCH_ROM(BANK(frog_code));
		frog_wake();
		save_item(DATA_IS_NIGHT, is_night);
	}
}

void tap_pond() {
	if (hand_state == HAND_HOLD_JAR && hand_y >= 64 && hand_x < 120) {
		set_hand_state(HAND_TIP_JAR);

	} else if (hand_state == HAND_EMPTY) {
		SWITCH_ROM(BANK(pond_code));
		if (grab_fly(hand_x, hand_y)) {
			set_hand_state(HAND_HOLD_FLY);
		}
	}
}

void tap_garden() {
	if (hand_state == HAND_HOLD_JAR && hand_y >= 40 && hand_y < 96 && hand_x >= 56 && hand_x < 156) {
		set_hand_state(HAND_TIP_JAR);
		if (jar_fullness > 0) {
			SWITCH_ROM(BANK(garden_code));
			if (hand_x >= 56 && hand_x < 88) {
				water_plant(1);
			} else if (hand_x >= 88 && hand_x < 120) {
				water_plant(2);
			} else {
				water_plant(3);
			}
		}

	} else if (hand_state == HAND_EMPTY && hand_y >= 40 && hand_y < 96) {
		if (num_blackberries + num_blueberries + num_strawberries < 6) {
			SWITCH_ROM(BANK(garden_code));
			uint8_t new_hand_state = HAND_EMPTY;
			if (hand_x >= 56 && hand_x < 88) {
				new_hand_state = pick_fruit(1);
			} else if (hand_x >= 88 && hand_x < 120) {
				new_hand_state = pick_fruit(2);
			} else if (hand_x >= 120 && hand_x < 156) {
				new_hand_state = pick_fruit(3);
			}
			if (new_hand_state) {
				set_hand_state(new_hand_state);
			}
		}
	}
}

void tap_stats() {
	if (hand_intersects(148, 136, 24, 32) && time_speed != SPEED_PAUSE) {
		go_screen(prev_screen);

	} else if (hand_intersects(28, 132, 24, 16)) {
		time_speed = SPEED_PAUSE;
		save_item(DATA_TIME_SPEED, time_speed);
		draw_speed_buttons();

	} else if (hand_intersects(52, 132, 24, 16)) {
		time_speed = SPEED_SLOW;
		save_item(DATA_TIME_SPEED, time_speed);
		draw_speed_buttons();

	} else if (hand_intersects(76, 132, 24, 16)) {
		time_speed = SPEED_NORMAL;
		save_item(DATA_TIME_SPEED, time_speed);
		draw_speed_buttons();

	} else if (hand_intersects(100, 132, 24, 16)) {
		time_speed = SPEED_FAST;
		save_item(DATA_TIME_SPEED, time_speed);
		draw_speed_buttons();
	}
}

void read_joypad() {
	SWITCH_ROM(BANK(frog_code));
	if (hand_state == HAND_TIP_JAR || frog_eating_fruit) {
		return;
	}

	uint8_t joypad_value = joypad();
	uint8_t hand_intersects_frog = hand_intersects(frog_x - 12, frog_y - 8, 24, 16);

	press_dpad(joypad_value);

	if (joypad_value & J_A && !a_button_pressed) {
		a_button_pressed = TRUE;

		if (current_screen == SCREEN_STATS) {
			tap_stats();

		} else {
			if (hand_y > 132) {
				tap_menu();

			} else if (hand_intersects_frog && frog_state != FROG_SLEEP && frog_state != FROG_WASH) {
				tap_frog();

			} else if (hand_state == HAND_HOLD_FLY) {
				SWITCH_ROM(BANK(pond_code));
				release_fly(hand_x, hand_y);
				set_hand_state(HAND_EMPTY);

			} else if (current_screen == SCREEN_FIELD) {
				tap_field();

			} else if (current_screen == SCREEN_POND) {
				tap_pond();

			} else if (current_screen == SCREEN_GARDEN) {
				tap_garden();
			}
		}

	} else if (!(joypad_value & J_A)) {
		a_button_pressed = FALSE;
	}

	if (frog_state == FROG_WASH && (!a_button_pressed || !hand_intersects_frog)) {
		SWITCH_ROM(BANK(frog_code));
		frog_stop_wash();
	}

	if (joypad_value & J_B && !b_button_pressed) {
		b_button_pressed = TRUE;
		if (current_screen == SCREEN_STATS) {
			go_screen(prev_screen);

		} else if (hand_state != HAND_EMPTY && frog_state != FROG_WASH) {
			release_item();
			set_hand_state(HAND_EMPTY);
			draw_menu();
		}

	} else if (!(joypad_value & J_B)) {
		b_button_pressed = FALSE;
	}
}

/* ============ */
/*     DATA     */
/* ============ */

void load_data() {
	time_speed = load_item(DATA_TIME_SPEED, time_speed);

	is_night = load_item(DATA_IS_NIGHT, is_night);

	if (is_night) {
		put_moon_in_sky();
		SWITCH_ROM(BANK(frog_code));
		frog_sleep();
	}

	jar_fullness = load_item(DATA_JAR_FULLNESS, jar_fullness);

	next_fruit = load_item(DATA_NEXT_FRUIT, next_fruit);
	num_blackberries = load_item(DATA_NUM_BLACKBERRIES, num_blackberries);
	num_blueberries = load_item(DATA_NUM_BLUEBERRIES, num_blueberries);
	num_strawberries = load_item(DATA_NUM_STRAWBERRIES, num_strawberries);

	SWITCH_ROM(BANK(frog_code));
	load_frog_data();

	SWITCH_ROM(BANK(garden_code));
	load_garden_data();
}

/* =============== */
/*     GENERAL     */
/* =============== */

void update_after_break() {
	uint16_t days = 0;
	uint8_t hours = 0;
	uint8_t minutes = 0;
	uint8_t seconds = 0;
	read_clock(&days, &hours, &minutes, &seconds);

	EMU_MESSAGE("");
	EMU_printf("TIME: %d days, %hd hours, %hd minutes, %hd seconds", days, (uint8_t) hours, (uint8_t) minutes, (uint8_t) seconds);

	if (time_speed != SPEED_PAUSE) {
		SWITCH_ROM(BANK(frog_code));
		update_frog_after_break(time_speed, &days, &hours, &minutes, &seconds);

		SWITCH_ROM(BANK(garden_code));
		update_garden_after_break(time_speed, &days, &hours, &minutes, &seconds);
	}
}

void draw_sprites() {
	last_used_sprite = 0;

	SWITCH_ROM(BANK(frog_code));
	animate_frog(current_screen == SCREEN_FIELD);

	if (hand_state == HAND_FEED_BLACKBERRY || hand_state == HAND_FEED_BLUEBERRY || hand_state == HAND_FEED_STRAWBERRY) {
		if (frog_eating_fruit == 2 && hand_frame == 0) {
			hand_frame = 1;
			set_hand_state(hand_state);
		} else if (frog_eating_fruit == 5 && hand_frame == 1) {
			hand_frame = 2;
			set_hand_state(hand_state);
		} else if (frog_eating_fruit == 8 && hand_frame == 2) {
			hand_frame = 255;
		} else if (!frog_eating_fruit) {
			hand_frame = 0;
			set_hand_state(HAND_EMPTY);
		}
	} else if (hand_state == HAND_HOLD_FLY && frog_eating_fly == 2) {
		set_hand_state(HAND_EMPTY);
	}

	if (hand_state == HAND_TICKLE && current_frog_state != FROG_TICKLED) {
		set_hand_state(HAND_EMPTY);
	}

	if (hand_frame < 255 && current_frog_state != FROG_EVOLVING) {
		draw_hand();
	}

	if (current_screen != SCREEN_STATS && ((frog_state != FROG_SLEEP && frog_evo != EVO_EGG) || current_screen == SCREEN_FIELD)) {
		draw_frog();
	}

	SWITCH_ROM(BANK(pond_code));
	draw_flies(&last_used_sprite, is_night, current_screen == SCREEN_POND);

	switch (current_screen) {
		case SCREEN_FIELD:
			draw_field();
			break;

		case SCREEN_POND:
			SWITCH_ROM(BANK(pond_code));
			draw_pond_sparkles(is_night, current_screen == SCREEN_POND);
			break;

		case SCREEN_GARDEN:
			SWITCH_ROM(BANK(garden_code));
			draw_garden_sparkles(&last_used_sprite);
			break;
	}

	hide_sprites_range(last_used_sprite, MAX_HARDWARE_SPRITES);
}

void setup() {
	initrand(DIV_REG);
	load_data();
	setup_frog();
	set_hand_state(HAND_EMPTY);
	set_screen(SCREEN_FIELD);
	update_after_break();
}

void main(void) {
	DISPLAY_ON;
	SHOW_BKG;
	SHOW_SPRITES;
	SPRITES_8x8;
	OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);

	setup();

	clock_t prev_time = clock();

	while(1) {
		if (switching_screens) {
			update_screen_switch();

		} else {
			draw_sprites();
			read_joypad();
		}

		if (time_speed != SPEED_PAUSE && clock() - prev_time > CLOCKS_PER_SEC) {
			SWITCH_ROM(BANK(frog_code));
			update_frog(time_speed);

			if (current_screen == SCREEN_STATS) {
				draw_stats();
			}

			SWITCH_ROM(BANK(garden_code));
			update_garden(time_speed, current_screen == SCREEN_GARDEN);

			prev_time = clock();
		}

		wait_vbl_done(); // wait for next frame
	}
}
