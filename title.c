#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "sprites/background/title_screen.h"
#define FALSE 0
#define TRUE 1

void draw_title_screen() {
	SWITCH_ROM(BANK(title_screen));
	set_bkg_data(0, title_screen_TILE_COUNT, title_screen_tiles);
	set_bkg_tiles(0, 0, 20, 18, title_screen_map);
}

uint8_t title_screen_loop() {
	uint8_t reset_counter = 0;

	while(1) {
		uint8_t joypad_value = joypad();

		if (joypad_value & J_START || joypad_value & J_A) {
			return FALSE;
		}

		if (joypad_value & J_SELECT) {
			reset_counter += 1;
			if (reset_counter >= 240) {
				return TRUE;
			}
		} else if (!(joypad_value & J_B)) {
			reset_counter = 0;
		}

		wait_vbl_done(); // wait for next frame
	}
}
