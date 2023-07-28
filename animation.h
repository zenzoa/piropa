#define ANIM_CONTINUES 0
#define ANIM_COMPLETE 1

extern typedef struct animation_t {
	uint8_t ticks;
	uint8_t ticks_per_frame;
	uint8_t frame;
	uint8_t frame_count;
	uint8_t loop;
	uint8_t loop_count;
} animation_t;

extern animation_t new_animation(uint8_t ticks_per_frame, uint8_t frame_count, uint8_t loop_count);
extern uint8_t update_animation(animation_t *anim);
