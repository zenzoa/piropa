#include <gbdk/platform.h>
#include <rand.h>
#include <time.h>

#include "save.h"
#include "joypad.h"
#include "scene.h"
#include "music.h"
#include "colors.h"
#include "common.h"

void main(void) {
	// setup color palettes
	can_use_color = (_cpu == CGB_TYPE);
	set_bkg_colors(3);
	set_sprite_colors(3);

	// enable graphics
	SPRITES_8x8;
	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;

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
