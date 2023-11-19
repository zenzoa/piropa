BANKREF_EXTERN(garden_bank)

extern void update_plants(uint8_t game_speed);
extern void setup_garden_data(void) NONBANKED;
extern void setup_garden(void);
extern void update_garden(void);
extern void restore_garden_tile(uint8_t x, uint8_t y) NONBANKED;
