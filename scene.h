extern uint8_t current_scene;
#define TITLE_SCREEN 0
#define CLOCK_SCREEN 1
#define INVENTORY 2
#define FIELD 3
#define POND 4
#define GARDEN 5

extern uint8_t is_night;

extern void setup_scene(uint8_t new_scene);
extern void update_scene(void);
extern void start_transition_to_scene(uint8_t new_scene, uint8_t new_is_night);
