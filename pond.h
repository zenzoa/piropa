BANKREF_EXTERN(pond_bank)

extern void setup_pond_data(void) NONBANKED;
extern void setup_pond(void);
extern void update_pond(void);
extern void restore_pond_tile(uint8_t x, uint8_t y) NONBANKED;
