#include <gbdk/platform.h>
#include <rand.h>
#include <time.h>

#include "save.h"
#include "joypad.h"
#include "scene.h"
#include "audio.h"
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

	// init music
	__critical {
		add_VBL(update_audio);
	}
	play_music(NO_MUSIC);
	play_sfx(SFX_EVOLVE);

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
