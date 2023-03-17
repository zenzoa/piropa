#include <gbdk/metasprites.h>

#include "sprites/hand_normal.h"

#define DEFAULT_HAND 0
#define TICKLE_1 1
#define TICKLE_2 2
#define HOLD_JAR_EMPTY 3
#define HOLD_JAR_FULL 4
#define HOLD_JAR_2_3 5
#define HOLD_JAR_1_3 6
#define TIP_JAR_EMPTY 7
#define TIP_JAR_FULL 8
#define TIP_JAR_2_3 9
#define TIP_JAR_1_3 10
#define HOLD_SOAP 11
#define HOLD_MOON 12
#define HOLD_STRAWBERRY 13
#define HOLD_BLUEBERRY 14
#define HOLD_BLACKBERRY 15

extern uint8_t hand_type;

extern void init_hand();
extern void draw_hand(uint8_t *last_used_sprite, uint8_t frog_x);
extern void move_hand(int16_t dx, int16_t dy);
extern void get_hand_position(uint8_t *x, uint8_t *y);