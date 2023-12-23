#include <gbdk/platform.h>
#include <gb/gb.h>
#include <stdint.h>

#include "hugedriver/include/hUGEDriver.h"
#include "music/music_day.h"
#include "music/music_night.h"
#include "music/music_death.h"

#include "cbtfx.h"
#include "sfx/sfx_beep.h"
#include "sfx/sfx_tap.h"
#include "sfx/sfx_drop.h"
#include "sfx/sfx_pet.h"
#include "sfx/sfx_wash.h"
#include "sfx/sfx_meds.h"
#include "sfx/sfx_eat.h"
#include "sfx/sfx_happy.h"
#include "sfx/sfx_sad.h"
#include "sfx/sfx_meep1.h"
#include "sfx/sfx_meep2.h"
#include "sfx/sfx_meep3.h"
#include "sfx/sfx_evolve.h"
#include "sfx/sfx_die.h"
#include "sfx/sfx_chomp.h"
#include "sfx/sfx_sweep.h"

#define MUSIC_DRIVER_CH2_ON hUGE_mute_channel(HT_CH2, 0);
#define MUSIC_DRIVER_CH2_OFF hUGE_mute_channel(HT_CH2, 1);
#define MUSIC_DRIVER_CH4_ON hUGE_mute_channel(HT_CH4, 0);
#define MUSIC_DRIVER_CH4_OFF hUGE_mute_channel(HT_CH4, 1);

#define NO_MUSIC 0
#define DAY_MUSIC 1
#define NIGHT_MUSIC 2
#define DEATH_MUSIC 3

uint8_t current_music = 255;
uint8_t current_music_bank;

static const unsigned char * sfx_list[] = {
	&sfx_beep[0],
	&sfx_tap[0],
	&sfx_drop[0],
	&sfx_pet[0],
	&sfx_wash[0],
	&sfx_meds[0],
	&sfx_eat[0],
	&sfx_happy[0],
	&sfx_sad[0],
	&sfx_meep1[0],
	&sfx_meep2[0],
	&sfx_meep3[0],
	&sfx_evolve[0],
	&sfx_die[0],
	&sfx_chomp[0],
	&sfx_sweep[0]
};

void update_audio(void) {
	if (current_music != NO_MUSIC) {
		uint8_t saved_bank = _current_bank;
		SWITCH_ROM(current_music_bank);
		hUGE_dosound();
		SWITCH_ROM(saved_bank);
	}

	CBTFX_update();
}

void play_music(uint8_t new_music) {
	if (current_music != new_music) {
		current_music = new_music;

		__critical {
			// reset audio registers
			NR52_REG = 0;
			NR52_REG = 0x80;
			NR51_REG = 0xFF;
			NR50_REG = 0x77;

			hUGE_mute_channel(HT_CH1,HT_CH_MUTE);
			hUGE_mute_channel(HT_CH2,HT_CH_MUTE);
			hUGE_mute_channel(HT_CH3,HT_CH_MUTE);
			hUGE_mute_channel(HT_CH4,HT_CH_MUTE);

			switch(new_music) {
				case DAY_MUSIC:
					current_music_bank = BANK(music_day_bank);
					SWITCH_ROM(current_music_bank);
					hUGE_init(&music_day);
					break;

				case NIGHT_MUSIC:
					current_music_bank = BANK(music_night_bank);
					SWITCH_ROM(current_music_bank);
					hUGE_init(&music_night);
					break;

				case DEATH_MUSIC:
					current_music_bank = BANK(music_death_bank);
					SWITCH_ROM(current_music_bank);
					hUGE_init(&music_death);
					break;
			}
		}
	}
}

void play_sfx(uint8_t i) {
	CBTFX_init(sfx_list[i]);
}
