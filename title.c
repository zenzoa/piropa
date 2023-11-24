#pragma bank 255

#include <gbdk/platform.h>
#include <rand.h>

#include "scene.h"
#include "common.h"

#include "sprites/backgrounds/title.h"
#include "sprites/backgrounds/title_start.h"
#include "sprites/backgrounds/title_continue.h"
#include "sprites/backgrounds/title_reset.h"
#include "sprites/backgrounds/title_confirm.h"
#include "sprites/backgrounds/title_credits.h"
#include "sprites/arrows/select_arrow.h"

#define START_VRAM 0xe0
#define CONTINUE_VRAM 0x68
#define RESET_VRAM 0x72
#define CONFIRM_VRAM 0x78
#define CREDITS_VRAM 0xf0
#define BLANK_VRAM 0x2d

static const unsigned char start_tile_map[5] = { BLANK_VRAM, 0xe0, 0xe1, 0xe2, BLANK_VRAM };
static const unsigned char start_selected_tile_map[5] = { BLANK_VRAM, 0xe3, 0xe4, 0xe5, BLANK_VRAM };

static const unsigned char continue_tile_map[5] = { 0x68, 0x69, 0x6a, 0x6b, 0x6c };
static const unsigned char continue_selected_tile_map[5] = { 0x6d, 0x6e, 0x6f, 0x70, 0x71 };

static const unsigned char reset_tile_map[5] = { BLANK_VRAM, 0x72, 0x73, 0x74, BLANK_VRAM };
static const unsigned char reset_selected_tile_map[5] = { BLANK_VRAM, 0x75, 0x76, 0x77, BLANK_VRAM };

static const unsigned char confirm_reset_tile_map[5] = { 0x78, 0x79, 0x7a, 0x7b, 0x7c };

static const unsigned char credits_tile_map[5] = { 0xf0, 0xf1, 0xf2, 0xf3, 0xf4 };
static const unsigned char credits_selected_tile_map[5] = { 0xf5, 0xf6, 0xf7, 0xf8, 0xf9 };

#define TITLE_ITEM_CONTINUE 0
#define TITLE_ITEM_RESET 1
#define TITLE_ITEM_CONFIRM_RESET 2
#define TITLE_ITEM_CREDITS 3
static uint8_t selected_title_item;

#define START_TILE_Y 0x0d
#define CONTINUE_TILE_Y 0x0b
#define RESET_TILE_Y 0x0d
#define CREDITS_TILE_Y 0x0f

static uint8_t arrow_anim_counter;
static uint8_t arrow_anim_frame;

static uint8_t rand_seeded;

void draw_title_sprites(void) BANKED {
	arrow_anim_counter += 1;
	if (arrow_anim_counter >= 32) {
		arrow_anim_counter = 0;
		arrow_anim_frame = !arrow_anim_frame;

		switch(selected_title_item) {
			case TITLE_ITEM_CONTINUE:
				if (has_save) {
					move_sprite(0, 105 - arrow_anim_frame, 104);
					move_sprite(1, 152 + arrow_anim_frame, 104);
				} else {
					move_sprite(0, 112 - arrow_anim_frame, 120);
					move_sprite(1, 144 + arrow_anim_frame, 120);
				}
				break;

			case TITLE_ITEM_RESET:
				move_sprite(0, 111 - arrow_anim_frame, 120);
				move_sprite(1, 145 + arrow_anim_frame, 120);
				break;

			case TITLE_ITEM_CONFIRM_RESET:
				move_sprite(0, 103 - arrow_anim_frame, 120);
				move_sprite(1, 153 + arrow_anim_frame, 120);
				break;

			case TITLE_ITEM_CREDITS:
				move_sprite(0, 103 - arrow_anim_frame, 136);
				move_sprite(1, 153 + arrow_anim_frame, 136);
				break;
		}
	}
	last_sprite = 2;
}

static void select_title_item(uint8_t new_item) {
	selected_title_item = new_item;

	switch(selected_title_item) {
		case TITLE_ITEM_CONTINUE:
			if (has_save) {
				set_bkg_tiles(0x0d, CONTINUE_TILE_Y, 5, 1, continue_selected_tile_map);
				set_bkg_tiles(0x0d, RESET_TILE_Y, 5, 1, reset_tile_map);
			} else {
				set_bkg_tiles(0x0d, START_TILE_Y, 5, 1, start_selected_tile_map);
			}
			set_bkg_tiles(0x0d, CREDITS_TILE_Y, 5, 1, credits_tile_map);
			break;

		case TITLE_ITEM_RESET:
			set_bkg_tiles(0x0d, CONTINUE_TILE_Y, 5, 1, continue_tile_map);
			set_bkg_tiles(0x0d, RESET_TILE_Y, 5, 1, reset_selected_tile_map);
			set_bkg_tiles(0x0d, CREDITS_TILE_Y, 5, 1, credits_tile_map);
			break;

		case TITLE_ITEM_CONFIRM_RESET:
			set_bkg_tiles(0x0d, CONTINUE_TILE_Y, 5, 1, continue_tile_map);
			set_bkg_tiles(0x0d, RESET_TILE_Y, 5, 1, confirm_reset_tile_map);
			set_bkg_tiles(0x0d, CREDITS_TILE_Y, 5, 1, credits_tile_map);
			break;

		case TITLE_ITEM_CREDITS:
			if (has_save) {
				set_bkg_tiles(0x0d, CONTINUE_TILE_Y, 5, 1, continue_tile_map);
				set_bkg_tiles(0x0d, RESET_TILE_Y, 5, 1, reset_tile_map);
			} else {
				set_bkg_tiles(0x0d, START_TILE_Y, 5, 1, start_tile_map);
			}
			set_bkg_tiles(0x0d, CREDITS_TILE_Y, 5, 1, credits_selected_tile_map);
			break;
	}

	arrow_anim_counter = 32;
	arrow_anim_frame = 1;
}

void setup_title(void) BANKED {
	set_banked_bkg_data(BANK(title), 0, title_TILE_COUNT, title_tiles);
	set_banked_bkg_tiles(BANK(title), 0, 0, 20, 18, title_map);

	set_banked_sprite_data(BANK(select_arrow), 0xff, select_arrow_TILE_COUNT, select_arrow_tiles);
	set_sprite_tile(0, 0xff);
	set_sprite_tile(1, 0xff);
	set_sprite_prop(1, 32);

	if (has_save) {
		set_banked_bkg_data(BANK(title_continue), CONTINUE_VRAM, title_continue_TILE_COUNT, title_continue_tiles);
		set_banked_bkg_data(BANK(title_reset), RESET_VRAM, title_reset_TILE_COUNT, title_reset_tiles);
		set_banked_bkg_data(BANK(title_confirm), CONFIRM_VRAM, title_confirm_TILE_COUNT, title_confirm_tiles);
		set_banked_bkg_data(BANK(title_credits), CREDITS_VRAM, title_credits_TILE_COUNT, title_credits_tiles);

		select_title_item(TITLE_ITEM_CONTINUE);

	} else {
		set_banked_bkg_data(BANK(title_start), START_VRAM, title_start_TILE_COUNT, title_start_tiles);
		set_banked_bkg_data(BANK(title_credits), CREDITS_VRAM, title_credits_TILE_COUNT, title_credits_tiles);

		select_title_item(TITLE_ITEM_CONTINUE);
	}
}

void handle_title_input(uint8_t button_pressed) BANKED {
	switch(button_pressed) {
		case A_BUTTON:
			switch(selected_title_item) {
				case TITLE_ITEM_CONTINUE:
					if (!rand_seeded) {
						rand_seeded = TRUE;
						initrand(DIV_REG);
					}
					if (last_scene == TITLE) {
						transition_to_scene(FIELD, is_night);
					} else {
						transition_to_scene(last_scene, is_night);
					}
					break;
				case TITLE_ITEM_RESET:
					select_title_item(TITLE_ITEM_CONFIRM_RESET);
					break;
				case TITLE_ITEM_CONFIRM_RESET:
					reset_data();
					break;
				case TITLE_ITEM_CREDITS:
					transition_to_scene(CREDITS, is_night);
					break;
			}
			break;

		case B_BUTTON:
			if (selected_title_item == TITLE_ITEM_CONFIRM_RESET) {
				select_title_item(TITLE_ITEM_RESET);
			} else if (last_scene != TITLE && last_scene != CREDITS) {
				transition_to_scene(last_scene, is_night);
			}
			break;

		case UP_BUTTON:
			if (selected_title_item == TITLE_ITEM_CREDITS && has_save) {
				select_title_item(TITLE_ITEM_RESET);
			} else {
				select_title_item(TITLE_ITEM_CONTINUE);
			}
			break;

		case DOWN_BUTTON:
			if (selected_title_item == TITLE_ITEM_CONTINUE && has_save) {
				select_title_item(TITLE_ITEM_RESET);
			} else {
				select_title_item(TITLE_ITEM_CREDITS);
			}
			break;
	}
}
