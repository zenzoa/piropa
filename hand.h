#define DEFAULT_HAND 0
#define TICKLE_1 1
#define TICKLE_2 2
#define JAR_EMPTY 3
#define JAR_EMPTY_TIP 4
#define JAR_FULL 5
#define JAR_FULL_TIP 6
#define JAR_2_3 7
#define JAR_2_3_TIP 8
#define JAR_1_3 9
#define JAR_1_3_TIP 10
#define HOLD_SOAP 11
#define HOLD_MOON 12
#define HOLD_STRAWBERRY 13
#define HOLD_BLUEBERRY 14
#define HOLD_BLACKBERRY 15

extern uint8_t hand_type;

extern void init_hand();
extern void set_hand_type(uint8_t new_hand_type);
extern void draw_hand(uint8_t *last_used_sprite, uint8_t frog_x);
extern void move_hand(int16_t dx, int16_t dy);
extern void get_hand_position(uint8_t *x, uint8_t *y);