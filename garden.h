BANKREF_EXTERN(garden_code)

#define PLANT_VRAM 0xD0
#define SPARKLE_VRAM 0xEC

extern void draw_plants();
extern void update_garden(uint8_t time_speed, uint8_t draw);
extern void update_garden_after_break(uint8_t time_speed, uint16_t *days, uint8_t *hours, uint8_t *minutes, uint8_t *seconds);
extern void water_plant(uint8_t plant_number);
extern uint8_t pick_fruit(uint8_t plant_number);
extern void draw_garden_sparkles(uint8_t *last_used_sprite);
extern void load_garden_data();
