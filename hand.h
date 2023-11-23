extern uint8_t sweep_count;

extern void move_hand_by_frac(int16_t dx_frac, int16_t dy_frac) BANKED;
extern void move_hand(uint8_t joypad_value) BANKED;
extern uint8_t is_hand_empty(void) BANKED;
extern uint8_t is_hand_over_frog(void) BANKED;
extern void set_hand_state(uint8_t new_state) BANKED;
extern void setup_hand(void) BANKED;
extern void draw_hand(void) BANKED;
extern void update_hand(void) BANKED;
