/*

	sfx_chomp

	Sound Effect File.
	
	Info:
		Length			:	14
		Priority		:	15
		Channels used	:	Duty channel 2 & Noise channel
		SGB Support		:	No
*/

#ifndef __sfx_chomp_h_INCLUDE
#define __sfx_chomp_h_INCLUDE
#define CBTFX_PLAY_sfx_chomp CBTFX_init(&sfx_chomp[0])
extern const unsigned char sfx_chomp[];
#endif