#include <gbdk/platform.h>
#include <gb/gb.h>
#include <stdint.h>

#include "hugedriver/include/hUGEDriver.h"
#include "music/bs_rpg_forest.h"

#define FROG_MUSIC 0

uint8_t current_music = 255;
uint8_t current_music_bank = BANK(bs_rpg_forest_bank);

void set_music(uint8_t new_music) {
	if (current_music != new_music) {
		current_music = new_music;
		__critical {
			hUGE_mute_channel(HT_CH1,HT_CH_MUTE);
			hUGE_mute_channel(HT_CH2,HT_CH_MUTE);
			hUGE_mute_channel(HT_CH3,HT_CH_MUTE);
			hUGE_mute_channel(HT_CH4,HT_CH_MUTE);

			switch(new_music) {
				case FROG_MUSIC:
					current_music_bank = BANK(bs_rpg_forest_bank);
					SWITCH_ROM(current_music_bank);
					hUGE_init(&bs_rpg_forest);
					break;
			}
		}
	}
}

void play_music(void) {
	uint8_t saved_bank = _current_bank;
	SWITCH_ROM(current_music_bank);
	hUGE_dosound();
	SWITCH_ROM(saved_bank);
}
