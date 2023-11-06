#include <gbdk/platform.h>

#include "save.h"
#include "hand.h"
#include "frog.h"
#include "hud.h"
#include "scene.h"
#include "title.h"
#include "field.h"
#include "info.h"

#define A_BUTTON 0
#define B_BUTTON 1
#define UP_BUTTON 2
#define RIGHT_BUTTON 3
#define DOWN_BUTTON 4
#define LEFT_BUTTON 5

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
			if (joypad_value & J_LEFT) {
				if (joypad_value & J_UP) {
					move_hand_by_frac(-181, -181);
				} else if (joypad_value & J_DOWN) {
					move_hand_by_frac(-181, 181);
				} else {
					move_hand_by_frac(-256, 0);
				}
			} else if (joypad_value & J_RIGHT) {
				if (joypad_value & J_UP) {
					move_hand_by_frac(181, -181);
				} else if (joypad_value & J_DOWN) {
					move_hand_by_frac(181, 181);
				} else {
					move_hand_by_frac(256, 0);
				}
			} else if (joypad_value & J_UP) {
				move_hand_by_frac(0, -256);
			} else if (joypad_value & J_DOWN) {
				move_hand_by_frac(0, 256);
			}
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
					if (hand_state == HAND_MOON && hand_y >= 32 && hand_y < 80) {
						if (is_night && current_scene == FIELD) {
							SWITCH_ROM(BANK(field_bank));
							return_moon_to_sky();
							set_hand_state(HAND_DEFAULT);
						} else if (!is_night) {
							start_transition_to_scene(FIELD, TRUE);
							set_hand_state(HAND_DEFAULT);
						}

					} else if (is_night && current_scene == FIELD && hand_x >= 72 && hand_x < 96 && hand_y >= 48 && hand_y < 68) {
						SWITCH_ROM(BANK(field_bank));
						grab_moon_from_sky();
						set_hand_state(HAND_MOON);

					} else if ((hand_state == HAND_BROOM || hand_state == HAND_BROOM_USE) && current_scene == FIELD) {
						set_hand_state(HAND_BROOM_USE);
						sweep_count = 2;

					} else if (is_hand_over_frog() && !is_night && life_stage != EGG && life_stage != DEAD) {
						if (is_hand_empty() || hand_state == HAND_PET2) {
							start_pet();
							set_hand_state(HAND_PET1);
						} else if (hand_state == HAND_PET1) {
							start_pet();
							set_hand_state(HAND_PET2);
						} else if (hand_state == HAND_MEDICINE) {
							start_medicate();
							set_hand_state(HAND_MEDICINE_USE);
						} else if (hand_state == HAND_SOAP || hand_state == HAND_SOAP_USE) {
							start_wash();
							set_hand_state(HAND_SOAP_USE);
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
