BANKREF_EXTERN(frog_bank)

extern uint8_t goal_x;
extern uint8_t goal_y;

extern uint8_t mood;

extern uint8_t action;
#define ACTION_STAND 0
#define ACTION_EMOTE 1
#define ACTION_WALK 2
#define ACTION_BITE 3
#define ACTION_EAT 4
#define ACTION_REFUSE 5
#define ACTION_ENJOY 6
#define ACTION_YAWN 7
#define ACTION_SLEEP 8
#define ACTION_WAKE 9
#define ACTION_WASH 10
#define ACTION_CLEAN 11
#define ACTION_PET 12
#define ACTION_LOVE 13
#define ACTION_MEDICATE 14
#define ACTION_POOP 15
#define ACTION_WATERING 16

extern void update_stats(void);
extern void setup_frog(uint8_t reset);
extern void draw_frog(uint8_t *last_sprite);
extern void update_frog(void);

extern void start_feed(uint8_t bug_type);
extern void start_pet(void);
extern void start_medicate(void);
extern void start_wash(void);
extern void start_sleep(void);
extern void start_walk_to_plant(uint8_t plant_number);

extern void place_in_scene(void);
