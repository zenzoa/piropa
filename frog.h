BANKREF_EXTERN(frog_bank)

extern uint16_t age;
extern uint8_t fullness;
extern uint8_t happiness;

extern void update_stats(uint16_t time_diff);
extern void reset_frog();
extern void draw_frog(uint8_t *last_sprite);
