extern uint8_t selected_title_item;
#define CONTINUE 0
#define RESTART 1
#define CONFIRM_RESTART 2

extern void draw_title_sprites(uint8_t *last_sprite);
extern void update_title(void);
extern void select_title_item(uint8_t new_item);
extern void setup_title(void);
