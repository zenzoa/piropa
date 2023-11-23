#define BUG_NONE 0
#define BUG_FLY 1
#define BUG_DRAGONFLY 2
#define BUG_FIREFLY 3
#define BUG_BUTTERFLY 4

extern void respawn_bugs(void) BANKED;
extern void draw_bugs(void) BANKED;
extern uint8_t grab_bug(void) BANKED;
extern void drop_bug(uint8_t bug_type) BANKED;
extern void setup_bugs(void) BANKED;
extern void setup_bugs_data(void) BANKED;
