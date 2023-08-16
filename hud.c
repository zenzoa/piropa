#include <gbdk/platform.h>

#include "clock.h"
#include "frog.h"

#include "sprites/backgrounds/hud.h"

#define HUD_VRAM 0xe0
#define COLON_VRAM 0xea
#define AM_VRAM 0xeb
#define PM_VRAM 0xec

#define FULLNESS_EMPTY_VRAM 0xed
#define FULLNESS_FULL_VRAM 0xee
#define HAPPINESS_EMPTY_VRAM 0xef
#define HAPPINESS_FULL_VRAM 0xf0

uint8_t clock_vram = HUD_VRAM;

uint8_t hud_hours_0 = 7;
uint8_t hud_minutes_0 = 30;
uint8_t hud_seconds_0 = 0;

uint8_t hud_hours;
uint8_t hud_minutes;
uint8_t hud_seconds;

void draw_stats(void) {
	SWITCH_ROM(BANK(frog_bank));

	uint8_t i = 1;
	uint8_t tile = 0;
	while (i <= 5) {
		tile = (fullness >= i * 2) ? FULLNESS_FULL_VRAM : FULLNESS_EMPTY_VRAM;
		set_bkg_tile_xy(i, 1, tile);

		tile = (happiness >= i * 2) ? HAPPINESS_FULL_VRAM : HAPPINESS_EMPTY_VRAM;
		set_bkg_tile_xy(19 - i, 1, tile);

		i++;
	}
}

void draw_time(void) {
	uint8_t display_hours = hud_hours;
	if (display_hours > 12) {
		display_hours -= 12;
		set_bkg_tile_xy(12, 1, PM_VRAM);
	} else {
		set_bkg_tile_xy(12, 1, AM_VRAM);
	}

	set_bkg_tile_xy(7, 1, clock_vram + (hud_hours / 10));
	set_bkg_tile_xy(8, 1, clock_vram + (hud_hours % 10));

	set_bkg_tile_xy(9, 1, COLON_VRAM);

	set_bkg_tile_xy(10, 1, clock_vram + (hud_minutes / 10));
	set_bkg_tile_xy(11, 1, clock_vram + (hud_minutes % 10));
}

void draw_hud(void) {
	draw_time();
	draw_stats();
}

void update_hud_clock(void) {
	hud_seconds = hud_seconds_0 + seconds;
	uint8_t seconds_overflow = 0;
	if (hud_seconds >= 60) {
		hud_seconds -= 60;
		seconds_overflow = 1;
	}

	hud_minutes = hud_minutes_0 + minutes + seconds_overflow;
	uint8_t minutes_overflow = 0;
	if (hud_minutes >= 60) {
		hud_minutes -= 60;
		minutes_overflow = 1;
	}

	hud_hours = hud_hours_0 + hours + minutes_overflow;
	if (hud_hours > 24) {
		hud_hours = 1;
	}
}

void setup_hud(void) {
	SWITCH_ROM(BANK(hud));
	set_bkg_data(HUD_VRAM, 17, hud_tiles);
	update_hud_clock();
	draw_hud();
}
