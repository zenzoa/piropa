#include <gbdk/platform.h>

uint16_t days = 0;
uint8_t hours = 0;
uint8_t minutes = 0;
uint8_t seconds = 0;

void read_clock() {
	/* MBC3 RTC: https://gbdev.io/pandocs/MBC3.html */
	/* Thanks to CasualPokePlayer and NanoCodeBug for help with this! */

	ENABLE_RAM;

	volatile uint8_t * const latch_clock = (volatile uint8_t * const)0x6000;
	*latch_clock = 0;
	*latch_clock = 1;

	volatile uint8_t * const rtc_register = (volatile uint8_t * const)0xA000;

	SWITCH_RAM(0x8);
	seconds = *rtc_register;
	SWITCH_RAM(0x9);
	minutes = *rtc_register;
	SWITCH_RAM(0xA);
	hours = *rtc_register;
	SWITCH_RAM(0xB);
	days = *rtc_register;

	SWITCH_RAM(0xC);
	// bit 0 is the most significant bit of the day register
	// day is a total of 9 bits or 511 days
	if (*rtc_register & 0x01) {
		days |= 0x0100;
	}
	// day overflow bit set
	if (*rtc_register & 0b10000000) {
		days += 512;
	}

	DISABLE_RAM;
}

void reset_clock() {
	days = 0;
	hours = 0;
	minutes = 0;
	seconds = 0;

	ENABLE_RAM;

	volatile uint8_t * const latch_clock = (volatile uint8_t * const)0x6000;
	*latch_clock = 0;
	*latch_clock = 1;

	volatile uint8_t * const rtc_register = (volatile uint8_t * const)0xA000;
	SWITCH_RAM(0x8);
	*rtc_register = 0;
	SWITCH_RAM(0x9);
	*rtc_register = 0;
	SWITCH_RAM(0xA);
	*rtc_register = 0;
	SWITCH_RAM(0xB);
	*rtc_register = 0;
	SWITCH_RAM(0xC);
	*rtc_register = 0;

	DISABLE_RAM;
}
