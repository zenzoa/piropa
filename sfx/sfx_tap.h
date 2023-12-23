/*

	sfx_tap

	Sound Effect File.
	
	Info:
		Length			:	9
		Priority		:	3
		Channels used	:	Noise channel
		SGB Support		:	No
*/

#ifndef __sfx_tap_h_INCLUDE
#define __sfx_tap_h_INCLUDE
#define CBTFX_PLAY_sfx_tap CBTFX_init(&sfx_tap[0])
extern const unsigned char sfx_tap[];
#endif