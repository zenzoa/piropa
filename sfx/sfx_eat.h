/*

	sfx_eat

	Sound Effect File.
	
	Info:
		Length			:	10
		Priority		:	0
		Channels used	:	Duty channel 2 & Noise channel
		SGB Support		:	No
*/

#ifndef __sfx_eat_h_INCLUDE
#define __sfx_eat_h_INCLUDE
#define CBTFX_PLAY_sfx_eat CBTFX_init(&sfx_eat[0])
extern const unsigned char sfx_eat[];
#endif