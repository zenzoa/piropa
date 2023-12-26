#pragma bank 255

#include <gbdk/platform.h>

#include "save.h"
#include "hand.h"
#include "frog.h"
#include "bugs.h"
#include "hud.h"
#include "scene.h"
#include "title.h"
#include "field.h"
#include "garden.h"
#include "info.h"
#include "inventory.h"
#include "common.h"
#include "audio.h"

static uint8_t joypad_value;
static uint8_t a_button_pressed;
static uint8_t b_button_pressed;
static uint8_t dpad_button_pressed;
static uint8_t snapped_to_edge;

static void handle_dpad(void) {
	switch(current_scene) {
		case TITLE:
			if ((joypad_value & J_UP) && !dpad_button_pressed) {
				dpad_button_pressed = TRUE;
				play_sfx(SFX_BEEP);
				handle_title_input(UP_BUTTON);
			} else if ((joypad_value & J_DOWN) && !dpad_button_pressed) {
				dpad_button_pressed = TRUE;
				play_sfx(SFX_BEEP);
				handle_title_input(DOWN_BUTTON);
			} else if (!(joypad_value & J_UP) && !(joypad_value & J_DOWN)) {
				dpad_button_pressed = FALSE;
			}
			break;

		case FIELD:
		case POND:
		case GARDEN:
			if ((joypad_value & J_LEFT) || (joypad_value & J_RIGHT) || (joypad_value & J_UP) || (joypad_value & J_DOWN)) {
				if (!dpad_button_pressed && b_button_pressed) {
					snap_hand_to_edge(joypad_value);
					snapped_to_edge = TRUE;
				} else if (!b_button_pressed) {
					move_hand(joypad_value);
				}
				dpad_button_pressed = TRUE;
			} else {
				dpad_button_pressed = FALSE;
				snapped_to_edge = FALSE;
			}
			break;

		case INFO:
			if ((joypad_value & J_LEFT) && !dpad_button_pressed) {
				dpad_button_pressed = TRUE;
				play_sfx(SFX_BEEP);
				handle_info_input(LEFT_BUTTON);
			} else if ((joypad_value & J_RIGHT) && !dpad_button_pressed) {
				dpad_button_pressed = TRUE;
				play_sfx(SFX_BEEP);
				handle_info_input(RIGHT_BUTTON);
			} else if (!(joypad_value & J_LEFT) && !(joypad_value & J_RIGHT)) {
				dpad_button_pressed = FALSE;
			}
			break;

		case INVENTORY:
			if ((joypad_value & J_LEFT) && !dpad_button_pressed) {
				dpad_button_pressed = TRUE;
				play_sfx(SFX_BEEP);
				handle_inventory_input(LEFT_BUTTON);
			} else if ((joypad_value & J_RIGHT) && !dpad_button_pressed) {
				dpad_button_pressed = TRUE;
				play_sfx(SFX_BEEP);
				handle_inventory_input(RIGHT_BUTTON);
			} else if ((joypad_value & J_UP) && !dpad_button_pressed) {
				dpad_button_pressed = TRUE;
				play_sfx(SFX_BEEP);
				handle_inventory_input(UP_BUTTON);
			} else if ((joypad_value & J_DOWN) && !dpad_button_pressed) {
				dpad_button_pressed = TRUE;
				play_sfx(SFX_BEEP);
				handle_inventory_input(DOWN_BUTTON);
			} else if (!(joypad_value & J_LEFT) && !(joypad_value & J_RIGHT) && !(joypad_value & J_UP) && !(joypad_value & J_DOWN)) {
				dpad_button_pressed = FALSE;
			}
			break;
	}
}

static void handle_a_button(void) {
	if (joypad_value & J_A && !a_button_pressed) {
		a_button_pressed = TRUE;

		switch(current_scene) {
			case TITLE:
				play_sfx(SFX_TAP);
				handle_title_input(A_BUTTON);
				break;

			case FIELD:
			case POND:
			case GARDEN:
				if (!handle_hud_input(A_BUTTON)) {
					if (hand_state == HAND_MOON && hand_y >= 32 && hand_y < 80) {
						play_sfx(SFX_DROP);
						if (is_night && current_scene == FIELD) {
							set_hand_state(HAND_DEFAULT);
							return_moon_to_sky();
						} else if (!is_night) {
							set_hand_state(HAND_DEFAULT);
							transition_to_scene(FIELD, TRUE);
						}

					} else if (is_night && current_scene == FIELD && hand_x >= 72 && hand_x < 96 && hand_y >= 48 && hand_y < 68) {
						play_sfx(SFX_TAP);
						grab_moon_from_sky();
						set_hand_state(HAND_MOON);

					} else if (hand_state == HAND_BROOM) {
						play_sfx(SFX_SWEEP);
						set_hand_state(HAND_BROOM_USE);
						sweep_count = 2;

					} else if (hand_state == HAND_BROOM_USE) {
						set_hand_state(HAND_BROOM);
						sweep_count = 2;

					} else if (is_hand_over_frog() && !is_night && life_stage != EGG && life_stage != DEAD) {
						if (is_hand_empty() || hand_state == HAND_PET2) {
							set_hand_state(HAND_PET1);
							start_pet();
						} else if (hand_state == HAND_PET1) {
							set_hand_state(HAND_PET2);
							start_pet();
						} else if (hand_state == HAND_MEDICINE) {
							set_hand_state(HAND_MEDICINE_USE);
							start_medicate();
						} else if (hand_state == HAND_SOAP || hand_state == HAND_SOAP_USE) {
							set_hand_state(HAND_SOAP_USE);
							start_wash();
						} else if (hand_state == HAND_FLY) {
							set_hand_state(HAND_DEFAULT);
							start_feed(BUG_FLY);
						} else if (hand_state == HAND_DRAGONFLY) {
							set_hand_state(HAND_DEFAULT);
							start_feed(BUG_DRAGONFLY);
						} else if (hand_state == HAND_FIREFLY) {
							set_hand_state(HAND_DEFAULT);
							start_feed(BUG_FIREFLY);
						} else if (hand_state == HAND_BUTTERFLY) {
							set_hand_state(HAND_DEFAULT);
							start_feed(BUG_BUTTERFLY);
						}

					} else if (is_hand_over_basket() && (hand_state == HAND_FLY || hand_state == HAND_DRAGONFLY || hand_state == HAND_FIREFLY || hand_state == HAND_BUTTERFLY)) {
						switch(hand_state) {
							case HAND_FLY:
								play_sfx(SFX_DROP);
								put_bug_in_inventory(BUG_FLY);
								break;
							case HAND_DRAGONFLY:
								play_sfx(SFX_DROP);
								put_bug_in_inventory(BUG_DRAGONFLY);
								break;
							case HAND_FIREFLY:
								play_sfx(SFX_DROP);
								put_bug_in_inventory(BUG_FIREFLY);
								break;
							case HAND_BUTTERFLY:
								play_sfx(SFX_DROP);
								put_bug_in_inventory(BUG_BUTTERFLY);
								break;
						}
						set_hand_state(HAND_DEFAULT);

					} else if (is_hand_empty()) {
						uint8_t bug_type = grab_bug();
						switch(bug_type) {
							case BUG_FLY:
								play_sfx(SFX_BEEP);
								set_hand_state(HAND_FLY);
								break;
							case BUG_DRAGONFLY:
								play_sfx(SFX_BEEP);
								set_hand_state(HAND_DRAGONFLY);
								break;
							case BUG_FIREFLY:
								play_sfx(SFX_BEEP);
								set_hand_state(HAND_FIREFLY);
								break;
							case BUG_BUTTERFLY:
								play_sfx(SFX_BEEP);
								set_hand_state(HAND_BUTTERFLY);
								draw_plants();
								break;

							default:
								if (current_scene == FIELD && is_hand_over_basket()) {
									play_sfx(SFX_TAP);
									transition_to_scene(INVENTORY, is_night);

								} else if (current_scene == GARDEN && !is_night) {
									if (hand_x >= PLANT_0_X*8 && hand_x < PLANT_0_X*8+24 && hand_y >= PLANT_0_Y*8+4 && hand_y < PLANT_0_Y*8+28) {
										start_walk_to_plant(0);
									} else if (hand_x >= PLANT_1_X*8 && hand_x < PLANT_1_X*8+24 && hand_y >= PLANT_1_Y*8+4 && hand_y < PLANT_1_Y*8+28) {
										start_walk_to_plant(1);
									} else if (hand_x >= PLANT_2_X*8 && hand_x < PLANT_2_X*8+24 && hand_y >= PLANT_2_Y*8+4 && hand_y < PLANT_2_Y*8+28) {
										start_walk_to_plant(2);
									}
								}
						}

					}
				}

				break;

			case INFO:
				play_sfx(SFX_TAP);
				handle_info_input(A_BUTTON);
				break;

			case INVENTORY:
				play_sfx(SFX_TAP);
				handle_inventory_input(A_BUTTON);
				break;

		}

	} else if (!(joypad_value & J_A)) {
		a_button_pressed = FALSE;
	}
}

static void handle_b_button(void) {
	if (joypad_value & J_B && !b_button_pressed) {
		b_button_pressed = TRUE;

	} else if (!(joypad_value & J_B) && b_button_pressed) {
		switch(current_scene) {
			case TITLE:
				handle_title_input(B_BUTTON);
				break;

			case FIELD:
			case POND:
			case GARDEN:
				if (snapped_to_edge) {
					snapped_to_edge = FALSE;
				} else {
					switch(hand_state) {
						case HAND_FLY:
							if (is_hand_over_frog() && !is_night && life_stage != EGG && life_stage != DEAD) {
								set_hand_state(HAND_DEFAULT);
								start_feed(BUG_FLY);
							} else if (is_hand_over_basket()) {
								put_bug_in_inventory(BUG_FLY);
							} else {
								drop_bug(BUG_FLY);
							}
							break;

						case HAND_DRAGONFLY:
							if (is_hand_over_frog() && !is_night && life_stage != EGG && life_stage != DEAD) {
								set_hand_state(HAND_DEFAULT);
								start_feed(BUG_DRAGONFLY);
							} else if (is_hand_over_basket()) {
								put_bug_in_inventory(BUG_DRAGONFLY);
							} else {
								drop_bug(BUG_DRAGONFLY);
							}
							break;

						case HAND_FIREFLY:
							if (is_hand_over_frog() && !is_night && life_stage != EGG && life_stage != DEAD) {
								set_hand_state(HAND_DEFAULT);
								start_feed(BUG_FIREFLY);
							} else if (is_hand_over_basket()) {
								put_bug_in_inventory(BUG_FIREFLY);
							} else {
								drop_bug(BUG_FIREFLY);
							}
							break;

						case HAND_BUTTERFLY:
							if (is_hand_over_frog() && !is_night && life_stage != EGG && life_stage != DEAD) {
								set_hand_state(HAND_DEFAULT);
								start_feed(BUG_BUTTERFLY);
							} else if (is_hand_over_basket()) {
								put_bug_in_inventory(BUG_BUTTERFLY);
							} else {
								drop_bug(BUG_BUTTERFLY);
							}
							break;
					}

					drop_all(0);
					if (!is_hand_empty()) {
						play_sfx(SFX_DROP);
					}
					set_hand_state(HAND_DEFAULT);
				}
				break;

			case INFO:
				play_sfx(SFX_DROP);
				handle_info_input(B_BUTTON);
				break;

			case INVENTORY:
				play_sfx(SFX_DROP);
				handle_inventory_input(B_BUTTON);
				break;

			case CREDITS:
				play_sfx(SFX_DROP);
				transition_to_scene(TITLE, is_night);
				break;
		}

		b_button_pressed = FALSE;
	}
}

void handle_input(void) BANKED {
	joypad_value = joypad();

	handle_dpad();
	handle_a_button();
	handle_b_button();

	if (current_scene != TITLE && ((joypad_value & J_START) || (joypad_value & J_SELECT))) {
		transition_to_scene(TITLE, is_night);
	}
}
