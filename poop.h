extern void setup_poop_data(void) NONBANKED ;
extern void reset_poops(void) BANKED;
extern void draw_poops(void) BANKED;
extern void add_poop(uint8_t x, uint8_t y) BANKED;
extern void clean_poop_at(uint8_t x, uint8_t y) NONBANKED;
extern void update_poops(void) BANKED;
