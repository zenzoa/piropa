#include <gbdk/platform.h>
#include <rand.h>
#include <time.h>

#include "save.h"
#include "joypad.h"
#include "scene.h"

void main(void) {
	DISPLAY_ON;
	SHOW_BKG;
	SHOW_SPRITES;
	SPRITES_8x8;
	OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);

	load_data();
	setup_data(!has_save);
	setup_scene(TITLE);

	while(1) {
		handle_input();
		update_scene();
		vsync(); // wait for next frame
	}
}
