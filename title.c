#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "save.h"

#include "sprites/backgrounds/title.h"
#include "sprites/backgrounds/title_start.h"
#include "sprites/backgrounds/title_continue.h"
#include "sprites/backgrounds/title_restart.h"
#include "sprites/backgrounds/title_confirm.h"
#include "sprites/misc_8x8/select_arrow.h"

const unsigned char start_tile_map[3] = { 0x70, 0x71, 0x72 };

const unsigned char continue_tile_map[5] = { 0x68, 0x69, 0x6a, 0x6b, 0x6c };
const unsigned char continue_selected_tile_map[5] = { 0x6d, 0x6e, 0x6f, 0x70, 0x71 };

const unsigned char restart_tile_map[5] = { 0x72, 0x73, 0x74, 0x75, 0x76 };
const unsigned char restart_selected_tile_map[5] = { 0x77, 0x78, 0x79, 0x7a, 0x7b };

const unsigned char confirm_restart_tile_map[5] = { 0xcb, 0xcc, 0xcd, 0xce, 0xcf };

uint8_t selected_title_item;
#define CONTINUE 0
#define RESTART 1
#define CONFIRM_RESTART 2

uint8_t arrow_anim_counter;
uint8_t arrow_anim_frame;

void draw_title_sprites(uint8_t *last_sprite) {
	arrow_anim_counter += 1;
	if (arrow_anim_counter >= 32) {
		arrow_anim_counter = 0;
		arrow_anim_frame = !arrow_anim_frame;

		if (!has_save) {
			move_sprite(0, 112 - arrow_anim_frame, 136);
			move_sprite(1, 144 + arrow_anim_frame, 136);

		} else {
			switch(selected_title_item) {
				case CONTINUE:
					move_sprite(0, 105 - arrow_anim_frame, 120);
					move_sprite(1, 152 + arrow_anim_frame, 120);
					break;

				case RESTART:
					move_sprite(0, 108 - arrow_anim_frame, 136);
					move_sprite(1, 149 + arrow_anim_frame, 136);
					break;

				case CONFIRM_RESTART:
					move_sprite(0, 103 - arrow_anim_frame, 136);
					move_sprite(1, 154 + arrow_anim_frame, 136);
					break;
			}
		}
	}

	*last_sprite = 2;
}

void select_title_item(uint8_t new_item) {
	selected_title_item = new_item;

	switch(selected_title_item) {
		case CONTINUE:
			set_bkg_tiles(0x0d, 0x0d, 5, 1, continue_selected_tile_map);
			set_bkg_tiles(0x0d, 0x0f, 5, 1, restart_tile_map);
			break;

		case RESTART:
			set_bkg_tiles(0x0d, 0x0d, 5, 1, continue_tile_map);
			set_bkg_tiles(0x0d, 0x0f, 5, 1, restart_selected_tile_map);
			break;

		case CONFIRM_RESTART:
			set_bkg_tiles(0x0d, 0x0f, 5, 1, confirm_restart_tile_map);
			break;
	}

	arrow_anim_counter = 32;
	arrow_anim_frame = 1;
}

void setup_title(void) {
	SWITCH_ROM(BANK(title));
	set_bkg_data(0, title_TILE_COUNT, title_tiles);
	set_bkg_tiles(0, 0, 20, 18, title_map);

	if (has_save) {
		SWITCH_ROM(BANK(title_continue));
		set_bkg_data(0x68, title_continue_TILE_COUNT, title_continue_tiles);
		set_bkg_tiles(0x0d, 0x0d, 5, 1, continue_tile_map);

		SWITCH_ROM(BANK(title_restart));
		set_bkg_data(0x72, title_restart_TILE_COUNT, title_restart_tiles);
		set_bkg_tiles(0x0d, 0x0f, 5, 1, restart_tile_map);

		SWITCH_ROM(BANK(title_confirm));
		set_bkg_data(0xcb, title_confirm_TILE_COUNT, title_confirm_tiles);

	} else {
		SWITCH_ROM(BANK(title_start));
		set_bkg_data(0x70, title_start_TILE_COUNT, title_start_tiles);
		set_bkg_tiles(0x0e, 0x0f, 3, 1, start_tile_map);
	}

	SWITCH_ROM(BANK(select_arrow));
	set_sprite_data(0, select_arrow_TILE_COUNT, select_arrow_tiles);
	set_sprite_tile(0, 0);
	set_sprite_tile(1, 0);
	set_sprite_prop(1, 32);

	select_title_item(CONTINUE);
}
