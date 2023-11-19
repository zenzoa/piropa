#pragma bank 255

#include <gbdk/platform.h>
#include <rand.h>

#include "scene.h"
#include "shared_variables.h"

#include "sprites/backgrounds/title.h"
#include "sprites/backgrounds/title_start.h"
#include "sprites/backgrounds/title_continue.h"
#include "sprites/backgrounds/title_reset.h"
#include "sprites/backgrounds/title_confirm.h"
#include "sprites/misc_8x8/select_arrow.h"

BANKREF(title_bank)

const unsigned char start_tile_map[3] = { 0x70, 0x71, 0x72 };

const unsigned char continue_tile_map[5] = { 0x68, 0x69, 0x6a, 0x6b, 0x6c };
const unsigned char continue_selected_tile_map[5] = { 0x6d, 0x6e, 0x6f, 0x70, 0x71 };

const unsigned char reset_tile_map[5] = { 0x33, 0x72, 0x73, 0x74, 0x33 };
const unsigned char reset_selected_tile_map[5] = { 0x33, 0x75, 0x76, 0x77, 0x33 };

const unsigned char confirm_reset_tile_map[5] = { 0x78, 0x79, 0x7a, 0x7b, 0x7c };

uint8_t selected_title_item;
#define TITLE_ITEM_CONTINUE 0
#define TITLE_ITEM_RESET 1
#define TITLE_ITEM_CONFIRM_RESET 2

uint8_t arrow_anim_counter;
uint8_t arrow_anim_frame;

uint8_t rand_seeded = FALSE;

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
				case TITLE_ITEM_CONTINUE:
					move_sprite(0, 105 - arrow_anim_frame, 120);
					move_sprite(1, 152 + arrow_anim_frame, 120);
					break;

				case TITLE_ITEM_RESET:
					move_sprite(0, 111 - arrow_anim_frame, 136);
					move_sprite(1, 145 + arrow_anim_frame, 136);
					break;

				case TITLE_ITEM_CONFIRM_RESET:
					move_sprite(0, 103 - arrow_anim_frame, 136);
					move_sprite(1, 153 + arrow_anim_frame, 136);
					break;
			}
		}
	}

	*last_sprite = 2;
}

void select_title_item(uint8_t new_item) {
	selected_title_item = new_item;

	switch(selected_title_item) {
		case TITLE_ITEM_CONTINUE:
			set_bkg_tiles(0x0d, 0x0d, 5, 1, continue_selected_tile_map);
			set_bkg_tiles(0x0d, 0x0f, 5, 1, reset_tile_map);
			break;

		case TITLE_ITEM_RESET:
			set_bkg_tiles(0x0d, 0x0d, 5, 1, continue_tile_map);
			set_bkg_tiles(0x0d, 0x0f, 5, 1, reset_selected_tile_map);
			break;

		case TITLE_ITEM_CONFIRM_RESET:
			set_bkg_tiles(0x0d, 0x0f, 5, 1, confirm_reset_tile_map);
			break;
	}

	arrow_anim_counter = 32;
	arrow_anim_frame = 1;
}

void setup_title_data(void) NONBANKED {
	SWITCH_ROM(BANK(title));
	set_bkg_data(0, title_TILE_COUNT, title_tiles);
	set_bkg_tiles(0, 0, 20, 18, title_map);

	if (has_save) {
		SWITCH_ROM(BANK(title_continue));
		set_bkg_data(0x68, title_continue_TILE_COUNT, title_continue_tiles);

		SWITCH_ROM(BANK(title_reset));
		set_bkg_data(0x72, title_reset_TILE_COUNT, title_reset_tiles);

		SWITCH_ROM(BANK(title_confirm));
		set_bkg_data(0x78, title_confirm_TILE_COUNT, title_confirm_tiles);

	} else {
		SWITCH_ROM(BANK(title_start));
		set_bkg_data(0x70, title_start_TILE_COUNT, title_start_tiles);
	}

	SWITCH_ROM(BANK(select_arrow));
	set_sprite_data(0xff, select_arrow_TILE_COUNT, select_arrow_tiles);
}

void setup_title(void) {
	if (has_save) {
		set_bkg_tiles(0x0d, 0x0d, 5, 1, continue_tile_map);
		set_bkg_tiles(0x0d, 0x0f, 5, 1, reset_tile_map);

	} else {
		set_bkg_tiles(0x0e, 0x0f, 3, 1, start_tile_map);
	}

	set_sprite_tile(0, 0xff);
	set_sprite_tile(1, 0xff);
	set_sprite_prop(1, 32);

	if (has_save) {
		select_title_item(TITLE_ITEM_CONTINUE);
	}
}

void handle_title_input(uint8_t button_pressed) {
	switch(button_pressed) {
		case A_BUTTON:
			if (has_save) {
				switch(selected_title_item) {
					case TITLE_ITEM_CONTINUE:
						if (!rand_seeded) {
							rand_seeded = TRUE;
							initrand(DIV_REG);
						}
						start_transition_to_scene(last_scene, is_night);
						break;
					case TITLE_ITEM_RESET:
						select_title_item(TITLE_ITEM_CONFIRM_RESET);
						break;
					case TITLE_ITEM_CONFIRM_RESET:
						reset_data();
						break;
				}
			} else {
				start_transition_to_scene(FIELD, FALSE);
			}
			break;

		case B_BUTTON:
			if (has_save) {
				if (selected_title_item == TITLE_ITEM_CONFIRM_RESET) {
					select_title_item(TITLE_ITEM_RESET);
				}
			}
			break;

		case UP_BUTTON:
			if (has_save && selected_title_item != TITLE_ITEM_CONTINUE) {
				select_title_item(TITLE_ITEM_CONTINUE);
			}
			break;

		case DOWN_BUTTON:
			if (has_save && selected_title_item == TITLE_ITEM_CONTINUE) {
				select_title_item(TITLE_ITEM_RESET);
			}
			break;
	}
}
