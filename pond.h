BANKREF_EXTERN(pond_bank)

extern void setup_pond_data(uint8_t is_night) NONBANKED;
extern void setup_pond(uint8_t is_night);
extern void update_pond(uint8_t is_night);
extern void restore_pond_tile(uint8_t x, uint8_t y) NONBANKED;
