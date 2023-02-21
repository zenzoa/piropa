#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "clock.h"
#include "frog.h"
#include "hand.h"

uint8_t joypad_current = 0;
uint8_t animation_counter = 0;
uint8_t animation_speed = 32;

void read_joypad();
void draw_sprites();

/* ========================================================================= */

void main(void) {
	DISPLAY_ON;
	SHOW_SPRITES;
	SPRITES_8x8;
	
	// TODO: read save data and update frog based on time that has passed
	reset_clock(); // do this when new frog is born
	
	init_hand();
	init_frog();
	
    while(1) {
    	read_joypad();
    	
		if (animation_counter >= animation_speed) {
			update_frog();
			animation_counter = 0;
		}
		animation_counter++;
		
		draw_sprites();

		wait_vbl_done(); // wait for next frame
    }
}

void read_joypad() {
	joypad_current = joypad();
	if (joypad_current & J_LEFT) {
		if (joypad_current & J_UP) {
			move_hand(-181, -181); // sqrt(1/2) -> Q8.8
		} else if (joypad_current & J_DOWN) {
			move_hand(-181, 181);
		} else {
   			move_hand(-256, 0); // 1 -> Q8.8
		}
	} else if (joypad_current & J_RIGHT) {
		if (joypad_current & J_UP) {
			move_hand(181, -181);
		} else if (joypad_current & J_DOWN) {
			move_hand(181, 181);
		} else {
   			move_hand(256, 0);
		}
	} else {
		if (joypad_current & J_UP) {
			move_hand(0, -256);
		} else if (joypad_current & J_DOWN) {
			move_hand(0, 256);
		}
	}
}

void draw_sprites() {
	uint8_t last_used_sprite = 0;
	draw_frog(&last_used_sprite);
	draw_hand(&last_used_sprite);
	hide_sprites_range(last_used_sprite, MAX_HARDWARE_SPRITES);
}
