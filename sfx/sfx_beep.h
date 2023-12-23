/*

	sfx_beep

	Sound Effect File.

	Info:
		Length			:	1
		Priority		:	0
		Channels used	:	Noise channel
		SGB Support		:	No
*/

#ifndef __sfx_beep_h_INCLUDE
#define __sfx_beep_h_INCLUDE
#define CBTFX_PLAY_sfx_beep CBTFX_init(&sfx_beep[0])
extern const unsigned char sfx_beep[];
#endif
