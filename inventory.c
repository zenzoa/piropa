#pragma bank 255

#include <gbdk/platform.h>

#include "hand.h"
#include "scene.h"
#include "common.h"

#include "sprites/backgrounds/inventory.h"
#include "sprites/backgrounds/inventory_bugs.h"
#include "sprites/backgrounds/numbers.h"
#include "sprites/arrows/select_arrow.h"

static uint8_t selected_inventory_item = BUG_FLY;
static uint8_t arrow_anim_counter;
static uint8_t arrow_anim_frame;

void put_bug_in_inventory(uint8_t bug_type) BANKED {
	switch(bug_type) {
		case BUG_FLY:
			if (inventory_flies < 9) {
				inventory_flies += 1;
			}
			break;
		case BUG_DRAGONFLY:
			if (inventory_dragonflies < 9) {
				inventory_dragonflies += 1;
			}
			break;
		case BUG_FIREFLY:
			if (inventory_fireflies < 9) {
				inventory_fireflies += 1;
			}
			break;
		case BUG_BUTTERFLY:
			if (inventory_butterflies < 9) {
				inventory_butterflies += 1;
			}
			break;
		case BUG_CICADA:
			if (inventory_cicadas < 9) {
				inventory_cicadas += 1;
			}
			break;
	}
}

static void take_bug_out_of_inventory(void) {
	switch(selected_inventory_item) {
		case BUG_FLY:
			if (inventory_flies > 0) {
				inventory_flies -= 1;
				set_hand_state(HAND_FLY);
			}
			break;
		case BUG_DRAGONFLY:
			if (inventory_dragonflies > 0) {
				inventory_dragonflies -= 1;
				set_hand_state(HAND_DRAGONFLY);
			}
			break;
		case BUG_FIREFLY:
			if (inventory_fireflies > 0) {
				inventory_fireflies -= 1;
				set_hand_state(HAND_FIREFLY);
			}
			break;
		case BUG_BUTTERFLY:
			if (inventory_butterflies > 0) {
				inventory_butterflies -= 1;
				set_hand_state(HAND_BUTTERFLY);
			}
			break;
		case BUG_CICADA:
			if (inventory_cicadas > 0) {
				inventory_cicadas -= 1;
				set_hand_state(HAND_CICADA);
			}
			break;
	}
	transition_to_scene(FIELD, is_night);
}

void draw_inventory_sprites(void) BANKED {
	arrow_anim_counter += 1;
	if (arrow_anim_counter >= 32) {
		arrow_anim_counter = 0;
		arrow_anim_frame = !arrow_anim_frame;
		switch(selected_inventory_item) {
			case BUG_FLY:
				move_sprite(0, 48 - arrow_anim_frame, 62);
				move_sprite(1, 83 + arrow_anim_frame, 62);
				break;
			case BUG_DRAGONFLY:
				move_sprite(0, 88 - arrow_anim_frame, 62);
				move_sprite(1, 123 + arrow_anim_frame, 62);
				break;
			case BUG_FIREFLY:
				move_sprite(0, 88 - arrow_anim_frame, 86);
				move_sprite(1, 123 + arrow_anim_frame, 86);
				break;
			case BUG_BUTTERFLY:
				move_sprite(0, 48 - arrow_anim_frame, 86);
				move_sprite(1, 83 + arrow_anim_frame, 86);
				break;
			case BUG_CICADA:
				move_sprite(0, 48 - arrow_anim_frame, 110);
				move_sprite(1, 83 + arrow_anim_frame, 110);
				break;
		}
	}
	last_sprite = 2;
}

static void select_inventory_item(uint8_t new_item) {
	selected_inventory_item = new_item;
	arrow_anim_counter = 32;
	arrow_anim_frame = 1;
}

void setup_inventory(void) BANKED {
	set_banked_bkg_data(BANK(inventory), 0, inventory_TILE_COUNT, inventory_tiles);
	set_banked_bkg_tiles(BANK(inventory), 0, 0, 20, 18, inventory_map);

	set_banked_bkg_data(BANK(numbers), 0x50, numbers_TILE_COUNT, numbers_tiles);
	set_banked_bkg_data(BANK(inventory_bugs), 0x40, inventory_bugs_TILE_COUNT, inventory_bugs_tiles);

	set_banked_sprite_data(BANK(select_arrow), 0xff, select_arrow_TILE_COUNT, select_arrow_tiles);

	if (inventory_flies > 0) {
		set_bkg_tile_xy(6, 6, 0x40);
		set_bkg_tile_xy(7, 6, 0x41);
		set_bkg_tile_xy(8, 6, 0x50 + inventory_flies);
	}
	if (inventory_dragonflies > 0) {
		set_bkg_tile_xy(11, 5, 0x44);
		set_bkg_tile_xy(12, 5, 0x45);
		set_bkg_tile_xy(11, 6, 0x46);
		set_bkg_tile_xy(12, 6, 0x47);
		set_bkg_tile_xy(13, 6, 0x50 + inventory_dragonflies);
	}
	if (inventory_fireflies > 0) {
		set_bkg_tile_xy(11, 9, 0x42);
		set_bkg_tile_xy(12, 9, 0x43);
		set_bkg_tile_xy(13, 9, 0x50 + inventory_fireflies);
	}
	if (inventory_butterflies > 0) {
		set_bkg_tile_xy(6, 8, 0x48);
		set_bkg_tile_xy(7, 8, 0x49);
		set_bkg_tile_xy(6, 9, 0x4a);
		set_bkg_tile_xy(7, 9, 0x4b);
		set_bkg_tile_xy(8, 9, 0x50 + inventory_butterflies);
	}
	if (inventory_cicadas > 0) {
		set_bkg_tile_xy(6, 11, 0x4c);
		set_bkg_tile_xy(7, 11, 0x49);
		set_bkg_tile_xy(6, 12, 0x4d);
		set_bkg_tile_xy(7, 12, 0x4e);
		set_bkg_tile_xy(8, 12, 0x50 + inventory_cicadas);
	}

	set_sprite_tile(0, 0xff);
	set_sprite_tile(1, 0xff);
	set_sprite_prop(0, 0);
	set_sprite_prop(1, 32);

	hide_sprites_range(0, MAX_HARDWARE_SPRITES);
}

void handle_inventory_input(uint8_t button_pressed) BANKED {
	switch(button_pressed) {
		case A_BUTTON:
			take_bug_out_of_inventory();
			break;

		case B_BUTTON:
			transition_to_scene(FIELD, is_night);
			break;

		case LEFT_BUTTON:
			switch(selected_inventory_item) {
				case BUG_DRAGONFLY:
					select_inventory_item(BUG_FLY);
					break;
				case BUG_FIREFLY:
					select_inventory_item(BUG_BUTTERFLY);
					break;
			}
			break;

		case RIGHT_BUTTON:
			switch(selected_inventory_item) {
				case BUG_FLY:
					select_inventory_item(BUG_DRAGONFLY);
					break;
				case BUG_BUTTERFLY:
					select_inventory_item(BUG_FIREFLY);
					break;
			}
			break;

		case UP_BUTTON:
			switch(selected_inventory_item) {
				case BUG_BUTTERFLY:
					select_inventory_item(BUG_FLY);
					break;
				case BUG_FIREFLY:
					select_inventory_item(BUG_DRAGONFLY);
					break;
				case BUG_CICADA:
					select_inventory_item(BUG_BUTTERFLY);
					break;
			}
			break;

		case DOWN_BUTTON:
			switch(selected_inventory_item) {
				case BUG_FLY:
					select_inventory_item(BUG_BUTTERFLY);
					break;
				case BUG_DRAGONFLY:
					select_inventory_item(BUG_FIREFLY);
					break;
				case BUG_BUTTERFLY:
					select_inventory_item(BUG_CICADA);
					break;
			}
			break;
	}
}

void reset_inventory(void) BANKED {
	inventory_flies = 0;
	inventory_dragonflies = 0;
	inventory_fireflies = 0;
	inventory_butterflies = 0;
	inventory_cicadas = 0;
}
