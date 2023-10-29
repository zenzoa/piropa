#define EMOTE_NONE 0
#define EMOTE_SUN 1
#define EMOTE_SAD 2
#define EMOTE_ANGRY 3
#define EMOTE_BUBBLES 4
#define EMOTE_SPARKLE 5
#define EMOTE_HEART 6
#define EMOTE_HEARTBREAK 7
#define EMOTE_SLEEP 8
#define EMOTE_SKULL 9
#define EMOTE_HEAL 10

extern void swap_emote_vram(void);
extern void set_emote_sprite_data(uint8_t emote);
extern void draw_emote_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite);

extern void setup_emote_sprites(void);
extern void draw_dirt_sprite(uint8_t x, uint8_t y, uint8_t *last_sprite);
extern void draw_bath_sprite(uint8_t x, uint8_t y, uint8_t frame, uint8_t *last_sprite);
