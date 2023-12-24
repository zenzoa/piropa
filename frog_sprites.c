#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "common.h"

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

#define FROG_TILE_COUNT 24

static const metasprite_t frog_metasprite0[] = {
	METASPR_ITEM(0, 0, 0x00, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x01, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x02, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x03, S_PAL(0)),
	METASPR_ITEM(8, -24, 0x08, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x09, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x0a, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x0b, S_PAL(0)),
	METASPR_ITEM(8, -24, 0x10, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x11, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x12, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x13, S_PAL(0)),
	METASPR_TERM
};

static const metasprite_t frog_metasprite1[] = {
	METASPR_ITEM(0, 0, 0x04, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x05, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x06, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x07, S_PAL(0)),
	METASPR_ITEM(8, -24, 0x0c, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x0d, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x0e, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x0f, S_PAL(0)),
	METASPR_ITEM(8, -24, 0x14, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x15, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x16, S_PAL(0)),
	METASPR_ITEM(0, 8, 0x17, S_PAL(0)),
	METASPR_TERM
};

static const metasprite_t* const frog_metasprites[2] = { frog_metasprite0, frog_metasprite1 };

const sprite_data_t frog_sprite_table[14][11] = {
	{
		{ BANK(egg), FROG_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)frog_metasprites },
		{ BANK(egg), FROG_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)frog_metasprites },
		{ BANK(egg), FROG_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)frog_metasprites },
		{ BANK(egg), FROG_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)frog_metasprites },
		{ BANK(egg), FROG_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)frog_metasprites },
		{ BANK(egg), FROG_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)frog_metasprites },
		{ BANK(egg), FROG_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)frog_metasprites },
		{ BANK(egg), FROG_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)frog_metasprites },
		{ BANK(egg), FROG_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)frog_metasprites },
		{ BANK(egg), FROG_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)frog_metasprites },
		{ BANK(egg), FROG_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)frog_metasprites }
	},
	{
		{ BANK(tadpole_neutral), FROG_TILE_COUNT, (uint8_t *)tadpole_neutral_tiles, (uint8_t *)frog_metasprites },
		{ BANK(tadpole_happy), FROG_TILE_COUNT, (uint8_t *)tadpole_happy_tiles, (uint8_t *)frog_metasprites },
		{ BANK(tadpole_laugh), FROG_TILE_COUNT, (uint8_t *)tadpole_laugh_tiles, (uint8_t *)frog_metasprites },
		{ BANK(tadpole_sad), FROG_TILE_COUNT, (uint8_t *)tadpole_sad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(tadpole_stressed), FROG_TILE_COUNT, (uint8_t *)tadpole_stressed_tiles, (uint8_t *)frog_metasprites },
		{ BANK(tadpole_angry), FROG_TILE_COUNT, (uint8_t *)tadpole_angry_tiles, (uint8_t *)frog_metasprites },
		{ BANK(tadpole_eat), FROG_TILE_COUNT, (uint8_t *)tadpole_eat_tiles, (uint8_t *)frog_metasprites },
		{ BANK(tadpole_yawn), FROG_TILE_COUNT, (uint8_t *)tadpole_yawn_tiles, (uint8_t *)frog_metasprites },
		{ BANK(tadpole_walk), FROG_TILE_COUNT, (uint8_t *)tadpole_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(tadpole_walk), FROG_TILE_COUNT, (uint8_t *)tadpole_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(tadpole_sleep), FROG_TILE_COUNT, (uint8_t *)tadpole_sleep_tiles, (uint8_t *)frog_metasprites }
	},
	{
		{ BANK(froglet_neutral), FROG_TILE_COUNT, (uint8_t *)froglet_neutral_tiles, (uint8_t *)frog_metasprites },
		{ BANK(froglet_happy), FROG_TILE_COUNT, (uint8_t *)froglet_happy_tiles, (uint8_t *)frog_metasprites },
		{ BANK(froglet_laugh), FROG_TILE_COUNT, (uint8_t *)froglet_laugh_tiles, (uint8_t *)frog_metasprites },
		{ BANK(froglet_sad), FROG_TILE_COUNT, (uint8_t *)froglet_sad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(froglet_stressed), FROG_TILE_COUNT, (uint8_t *)froglet_stressed_tiles, (uint8_t *)frog_metasprites },
		{ BANK(froglet_angry), FROG_TILE_COUNT, (uint8_t *)froglet_angry_tiles, (uint8_t *)frog_metasprites },
		{ BANK(froglet_eat), FROG_TILE_COUNT, (uint8_t *)froglet_eat_tiles, (uint8_t *)frog_metasprites },
		{ BANK(froglet_yawn), FROG_TILE_COUNT, (uint8_t *)froglet_yawn_tiles, (uint8_t *)frog_metasprites },
		{ BANK(froglet_walk), FROG_TILE_COUNT, (uint8_t *)froglet_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(froglet_walk), FROG_TILE_COUNT, (uint8_t *)froglet_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(froglet_sleep), FROG_TILE_COUNT, (uint8_t *)froglet_sleep_tiles, (uint8_t *)frog_metasprites }
	},
	{
		{ BANK(teen_norm_neutral), FROG_TILE_COUNT, (uint8_t *)teen_norm_neutral_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_norm_happy), FROG_TILE_COUNT, (uint8_t *)teen_norm_happy_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_norm_laugh), FROG_TILE_COUNT, (uint8_t *)teen_norm_laugh_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_norm_sad), FROG_TILE_COUNT, (uint8_t *)teen_norm_sad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_norm_stressed), FROG_TILE_COUNT, (uint8_t *)teen_norm_stressed_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_norm_angry), FROG_TILE_COUNT, (uint8_t *)teen_norm_angry_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_norm_eat), FROG_TILE_COUNT, (uint8_t *)teen_norm_eat_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_norm_yawn), FROG_TILE_COUNT, (uint8_t *)teen_norm_yawn_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_norm_walk), FROG_TILE_COUNT, (uint8_t *)teen_norm_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_norm_walk), FROG_TILE_COUNT, (uint8_t *)teen_norm_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_norm_sleep), FROG_TILE_COUNT, (uint8_t *)teen_norm_sleep_tiles, (uint8_t *)frog_metasprites }
	},
	{
		{ BANK(teen_tail_neutral), FROG_TILE_COUNT, (uint8_t *)teen_tail_neutral_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_tail_happy), FROG_TILE_COUNT, (uint8_t *)teen_tail_happy_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_tail_laugh), FROG_TILE_COUNT, (uint8_t *)teen_tail_laugh_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_tail_sad), FROG_TILE_COUNT, (uint8_t *)teen_tail_sad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_tail_stressed), FROG_TILE_COUNT, (uint8_t *)teen_tail_stressed_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_tail_angry), FROG_TILE_COUNT, (uint8_t *)teen_tail_angry_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_tail_eat), FROG_TILE_COUNT, (uint8_t *)teen_tail_eat_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_tail_yawn), FROG_TILE_COUNT, (uint8_t *)teen_tail_yawn_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_tail_walk), FROG_TILE_COUNT, (uint8_t *)teen_tail_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_tail_walk), FROG_TILE_COUNT, (uint8_t *)teen_tail_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_tail_sleep), FROG_TILE_COUNT, (uint8_t *)teen_tail_sleep_tiles, (uint8_t *)frog_metasprites }
	},
	{
		{ BANK(teen_bw_neutral), FROG_TILE_COUNT, (uint8_t *)teen_bw_neutral_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_bw_happy), FROG_TILE_COUNT, (uint8_t *)teen_bw_happy_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_bw_laugh), FROG_TILE_COUNT, (uint8_t *)teen_bw_laugh_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_bw_sad), FROG_TILE_COUNT, (uint8_t *)teen_bw_sad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_bw_stressed), FROG_TILE_COUNT, (uint8_t *)teen_bw_stressed_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_bw_angry), FROG_TILE_COUNT, (uint8_t *)teen_bw_angry_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_bw_eat), FROG_TILE_COUNT, (uint8_t *)teen_bw_eat_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_bw_yawn), FROG_TILE_COUNT, (uint8_t *)teen_bw_yawn_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_bw_walk), FROG_TILE_COUNT, (uint8_t *)teen_bw_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_bw_walk), FROG_TILE_COUNT, (uint8_t *)teen_bw_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(teen_bw_sleep), FROG_TILE_COUNT, (uint8_t *)teen_bw_sleep_tiles, (uint8_t *)frog_metasprites }
	},
	{
		{ BANK(norm_neutral), FROG_TILE_COUNT, (uint8_t *)norm_neutral_tiles, (uint8_t *)frog_metasprites },
		{ BANK(norm_happy), FROG_TILE_COUNT, (uint8_t *)norm_happy_tiles, (uint8_t *)frog_metasprites },
		{ BANK(norm_laugh), FROG_TILE_COUNT, (uint8_t *)norm_laugh_tiles, (uint8_t *)frog_metasprites },
		{ BANK(norm_sad), FROG_TILE_COUNT, (uint8_t *)norm_sad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(norm_stressed), FROG_TILE_COUNT, (uint8_t *)norm_stressed_tiles, (uint8_t *)frog_metasprites },
		{ BANK(norm_angry), FROG_TILE_COUNT, (uint8_t *)norm_angry_tiles, (uint8_t *)frog_metasprites },
		{ BANK(norm_eat), FROG_TILE_COUNT, (uint8_t *)norm_eat_tiles, (uint8_t *)frog_metasprites },
		{ BANK(norm_yawn), FROG_TILE_COUNT, (uint8_t *)norm_yawn_tiles, (uint8_t *)frog_metasprites },
		{ BANK(norm_walk), FROG_TILE_COUNT, (uint8_t *)norm_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(norm_walk), FROG_TILE_COUNT, (uint8_t *)norm_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(norm_sleep), FROG_TILE_COUNT, (uint8_t *)norm_sleep_tiles, (uint8_t *)frog_metasprites }
	},
	{
		{ BANK(mush_neutral), FROG_TILE_COUNT, (uint8_t *)mush_neutral_tiles, (uint8_t *)frog_metasprites },
		{ BANK(mush_happy), FROG_TILE_COUNT, (uint8_t *)mush_happy_tiles, (uint8_t *)frog_metasprites },
		{ BANK(mush_laugh), FROG_TILE_COUNT, (uint8_t *)mush_laugh_tiles, (uint8_t *)frog_metasprites },
		{ BANK(mush_sad), FROG_TILE_COUNT, (uint8_t *)mush_sad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(mush_stressed), FROG_TILE_COUNT, (uint8_t *)mush_stressed_tiles, (uint8_t *)frog_metasprites },
		{ BANK(mush_angry), FROG_TILE_COUNT, (uint8_t *)mush_angry_tiles, (uint8_t *)frog_metasprites },
		{ BANK(mush_eat), FROG_TILE_COUNT, (uint8_t *)mush_eat_tiles, (uint8_t *)frog_metasprites },
		{ BANK(mush_yawn), FROG_TILE_COUNT, (uint8_t *)mush_yawn_tiles, (uint8_t *)frog_metasprites },
		{ BANK(mush_walk), FROG_TILE_COUNT, (uint8_t *)mush_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(mush_walk), FROG_TILE_COUNT, (uint8_t *)mush_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(mush_sleep), FROG_TILE_COUNT, (uint8_t *)mush_sleep_tiles, (uint8_t *)frog_metasprites }
	},
	{
		{ BANK(axo_neutral), FROG_TILE_COUNT, (uint8_t *)axo_neutral_tiles, (uint8_t *)frog_metasprites },
		{ BANK(axo_happy), FROG_TILE_COUNT, (uint8_t *)axo_happy_tiles, (uint8_t *)frog_metasprites },
		{ BANK(axo_laugh), FROG_TILE_COUNT, (uint8_t *)axo_laugh_tiles, (uint8_t *)frog_metasprites },
		{ BANK(axo_sad), FROG_TILE_COUNT, (uint8_t *)axo_sad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(axo_stressed), FROG_TILE_COUNT, (uint8_t *)axo_stressed_tiles, (uint8_t *)frog_metasprites },
		{ BANK(axo_angry), FROG_TILE_COUNT, (uint8_t *)axo_angry_tiles, (uint8_t *)frog_metasprites },
		{ BANK(axo_eat), FROG_TILE_COUNT, (uint8_t *)axo_eat_tiles, (uint8_t *)frog_metasprites },
		{ BANK(axo_yawn), FROG_TILE_COUNT, (uint8_t *)axo_yawn_tiles, (uint8_t *)frog_metasprites },
		{ BANK(axo_walk), FROG_TILE_COUNT, (uint8_t *)axo_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(axo_walk), FROG_TILE_COUNT, (uint8_t *)axo_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(axo_sleep), FROG_TILE_COUNT, (uint8_t *)axo_sleep_tiles, (uint8_t *)frog_metasprites }
	},
	{
		{ BANK(dino_neutral), FROG_TILE_COUNT, (uint8_t *)dino_neutral_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dino_happy), FROG_TILE_COUNT, (uint8_t *)dino_happy_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dino_laugh), FROG_TILE_COUNT, (uint8_t *)dino_laugh_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dino_sad), FROG_TILE_COUNT, (uint8_t *)dino_sad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dino_stressed), FROG_TILE_COUNT, (uint8_t *)dino_stressed_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dino_angry), FROG_TILE_COUNT, (uint8_t *)dino_angry_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dino_eat), FROG_TILE_COUNT, (uint8_t *)dino_eat_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dino_yawn), FROG_TILE_COUNT, (uint8_t *)dino_yawn_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dino_walk), FROG_TILE_COUNT, (uint8_t *)dino_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dino_walk), FROG_TILE_COUNT, (uint8_t *)dino_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dino_sleep), FROG_TILE_COUNT, (uint8_t *)dino_sleep_tiles, (uint8_t *)frog_metasprites }
	},
	{
		{ BANK(apple_neutral), FROG_TILE_COUNT, (uint8_t *)apple_neutral_tiles, (uint8_t *)frog_metasprites },
		{ BANK(apple_happy), FROG_TILE_COUNT, (uint8_t *)apple_happy_tiles, (uint8_t *)frog_metasprites },
		{ BANK(apple_laugh), FROG_TILE_COUNT, (uint8_t *)apple_laugh_tiles, (uint8_t *)frog_metasprites },
		{ BANK(apple_sad), FROG_TILE_COUNT, (uint8_t *)apple_sad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(apple_stressed), FROG_TILE_COUNT, (uint8_t *)apple_stressed_tiles, (uint8_t *)frog_metasprites },
		{ BANK(apple_angry), FROG_TILE_COUNT, (uint8_t *)apple_angry_tiles, (uint8_t *)frog_metasprites },
		{ BANK(apple_eat), FROG_TILE_COUNT, (uint8_t *)apple_eat_tiles, (uint8_t *)frog_metasprites },
		{ BANK(apple_yawn), FROG_TILE_COUNT, (uint8_t *)apple_yawn_tiles, (uint8_t *)frog_metasprites },
		{ BANK(apple_walk), FROG_TILE_COUNT, (uint8_t *)apple_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(apple_walk), FROG_TILE_COUNT, (uint8_t *)apple_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(apple_sleep), FROG_TILE_COUNT, (uint8_t *)apple_sleep_tiles, (uint8_t *)frog_metasprites }
	},
	{
		{ BANK(panda_neutral), FROG_TILE_COUNT, (uint8_t *)panda_neutral_tiles, (uint8_t *)frog_metasprites },
		{ BANK(panda_happy), FROG_TILE_COUNT, (uint8_t *)panda_happy_tiles, (uint8_t *)frog_metasprites },
		{ BANK(panda_laugh), FROG_TILE_COUNT, (uint8_t *)panda_laugh_tiles, (uint8_t *)frog_metasprites },
		{ BANK(panda_sad), FROG_TILE_COUNT, (uint8_t *)panda_sad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(panda_stressed), FROG_TILE_COUNT, (uint8_t *)panda_stressed_tiles, (uint8_t *)frog_metasprites },
		{ BANK(panda_angry), FROG_TILE_COUNT, (uint8_t *)panda_angry_tiles, (uint8_t *)frog_metasprites },
		{ BANK(panda_eat), FROG_TILE_COUNT, (uint8_t *)panda_eat_tiles, (uint8_t *)frog_metasprites },
		{ BANK(panda_yawn), FROG_TILE_COUNT, (uint8_t *)panda_yawn_tiles, (uint8_t *)frog_metasprites },
		{ BANK(panda_walk), FROG_TILE_COUNT, (uint8_t *)panda_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(panda_walk), FROG_TILE_COUNT, (uint8_t *)panda_walk_tiles, (uint8_t *)frog_metasprites },
		{ BANK(panda_sleep), FROG_TILE_COUNT, (uint8_t *)panda_sleep_tiles, (uint8_t *)frog_metasprites }
	},
	{
		{ BANK(dead_bad), FROG_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_bad), FROG_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_bad), FROG_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_bad), FROG_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_bad), FROG_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_bad), FROG_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_bad), FROG_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_bad), FROG_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_bad), FROG_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_bad), FROG_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_bad), FROG_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)frog_metasprites }
	},
	{
		{ BANK(dead_good), FROG_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_good), FROG_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_good), FROG_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_good), FROG_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_good), FROG_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_good), FROG_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_good), FROG_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_good), FROG_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_good), FROG_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_good), FROG_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)frog_metasprites },
		{ BANK(dead_good), FROG_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)frog_metasprites }
	}
};
