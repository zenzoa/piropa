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
#include "shared_variables.h"

uint8_t joypad_value;
uint8_t a_button_pressed = FALSE;
uint8_t b_button_pressed = FALSE;
uint8_t dpad_button_pressed = FALSE;

void handle_dpad(void) {
	switch(current_scene) {
		case TITLE:
			SWITCH_ROM(BANK(title_bank));
			if ((joypad_value & J_UP) && !dpad_button_pressed) {
				dpad_button_pressed = TRUE;
				handle_title_input(UP_BUTTON);
			} else if ((joypad_value & J_DOWN) && !dpad_button_pressed) {
				dpad_button_pressed = TRUE;
				handle_title_input(DOWN_BUTTON);
			} else if (!(joypad_value & J_UP) && !(joypad_value & J_UP)) {
				dpad_button_pressed = FALSE;
			}
			break;

		case FIELD:
		case POND:
		case GARDEN:
			SWITCH_ROM(BANK(hand_bank));
			move_hand(joypad_value);
			break;

		case INFO:
			SWITCH_ROM(BANK(info_bank));
			if ((joypad_value & J_LEFT) && !dpad_button_pressed) {
				dpad_button_pressed = TRUE;
				handle_info_input(LEFT_BUTTON);
			} else if ((joypad_value & J_RIGHT) && !dpad_button_pressed) {
				dpad_button_pressed = TRUE;
				handle_info_input(RIGHT_BUTTON);
			} else if (!(joypad_value & J_LEFT) && !(joypad_value & J_RIGHT)) {
				dpad_button_pressed = FALSE;
			}
			break;
	}
}

void handle_a_button(void) {
	if (joypad_value & J_A && !a_button_pressed) {
		a_button_pressed = TRUE;

		switch(current_scene) {
			case TITLE:
				SWITCH_ROM(BANK(title_bank));
				handle_title_input(A_BUTTON);
				break;

			case FIELD:
			case POND:
			case GARDEN:
				SWITCH_ROM(BANK(hud_bank));
				if (!handle_hud_input(A_BUTTON)) {
					SWITCH_ROM(BANK(hand_bank));
					if (hand_state == HAND_MOON && hand_y >= 32 && hand_y < 80) {
						if (is_night && current_scene == FIELD) {
							set_hand_state(HAND_DEFAULT);
							SWITCH_ROM(BANK(field_bank));
							return_moon_to_sky();
						} else if (!is_night) {
							set_hand_state(HAND_DEFAULT);
							start_transition_to_scene(FIELD, TRUE);
						}

					} else if (is_night && current_scene == FIELD && hand_x >= 72 && hand_x < 96 && hand_y >= 48 && hand_y < 68) {
						SWITCH_ROM(BANK(field_bank));
						grab_moon_from_sky();
						set_hand_state(HAND_MOON);

					} else if (hand_state == HAND_BROOM || hand_state == HAND_BROOM_USE) {
						set_hand_state(HAND_BROOM_USE);
						sweep_count = 2;

					} else if (is_hand_over_frog() && !is_night && life_stage != EGG && life_stage != DEAD) {
						if (is_hand_empty() || hand_state == HAND_PET2) {
							set_hand_state(HAND_PET1);
							SWITCH_ROM(BANK(frog_bank));
							start_pet();
						} else if (hand_state == HAND_PET1) {
							set_hand_state(HAND_PET2);
							SWITCH_ROM(BANK(frog_bank));
							start_pet();
						} else if (hand_state == HAND_MEDICINE) {
							set_hand_state(HAND_MEDICINE_USE);
							SWITCH_ROM(BANK(frog_bank));
							start_medicate();
						} else if (hand_state == HAND_SOAP || hand_state == HAND_SOAP_USE) {
							set_hand_state(HAND_SOAP_USE);
							SWITCH_ROM(BANK(frog_bank));
							start_wash();
						} else if (hand_state == HAND_FLY) {
							set_hand_state(HAND_DEFAULT);
							SWITCH_ROM(BANK(frog_bank));
							start_feed(BUG_FLY);
						} else if (hand_state == HAND_DRAGONFLY) {
							set_hand_state(HAND_DEFAULT);
							SWITCH_ROM(BANK(frog_bank));
							start_feed(BUG_DRAGONFLY);
						} else if (hand_state == HAND_FIREFLY) {
							set_hand_state(HAND_DEFAULT);
							SWITCH_ROM(BANK(frog_bank));
							start_feed(BUG_FIREFLY);
						} else if (hand_state == HAND_BUTTERFLY) {
							set_hand_state(HAND_DEFAULT);
							SWITCH_ROM(BANK(frog_bank));
							start_feed(BUG_BUTTERFLY);
						}

					} else if (is_hand_empty()) {
						SWITCH_ROM(BANK(bugs_bank));
						uint8_t bug_type = grab_bug();
						switch(bug_type) {
							case BUG_FLY:
								set_hand_state(HAND_FLY);
								break;
							case BUG_DRAGONFLY:
								set_hand_state(HAND_DRAGONFLY);
								break;
							case BUG_FIREFLY:
								set_hand_state(HAND_FIREFLY);
								break;
							case BUG_BUTTERFLY:
								set_hand_state(HAND_BUTTERFLY);
								break;

							default:
								if (current_scene == GARDEN && !is_night) {
									if (hand_x >= PLANT_0_X*8 && hand_x < PLANT_0_X*8+24 && hand_y >= PLANT_0_Y*8+4 && hand_y < PLANT_0_Y*8+28) {
										SWITCH_ROM(BANK(frog_bank));
										start_walk_to_plant(0);
									} else if (hand_x >= PLANT_1_X*8 && hand_x < PLANT_1_X*8+24 && hand_y >= PLANT_1_Y*8+4 && hand_y < PLANT_1_Y*8+28) {
										SWITCH_ROM(BANK(frog_bank));
										start_walk_to_plant(1);
									} else if (hand_x >= PLANT_2_X*8 && hand_x < PLANT_2_X*8+24 && hand_y >= PLANT_2_Y*8+4 && hand_y < PLANT_2_Y*8+28) {
										SWITCH_ROM(BANK(frog_bank));
										start_walk_to_plant(2);
									}
								}
						}

					}
				}

				break;

			case INFO:
				SWITCH_ROM(BANK(info_bank));
				handle_info_input(A_BUTTON);
				break;

		}

	} else if (!(joypad_value & J_A)) {
		a_button_pressed = FALSE;
	}
}

void handle_b_button(void) {
	if (joypad_value & J_B && !b_button_pressed) {
		b_button_pressed = TRUE;
		switch(current_scene) {
			case TITLE:
				SWITCH_ROM(BANK(title_bank));
				handle_title_input(B_BUTTON);
				break;

			case FIELD:
			case POND:
			case GARDEN:
				SWITCH_ROM(BANK(bugs_bank));
				switch(hand_state) {
					case HAND_FLY:
						drop_bug(BUG_FLY);
						break;
					case HAND_DRAGONFLY:
						drop_bug(BUG_DRAGONFLY);
						break;
					case HAND_FIREFLY:
						drop_bug(BUG_FIREFLY);
						break;
					case HAND_BUTTERFLY:
						drop_bug(BUG_BUTTERFLY);
						break;
				}
				SWITCH_ROM(BANK(hud_bank));
				drop_all(0);
				set_hand_state(HAND_DEFAULT);
				break;

			case INFO:
				SWITCH_ROM(BANK(info_bank));
				handle_info_input(B_BUTTON);
				break;
		}

	} else if (!(joypad_value & J_B)) {
		b_button_pressed = FALSE;
	}
}

void handle_input(void) {
	joypad_value = joypad();

	handle_dpad();
	handle_a_button();
	handle_b_button();

	if (current_scene != TITLE && ((joypad_value & J_START) || (joypad_value & J_SELECT))) {
		start_transition_to_scene(TITLE, is_night);
	}
}
