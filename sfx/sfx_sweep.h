/*

	sfx_sweep

	Sound Effect File.
	
	Info:
		Length			:	21
		Priority		:	1
		Channels used	:	Duty channel 2 & Noise channel
		SGB Support		:	No
*/

#ifndef __sfx_sweep_h_INCLUDE
#define __sfx_sweep_h_INCLUDE
#define CBTFX_PLAY_sfx_sweep CBTFX_init(&sfx_sweep[0])
extern const unsigned char sfx_sweep[];
#endif