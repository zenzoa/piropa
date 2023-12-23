/*

	sfx_wash

	Sound Effect File.
	
	Info:
		Length			:	11
		Priority		:	0
		Channels used	:	Duty channel 2 & Noise channel
		SGB Support		:	No
*/

#ifndef __sfx_wash_h_INCLUDE
#define __sfx_wash_h_INCLUDE
#define CBTFX_PLAY_sfx_wash CBTFX_init(&sfx_wash[0])
extern const unsigned char sfx_wash[];
#endif