#define HAND_DEFAULT 0
#define HAND_OPEN 1

extern void swap_hand_vram();
extern void set_hand_sprite_data(uint8_t hand_state);
extern void draw_hand_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite);
