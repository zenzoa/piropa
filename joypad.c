#include <gbdk/platform.h>

#include "hud.h"
#include "hand.h"
#include "frog.h"

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

		if (is_hand_over_frog()) {
			pet_frog();
			if (is_hand_empty() || hand_state == HAND_PET2) {
				set_hand_state(HAND_PET1);
			} else if (hand_state == HAND_PET1) {
				set_hand_state(HAND_PET2);
			}

		} else if (is_hand_over_medicine()) {
			hold_medicine();
			set_hand_state(HAND_MEDICINE);

		} else if (is_hand_over_soap()) {
			hold_soap();
			set_hand_state(HAND_SOAP);

		} else if (is_hand_over_broom()) {
			hold_broom();
			set_hand_state(HAND_BROOM);

		} else if (is_hand_over_moon()) {
			hold_moon();
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
