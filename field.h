BANKREF_EXTERN(field_bank)

extern void setup_field_data(void) NONBANKED;
extern void setup_field(uint8_t hand_has_moon);
extern void update_field(void);
extern void restore_field_tile(uint8_t x, uint8_t y) NONBANKED;

extern void set_basket(uint8_t is_open);

extern void grab_moon_from_sky(void);
extern void return_moon_to_sky(void);
