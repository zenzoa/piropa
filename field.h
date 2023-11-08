BANKREF_EXTERN(field_bank)

#define MAX_POOPS 6
extern uint8_t poops_x[MAX_POOPS];
extern uint8_t poops_y[MAX_POOPS];

extern void setup_field_data(void) NONBANKED;
extern void setup_field(void);
extern void update_field(void);

extern void grab_moon_from_sky(void);
extern void return_moon_to_sky(void);

extern void clean_poop_at(uint8_t x, uint8_t y);
extern void add_poop(uint8_t x, uint8_t y);
