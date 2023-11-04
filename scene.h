extern uint8_t current_scene;
#define TITLE 0
#define FIELD 1
#define POND 2
#define GARDEN 3
#define STATS 4
#define INVENTORY 5

extern uint8_t is_night;

extern void setup_scene(uint8_t new_scene);
extern void update_scene(void);
extern void start_transition_to_scene(uint8_t new_scene, uint8_t new_is_night);
extern void restart(void);
