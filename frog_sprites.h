#define STAGE_EGG 0
#define STAGE_BABY 1
#define STAGE_CHILD 2
#define STAGE_TEEN_NORM 3
#define STAGE_TEEN_TAIL 4
#define STAGE_TEEN_BW 5
#define STAGE_NORM 6
#define STAGE_MUSH 7
#define STAGE_AXO 8
#define STAGE_DINO 9
#define STAGE_APPLE 10
#define STAGE_PANDA 11
#define STAGE_DEAD_BAD 12
#define STAGE_DEAD_GOOD 13

#define FACE_NEUTRAL 0
#define FACE_HAPPY 1
#define FACE_OVERJOYED 2
#define FACE_SAD 3
#define FACE_SCARED 4
#define FACE_ANGRY 5
#define FACE_EAT 6
#define FACE_WALK_LEFT 7
#define FACE_WALK_RIGHT 8
#define FACE_SLEEP 9

extern void swap_frog_vram();
extern void set_frog_sprite_data(uint8_t stage, uint8_t face);
extern void draw_frog_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite);
