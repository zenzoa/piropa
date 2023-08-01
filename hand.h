extern uint8_t hand_x;
extern uint8_t hand_y;

extern void set_hand_state(uint8_t new_state);
extern void setup_hand();
extern void draw_hand(uint8_t *last_sprite);
extern void move_hand_by_frac(int16_t dx_frac, int16_t dy_frac);
extern void update_hand();
