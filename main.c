#include <gbdk/platform.h>
#include <rand.h>
#include <time.h>

#include "save.h"
#include "joypad.h"
#include "scene.h"
#include "music.h"
#include "common.h"

void main(void) {
	// enable graphics
	DISPLAY_ON;

	BGP_REG = DMG_PALETTE(DMG_BLACK, DMG_BLACK, DMG_BLACK, DMG_BLACK);
	SHOW_BKG;

	OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
	SPRITES_8x8;
	SHOW_SPRITES;

	// enable sound
	NR52_REG = 0x80;
	NR51_REG = 0xFF;
	NR50_REG = 0x77;

	// init music
	__critical {
		set_music(FROG_MUSIC);
		add_VBL(play_music);
	}

	load_data();

	setup_data(!has_save);

	transition_to_scene(TITLE, is_night);

	// main loop
	while(1) {
		handle_input();
		update_scene();
		vsync(); // wait for next frame
	}
}
