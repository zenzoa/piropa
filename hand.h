BANKREF_EXTERN(hand_bank)

extern uint8_t sweep_count;

extern void move_hand_by_frac(int16_t dx_frac, int16_t dy_frac);
extern void move_hand(uint8_t joypad_value);
extern uint8_t is_hand_empty(void);
extern uint8_t is_hand_over_frog(void);
extern void set_hand_state(uint8_t new_state) NONBANKED;
extern void setup_hand(void);
extern void draw_hand(uint8_t *last_sprite);
extern void update_hand(void);
