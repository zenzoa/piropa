BANKREF_EXTERN(frog_code)

#define EVO_EGG 0
#define EVO_BABY 1
#define EVO_CHILD 2
#define EVO_TEEN 3
#define EVO_TEEN_TAIL 4
#define EVO_TEEN_APPLE 5
#define EVO_ADULT 6
#define EVO_AXO 7
#define EVO_APPLE 8
#define EVO_MUSH 9
#define EVO_DINO 10

#define FROG_STAND 0
#define FROG_WALK_LEFT 1
#define FROG_WALK_RIGHT 2
#define FROG_HAPPY 3
#define FROG_SAD 4
#define FROG_EAT 5
#define FROG_TICKLED 6
#define FROG_SLEEP 7
#define FROG_WASH 8

extern uint8_t frog_x;
extern uint8_t frog_y;
extern uint8_t frog_evo;
extern uint8_t frog_state;
extern uint8_t frog_anim_frame;
extern uint8_t frog_anim_speed;
extern uint8_t frog_eating_fruit;
extern uint8_t frog_eating_fly;
extern uint8_t show_emote;
extern uint8_t friendship;
extern uint8_t happy;
extern uint8_t full;
extern uint8_t clean;
extern uint8_t energy;

extern void frog_tickle(uint8_t frame);
extern void frog_sleep();
extern void frog_wake();
extern void frog_start_wash();
extern void frog_stop_wash();
extern uint8_t frog_eat_fruit();
extern void frog_eat_fly();
extern void frog_change_rooms();
extern void move_frog(uint8_t x, uint8_t y);
extern void set_goal(uint8_t x, uint8_t y);
extern void set_random_goal();
extern void animate_frog(uint8_t wandering);
extern void update_frog(uint8_t time_speed);
extern void update_frog_after_break(uint8_t time_speed, uint16_t *days, uint8_t *hours, uint8_t *minutes, uint8_t *seconds);
extern void load_frog_data();
