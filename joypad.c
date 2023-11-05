#include <gbdk/platform.h>

#include "save.h"
#include "hand.h"
#include "frog.h"
#include "hud.h"
#include "scene.h"
#include "title.h"
#include "field.h"

uint8_t joypad_value;
uint8_t a_button_pressed = FALSE;
uint8_t b_button_pressed = FALSE;

void handle_dpad(void) {
	switch(current_scene) {
		case TITLE:
			if (has_save) {
				SWITCH_ROM(BANK(title_bank));
				if (joypad_value & J_UP) {
					select_title_item(TITLE_ITEM_CONTINUE);
				} else if ((joypad_value & J_DOWN) && selected_title_item == TITLE_ITEM_CONTINUE) {
					select_title_item(TITLE_ITEM_RESET);
				}
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
	}
}

void handle_a_button(void) {
	if (joypad_value & J_A && !a_button_pressed) {
		a_button_pressed = TRUE;

		switch(current_scene) {
			case TITLE:
				if (has_save) {
					SWITCH_ROM(BANK(title_bank));
					switch(selected_title_item) {
						case TITLE_ITEM_CONTINUE:
							start_transition_to_scene(FIELD, is_night);
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

			case FIELD:
			case POND:
			case GARDEN:
				SWITCH_ROM(BANK(hud_bank));

				if (is_hand_over_medicine()) {
					if (hold_medicine()) {
						set_hand_state(HAND_MEDICINE);
					} else {
						drop_all(0);
						set_hand_state(HAND_DEFAULT);
					}

				} else if (is_hand_over_soap()) {
					if (hold_soap()) {
						set_hand_state(HAND_SOAP);
					} else {
						drop_all(0);
						set_hand_state(HAND_DEFAULT);
					}

				} else if (is_hand_over_broom()) {
					if (hold_broom()) {
						set_hand_state(HAND_BROOM);
					} else {
						drop_all(0);
						set_hand_state(HAND_DEFAULT);
					}

				} else if (is_hand_over_moon()) {
					if (hold_moon()) {
						set_hand_state(HAND_MOON);
					} else {
						drop_all(0);
						set_hand_state(HAND_DEFAULT);
					}

				} else if (hand_state == HAND_MOON && hand_y >= 32 && hand_y < 80) {
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
				if (has_save) {
					SWITCH_ROM(BANK(title_bank));
					if (selected_title_item == TITLE_ITEM_CONFIRM_RESET) {
						select_title_item(TITLE_ITEM_RESET);
					}
				}
				break;

			case FIELD:
			case POND:
			case GARDEN:
				SWITCH_ROM(BANK(hud_bank));
				drop_all(0);
				set_hand_state(HAND_DEFAULT);
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
