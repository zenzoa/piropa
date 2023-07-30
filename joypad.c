#include <gbdk/platform.h>

#include "hand.h"

uint8_t joypad_value;
uint8_t a_button_pressed = FALSE;
uint8_t b_button_pressed = FALSE;

void handle_dpad() {
	SWITCH_ROM(BANK(hand_bank));
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

void handle_a_button() {
	if (joypad_value & J_A && !a_button_pressed) {
		a_button_pressed = TRUE;
		// some stuff
	} else if (!(joypad_value & J_A)) {
		a_button_pressed = FALSE;
	}
}

void handle_b_button() {
	if (joypad_value & J_B && !b_button_pressed) {
		b_button_pressed = TRUE;
		// some stuff
	} else if (!(joypad_value & J_B)) {
		b_button_pressed = FALSE;
	}
}

void handle_input() {
	joypad_value = joypad();
	handle_dpad();
	handle_a_button();
	handle_b_button();
}
