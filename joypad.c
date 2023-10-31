#include <gbdk/platform.h>

#include "hand.h"
#include "frog.h"
#include "hud.h"
#include "scene.h"
#include "field.h"

uint8_t joypad_value;
uint8_t a_button_pressed = FALSE;
uint8_t b_button_pressed = FALSE;

void handle_dpad(void) {
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
}

void handle_a_button(void) {
	if (joypad_value & J_A && !a_button_pressed) {
		a_button_pressed = TRUE;

		if (is_hand_over_frog() && !is_night) {
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

		} else if (is_hand_over_medicine()) {
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
			} else if (is_night) {
				start_transition_to_scene(FIELD, FALSE);
			} else {
				drop_all(0);
				set_hand_state(HAND_DEFAULT);
			}

		} else if (hand_state == HAND_MOON && hand_y >= 32 && hand_y < 80) {
			if (is_night && current_scene == FIELD) {
				return_moon_to_sky();
				set_hand_state(HAND_DEFAULT);
			} else if (!is_night) {
				start_transition_to_scene(FIELD, TRUE);
			}

		} else if (is_night && current_scene == FIELD && hand_x >= 72 && hand_x < 96 && hand_y >= 48 && hand_y < 68) {
			grab_moon_from_sky();
			set_hand_state(HAND_MOON);
		}

	} else if (!(joypad_value & J_A)) {
		a_button_pressed = FALSE;
	}
}

void handle_b_button(void) {
	if (joypad_value & J_B && !b_button_pressed) {
		b_button_pressed = TRUE;
		drop_all(0);
		set_hand_state(HAND_DEFAULT);

	} else if (!(joypad_value & J_B)) {
		b_button_pressed = FALSE;
	}
}

void handle_input(void) {
	joypad_value = joypad();
	handle_dpad();
	handle_a_button();
	handle_b_button();
}
