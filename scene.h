extern uint8_t current_scene;
#define TITLE_SCREEN 0
#define CLOCK_SCREEN 1
#define INVENTORY 2
#define FIELD 3
#define POND 4
#define GARDEN 5

extern uint8_t time_of_day;
#define DAY 0
#define NIGHT 1

extern void setup_scene(uint8_t new_scene);
extern void update_scene(void);
