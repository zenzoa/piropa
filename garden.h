BANKREF_EXTERN(garden_bank)

extern void update_plants(uint8_t game_speed);
extern void setup_garden_data(uint8_t is_night) NONBANKED;
extern void setup_garden(uint8_t is_night);
extern void update_garden(uint8_t is_night);
extern void restore_garden_tile(uint8_t x, uint8_t y) NONBANKED;
