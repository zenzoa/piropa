#include <gbdk/platform.h>

#include "scene.h"
#include "audio.h"
#include "common.h"
#include "frog_sprites.h"

#include "sprites/backgrounds/endscreen.h"
#include "sprites/death/ghost.h"
#include "sprites/death/wing.h"

static sprite_data_t frog_sprite;
static uint8_t frog_palette = GREEN_PALETTE;

#define FROG_VRAM_1 0x0
#define FROG_VRAM_2 0x20
static uint8_t frog_vram = FROG_VRAM_1;

static uint8_t anim_counter;
static uint8_t anim_speed;
static uint8_t going_left;

#define WING_VRAM 0xB4
static uint8_t wings_frame;

#define GHOST_VRAM 0xBC
static uint8_t show_ghost;
static uint8_t ghost_x;
static uint8_t ghost_y;
static uint8_t ghost_flip_counter;
static uint8_t ghost_flip;

static void swap_frog_vram(void) {
	if (frog_vram == FROG_VRAM_1) {
		frog_vram = FROG_VRAM_2;
	} else {
		frog_vram = FROG_VRAM_1;
	}
}

static void update_frog_sprite_data(void) {
	frog_sprite = frog_sprite_table[stage][anim];
	swap_frog_vram();
	set_banked_sprite_data(frog_sprite.bank, frog_vram, frog_sprite.tile_count, frog_sprite.tiles);
}

static void end_death_anim(void) {
	death_anim_complete = TRUE;
	transition_to_scene(FIELD, is_night);
}

static void update_good_death(void) {
	anim_counter += 1;
	if (anim_counter >= anim_speed) {
		anim_counter = 0;
		frog_y -= 2;
		if (anim_speed > 8) {
			anim_speed -= 2;
		}
		if (frog_y == 60) {
			play_music(DEATH_MUSIC);
		} else if (frog_y > 144 && frog_y <= 240) {
			end_death_anim();
		}
		wings_frame = !wings_frame;
	}
}

static void update_bad_death(void) {
	anim_counter += 1;
	if (anim_counter >= anim_speed) {
		anim_counter = 0;
		if (anim == ANIM_DEAD) {
			ghost_y -= 1;
			ghost_flip_counter += 1;
			if (ghost_flip_counter >= 4) {
				ghost_flip_counter = 0;
				ghost_flip = !ghost_flip;
			}
			if (ghost_y > 144 && ghost_y <= 240) {
				end_death_anim();
			}

		} else {
			anim_speed += 1;
			if (anim_speed <= 26) {
				if (going_left) {
					frog_x -= 1;
				} else {
					frog_x += 1;
				}
				going_left = !going_left;
			} else if (anim_speed >= 28) {
				anim = ANIM_DEAD;
				update_frog_sprite_data();
				show_ghost = TRUE;
				ghost_x = frog_x + 8;
				ghost_y = frog_y + 8;
				anim_speed = 3;
				play_music(DEATH_MUSIC);
			}
		}
	}
}

void update_endscreen(void) {
	if (good_death) {
		update_good_death();
	} else {
		update_bad_death();
	}
}

void draw_endscreen_sprites(void) {
	if (stage != STAGE_DEAD_GOOD && stage != STAGE_DEAD_BAD) {
		draw_banked_sprite(frog_sprite.bank, frog_sprite.metasprites, 0, frog_vram, frog_palette, frog_x, frog_y);
	}
	if (good_death) {
		draw_banked_sprite(BANK(wing), wing_metasprites, wings_frame, WING_VRAM, GREEN_PALETTE, frog_x - 8, frog_y - 1);
		draw_banked_sprite_flip(BANK(wing), wing_metasprites, wings_frame, WING_VRAM, GREEN_PALETTE, frog_x + 40, frog_y - 1);
	} else if (show_ghost) {
		if (ghost_flip) {
			draw_banked_sprite_flip(BANK(ghost), ghost_metasprites, 0, GHOST_VRAM, GREEN_PALETTE, ghost_x + 16, ghost_y);
		} else {
			draw_banked_sprite(BANK(ghost), ghost_metasprites, 0, GHOST_VRAM, GREEN_PALETTE, ghost_x, ghost_y);
		}
	}
}

void setup_endscreen(void) {
	set_banked_bkg_data(BANK(endscreen), 0, endscreen_TILE_COUNT, endscreen_tiles);
	set_banked_bkg_tiles(BANK(endscreen), 0, 0, 20, 18, endscreen_map);

	hide_sprites_range(0, MAX_HARDWARE_SPRITES);

	set_banked_sprite_data(BANK(ghost), GHOST_VRAM, ghost_TILE_COUNT, ghost_tiles);
	set_banked_sprite_data(BANK(wing), WING_VRAM, wing_TILE_COUNT, wing_tiles);

	if (good_death) {
		anim = ANIM_HAPPY;
	} else {
		anim = ANIM_SAD;
	}
	update_frog_sprite_data();

	if (stage == STAGE_TEEN_BW || stage == STAGE_PANDA || stage == STAGE_APPLE || stage == STAGE_MUSH) {
		frog_palette = BROWN_PALETTE;
	} else if (stage == STAGE_AXO) {
		frog_palette = PINK_PALETTE;
	} else {
		frog_palette = GREEN_PALETTE;
	}

	frog_x = 72;
	frog_y = 80;

	anim_counter = 0;
	anim_speed = 12;
	going_left = FALSE;

	wings_frame = 0;

	show_ghost = 0;
	ghost_x = 0;
	ghost_y = 0;
	ghost_flip_counter = 0;
	ghost_flip = 0;

	play_music(NO_MUSIC);
	if (good_death) {
		anim_speed = 24;
		play_sfx(SFX_DIE);
	} else {
		play_sfx(SFX_SAD);
	}
}
