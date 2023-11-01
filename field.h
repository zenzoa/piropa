extern uint8_t moon_in_sky;
extern uint8_t sky_anim_counter;

#define MAX_POOPS 6

extern void draw_poops(void);

extern void setup_field(void);
extern void update_field(void);

extern void grab_moon_from_sky(void);
extern void return_moon_to_sky(void);

extern uint8_t is_poop_at(uint8_t x, uint8_t y);
extern void clean_poop_at(uint8_t x, uint8_t y);
extern void add_poop(uint8_t x, uint8_t y);
