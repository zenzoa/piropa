BANKREF_EXTERN(title_bank)

extern uint8_t selected_title_item;
#define TITLE_ITEM_CONTINUE 0
#define TITLE_ITEM_RESET 1
#define TITLE_ITEM_CONFIRM_RESET 2

extern void draw_title_sprites(uint8_t *last_sprite);
extern void update_title(void);
extern void select_title_item(uint8_t new_item);
extern void setup_title_data(void) NONBANKED;
extern void setup_title(void);
