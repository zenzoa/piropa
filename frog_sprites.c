#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "sprites/frogs/norm_neutral.h"
#include "sprites/frogs/norm_happy.h"
#include "sprites/frogs/norm_overjoyed.h"
#include "sprites/frogs/norm_sad.h"
#include "sprites/frogs/norm_scared.h"
#include "sprites/frogs/norm_angry.h"
#include "sprites/frogs/norm_eat.h"
#include "sprites/frogs/norm_walk.h"
#include "sprites/frogs/norm_sleep.h"

#include "sprites/frogs/mush_neutral.h"
#include "sprites/frogs/mush_happy.h"
#include "sprites/frogs/mush_overjoyed.h"
#include "sprites/frogs/mush_sad.h"
#include "sprites/frogs/mush_scared.h"
#include "sprites/frogs/mush_angry.h"
#include "sprites/frogs/mush_eat.h"
#include "sprites/frogs/mush_walk.h"
#include "sprites/frogs/mush_sleep.h"

#include "sprites/frogs/axo_neutral.h"
#include "sprites/frogs/axo_happy.h"
#include "sprites/frogs/axo_overjoyed.h"
#include "sprites/frogs/axo_sad.h"
#include "sprites/frogs/axo_scared.h"
#include "sprites/frogs/axo_angry.h"
#include "sprites/frogs/axo_eat.h"
#include "sprites/frogs/axo_walk.h"
#include "sprites/frogs/axo_sleep.h"

#include "sprites/frogs/dino_neutral.h"
#include "sprites/frogs/dino_happy.h"
#include "sprites/frogs/dino_overjoyed.h"
#include "sprites/frogs/dino_sad.h"
#include "sprites/frogs/dino_scared.h"
#include "sprites/frogs/dino_angry.h"
#include "sprites/frogs/dino_eat.h"
#include "sprites/frogs/dino_walk.h"
#include "sprites/frogs/dino_sleep.h"

#include "sprites/frogs/apple_neutral.h"
#include "sprites/frogs/apple_happy.h"
#include "sprites/frogs/apple_overjoyed.h"
#include "sprites/frogs/apple_sad.h"
#include "sprites/frogs/apple_scared.h"
#include "sprites/frogs/apple_angry.h"
#include "sprites/frogs/apple_eat.h"
#include "sprites/frogs/apple_walk.h"
#include "sprites/frogs/apple_sleep.h"

#include "sprites/frogs/panda_neutral.h"
#include "sprites/frogs/panda_happy.h"
#include "sprites/frogs/panda_overjoyed.h"
#include "sprites/frogs/panda_sad.h"
#include "sprites/frogs/panda_scared.h"
#include "sprites/frogs/panda_angry.h"
#include "sprites/frogs/panda_eat.h"
#include "sprites/frogs/panda_walk.h"
#include "sprites/frogs/panda_sleep.h"

#define STAGE_EGG 0
#define STAGE_BABY 1
#define STAGE_CHILD 2
#define STAGE_TEEN_NORM 3
#define STAGE_TEEN_TAIL 4
#define STAGE_TEEN_BW 5
#define STAGE_NORM 6
#define STAGE_MUSH 7
#define STAGE_AXO 8
#define STAGE_DINO 9
#define STAGE_APPLE 10
#define STAGE_PANDA 11
#define STAGE_DEAD_BAD 12
#define STAGE_DEAD_GOOD 13

#define FACE_NEUTRAL 0
#define FACE_HAPPY 1
#define FACE_OVERJOYED 2
#define FACE_SAD 3
#define FACE_SCARED 4
#define FACE_ANGRY 5
#define FACE_EAT 6
#define FACE_WALK_LEFT 7
#define FACE_WALK_RIGHT 8
#define FACE_SLEEP 9

uint8_t frog_sprite_bank;
metasprite_t** frog_metasprites;
uint8_t frog_flipped = FALSE;

#define FROG_VRAM_1 0x0
#define FROG_VRAM_2 0x18
uint8_t frog_vram = FROG_VRAM_1;

void swap_frog_vram() {
	if (frog_vram == FROG_VRAM_1) {
		frog_vram = FROG_VRAM_2;
	} else {
		frog_vram = FROG_VRAM_1;
	}
}

void set_frog_sprite_data(uint8_t stage, uint8_t face) {
	uint8_t saved_bank = _current_bank;
	frog_flipped = FALSE;

	switch(stage) {
		case STAGE_NORM:
			switch(face) {
				case FACE_NEUTRAL:
					frog_sprite_bank = BANK(norm_neutral);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_neutral_TILE_COUNT, norm_neutral_tiles);
					frog_metasprites = norm_neutral_metasprites;
					break;
				case FACE_HAPPY:
					frog_sprite_bank = BANK(norm_happy);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_happy_TILE_COUNT, norm_happy_tiles);
					frog_metasprites = norm_happy_metasprites;
					break;
				case FACE_OVERJOYED:
					frog_sprite_bank = BANK(norm_overjoyed);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_overjoyed_TILE_COUNT, norm_overjoyed_tiles);
					frog_metasprites = norm_overjoyed_metasprites;
					break;
				case FACE_SAD:
					frog_sprite_bank = BANK(norm_sad);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_sad_TILE_COUNT, norm_sad_tiles);
					frog_metasprites = norm_sad_metasprites;
					break;
				case FACE_SCARED:
					frog_sprite_bank = BANK(norm_scared);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_scared_TILE_COUNT, norm_scared_tiles);
					frog_metasprites = norm_scared_metasprites;
					break;
				case FACE_ANGRY:
					frog_sprite_bank = BANK(norm_angry);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_angry_TILE_COUNT, norm_angry_tiles);
					frog_metasprites = norm_angry_metasprites;
					break;
				case FACE_EAT:
					frog_sprite_bank = BANK(norm_eat);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_eat_TILE_COUNT, norm_eat_tiles);
					frog_metasprites = norm_eat_metasprites;
					break;
				case FACE_WALK_LEFT:
					frog_sprite_bank = BANK(norm_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_walk_TILE_COUNT, norm_walk_tiles);
					frog_metasprites = norm_walk_metasprites;
					break;
				case FACE_WALK_RIGHT:
					frog_sprite_bank = BANK(norm_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_walk_TILE_COUNT, norm_walk_tiles);
					frog_metasprites = norm_walk_metasprites;
					frog_flipped = TRUE;
					break;
				case FACE_SLEEP:
					frog_sprite_bank = BANK(norm_sleep);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_sleep_TILE_COUNT, norm_sleep_tiles);
					frog_metasprites = norm_sleep_metasprites;
					break;
			}
			break;
	}

	SWITCH_ROM(saved_bank);
}

void draw_frog_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite) {
	uint8_t saved_bank = _current_bank;

	SWITCH_ROM(frog_sprite_bank);
	if (frog_flipped) {
		*last_sprite += move_metasprite_vflip(frog_metasprites[frame], frog_vram, *last_sprite, x + 32, y);
	} else {
		*last_sprite += move_metasprite(frog_metasprites[frame], frog_vram, *last_sprite, x, y);
	}

	SWITCH_ROM(saved_bank);
}
