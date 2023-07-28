#include <gbdk/platform.h>

#define ANIM_CONTINUES 0
#define ANIM_COMPLETE 1

typedef struct animation_t {
	uint8_t ticks;
	uint8_t ticks_per_frame;
	uint8_t frame;
	uint8_t frame_count;
	uint8_t loop;
	uint8_t loop_count;
} animation_t;

animation_t new_animation(uint8_t ticks_per_frame, uint8_t frame_count, uint8_t loop_count) {
	animation_t anim = {
		0, ticks_per_frame,
		0, frame_count,
		0, loop_count
	};
	return anim;
}

uint8_t update_animation(animation_t *anim) {
	anim->ticks += 1;
	if (anim->ticks >= anim->ticks_per_frame) {
		anim->ticks = 0;
		anim->frame += 1;
		if (anim->frame >= anim->frame_count) {
			anim->frame = 0;
			if (anim->loop_count > 0) {
				anim->loop += 1;
				if (anim->loop >= anim->loop_count) {
					return ANIM_COMPLETE;
				}
			}
		}
	}
	return ANIM_CONTINUES;
}
