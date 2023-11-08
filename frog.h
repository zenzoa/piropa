BANKREF_EXTERN(frog_bank)

extern uint8_t frog_x;
extern uint8_t frog_y;

extern uint16_t age;
extern uint8_t age_part;

extern uint8_t life_stage;
#define EGG 0
#define TADPOLE 1
#define FROGLET 2
#define TEEN 3
#define ADULT 4
#define DEAD 5

extern uint8_t mood;

extern uint8_t action;
#define ACTION_STAND 0
#define ACTION_EMOTE 1
#define ACTION_WALK 2
#define ACTION_EAT 3
#define ACTION_REFUSE 4
#define ACTION_ENJOY 5
#define ACTION_YAWN 6
#define ACTION_SLEEP 7
#define ACTION_WAKE 8
#define ACTION_WASH 9
#define ACTION_CLEAN 10
#define ACTION_PET 11
#define ACTION_LOVE 12
#define ACTION_MEDICATE 13
#define ACTION_POOP 14

extern uint8_t stomach;
extern uint8_t bowels;
extern uint8_t weight;
extern uint8_t hygiene;
extern uint8_t energy;
extern uint8_t love;
extern uint8_t medicine;
extern uint8_t health;
extern uint8_t sickness;

extern uint8_t poops;

extern uint8_t stage;
extern uint8_t anim;
extern uint8_t emote;

extern uint8_t is_evolving;

extern void update_stats(void);
extern void setup_frog(uint8_t reset);
extern void draw_frog(uint8_t *last_sprite);
extern void update_frog(void);

extern void start_pet(void);
extern void start_medicate(void);
extern void start_wash(void);
extern void start_sleep(void);

extern void place_in_scene(void);
