#pragma bank 255

#include <gbdk/platform.h>

#include "scene.h"
#include "common.h"

#include "sprites/backgrounds/credits.h"

void setup_credits(void) BANKED {
	set_banked_bkg_data(BANK(credits), 0, credits_TILE_COUNT, credits_tiles);
	set_banked_bkg_tiles(BANK(credits), 0, 0, 20, 18, credits_map);
}
