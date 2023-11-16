#include <time.h>

extern uint8_t last_scene;
extern uint8_t current_scene;
#define TITLE 0
#define FIELD 1
#define POND 2
#define GARDEN 3
#define INFO 4
#define INVENTORY 5

extern uint8_t is_night;
extern uint8_t is_transitioning;

extern uint8_t game_speed;
#define SPEED_FAST 0
#define SPEED_MEDIUM 1
#define SPEED_SLOW 2

extern const unsigned char big_cloud_1_tile_map[3];
extern const unsigned char big_cloud_2_tile_map[3];
extern const unsigned char small_cloud_1_tile_map[2];
extern const unsigned char small_cloud_2_tile_map[2];

extern time_t last_time;
extern time_t current_time;

extern uint8_t restore_x;
extern uint8_t restore_y;

extern void setup_scene(uint8_t new_scene);
extern void update_scene(void);
extern void start_transition_to_scene(uint8_t new_scene, uint8_t new_is_night);
extern void reset_data(void);
