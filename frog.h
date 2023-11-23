extern void update_stats(void) BANKED;
extern void setup_frog(uint8_t reset) BANKED;
extern void draw_frog(void) BANKED;
extern void update_frog(void) BANKED;

extern void start_feed(uint8_t bug_type) BANKED;
extern void start_pet(void) BANKED;
extern void start_medicate(void) BANKED;
extern void start_wash(void) BANKED;
extern void start_sleep(void) BANKED;
extern void start_walk_to_plant(uint8_t plant_number) BANKED;

extern uint8_t is_sleeping(void) BANKED;

extern void place_in_scene(void) BANKED;
