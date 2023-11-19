BANKREF_EXTERN(bugs_bank)

#define BUG_NONE 0
#define BUG_FLY 1
#define BUG_DRAGONFLY 2
#define BUG_FIREFLY 3
#define BUG_BUTTERFLY 4

#define FLY_COUNT 5
extern uint8_t fly_respawn[FLY_COUNT];

#define DRAGONFLY_COUNT 1
extern uint8_t dragonfly_respawn[DRAGONFLY_COUNT];

#define FIREFLY_COUNT 3
extern uint8_t firefly_respawn[FIREFLY_COUNT];

#define BUTTERFLY_COUNT 3
extern uint8_t butterfly_respawn[FIREFLY_COUNT];

extern void respawn_bugs(void);
extern void draw_bugs(uint8_t *last_sprite);
extern uint8_t grab_bug(void);
extern void drop_bug(uint8_t bug_type);
extern void setup_bugs(void);
extern void setup_bugs_data(void) NONBANKED;
