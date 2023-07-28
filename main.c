#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "clock.h"
#include "save.h"
#include "animation.h"
#include "frog.h"
#include "hud.h"

#include "sprites/backgrounds/field.h"

uint8_t last_sprite;

uint8_t frames = 0;
uint8_t last_stat_check_min = 0;
uint8_t last_stat_check_sec = 0;

void main() {
	DISPLAY_ON;
	SHOW_BKG;
	SHOW_SPRITES;
	SPRITES_8x8;
	OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);

	SWITCH_ROM(BANK(field));
	set_bkg_data(0, field_TILE_COUNT, field_tiles);
	set_bkg_tiles(0, 0, 20, 18, field_map);

	SWITCH_ROM(BANK(frog_bank));
	reset_frog();

	if (load_data()) {
		read_clock();
		update_hud_clock();
		last_stat_check_min = minutes;
		last_stat_check_sec = seconds;
	} else {
		reset_clock();
		save_data();
	}

	setup_hud();

	while(1) {
		last_sprite = 0;
		SWITCH_ROM(BANK(frog_bank));
		draw_frog(&last_sprite);
		hide_sprites_range(last_sprite, MAX_HARDWARE_SPRITES);

		frames += 1;
		if (frames >= 60) {
			frames = 0;
			read_clock();
			update_hud_clock();
			if (minutes != last_stat_check_min && seconds >= last_stat_check_sec) {
				last_stat_check_min = minutes;
				update_stats(1);
				draw_hud();
				save_data();
			}
		}

		wait_vbl_done(); // wait for next frame
	}
}
