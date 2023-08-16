#define EMOTE_NONE 0
#define EMOTE_HAPPY 1
#define EMOTE_SAD 2
#define EMOTE_SCARED 3
#define EMOTE_ANGRY 4
#define EMOTE_SLEEP 5
#define EMOTE_SICK 6
#define EMOTE_LOVE 7

extern void swap_emote_vram(void);
extern void set_emote_sprite_data(uint8_t emote);
extern void draw_emote_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite);
