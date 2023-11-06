BANKREF_EXTERN(title_bank)

extern void draw_title_sprites(uint8_t *last_sprite);
extern void update_title(void);
extern void setup_title_data(void) NONBANKED;
extern void setup_title(void);
extern void handle_title_input(uint8_t button_pressed);
