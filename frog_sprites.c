#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "shared_variables.h"

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

#define FROG_VRAM_1 0x0
#define FROG_VRAM_2 0x20
uint8_t frog_vram = FROG_VRAM_1;

typedef struct frog_sprite_t {
	uint8_t bank;
	uint8_t tile_count;
	uint8_t * tiles;
	uint8_t * metasprites;
	uint8_t flipped;
} frog_sprite_t;

frog_sprite_t frog_sprite_data;
frog_sprite_t frog_sprite_data_table[14][11] = {
	{
		{ BANK(egg), egg_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)egg_metasprites, FALSE },
		{ BANK(egg), egg_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)egg_metasprites, FALSE },
		{ BANK(egg), egg_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)egg_metasprites, FALSE },
		{ BANK(egg), egg_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)egg_metasprites, FALSE },
		{ BANK(egg), egg_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)egg_metasprites, FALSE },
		{ BANK(egg), egg_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)egg_metasprites, FALSE },
		{ BANK(egg), egg_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)egg_metasprites, FALSE },
		{ BANK(egg), egg_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)egg_metasprites, FALSE },
		{ BANK(egg), egg_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)egg_metasprites, FALSE },
		{ BANK(egg), egg_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)egg_metasprites, FALSE },
		{ BANK(egg), egg_TILE_COUNT, (uint8_t *)egg_tiles, (uint8_t *)egg_metasprites, FALSE }
	},
	{
		{ BANK(tadpole_neutral), tadpole_neutral_TILE_COUNT, (uint8_t *)tadpole_neutral_tiles, (uint8_t *)tadpole_neutral_metasprites, FALSE },
		{ BANK(tadpole_happy), tadpole_happy_TILE_COUNT, (uint8_t *)tadpole_happy_tiles, (uint8_t *)tadpole_happy_metasprites, FALSE },
		{ BANK(tadpole_laugh), tadpole_laugh_TILE_COUNT, (uint8_t *)tadpole_laugh_tiles, (uint8_t *)tadpole_laugh_metasprites, FALSE },
		{ BANK(tadpole_sad), tadpole_sad_TILE_COUNT, (uint8_t *)tadpole_sad_tiles, (uint8_t *)tadpole_sad_metasprites, FALSE },
		{ BANK(tadpole_stressed), tadpole_stressed_TILE_COUNT, (uint8_t *)tadpole_stressed_tiles, (uint8_t *)tadpole_stressed_metasprites, FALSE },
		{ BANK(tadpole_angry), tadpole_angry_TILE_COUNT, (uint8_t *)tadpole_angry_tiles, (uint8_t *)tadpole_angry_metasprites, FALSE },
		{ BANK(tadpole_eat), tadpole_eat_TILE_COUNT, (uint8_t *)tadpole_eat_tiles, (uint8_t *)tadpole_eat_metasprites, FALSE },
		{ BANK(tadpole_yawn), tadpole_yawn_TILE_COUNT, (uint8_t *)tadpole_yawn_tiles, (uint8_t *)tadpole_yawn_metasprites, FALSE },
		{ BANK(tadpole_walk), tadpole_walk_TILE_COUNT, (uint8_t *)tadpole_walk_tiles, (uint8_t *)tadpole_walk_metasprites, FALSE },
		{ BANK(tadpole_walk), tadpole_walk_TILE_COUNT, (uint8_t *)tadpole_walk_tiles, (uint8_t *)tadpole_walk_metasprites, TRUE },
		{ BANK(tadpole_sleep), tadpole_sleep_TILE_COUNT, (uint8_t *)tadpole_sleep_tiles, (uint8_t *)tadpole_sleep_metasprites, FALSE }
	},
	{
		{ BANK(froglet_neutral), froglet_neutral_TILE_COUNT, (uint8_t *)froglet_neutral_tiles, (uint8_t *)froglet_neutral_metasprites, FALSE },
		{ BANK(froglet_happy), froglet_happy_TILE_COUNT, (uint8_t *)froglet_happy_tiles, (uint8_t *)froglet_happy_metasprites, FALSE },
		{ BANK(froglet_laugh), froglet_laugh_TILE_COUNT, (uint8_t *)froglet_laugh_tiles, (uint8_t *)froglet_laugh_metasprites, FALSE },
		{ BANK(froglet_sad), froglet_sad_TILE_COUNT, (uint8_t *)froglet_sad_tiles, (uint8_t *)froglet_sad_metasprites, FALSE },
		{ BANK(froglet_stressed), froglet_stressed_TILE_COUNT, (uint8_t *)froglet_stressed_tiles, (uint8_t *)froglet_stressed_metasprites, FALSE },
		{ BANK(froglet_angry), froglet_angry_TILE_COUNT, (uint8_t *)froglet_angry_tiles, (uint8_t *)froglet_angry_metasprites, FALSE },
		{ BANK(froglet_eat), froglet_eat_TILE_COUNT, (uint8_t *)froglet_eat_tiles, (uint8_t *)froglet_eat_metasprites, FALSE },
		{ BANK(froglet_yawn), froglet_yawn_TILE_COUNT, (uint8_t *)froglet_yawn_tiles, (uint8_t *)froglet_yawn_metasprites, FALSE },
		{ BANK(froglet_walk), froglet_walk_TILE_COUNT, (uint8_t *)froglet_walk_tiles, (uint8_t *)froglet_walk_metasprites, FALSE },
		{ BANK(froglet_walk), froglet_walk_TILE_COUNT, (uint8_t *)froglet_walk_tiles, (uint8_t *)froglet_walk_metasprites, TRUE },
		{ BANK(froglet_sleep), froglet_sleep_TILE_COUNT, (uint8_t *)froglet_sleep_tiles, (uint8_t *)froglet_sleep_metasprites, FALSE }
	},
	{
		{ BANK(teen_norm_neutral), teen_norm_neutral_TILE_COUNT, (uint8_t *)teen_norm_neutral_tiles, (uint8_t *)teen_norm_neutral_metasprites, FALSE },
		{ BANK(teen_norm_happy), teen_norm_happy_TILE_COUNT, (uint8_t *)teen_norm_happy_tiles, (uint8_t *)teen_norm_happy_metasprites, FALSE },
		{ BANK(teen_norm_laugh), teen_norm_laugh_TILE_COUNT, (uint8_t *)teen_norm_laugh_tiles, (uint8_t *)teen_norm_laugh_metasprites, FALSE },
		{ BANK(teen_norm_sad), teen_norm_sad_TILE_COUNT, (uint8_t *)teen_norm_sad_tiles, (uint8_t *)teen_norm_sad_metasprites, FALSE },
		{ BANK(teen_norm_stressed), teen_norm_stressed_TILE_COUNT, (uint8_t *)teen_norm_stressed_tiles, (uint8_t *)teen_norm_stressed_metasprites, FALSE },
		{ BANK(teen_norm_angry), teen_norm_angry_TILE_COUNT, (uint8_t *)teen_norm_angry_tiles, (uint8_t *)teen_norm_angry_metasprites, FALSE },
		{ BANK(teen_norm_eat), teen_norm_eat_TILE_COUNT, (uint8_t *)teen_norm_eat_tiles, (uint8_t *)teen_norm_eat_metasprites, FALSE },
		{ BANK(teen_norm_yawn), teen_norm_yawn_TILE_COUNT, (uint8_t *)teen_norm_yawn_tiles, (uint8_t *)teen_norm_yawn_metasprites, FALSE },
		{ BANK(teen_norm_walk), teen_norm_walk_TILE_COUNT, (uint8_t *)teen_norm_walk_tiles, (uint8_t *)teen_norm_walk_metasprites, FALSE },
		{ BANK(teen_norm_walk), teen_norm_walk_TILE_COUNT, (uint8_t *)teen_norm_walk_tiles, (uint8_t *)teen_norm_walk_metasprites, TRUE },
		{ BANK(teen_norm_sleep), teen_norm_sleep_TILE_COUNT, (uint8_t *)teen_norm_sleep_tiles, (uint8_t *)teen_norm_sleep_metasprites, FALSE }
	},
	{
		{ BANK(teen_tail_neutral), teen_tail_neutral_TILE_COUNT, (uint8_t *)teen_tail_neutral_tiles, (uint8_t *)teen_tail_neutral_metasprites, FALSE },
		{ BANK(teen_tail_happy), teen_tail_happy_TILE_COUNT, (uint8_t *)teen_tail_happy_tiles, (uint8_t *)teen_tail_happy_metasprites, FALSE },
		{ BANK(teen_tail_laugh), teen_tail_laugh_TILE_COUNT, (uint8_t *)teen_tail_laugh_tiles, (uint8_t *)teen_tail_laugh_metasprites, FALSE },
		{ BANK(teen_tail_sad), teen_tail_sad_TILE_COUNT, (uint8_t *)teen_tail_sad_tiles, (uint8_t *)teen_tail_sad_metasprites, FALSE },
		{ BANK(teen_tail_stressed), teen_tail_stressed_TILE_COUNT, (uint8_t *)teen_tail_stressed_tiles, (uint8_t *)teen_tail_stressed_metasprites, FALSE },
		{ BANK(teen_tail_angry), teen_tail_angry_TILE_COUNT, (uint8_t *)teen_tail_angry_tiles, (uint8_t *)teen_tail_angry_metasprites, FALSE },
		{ BANK(teen_tail_eat), teen_tail_eat_TILE_COUNT, (uint8_t *)teen_tail_eat_tiles, (uint8_t *)teen_tail_eat_metasprites, FALSE },
		{ BANK(teen_tail_yawn), teen_tail_yawn_TILE_COUNT, (uint8_t *)teen_tail_yawn_tiles, (uint8_t *)teen_tail_yawn_metasprites, FALSE },
		{ BANK(teen_tail_walk), teen_tail_walk_TILE_COUNT, (uint8_t *)teen_tail_walk_tiles, (uint8_t *)teen_tail_walk_metasprites, FALSE },
		{ BANK(teen_tail_walk), teen_tail_walk_TILE_COUNT, (uint8_t *)teen_tail_walk_tiles, (uint8_t *)teen_tail_walk_metasprites, TRUE },
		{ BANK(teen_tail_sleep), teen_tail_sleep_TILE_COUNT, (uint8_t *)teen_tail_sleep_tiles, (uint8_t *)teen_tail_sleep_metasprites, FALSE }
	},
	{
		{ BANK(teen_bw_neutral), teen_bw_neutral_TILE_COUNT, (uint8_t *)teen_bw_neutral_tiles, (uint8_t *)teen_bw_neutral_metasprites, FALSE },
		{ BANK(teen_bw_happy), teen_bw_happy_TILE_COUNT, (uint8_t *)teen_bw_happy_tiles, (uint8_t *)teen_bw_happy_metasprites, FALSE },
		{ BANK(teen_bw_laugh), teen_bw_laugh_TILE_COUNT, (uint8_t *)teen_bw_laugh_tiles, (uint8_t *)teen_bw_laugh_metasprites, FALSE },
		{ BANK(teen_bw_sad), teen_bw_sad_TILE_COUNT, (uint8_t *)teen_bw_sad_tiles, (uint8_t *)teen_bw_sad_metasprites, FALSE },
		{ BANK(teen_bw_stressed), teen_bw_stressed_TILE_COUNT, (uint8_t *)teen_bw_stressed_tiles, (uint8_t *)teen_bw_stressed_metasprites, FALSE },
		{ BANK(teen_bw_angry), teen_bw_angry_TILE_COUNT, (uint8_t *)teen_bw_angry_tiles, (uint8_t *)teen_bw_angry_metasprites, FALSE },
		{ BANK(teen_bw_eat), teen_bw_eat_TILE_COUNT, (uint8_t *)teen_bw_eat_tiles, (uint8_t *)teen_bw_eat_metasprites, FALSE },
		{ BANK(teen_bw_yawn), teen_bw_yawn_TILE_COUNT, (uint8_t *)teen_bw_yawn_tiles, (uint8_t *)teen_bw_yawn_metasprites, FALSE },
		{ BANK(teen_bw_walk), teen_bw_walk_TILE_COUNT, (uint8_t *)teen_bw_walk_tiles, (uint8_t *)teen_bw_walk_metasprites, FALSE },
		{ BANK(teen_bw_walk), teen_bw_walk_TILE_COUNT, (uint8_t *)teen_bw_walk_tiles, (uint8_t *)teen_bw_walk_metasprites, TRUE },
		{ BANK(teen_bw_sleep), teen_bw_sleep_TILE_COUNT, (uint8_t *)teen_bw_sleep_tiles, (uint8_t *)teen_bw_sleep_metasprites, FALSE }
	},
	{
		{ BANK(norm_neutral), norm_neutral_TILE_COUNT, (uint8_t *)norm_neutral_tiles, (uint8_t *)norm_neutral_metasprites, FALSE },
		{ BANK(norm_happy), norm_happy_TILE_COUNT, (uint8_t *)norm_happy_tiles, (uint8_t *)norm_happy_metasprites, FALSE },
		{ BANK(norm_laugh), norm_laugh_TILE_COUNT, (uint8_t *)norm_laugh_tiles, (uint8_t *)norm_laugh_metasprites, FALSE },
		{ BANK(norm_sad), norm_sad_TILE_COUNT, (uint8_t *)norm_sad_tiles, (uint8_t *)norm_sad_metasprites, FALSE },
		{ BANK(norm_stressed), norm_stressed_TILE_COUNT, (uint8_t *)norm_stressed_tiles, (uint8_t *)norm_stressed_metasprites, FALSE },
		{ BANK(norm_angry), norm_angry_TILE_COUNT, (uint8_t *)norm_angry_tiles, (uint8_t *)norm_angry_metasprites, FALSE },
		{ BANK(norm_eat), norm_eat_TILE_COUNT, (uint8_t *)norm_eat_tiles, (uint8_t *)norm_eat_metasprites, FALSE },
		{ BANK(norm_yawn), norm_yawn_TILE_COUNT, (uint8_t *)norm_yawn_tiles, (uint8_t *)norm_yawn_metasprites, FALSE },
		{ BANK(norm_walk), norm_walk_TILE_COUNT, (uint8_t *)norm_walk_tiles, (uint8_t *)norm_walk_metasprites, FALSE },
		{ BANK(norm_walk), norm_walk_TILE_COUNT, (uint8_t *)norm_walk_tiles, (uint8_t *)norm_walk_metasprites, TRUE },
		{ BANK(norm_sleep), norm_sleep_TILE_COUNT, (uint8_t *)norm_sleep_tiles, (uint8_t *)norm_sleep_metasprites, FALSE }
	},
	{
		{ BANK(mush_neutral), mush_neutral_TILE_COUNT, (uint8_t *)mush_neutral_tiles, (uint8_t *)mush_neutral_metasprites, FALSE },
		{ BANK(mush_happy), mush_happy_TILE_COUNT, (uint8_t *)mush_happy_tiles, (uint8_t *)mush_happy_metasprites, FALSE },
		{ BANK(mush_laugh), mush_laugh_TILE_COUNT, (uint8_t *)mush_laugh_tiles, (uint8_t *)mush_laugh_metasprites, FALSE },
		{ BANK(mush_sad), mush_sad_TILE_COUNT, (uint8_t *)mush_sad_tiles, (uint8_t *)mush_sad_metasprites, FALSE },
		{ BANK(mush_stressed), mush_stressed_TILE_COUNT, (uint8_t *)mush_stressed_tiles, (uint8_t *)mush_stressed_metasprites, FALSE },
		{ BANK(mush_angry), mush_angry_TILE_COUNT, (uint8_t *)mush_angry_tiles, (uint8_t *)mush_angry_metasprites, FALSE },
		{ BANK(mush_eat), mush_eat_TILE_COUNT, (uint8_t *)mush_eat_tiles, (uint8_t *)mush_eat_metasprites, FALSE },
		{ BANK(mush_yawn), mush_yawn_TILE_COUNT, (uint8_t *)mush_yawn_tiles, (uint8_t *)mush_yawn_metasprites, FALSE },
		{ BANK(mush_walk), mush_walk_TILE_COUNT, (uint8_t *)mush_walk_tiles, (uint8_t *)mush_walk_metasprites, FALSE },
		{ BANK(mush_walk), mush_walk_TILE_COUNT, (uint8_t *)mush_walk_tiles, (uint8_t *)mush_walk_metasprites, TRUE },
		{ BANK(mush_sleep), mush_sleep_TILE_COUNT, (uint8_t *)mush_sleep_tiles, (uint8_t *)mush_sleep_metasprites, FALSE }
	},
	{
		{ BANK(axo_neutral), axo_neutral_TILE_COUNT, (uint8_t *)axo_neutral_tiles, (uint8_t *)axo_neutral_metasprites, FALSE },
		{ BANK(axo_happy), axo_happy_TILE_COUNT, (uint8_t *)axo_happy_tiles, (uint8_t *)axo_happy_metasprites, FALSE },
		{ BANK(axo_laugh), axo_laugh_TILE_COUNT, (uint8_t *)axo_laugh_tiles, (uint8_t *)axo_laugh_metasprites, FALSE },
		{ BANK(axo_sad), axo_sad_TILE_COUNT, (uint8_t *)axo_sad_tiles, (uint8_t *)axo_sad_metasprites, FALSE },
		{ BANK(axo_stressed), axo_stressed_TILE_COUNT, (uint8_t *)axo_stressed_tiles, (uint8_t *)axo_stressed_metasprites, FALSE },
		{ BANK(axo_angry), axo_angry_TILE_COUNT, (uint8_t *)axo_angry_tiles, (uint8_t *)axo_angry_metasprites, FALSE },
		{ BANK(axo_eat), axo_eat_TILE_COUNT, (uint8_t *)axo_eat_tiles, (uint8_t *)axo_eat_metasprites, FALSE },
		{ BANK(axo_yawn), axo_yawn_TILE_COUNT, (uint8_t *)axo_yawn_tiles, (uint8_t *)axo_yawn_metasprites, FALSE },
		{ BANK(axo_walk), axo_walk_TILE_COUNT, (uint8_t *)axo_walk_tiles, (uint8_t *)axo_walk_metasprites, FALSE },
		{ BANK(axo_walk), axo_walk_TILE_COUNT, (uint8_t *)axo_walk_tiles, (uint8_t *)axo_walk_metasprites, TRUE },
		{ BANK(axo_sleep), axo_sleep_TILE_COUNT, (uint8_t *)axo_sleep_tiles, (uint8_t *)axo_sleep_metasprites, FALSE }
	},
	{
		{ BANK(dino_neutral), dino_neutral_TILE_COUNT, (uint8_t *)dino_neutral_tiles, (uint8_t *)dino_neutral_metasprites, FALSE },
		{ BANK(dino_happy), dino_happy_TILE_COUNT, (uint8_t *)dino_happy_tiles, (uint8_t *)dino_happy_metasprites, FALSE },
		{ BANK(dino_laugh), dino_laugh_TILE_COUNT, (uint8_t *)dino_laugh_tiles, (uint8_t *)dino_laugh_metasprites, FALSE },
		{ BANK(dino_sad), dino_sad_TILE_COUNT, (uint8_t *)dino_sad_tiles, (uint8_t *)dino_sad_metasprites, FALSE },
		{ BANK(dino_stressed), dino_stressed_TILE_COUNT, (uint8_t *)dino_stressed_tiles, (uint8_t *)dino_stressed_metasprites, FALSE },
		{ BANK(dino_angry), dino_angry_TILE_COUNT, (uint8_t *)dino_angry_tiles, (uint8_t *)dino_angry_metasprites, FALSE },
		{ BANK(dino_eat), dino_eat_TILE_COUNT, (uint8_t *)dino_eat_tiles, (uint8_t *)dino_eat_metasprites, FALSE },
		{ BANK(dino_yawn), dino_yawn_TILE_COUNT, (uint8_t *)dino_yawn_tiles, (uint8_t *)dino_yawn_metasprites, FALSE },
		{ BANK(dino_walk), dino_walk_TILE_COUNT, (uint8_t *)dino_walk_tiles, (uint8_t *)dino_walk_metasprites, FALSE },
		{ BANK(dino_walk), dino_walk_TILE_COUNT, (uint8_t *)dino_walk_tiles, (uint8_t *)dino_walk_metasprites, TRUE },
		{ BANK(dino_sleep), dino_sleep_TILE_COUNT, (uint8_t *)dino_sleep_tiles, (uint8_t *)dino_sleep_metasprites, FALSE }
	},
	{
		{ BANK(apple_neutral), apple_neutral_TILE_COUNT, (uint8_t *)apple_neutral_tiles, (uint8_t *)apple_neutral_metasprites, FALSE },
		{ BANK(apple_happy), apple_happy_TILE_COUNT, (uint8_t *)apple_happy_tiles, (uint8_t *)apple_happy_metasprites, FALSE },
		{ BANK(apple_laugh), apple_laugh_TILE_COUNT, (uint8_t *)apple_laugh_tiles, (uint8_t *)apple_laugh_metasprites, FALSE },
		{ BANK(apple_sad), apple_sad_TILE_COUNT, (uint8_t *)apple_sad_tiles, (uint8_t *)apple_sad_metasprites, FALSE },
		{ BANK(apple_stressed), apple_stressed_TILE_COUNT, (uint8_t *)apple_stressed_tiles, (uint8_t *)apple_stressed_metasprites, FALSE },
		{ BANK(apple_angry), apple_angry_TILE_COUNT, (uint8_t *)apple_angry_tiles, (uint8_t *)apple_angry_metasprites, FALSE },
		{ BANK(apple_eat), apple_eat_TILE_COUNT, (uint8_t *)apple_eat_tiles, (uint8_t *)apple_eat_metasprites, FALSE },
		{ BANK(apple_yawn), apple_yawn_TILE_COUNT, (uint8_t *)apple_yawn_tiles, (uint8_t *)apple_yawn_metasprites, FALSE },
		{ BANK(apple_walk), apple_walk_TILE_COUNT, (uint8_t *)apple_walk_tiles, (uint8_t *)apple_walk_metasprites, FALSE },
		{ BANK(apple_walk), apple_walk_TILE_COUNT, (uint8_t *)apple_walk_tiles, (uint8_t *)apple_walk_metasprites, TRUE },
		{ BANK(apple_sleep), apple_sleep_TILE_COUNT, (uint8_t *)apple_sleep_tiles, (uint8_t *)apple_sleep_metasprites, FALSE }
	},
	{
		{ BANK(panda_neutral), panda_neutral_TILE_COUNT, (uint8_t *)panda_neutral_tiles, (uint8_t *)panda_neutral_metasprites, FALSE },
		{ BANK(panda_happy), panda_happy_TILE_COUNT, (uint8_t *)panda_happy_tiles, (uint8_t *)panda_happy_metasprites, FALSE },
		{ BANK(panda_laugh), panda_laugh_TILE_COUNT, (uint8_t *)panda_laugh_tiles, (uint8_t *)panda_laugh_metasprites, FALSE },
		{ BANK(panda_sad), panda_sad_TILE_COUNT, (uint8_t *)panda_sad_tiles, (uint8_t *)panda_sad_metasprites, FALSE },
		{ BANK(panda_stressed), panda_stressed_TILE_COUNT, (uint8_t *)panda_stressed_tiles, (uint8_t *)panda_stressed_metasprites, FALSE },
		{ BANK(panda_angry), panda_angry_TILE_COUNT, (uint8_t *)panda_angry_tiles, (uint8_t *)panda_angry_metasprites, FALSE },
		{ BANK(panda_eat), panda_eat_TILE_COUNT, (uint8_t *)panda_eat_tiles, (uint8_t *)panda_eat_metasprites, FALSE },
		{ BANK(panda_yawn), panda_yawn_TILE_COUNT, (uint8_t *)panda_yawn_tiles, (uint8_t *)panda_yawn_metasprites, FALSE },
		{ BANK(panda_walk), panda_walk_TILE_COUNT, (uint8_t *)panda_walk_tiles, (uint8_t *)panda_walk_metasprites, FALSE },
		{ BANK(panda_walk), panda_walk_TILE_COUNT, (uint8_t *)panda_walk_tiles, (uint8_t *)panda_walk_metasprites, TRUE },
		{ BANK(panda_sleep), panda_sleep_TILE_COUNT, (uint8_t *)panda_sleep_tiles, (uint8_t *)panda_sleep_metasprites, FALSE }
	},
	{
		{ BANK(dead_good), dead_good_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)dead_good_metasprites, FALSE },
		{ BANK(dead_good), dead_good_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)dead_good_metasprites, FALSE },
		{ BANK(dead_good), dead_good_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)dead_good_metasprites, FALSE },
		{ BANK(dead_good), dead_good_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)dead_good_metasprites, FALSE },
		{ BANK(dead_good), dead_good_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)dead_good_metasprites, FALSE },
		{ BANK(dead_good), dead_good_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)dead_good_metasprites, FALSE },
		{ BANK(dead_good), dead_good_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)dead_good_metasprites, FALSE },
		{ BANK(dead_good), dead_good_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)dead_good_metasprites, FALSE },
		{ BANK(dead_good), dead_good_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)dead_good_metasprites, FALSE },
		{ BANK(dead_good), dead_good_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)dead_good_metasprites, FALSE },
		{ BANK(dead_good), dead_good_TILE_COUNT, (uint8_t *)dead_good_tiles, (uint8_t *)dead_good_metasprites, FALSE }
	},
	{
		{ BANK(dead_bad), dead_bad_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)dead_bad_metasprites, FALSE },
		{ BANK(dead_bad), dead_bad_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)dead_bad_metasprites, FALSE },
		{ BANK(dead_bad), dead_bad_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)dead_bad_metasprites, FALSE },
		{ BANK(dead_bad), dead_bad_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)dead_bad_metasprites, FALSE },
		{ BANK(dead_bad), dead_bad_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)dead_bad_metasprites, FALSE },
		{ BANK(dead_bad), dead_bad_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)dead_bad_metasprites, FALSE },
		{ BANK(dead_bad), dead_bad_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)dead_bad_metasprites, FALSE },
		{ BANK(dead_bad), dead_bad_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)dead_bad_metasprites, FALSE },
		{ BANK(dead_bad), dead_bad_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)dead_bad_metasprites, FALSE },
		{ BANK(dead_bad), dead_bad_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)dead_bad_metasprites, FALSE },
		{ BANK(dead_bad), dead_bad_TILE_COUNT, (uint8_t *)dead_bad_tiles, (uint8_t *)dead_bad_metasprites, FALSE }
	}
};


void swap_frog_vram(void) {
	if (frog_vram == FROG_VRAM_1) {
		frog_vram = FROG_VRAM_2;
	} else {
		frog_vram = FROG_VRAM_1;
	}
}

void set_frog_sprite_data(void) {
	saved_bank = _current_bank;

	frog_sprite_data = frog_sprite_data_table[stage][anim];
	SWITCH_ROM(frog_sprite_data.bank);
	set_sprite_data(frog_vram, frog_sprite_data.tile_count, frog_sprite_data.tiles);

	SWITCH_ROM(saved_bank);
}

void draw_frog_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite) {
	saved_bank = _current_bank;

	// frog_sprite_data = frog_sprite_data_table[stage][anim];

	SWITCH_ROM(frog_sprite_data.bank);

	if (frog_sprite_data.flipped) {
		*last_sprite += move_metasprite_flipx(
			((metasprite_t**)frog_sprite_data.metasprites)[frame],
			frog_vram, 0, *last_sprite,
			x + 32, y
		);
	} else {
		*last_sprite += move_metasprite_ex(
			((metasprite_t**)frog_sprite_data.metasprites)[frame],
			frog_vram, 0, *last_sprite,
			x, y
		);
	}

	SWITCH_ROM(saved_bank);
}
