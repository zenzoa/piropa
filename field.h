extern void setup_field_data(void) BANKED;
extern void setup_field(uint8_t hand_has_moon) BANKED;
extern void update_field(void) BANKED;
extern void restore_field_tile(uint8_t x, uint8_t y) BANKED;

extern void set_basket(uint8_t is_open) BANKED;

extern void grab_moon_from_sky(void) BANKED;
extern void return_moon_to_sky(void) BANKED;
