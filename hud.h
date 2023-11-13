BANKREF_EXTERN(hud_bank)

extern void setup_hud_data(void) NONBANKED;
extern void draw_hud(void);

extern void drop_all(uint8_t except);
extern uint8_t handle_hud_input(uint8_t button_pressed);
