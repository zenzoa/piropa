#pragma bank 255

#include <gbdk/platform.h>

#include "common.h"

uint8_t can_use_color;

#define ui_color_0 RGBHTML(0xe7ebbc)
#define ui_color_1 RGBHTML(0x87c293)
#define ui_color_2 RGBHTML(0x637c8f)
#define ui_color_3 RGBHTML(0x4e3161)

#define day_color_0 RGBHTML(0xe7ebbc)
#define day_color_1 RGBHTML(0x87c293)
#define day_color_2 RGBHTML(0x637c8f)
#define day_color_3 RGBHTML(0x4e3161)

#define night_color_0 RGBHTML(0x87c293)
#define night_color_1 RGBHTML(0x637c8f)
#define night_color_2 RGBHTML(0x5b5280)
#define night_color_3 RGBHTML(0x4e3161)

#define green_color_0 RGBHTML(0xb2dba0)
#define green_color_1 RGBHTML(0x70a18f)
#define green_color_2 RGBHTML(0x4e3161)
#define green_color_3 RGBHTML(0x4e3161)

#define blue_color_0 RGBHTML(0xc0e5f3)
#define blue_color_1 RGBHTML(0x84b1dd)
#define blue_color_2 RGBHTML(0x4e3161)
#define blue_color_3 RGBHTML(0x4e3161)

#define pink_color_0 RGBHTML(0xedd5ca)
#define pink_color_1 RGBHTML(0xc98f8f)
#define pink_color_2 RGBHTML(0x4e3161)
#define pink_color_3 RGBHTML(0x4e3161)

#define brown_color_0 RGBHTML(0xe6cfa1)
#define brown_color_1 RGBHTML(0xd18b79)
#define brown_color_2 RGBHTML(0x612447)
#define brown_color_3 RGBHTML(0x612447)

#define grey_color_0 RGBHTML(0xfaffe0)
#define grey_color_1 RGBHTML(0xc3b8b1)
#define grey_color_2 RGBHTML(0x612447)
#define grey_color_3 RGBHTML(0x612447)

#define glow_color_0 RGBHTML(0xfaffe0)
#define glow_color_1 RGBHTML(0x87c293)
#define glow_color_2 RGBHTML(0x4e3161)
#define glow_color_3 RGBHTML(0x4e3161)

static const palette_color_t ui_bkg_palettes[] = {
	ui_color_0, ui_color_1, ui_color_2, ui_color_3,
	ui_color_1, ui_color_2, ui_color_3, ui_color_3,
	ui_color_2, ui_color_3, ui_color_3, ui_color_3,
	ui_color_3, ui_color_3, ui_color_3, ui_color_3,
	ui_color_2, ui_color_2, ui_color_2, ui_color_2,
	ui_color_1, ui_color_1, ui_color_1, ui_color_1,
	ui_color_0, ui_color_0, ui_color_0, ui_color_0
};

static const palette_color_t day_bkg_palettes[] = {
	day_color_0, day_color_1, day_color_2, day_color_3,
	day_color_1, day_color_2, day_color_3, day_color_3,
	day_color_2, day_color_3, day_color_3, day_color_3,
	day_color_3, day_color_3, day_color_3, day_color_3,
	day_color_2, day_color_2, day_color_2, day_color_2,
	day_color_1, day_color_1, day_color_1, day_color_1,
	day_color_0, day_color_0, day_color_0, day_color_0
};

static const palette_color_t night_bkg_palettes[] = {
	night_color_0, night_color_1, night_color_2, night_color_3,
	night_color_1, night_color_2, night_color_3, night_color_3,
	night_color_2, night_color_3, night_color_3, night_color_3,
	night_color_3, night_color_3, night_color_3, night_color_3,
	night_color_2, night_color_2, night_color_2, night_color_2,
	night_color_1, night_color_1, night_color_1, night_color_1,
	night_color_0, night_color_0, night_color_0, night_color_0
};

static const palette_color_t ui_sprite_palettes[] = {
	RGB_WHITE, ui_color_0, ui_color_1, ui_color_3,
	RGB_WHITE, ui_color_1, ui_color_3, ui_color_3,
	RGB_WHITE, ui_color_3, ui_color_3, ui_color_3,
	RGB_WHITE, ui_color_3, ui_color_3, ui_color_3
};

static const palette_color_t green_sprite_palettes[] = {
	RGB_WHITE, green_color_0, green_color_1, green_color_2,
	RGB_WHITE, green_color_1, green_color_2, green_color_3,
	RGB_WHITE, green_color_2, green_color_3, green_color_3,
	RGB_WHITE, green_color_3, green_color_3, green_color_3
};

static const palette_color_t blue_sprite_palettes[] = {
	RGB_WHITE, blue_color_0, blue_color_1, blue_color_2,
	RGB_WHITE, blue_color_1, blue_color_2, blue_color_3,
	RGB_WHITE, blue_color_2, blue_color_3, blue_color_3,
	RGB_WHITE, blue_color_3, blue_color_3, blue_color_3
};

static const palette_color_t pink_sprite_palettes[] = {
	RGB_WHITE, pink_color_0, pink_color_1, pink_color_2,
	RGB_WHITE, pink_color_1, pink_color_2, pink_color_3,
	RGB_WHITE, pink_color_2, pink_color_3, pink_color_3,
	RGB_WHITE, pink_color_3, pink_color_3, pink_color_3
};

static const palette_color_t brown_sprite_palettes[] = {
	RGB_WHITE, brown_color_0, brown_color_1, brown_color_2,
	RGB_WHITE, brown_color_1, brown_color_2, brown_color_3,
	RGB_WHITE, brown_color_2, brown_color_3, brown_color_3,
	RGB_WHITE, brown_color_3, brown_color_3, brown_color_3
};

static const palette_color_t grey_sprite_palettes[] = {
	RGB_WHITE, grey_color_0, grey_color_1, grey_color_2,
	RGB_WHITE, grey_color_1, grey_color_2, grey_color_3,
	RGB_WHITE, grey_color_2, grey_color_3, grey_color_3,
	RGB_WHITE, grey_color_3, grey_color_3, grey_color_3
};

static const palette_color_t glow_sprite_palettes[] = {
	RGB_WHITE, glow_color_0, glow_color_1, glow_color_2,
	RGB_WHITE, glow_color_1, glow_color_2, glow_color_3,
	RGB_WHITE, glow_color_2, glow_color_3, glow_color_3,
	RGB_WHITE, glow_color_3, glow_color_3, glow_color_3
};

#define HUD_ATTR 1 & 0x07
static const uint8_t default_attrs[80] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
static const uint8_t hud_attrs[80] = {
	HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR,
	HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR,
	HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR,
	HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR,
	HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR, HUD_ATTR
};

static void set_bkg_colors_cgb(uint8_t i) {
	if (!(current_scene == FIELD || current_scene == POND || current_scene == GARDEN)) {
		set_bkg_palette(0, 1, &ui_bkg_palettes[i]);
	} else if (is_night) {
		set_bkg_palette(0, 1, &night_bkg_palettes[i]);
	} else {
		set_bkg_palette(0, 1, &day_bkg_palettes[i]);
	}

	set_bkg_palette(1, 1, &ui_bkg_palettes[i]);

	if (current_scene == FIELD || current_scene == POND || current_scene == GARDEN) {
		set_bkg_attributes(0, 0, 20, 4, &hud_attrs[0]);
	} else {
		set_bkg_attributes(0, 0, 20, 4, &default_attrs[0]);
	}
}

void set_bkg_colors(uint8_t palette_num) BANKED {

	switch(palette_num) {
		case 0:
			if (can_use_color) {
				set_bkg_colors_cgb(0);
			} else {
				BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
			}
			break;

		case 1:
			if (can_use_color) {
				set_bkg_colors_cgb(4);
			} else {
				BGP_REG = DMG_PALETTE(DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK);
			}
			break;

		case 2:
			if (can_use_color) {
				set_bkg_colors_cgb(8);
			} else {
				BGP_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_BLACK, DMG_BLACK, DMG_BLACK);
			}
			break;

		case 3:
			if (can_use_color) {
				set_bkg_colors_cgb(12);
			} else {
				BGP_REG = DMG_PALETTE(DMG_BLACK, DMG_BLACK, DMG_BLACK, DMG_BLACK);
			}
			break;

		case 4:
			if (can_use_color) {
				set_bkg_colors_cgb(16);
			} else {
				BGP_REG = DMG_PALETTE(DMG_BLACK, DMG_BLACK, DMG_BLACK, DMG_BLACK);
			}
			break;

		case 5:
			if (can_use_color) {
				set_bkg_colors_cgb(20);
			} else {
				BGP_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_DARK_GRAY, DMG_DARK_GRAY, DMG_DARK_GRAY);
			}
			break;

		case 6:
			if (can_use_color) {
				set_bkg_colors_cgb(24);
			} else {
				BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_WHITE, DMG_WHITE, DMG_WHITE);
			}
			break;
	}
}

static void set_sprite_colors_cgb(uint8_t i) {
	set_sprite_palette(UI_PALETTE, 1, &ui_sprite_palettes[i]);
	set_sprite_palette(GREEN_PALETTE, 1, &green_sprite_palettes[i]);
	set_sprite_palette(BLUE_PALETTE, 1, &blue_sprite_palettes[i]);
	set_sprite_palette(PINK_PALETTE, 1, &pink_sprite_palettes[i]);
	set_sprite_palette(BROWN_PALETTE, 1, &brown_sprite_palettes[i]);
	set_sprite_palette(GREY_PALETTE, 1, &grey_sprite_palettes[i]);
	set_sprite_palette(GLOW_PALETTE, 1, &glow_sprite_palettes[i]);
}

void set_sprite_colors(uint8_t palette_num) BANKED {
	switch(palette_num) {
		case 0:
			if (can_use_color) {
				set_sprite_colors_cgb(0);
			} else {
				OBP0_REG = DMG_PALETTE(DMG_WHITE, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
			}
			break;

		case 1:
			if (can_use_color) {
				set_sprite_colors_cgb(4);
			} else {
				OBP0_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK, DMG_BLACK);
			}
			break;

		case 2:
			if (can_use_color) {
				set_sprite_colors_cgb(8);
			} else {
				OBP0_REG = DMG_PALETTE(DMG_WHITE, DMG_BLACK, DMG_BLACK, DMG_BLACK);
			}
			break;

		case 3:
			if (can_use_color) {
				set_sprite_colors_cgb(12);
			} else {
				OBP0_REG = DMG_PALETTE(DMG_WHITE, DMG_BLACK, DMG_BLACK, DMG_BLACK);
			}
			break;
	}
}
