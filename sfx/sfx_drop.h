/*

	sfx_drop

	Sound Effect File.
	
	Info:
		Length			:	9
		Priority		:	2
		Channels used	:	Noise channel
		SGB Support		:	No
*/

#ifndef __sfx_drop_h_INCLUDE
#define __sfx_drop_h_INCLUDE
#define CBTFX_PLAY_sfx_drop CBTFX_init(&sfx_drop[0])
extern const unsigned char sfx_drop[];
#endif