BANKREF_EXTERN(poop_bank)

#define MAX_POOPS 6
extern uint8_t poop_count;
extern uint8_t poops_to_add;
extern uint8_t poops_scene[MAX_POOPS];
extern uint8_t poops_x[MAX_POOPS];
extern uint8_t poops_y[MAX_POOPS];

extern void setup_poop_data(void) NONBANKED ;
extern void reset_poops(void);
extern void draw_poops(void);
extern void add_poop(uint8_t x, uint8_t y);
extern void clean_poop_at(uint8_t x, uint8_t y) NONBANKED;
extern void update_poops(void);
