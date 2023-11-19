extern uint8_t is_transitioning;

extern void setup_scene(uint8_t new_scene);
extern void update_scene(void);
extern void start_transition_to_scene(uint8_t new_scene, uint8_t new_is_night);
extern void setup_data(uint8_t reset);
extern void reset_data(void);
