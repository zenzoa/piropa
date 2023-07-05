BANKREF_EXTERN(pond_code)

#define POND_SPARKLE_VRAM 0xE6
#define FLY_VRAM 0xCC

extern void draw_pond_sparkles(uint8_t is_night, uint8_t at_pond);

extern void draw_flies(uint8_t *last_used_sprite, uint8_t is_night, uint8_t at_pond);
extern uint8_t grab_fly(uint8_t hand_x, uint8_t hand_y);
extern void release_fly(uint8_t hand_x, uint8_t hand_y);
extern void feed_fly();
extern void reset_flies();
extern void update_pond(uint8_t time_speed);
extern void update_pond_after_break(uint8_t time_speed, uint16_t *days, uint8_t *hours, uint8_t *minutes, uint8_t *seconds);
extern void load_pond_data();
