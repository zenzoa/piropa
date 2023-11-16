#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "sprites/frogs/egg.h"

#include "sprites/frogs/tadpole_neutral.h"
#include "sprites/frogs/tadpole_happy.h"
#include "sprites/frogs/tadpole_laugh.h"
#include "sprites/frogs/tadpole_sad.h"
#include "sprites/frogs/tadpole_stressed.h"
#include "sprites/frogs/tadpole_angry.h"
#include "sprites/frogs/tadpole_yawn.h"
#include "sprites/frogs/tadpole_eat.h"
#include "sprites/frogs/tadpole_walk.h"
#include "sprites/frogs/tadpole_sleep.h"

#include "sprites/frogs/froglet_neutral.h"
#include "sprites/frogs/froglet_happy.h"
#include "sprites/frogs/froglet_laugh.h"
#include "sprites/frogs/froglet_sad.h"
#include "sprites/frogs/froglet_stressed.h"
#include "sprites/frogs/froglet_angry.h"
#include "sprites/frogs/froglet_yawn.h"
#include "sprites/frogs/froglet_eat.h"
#include "sprites/frogs/froglet_walk.h"
#include "sprites/frogs/froglet_sleep.h"

#include "sprites/frogs/teen_norm_neutral.h"
#include "sprites/frogs/teen_norm_happy.h"
#include "sprites/frogs/teen_norm_laugh.h"
#include "sprites/frogs/teen_norm_sad.h"
#include "sprites/frogs/teen_norm_stressed.h"
#include "sprites/frogs/teen_norm_angry.h"
#include "sprites/frogs/teen_norm_yawn.h"
#include "sprites/frogs/teen_norm_eat.h"
#include "sprites/frogs/teen_norm_walk.h"
#include "sprites/frogs/teen_norm_sleep.h"

#include "sprites/frogs/teen_tail_neutral.h"
#include "sprites/frogs/teen_tail_happy.h"
#include "sprites/frogs/teen_tail_laugh.h"
#include "sprites/frogs/teen_tail_sad.h"
#include "sprites/frogs/teen_tail_stressed.h"
#include "sprites/frogs/teen_tail_angry.h"
#include "sprites/frogs/teen_tail_yawn.h"
#include "sprites/frogs/teen_tail_eat.h"
#include "sprites/frogs/teen_tail_walk.h"
#include "sprites/frogs/teen_tail_sleep.h"

#include "sprites/frogs/teen_bw_neutral.h"
#include "sprites/frogs/teen_bw_happy.h"
#include "sprites/frogs/teen_bw_laugh.h"
#include "sprites/frogs/teen_bw_sad.h"
#include "sprites/frogs/teen_bw_stressed.h"
#include "sprites/frogs/teen_bw_angry.h"
#include "sprites/frogs/teen_bw_yawn.h"
#include "sprites/frogs/teen_bw_eat.h"
#include "sprites/frogs/teen_bw_walk.h"
#include "sprites/frogs/teen_bw_sleep.h"

#include "sprites/frogs/norm_neutral.h"
#include "sprites/frogs/norm_happy.h"
#include "sprites/frogs/norm_laugh.h"
#include "sprites/frogs/norm_sad.h"
#include "sprites/frogs/norm_stressed.h"
#include "sprites/frogs/norm_angry.h"
#include "sprites/frogs/norm_yawn.h"
#include "sprites/frogs/norm_eat.h"
#include "sprites/frogs/norm_walk.h"
#include "sprites/frogs/norm_sleep.h"

#include "sprites/frogs/mush_neutral.h"
#include "sprites/frogs/mush_happy.h"
#include "sprites/frogs/mush_laugh.h"
#include "sprites/frogs/mush_sad.h"
#include "sprites/frogs/mush_stressed.h"
#include "sprites/frogs/mush_angry.h"
#include "sprites/frogs/mush_yawn.h"
#include "sprites/frogs/mush_eat.h"
#include "sprites/frogs/mush_walk.h"
#include "sprites/frogs/mush_sleep.h"

#include "sprites/frogs/axo_neutral.h"
#include "sprites/frogs/axo_happy.h"
#include "sprites/frogs/axo_laugh.h"
#include "sprites/frogs/axo_sad.h"
#include "sprites/frogs/axo_stressed.h"
#include "sprites/frogs/axo_angry.h"
#include "sprites/frogs/axo_yawn.h"
#include "sprites/frogs/axo_eat.h"
#include "sprites/frogs/axo_walk.h"
#include "sprites/frogs/axo_sleep.h"

#include "sprites/frogs/dino_neutral.h"
#include "sprites/frogs/dino_happy.h"
#include "sprites/frogs/dino_laugh.h"
#include "sprites/frogs/dino_sad.h"
#include "sprites/frogs/dino_stressed.h"
#include "sprites/frogs/dino_angry.h"
#include "sprites/frogs/dino_yawn.h"
#include "sprites/frogs/dino_eat.h"
#include "sprites/frogs/dino_walk.h"
#include "sprites/frogs/dino_sleep.h"

#include "sprites/frogs/apple_neutral.h"
#include "sprites/frogs/apple_happy.h"
#include "sprites/frogs/apple_laugh.h"
#include "sprites/frogs/apple_sad.h"
#include "sprites/frogs/apple_stressed.h"
#include "sprites/frogs/apple_angry.h"
#include "sprites/frogs/apple_yawn.h"
#include "sprites/frogs/apple_eat.h"
#include "sprites/frogs/apple_walk.h"
#include "sprites/frogs/apple_sleep.h"

#include "sprites/frogs/panda_neutral.h"
#include "sprites/frogs/panda_happy.h"
#include "sprites/frogs/panda_laugh.h"
#include "sprites/frogs/panda_sad.h"
#include "sprites/frogs/panda_stressed.h"
#include "sprites/frogs/panda_angry.h"
#include "sprites/frogs/panda_yawn.h"
#include "sprites/frogs/panda_eat.h"
#include "sprites/frogs/panda_walk.h"
#include "sprites/frogs/panda_sleep.h"

#include "sprites/frogs/dead_good.h"
#include "sprites/frogs/dead_bad.h"

#define STAGE_EGG 0
#define STAGE_TADPOLE 1
#define STAGE_FROGLET 2
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

#define ANIM_NEUTRAL 0
#define ANIM_HAPPY 1
#define ANIM_LAUGH 2
#define ANIM_SAD 3
#define ANIM_STRESSED 4
#define ANIM_ANGRY 5
#define ANIM_EAT 6
#define ANIM_YAWN 7
#define ANIM_WALK_LEFT 8
#define ANIM_WALK_RIGHT 9
#define ANIM_SLEEP 10

uint8_t frog_sprite_bank;
metasprite_t** frog_metasprites;
uint8_t frog_flipped = FALSE;

#define FROG_VRAM_1 0x0
#define FROG_VRAM_2 0x20
uint8_t frog_vram = FROG_VRAM_1;

void swap_frog_vram(void) {
	if (frog_vram == FROG_VRAM_1) {
		frog_vram = FROG_VRAM_2;
	} else {
		frog_vram = FROG_VRAM_1;
	}
}

void set_frog_sprite_data(uint8_t new_stage, uint8_t new_anim) {
	uint8_t saved_bank = _current_bank;
	frog_flipped = FALSE;

	switch(new_stage) {
		case STAGE_EGG:
			frog_sprite_bank = BANK(egg);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, egg_TILE_COUNT, egg_tiles);
			frog_metasprites = egg_metasprites;
			break;

		case STAGE_TADPOLE:
			switch(new_anim) {
				case ANIM_NEUTRAL:
					frog_sprite_bank = BANK(tadpole_neutral);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, tadpole_neutral_TILE_COUNT, tadpole_neutral_tiles);
					frog_metasprites = tadpole_neutral_metasprites;
					break;
				case ANIM_HAPPY:
					frog_sprite_bank = BANK(tadpole_happy);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, tadpole_happy_TILE_COUNT, tadpole_happy_tiles);
					frog_metasprites = tadpole_happy_metasprites;
					break;
				case ANIM_LAUGH:
					frog_sprite_bank = BANK(tadpole_laugh);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, tadpole_laugh_TILE_COUNT, tadpole_laugh_tiles);
					frog_metasprites = tadpole_laugh_metasprites;
					break;
				case ANIM_SAD:
					frog_sprite_bank = BANK(tadpole_sad);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, tadpole_sad_TILE_COUNT, tadpole_sad_tiles);
					frog_metasprites = tadpole_sad_metasprites;
					break;
				case ANIM_STRESSED:
					frog_sprite_bank = BANK(tadpole_stressed);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, tadpole_stressed_TILE_COUNT, tadpole_stressed_tiles);
					frog_metasprites = tadpole_stressed_metasprites;
					break;
				case ANIM_ANGRY:
					frog_sprite_bank = BANK(tadpole_angry);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, tadpole_angry_TILE_COUNT, tadpole_angry_tiles);
					frog_metasprites = tadpole_angry_metasprites;
					break;
				case ANIM_YAWN:
					frog_sprite_bank = BANK(tadpole_yawn);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, tadpole_yawn_TILE_COUNT, tadpole_yawn_tiles);
					frog_metasprites = tadpole_yawn_metasprites;
					break;
				case ANIM_EAT:
					frog_sprite_bank = BANK(tadpole_eat);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, tadpole_eat_TILE_COUNT, tadpole_eat_tiles);
					frog_metasprites = tadpole_eat_metasprites;
					break;
				case ANIM_WALK_LEFT:
					frog_sprite_bank = BANK(tadpole_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, tadpole_walk_TILE_COUNT, tadpole_walk_tiles);
					frog_metasprites = tadpole_walk_metasprites;
					break;
				case ANIM_WALK_RIGHT:
					frog_sprite_bank = BANK(tadpole_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, tadpole_walk_TILE_COUNT, tadpole_walk_tiles);
					frog_metasprites = tadpole_walk_metasprites;
					frog_flipped = TRUE;
					break;
				case ANIM_SLEEP:
					frog_sprite_bank = BANK(tadpole_sleep);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, tadpole_sleep_TILE_COUNT, tadpole_sleep_tiles);
					frog_metasprites = tadpole_sleep_metasprites;
					break;
			}
			break;

		case STAGE_FROGLET:
			switch(new_anim) {
				case ANIM_NEUTRAL:
					frog_sprite_bank = BANK(froglet_neutral);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, froglet_neutral_TILE_COUNT, froglet_neutral_tiles);
					frog_metasprites = froglet_neutral_metasprites;
					break;
				case ANIM_HAPPY:
					frog_sprite_bank = BANK(froglet_happy);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, froglet_happy_TILE_COUNT, froglet_happy_tiles);
					frog_metasprites = froglet_happy_metasprites;
					break;
				case ANIM_LAUGH:
					frog_sprite_bank = BANK(froglet_laugh);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, froglet_laugh_TILE_COUNT, froglet_laugh_tiles);
					frog_metasprites = froglet_laugh_metasprites;
					break;
				case ANIM_SAD:
					frog_sprite_bank = BANK(froglet_sad);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, froglet_sad_TILE_COUNT, froglet_sad_tiles);
					frog_metasprites = froglet_sad_metasprites;
					break;
				case ANIM_STRESSED:
					frog_sprite_bank = BANK(froglet_stressed);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, froglet_stressed_TILE_COUNT, froglet_stressed_tiles);
					frog_metasprites = froglet_stressed_metasprites;
					break;
				case ANIM_ANGRY:
					frog_sprite_bank = BANK(froglet_angry);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, froglet_angry_TILE_COUNT, froglet_angry_tiles);
					frog_metasprites = froglet_angry_metasprites;
					break;
				case ANIM_YAWN:
					frog_sprite_bank = BANK(froglet_yawn);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, froglet_yawn_TILE_COUNT, froglet_yawn_tiles);
					frog_metasprites = froglet_yawn_metasprites;
					break;
				case ANIM_EAT:
					frog_sprite_bank = BANK(froglet_eat);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, froglet_eat_TILE_COUNT, froglet_eat_tiles);
					frog_metasprites = froglet_eat_metasprites;
					break;
				case ANIM_WALK_LEFT:
					frog_sprite_bank = BANK(froglet_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, froglet_walk_TILE_COUNT, froglet_walk_tiles);
					frog_metasprites = froglet_walk_metasprites;
					break;
				case ANIM_WALK_RIGHT:
					frog_sprite_bank = BANK(froglet_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, froglet_walk_TILE_COUNT, froglet_walk_tiles);
					frog_metasprites = froglet_walk_metasprites;
					frog_flipped = TRUE;
					break;
				case ANIM_SLEEP:
					frog_sprite_bank = BANK(froglet_sleep);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, froglet_sleep_TILE_COUNT, froglet_sleep_tiles);
					frog_metasprites = froglet_sleep_metasprites;
					break;
			}
			break;

		case STAGE_TEEN_NORM:
			switch(new_anim) {
				case ANIM_NEUTRAL:
					frog_sprite_bank = BANK(teen_norm_neutral);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_norm_neutral_TILE_COUNT, teen_norm_neutral_tiles);
					frog_metasprites = teen_norm_neutral_metasprites;
					break;
				case ANIM_HAPPY:
					frog_sprite_bank = BANK(teen_norm_happy);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_norm_happy_TILE_COUNT, teen_norm_happy_tiles);
					frog_metasprites = teen_norm_happy_metasprites;
					break;
				case ANIM_LAUGH:
					frog_sprite_bank = BANK(teen_norm_laugh);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_norm_laugh_TILE_COUNT, teen_norm_laugh_tiles);
					frog_metasprites = teen_norm_laugh_metasprites;
					break;
				case ANIM_SAD:
					frog_sprite_bank = BANK(teen_norm_sad);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_norm_sad_TILE_COUNT, teen_norm_sad_tiles);
					frog_metasprites = teen_norm_sad_metasprites;
					break;
				case ANIM_STRESSED:
					frog_sprite_bank = BANK(teen_norm_stressed);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_norm_stressed_TILE_COUNT, teen_norm_stressed_tiles);
					frog_metasprites = teen_norm_stressed_metasprites;
					break;
				case ANIM_ANGRY:
					frog_sprite_bank = BANK(teen_norm_angry);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_norm_angry_TILE_COUNT, teen_norm_angry_tiles);
					frog_metasprites = teen_norm_angry_metasprites;
					break;
				case ANIM_YAWN:
					frog_sprite_bank = BANK(teen_norm_yawn);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_norm_yawn_TILE_COUNT, teen_norm_yawn_tiles);
					frog_metasprites = teen_norm_yawn_metasprites;
					break;
				case ANIM_EAT:
					frog_sprite_bank = BANK(teen_norm_eat);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_norm_eat_TILE_COUNT, teen_norm_eat_tiles);
					frog_metasprites = teen_norm_eat_metasprites;
					break;
				case ANIM_WALK_LEFT:
					frog_sprite_bank = BANK(teen_norm_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_norm_walk_TILE_COUNT, teen_norm_walk_tiles);
					frog_metasprites = teen_norm_walk_metasprites;
					break;
				case ANIM_WALK_RIGHT:
					frog_sprite_bank = BANK(teen_norm_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_norm_walk_TILE_COUNT, teen_norm_walk_tiles);
					frog_metasprites = teen_norm_walk_metasprites;
					frog_flipped = TRUE;
					break;
				case ANIM_SLEEP:
					frog_sprite_bank = BANK(teen_norm_sleep);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_norm_sleep_TILE_COUNT, teen_norm_sleep_tiles);
					frog_metasprites = teen_norm_sleep_metasprites;
					break;
			}
			break;

		case STAGE_TEEN_TAIL:
			switch(new_anim) {
				case ANIM_NEUTRAL:
					frog_sprite_bank = BANK(teen_tail_neutral);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_tail_neutral_TILE_COUNT, teen_tail_neutral_tiles);
					frog_metasprites = teen_tail_neutral_metasprites;
					break;
				case ANIM_HAPPY:
					frog_sprite_bank = BANK(teen_tail_happy);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_tail_happy_TILE_COUNT, teen_tail_happy_tiles);
					frog_metasprites = teen_tail_happy_metasprites;
					break;
				case ANIM_LAUGH:
					frog_sprite_bank = BANK(teen_tail_laugh);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_tail_laugh_TILE_COUNT, teen_tail_laugh_tiles);
					frog_metasprites = teen_tail_laugh_metasprites;
					break;
				case ANIM_SAD:
					frog_sprite_bank = BANK(teen_tail_sad);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_tail_sad_TILE_COUNT, teen_tail_sad_tiles);
					frog_metasprites = teen_tail_sad_metasprites;
					break;
				case ANIM_STRESSED:
					frog_sprite_bank = BANK(teen_tail_stressed);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_tail_stressed_TILE_COUNT, teen_tail_stressed_tiles);
					frog_metasprites = teen_tail_stressed_metasprites;
					break;
				case ANIM_ANGRY:
					frog_sprite_bank = BANK(teen_tail_angry);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_tail_angry_TILE_COUNT, teen_tail_angry_tiles);
					frog_metasprites = teen_tail_angry_metasprites;
					break;
				case ANIM_YAWN:
					frog_sprite_bank = BANK(teen_tail_yawn);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_tail_yawn_TILE_COUNT, teen_tail_yawn_tiles);
					frog_metasprites = teen_tail_yawn_metasprites;
					break;
				case ANIM_EAT:
					frog_sprite_bank = BANK(teen_tail_eat);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_tail_eat_TILE_COUNT, teen_tail_eat_tiles);
					frog_metasprites = teen_tail_eat_metasprites;
					break;
				case ANIM_WALK_LEFT:
					frog_sprite_bank = BANK(teen_tail_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_tail_walk_TILE_COUNT, teen_tail_walk_tiles);
					frog_metasprites = teen_tail_walk_metasprites;
					break;
				case ANIM_WALK_RIGHT:
					frog_sprite_bank = BANK(teen_tail_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_tail_walk_TILE_COUNT, teen_tail_walk_tiles);
					frog_metasprites = teen_tail_walk_metasprites;
					frog_flipped = TRUE;
					break;
				case ANIM_SLEEP:
					frog_sprite_bank = BANK(teen_tail_sleep);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_tail_sleep_TILE_COUNT, teen_tail_sleep_tiles);
					frog_metasprites = teen_tail_sleep_metasprites;
					break;
			}
			break;

		case STAGE_TEEN_BW:
			switch(new_anim) {
				case ANIM_NEUTRAL:
					frog_sprite_bank = BANK(teen_bw_neutral);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_bw_neutral_TILE_COUNT, teen_bw_neutral_tiles);
					frog_metasprites = teen_bw_neutral_metasprites;
					break;
				case ANIM_HAPPY:
					frog_sprite_bank = BANK(teen_bw_happy);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_bw_happy_TILE_COUNT, teen_bw_happy_tiles);
					frog_metasprites = teen_bw_happy_metasprites;
					break;
				case ANIM_LAUGH:
					frog_sprite_bank = BANK(teen_bw_laugh);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_bw_laugh_TILE_COUNT, teen_bw_laugh_tiles);
					frog_metasprites = teen_bw_laugh_metasprites;
					break;
				case ANIM_SAD:
					frog_sprite_bank = BANK(teen_bw_sad);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_bw_sad_TILE_COUNT, teen_bw_sad_tiles);
					frog_metasprites = teen_bw_sad_metasprites;
					break;
				case ANIM_STRESSED:
					frog_sprite_bank = BANK(teen_bw_stressed);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_bw_stressed_TILE_COUNT, teen_bw_stressed_tiles);
					frog_metasprites = teen_bw_stressed_metasprites;
					break;
				case ANIM_ANGRY:
					frog_sprite_bank = BANK(teen_bw_angry);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_bw_angry_TILE_COUNT, teen_bw_angry_tiles);
					frog_metasprites = teen_bw_angry_metasprites;
					break;
				case ANIM_YAWN:
					frog_sprite_bank = BANK(teen_bw_yawn);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_bw_yawn_TILE_COUNT, teen_bw_yawn_tiles);
					frog_metasprites = teen_bw_yawn_metasprites;
					break;
				case ANIM_EAT:
					frog_sprite_bank = BANK(teen_bw_eat);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_bw_eat_TILE_COUNT, teen_bw_eat_tiles);
					frog_metasprites = teen_bw_eat_metasprites;
					break;
				case ANIM_WALK_LEFT:
					frog_sprite_bank = BANK(teen_bw_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_bw_walk_TILE_COUNT, teen_bw_walk_tiles);
					frog_metasprites = teen_bw_walk_metasprites;
					break;
				case ANIM_WALK_RIGHT:
					frog_sprite_bank = BANK(teen_bw_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_bw_walk_TILE_COUNT, teen_bw_walk_tiles);
					frog_metasprites = teen_bw_walk_metasprites;
					frog_flipped = TRUE;
					break;
				case ANIM_SLEEP:
					frog_sprite_bank = BANK(teen_bw_sleep);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, teen_bw_sleep_TILE_COUNT, teen_bw_sleep_tiles);
					frog_metasprites = teen_bw_sleep_metasprites;
					break;
			}
			break;

		case STAGE_NORM:
			switch(new_anim) {
				case ANIM_NEUTRAL:
					frog_sprite_bank = BANK(norm_neutral);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_neutral_TILE_COUNT, norm_neutral_tiles);
					frog_metasprites = norm_neutral_metasprites;
					break;
				case ANIM_HAPPY:
					frog_sprite_bank = BANK(norm_happy);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_happy_TILE_COUNT, norm_happy_tiles);
					frog_metasprites = norm_happy_metasprites;
					break;
				case ANIM_LAUGH:
					frog_sprite_bank = BANK(norm_laugh);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_laugh_TILE_COUNT, norm_laugh_tiles);
					frog_metasprites = norm_laugh_metasprites;
					break;
				case ANIM_SAD:
					frog_sprite_bank = BANK(norm_sad);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_sad_TILE_COUNT, norm_sad_tiles);
					frog_metasprites = norm_sad_metasprites;
					break;
				case ANIM_STRESSED:
					frog_sprite_bank = BANK(norm_stressed);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_stressed_TILE_COUNT, norm_stressed_tiles);
					frog_metasprites = norm_stressed_metasprites;
					break;
				case ANIM_ANGRY:
					frog_sprite_bank = BANK(norm_angry);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_angry_TILE_COUNT, norm_angry_tiles);
					frog_metasprites = norm_angry_metasprites;
					break;
				case ANIM_YAWN:
					frog_sprite_bank = BANK(norm_yawn);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_yawn_TILE_COUNT, norm_yawn_tiles);
					frog_metasprites = norm_yawn_metasprites;
					break;
				case ANIM_EAT:
					frog_sprite_bank = BANK(norm_eat);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_eat_TILE_COUNT, norm_eat_tiles);
					frog_metasprites = norm_eat_metasprites;
					break;
				case ANIM_WALK_LEFT:
					frog_sprite_bank = BANK(norm_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_walk_TILE_COUNT, norm_walk_tiles);
					frog_metasprites = norm_walk_metasprites;
					break;
				case ANIM_WALK_RIGHT:
					frog_sprite_bank = BANK(norm_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_walk_TILE_COUNT, norm_walk_tiles);
					frog_metasprites = norm_walk_metasprites;
					frog_flipped = TRUE;
					break;
				case ANIM_SLEEP:
					frog_sprite_bank = BANK(norm_sleep);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, norm_sleep_TILE_COUNT, norm_sleep_tiles);
					frog_metasprites = norm_sleep_metasprites;
					break;
			}
			break;

		case STAGE_MUSH:
			switch(new_anim) {
				case ANIM_NEUTRAL:
					frog_sprite_bank = BANK(mush_neutral);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, mush_neutral_TILE_COUNT, mush_neutral_tiles);
					frog_metasprites = mush_neutral_metasprites;
					break;
				case ANIM_HAPPY:
					frog_sprite_bank = BANK(mush_happy);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, mush_happy_TILE_COUNT, mush_happy_tiles);
					frog_metasprites = mush_happy_metasprites;
					break;
				case ANIM_LAUGH:
					frog_sprite_bank = BANK(mush_laugh);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, mush_laugh_TILE_COUNT, mush_laugh_tiles);
					frog_metasprites = mush_laugh_metasprites;
					break;
				case ANIM_SAD:
					frog_sprite_bank = BANK(mush_sad);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, mush_sad_TILE_COUNT, mush_sad_tiles);
					frog_metasprites = mush_sad_metasprites;
					break;
				case ANIM_STRESSED:
					frog_sprite_bank = BANK(mush_stressed);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, mush_stressed_TILE_COUNT, mush_stressed_tiles);
					frog_metasprites = mush_stressed_metasprites;
					break;
				case ANIM_ANGRY:
					frog_sprite_bank = BANK(mush_angry);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, mush_angry_TILE_COUNT, mush_angry_tiles);
					frog_metasprites = mush_angry_metasprites;
					break;
				case ANIM_YAWN:
					frog_sprite_bank = BANK(mush_yawn);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, mush_yawn_TILE_COUNT, mush_yawn_tiles);
					frog_metasprites = mush_yawn_metasprites;
					break;
				case ANIM_EAT:
					frog_sprite_bank = BANK(mush_eat);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, mush_eat_TILE_COUNT, mush_eat_tiles);
					frog_metasprites = mush_eat_metasprites;
					break;
				case ANIM_WALK_LEFT:
					frog_sprite_bank = BANK(mush_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, mush_walk_TILE_COUNT, mush_walk_tiles);
					frog_metasprites = mush_walk_metasprites;
					break;
				case ANIM_WALK_RIGHT:
					frog_sprite_bank = BANK(mush_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, mush_walk_TILE_COUNT, mush_walk_tiles);
					frog_metasprites = mush_walk_metasprites;
					frog_flipped = TRUE;
					break;
				case ANIM_SLEEP:
					frog_sprite_bank = BANK(mush_sleep);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, mush_sleep_TILE_COUNT, mush_sleep_tiles);
					frog_metasprites = mush_sleep_metasprites;
					break;
			}
			break;

		case STAGE_AXO:
			switch(new_anim) {
				case ANIM_NEUTRAL:
					frog_sprite_bank = BANK(axo_neutral);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, axo_neutral_TILE_COUNT, axo_neutral_tiles);
					frog_metasprites = axo_neutral_metasprites;
					break;
				case ANIM_HAPPY:
					frog_sprite_bank = BANK(axo_happy);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, axo_happy_TILE_COUNT, axo_happy_tiles);
					frog_metasprites = axo_happy_metasprites;
					break;
				case ANIM_LAUGH:
					frog_sprite_bank = BANK(axo_laugh);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, axo_laugh_TILE_COUNT, axo_laugh_tiles);
					frog_metasprites = axo_laugh_metasprites;
					break;
				case ANIM_SAD:
					frog_sprite_bank = BANK(axo_sad);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, axo_sad_TILE_COUNT, axo_sad_tiles);
					frog_metasprites = axo_sad_metasprites;
					break;
				case ANIM_STRESSED:
					frog_sprite_bank = BANK(axo_stressed);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, axo_stressed_TILE_COUNT, axo_stressed_tiles);
					frog_metasprites = axo_stressed_metasprites;
					break;
				case ANIM_ANGRY:
					frog_sprite_bank = BANK(axo_angry);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, axo_angry_TILE_COUNT, axo_angry_tiles);
					frog_metasprites = axo_angry_metasprites;
					break;
				case ANIM_YAWN:
					frog_sprite_bank = BANK(axo_yawn);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, axo_yawn_TILE_COUNT, axo_yawn_tiles);
					frog_metasprites = axo_yawn_metasprites;
					break;
				case ANIM_EAT:
					frog_sprite_bank = BANK(axo_eat);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, axo_eat_TILE_COUNT, axo_eat_tiles);
					frog_metasprites = axo_eat_metasprites;
					break;
				case ANIM_WALK_LEFT:
					frog_sprite_bank = BANK(axo_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, axo_walk_TILE_COUNT, axo_walk_tiles);
					frog_metasprites = axo_walk_metasprites;
					break;
				case ANIM_WALK_RIGHT:
					frog_sprite_bank = BANK(axo_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, axo_walk_TILE_COUNT, axo_walk_tiles);
					frog_metasprites = axo_walk_metasprites;
					frog_flipped = TRUE;
					break;
				case ANIM_SLEEP:
					frog_sprite_bank = BANK(axo_sleep);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, axo_sleep_TILE_COUNT, axo_sleep_tiles);
					frog_metasprites = axo_sleep_metasprites;
					break;
			}
			break;

		case STAGE_DINO:
			switch(new_anim) {
				case ANIM_NEUTRAL:
					frog_sprite_bank = BANK(dino_neutral);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, dino_neutral_TILE_COUNT, dino_neutral_tiles);
					frog_metasprites = dino_neutral_metasprites;
					break;
				case ANIM_HAPPY:
					frog_sprite_bank = BANK(dino_happy);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, dino_happy_TILE_COUNT, dino_happy_tiles);
					frog_metasprites = dino_happy_metasprites;
					break;
				case ANIM_LAUGH:
					frog_sprite_bank = BANK(dino_laugh);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, dino_laugh_TILE_COUNT, dino_laugh_tiles);
					frog_metasprites = dino_laugh_metasprites;
					break;
				case ANIM_SAD:
					frog_sprite_bank = BANK(dino_sad);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, dino_sad_TILE_COUNT, dino_sad_tiles);
					frog_metasprites = dino_sad_metasprites;
					break;
				case ANIM_STRESSED:
					frog_sprite_bank = BANK(dino_stressed);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, dino_stressed_TILE_COUNT, dino_stressed_tiles);
					frog_metasprites = dino_stressed_metasprites;
					break;
				case ANIM_ANGRY:
					frog_sprite_bank = BANK(dino_angry);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, dino_angry_TILE_COUNT, dino_angry_tiles);
					frog_metasprites = dino_angry_metasprites;
					break;
				case ANIM_YAWN:
					frog_sprite_bank = BANK(dino_yawn);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, dino_yawn_TILE_COUNT, dino_yawn_tiles);
					frog_metasprites = dino_yawn_metasprites;
					break;
				case ANIM_EAT:
					frog_sprite_bank = BANK(dino_eat);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, dino_eat_TILE_COUNT, dino_eat_tiles);
					frog_metasprites = dino_eat_metasprites;
					break;
				case ANIM_WALK_LEFT:
					frog_sprite_bank = BANK(dino_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, dino_walk_TILE_COUNT, dino_walk_tiles);
					frog_metasprites = dino_walk_metasprites;
					break;
				case ANIM_WALK_RIGHT:
					frog_sprite_bank = BANK(dino_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, dino_walk_TILE_COUNT, dino_walk_tiles);
					frog_metasprites = dino_walk_metasprites;
					frog_flipped = TRUE;
					break;
				case ANIM_SLEEP:
					frog_sprite_bank = BANK(dino_sleep);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, dino_sleep_TILE_COUNT, dino_sleep_tiles);
					frog_metasprites = dino_sleep_metasprites;
					break;
			}
			break;

		case STAGE_APPLE:
			switch(new_anim) {
				case ANIM_NEUTRAL:
					frog_sprite_bank = BANK(apple_neutral);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, apple_neutral_TILE_COUNT, apple_neutral_tiles);
					frog_metasprites = apple_neutral_metasprites;
					break;
				case ANIM_HAPPY:
					frog_sprite_bank = BANK(apple_happy);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, apple_happy_TILE_COUNT, apple_happy_tiles);
					frog_metasprites = apple_happy_metasprites;
					break;
				case ANIM_LAUGH:
					frog_sprite_bank = BANK(apple_laugh);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, apple_laugh_TILE_COUNT, apple_laugh_tiles);
					frog_metasprites = apple_laugh_metasprites;
					break;
				case ANIM_SAD:
					frog_sprite_bank = BANK(apple_sad);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, apple_sad_TILE_COUNT, apple_sad_tiles);
					frog_metasprites = apple_sad_metasprites;
					break;
				case ANIM_STRESSED:
					frog_sprite_bank = BANK(apple_stressed);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, apple_stressed_TILE_COUNT, apple_stressed_tiles);
					frog_metasprites = apple_stressed_metasprites;
					break;
				case ANIM_ANGRY:
					frog_sprite_bank = BANK(apple_angry);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, apple_angry_TILE_COUNT, apple_angry_tiles);
					frog_metasprites = apple_angry_metasprites;
					break;
				case ANIM_YAWN:
					frog_sprite_bank = BANK(apple_yawn);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, apple_yawn_TILE_COUNT, apple_yawn_tiles);
					frog_metasprites = apple_yawn_metasprites;
					break;
				case ANIM_EAT:
					frog_sprite_bank = BANK(apple_eat);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, apple_eat_TILE_COUNT, apple_eat_tiles);
					frog_metasprites = apple_eat_metasprites;
					break;
				case ANIM_WALK_LEFT:
					frog_sprite_bank = BANK(apple_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, apple_walk_TILE_COUNT, apple_walk_tiles);
					frog_metasprites = apple_walk_metasprites;
					break;
				case ANIM_WALK_RIGHT:
					frog_sprite_bank = BANK(apple_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, apple_walk_TILE_COUNT, apple_walk_tiles);
					frog_metasprites = apple_walk_metasprites;
					frog_flipped = TRUE;
					break;
				case ANIM_SLEEP:
					frog_sprite_bank = BANK(apple_sleep);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, apple_sleep_TILE_COUNT, apple_sleep_tiles);
					frog_metasprites = apple_sleep_metasprites;
					break;
			}
			break;

		case STAGE_PANDA:
			switch(new_anim) {
				case ANIM_NEUTRAL:
					frog_sprite_bank = BANK(panda_neutral);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, panda_neutral_TILE_COUNT, panda_neutral_tiles);
					frog_metasprites = panda_neutral_metasprites;
					break;
				case ANIM_HAPPY:
					frog_sprite_bank = BANK(panda_happy);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, panda_happy_TILE_COUNT, panda_happy_tiles);
					frog_metasprites = panda_happy_metasprites;
					break;
				case ANIM_LAUGH:
					frog_sprite_bank = BANK(panda_laugh);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, panda_laugh_TILE_COUNT, panda_laugh_tiles);
					frog_metasprites = panda_laugh_metasprites;
					break;
				case ANIM_SAD:
					frog_sprite_bank = BANK(panda_sad);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, panda_sad_TILE_COUNT, panda_sad_tiles);
					frog_metasprites = panda_sad_metasprites;
					break;
				case ANIM_STRESSED:
					frog_sprite_bank = BANK(panda_stressed);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, panda_stressed_TILE_COUNT, panda_stressed_tiles);
					frog_metasprites = panda_stressed_metasprites;
					break;
				case ANIM_ANGRY:
					frog_sprite_bank = BANK(panda_angry);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, panda_angry_TILE_COUNT, panda_angry_tiles);
					frog_metasprites = panda_angry_metasprites;
					break;
				case ANIM_YAWN:
					frog_sprite_bank = BANK(panda_yawn);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, panda_yawn_TILE_COUNT, panda_yawn_tiles);
					frog_metasprites = panda_yawn_metasprites;
					break;
				case ANIM_EAT:
					frog_sprite_bank = BANK(panda_eat);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, panda_eat_TILE_COUNT, panda_eat_tiles);
					frog_metasprites = panda_eat_metasprites;
					break;
				case ANIM_WALK_LEFT:
					frog_sprite_bank = BANK(panda_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, panda_walk_TILE_COUNT, panda_walk_tiles);
					frog_metasprites = panda_walk_metasprites;
					break;
				case ANIM_WALK_RIGHT:
					frog_sprite_bank = BANK(panda_walk);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, panda_walk_TILE_COUNT, panda_walk_tiles);
					frog_metasprites = panda_walk_metasprites;
					frog_flipped = TRUE;
					break;
				case ANIM_SLEEP:
					frog_sprite_bank = BANK(panda_sleep);
					SWITCH_ROM(frog_sprite_bank);
					set_sprite_data(frog_vram, panda_sleep_TILE_COUNT, panda_sleep_tiles);
					frog_metasprites = panda_sleep_metasprites;
					break;
			}
			break;

		case STAGE_DEAD_BAD:
			frog_sprite_bank = BANK(dead_bad);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, dead_bad_TILE_COUNT, dead_bad_tiles);
			frog_metasprites = dead_bad_metasprites;
			break;

		case STAGE_DEAD_GOOD:
			frog_sprite_bank = BANK(dead_good);
			SWITCH_ROM(frog_sprite_bank);
			set_sprite_data(frog_vram, dead_good_TILE_COUNT, dead_good_tiles);
			frog_metasprites = dead_good_metasprites;
			break;

	}

	SWITCH_ROM(saved_bank);
}

void draw_frog_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite) {
	uint8_t saved_bank = _current_bank;

	SWITCH_ROM(frog_sprite_bank);
	if (frog_flipped) {
		*last_sprite += move_metasprite_flipx(frog_metasprites[frame], frog_vram, 0, *last_sprite, x + 32, y);
	} else {
		*last_sprite += move_metasprite_ex(frog_metasprites[frame], frog_vram, 0, *last_sprite, x, y);
	}

	SWITCH_ROM(saved_bank);
}
