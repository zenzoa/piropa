BANKREF_EXTERN(hand_bank)

extern uint8_t hand_x;
extern uint8_t hand_y;

extern void setup_hand();
extern void draw_hand(uint8_t *last_sprite, uint8_t frog_x);
extern void move_hand_by_frac(int16_t dx_frac, int16_t dy_frac);
