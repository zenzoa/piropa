extern uint8_t has_save;
extern uint8_t is_time_to_save;

#define SPEED_FAST 0
#define SPEED_MEDIUM 1
#define SPEED_SLOW 2
extern uint8_t game_speed;

#define TITLE 0
#define FIELD 1
#define POND 2
#define GARDEN 3
#define INFO 4
#define INVENTORY 5
#define CREDITS 6
extern uint8_t current_scene;
extern uint8_t last_scene;

extern uint8_t is_night;

extern uint8_t do_restore;
extern uint8_t restore_x;
extern uint8_t restore_y;

#define A_BUTTON 0
#define B_BUTTON 1
#define UP_BUTTON 2
#define RIGHT_BUTTON 3
#define DOWN_BUTTON 4
#define LEFT_BUTTON 5

#define HAND_DEFAULT 0
#define HAND_POINT 1
#define HAND_PET1 2
#define HAND_PET2 3
#define HAND_MEDICINE 4
#define HAND_MEDICINE_USE 5
#define HAND_SOAP 6
#define HAND_SOAP_USE 7
#define HAND_BROOM 8
#define HAND_BROOM_USE 9
#define HAND_MOON 10
#define HAND_FLY 11
#define HAND_DRAGONFLY 12
#define HAND_FIREFLY 13
#define HAND_BUTTERFLY 14
extern uint8_t hand_state;

extern uint8_t hand_x;
extern uint8_t hand_y;
extern uint16_t hand_x_frac;
extern uint16_t hand_y_frac;

extern uint8_t frog_x;
extern uint8_t frog_y;

extern uint16_t age;
extern uint8_t age_part;

#define EGG 0
#define TADPOLE 1
#define FROGLET 2
#define TEEN 3
#define ADULT 4
#define DEAD 5
extern uint8_t life_stage;

#define STAGE_EGG 0
#define STAGE_TADPOLE 1
#define STAGE_FROGLET 2
#define STAGE_TEEN_NORM 3
#define STAGE_TEEN_TAIL 4
#define STAGE_TEEN_BW 5
#define STAGE_NORM 6
#define STAGE_MUSH 7
#define STAGE_AXO 8
#define STAGE_DINO 9
#define STAGE_APPLE 10
#define STAGE_PANDA 11
#define STAGE_DEAD_BAD 12
#define STAGE_DEAD_GOOD 13
extern uint8_t stage;

#define ANIM_NEUTRAL 0
#define ANIM_HAPPY 1
#define ANIM_LAUGH 2
#define ANIM_SAD 3
#define ANIM_STRESSED 4
#define ANIM_ANGRY 5
#define ANIM_EAT 6
#define ANIM_YAWN 7
#define ANIM_WALK_LEFT 8
#define ANIM_WALK_RIGHT 9
#define ANIM_SLEEP 10
extern uint8_t anim;

extern uint8_t emote;

extern uint8_t is_evolving;

extern uint8_t stomach;
extern uint8_t bowels;
extern uint8_t weight;
extern uint8_t hygiene;
extern uint8_t energy;
extern uint8_t love;
extern uint8_t medicine;
extern uint8_t health;
extern uint8_t sickness;

extern uint8_t num_past_frogs;

#define MAX_POOPS 6
extern uint8_t poop_count;
extern uint8_t poops_to_add;
extern uint8_t poops_scene[MAX_POOPS];
extern uint8_t poops_x[MAX_POOPS];
extern uint8_t poops_y[MAX_POOPS];

#define BUG_NONE 0
#define BUG_FLY 1
#define BUG_DRAGONFLY 2
#define BUG_FIREFLY 3
#define BUG_BUTTERFLY 4

#define FLY_COUNT 6
extern uint8_t fly_alive[FLY_COUNT];
extern uint8_t fly_respawn[FLY_COUNT];
#define DRAGONFLY_COUNT 2
extern uint8_t dragonfly_alive[DRAGONFLY_COUNT];
extern uint8_t dragonfly_respawn[DRAGONFLY_COUNT];
#define FIREFLY_COUNT 4
extern uint8_t firefly_alive[FIREFLY_COUNT];
extern uint8_t firefly_respawn[FIREFLY_COUNT];
#define BUTTERFLY_COUNT 4
extern uint8_t butterfly_alive[BUTTERFLY_COUNT];
extern uint8_t butterfly_respawn[BUTTERFLY_COUNT];

extern uint8_t inventory_flies;
extern uint8_t inventory_dragonflies;
extern uint8_t inventory_fireflies;
extern uint8_t inventory_butterflies;

extern uint8_t num_dragonflies_eaten;
extern uint8_t num_fireflies_eaten;
extern uint8_t num_butterflies_eaten;

#define PLANT_COUNT 3
extern uint8_t plant_age[PLANT_COUNT];
extern uint8_t plant_stage[PLANT_COUNT];
extern uint8_t plant_is_watered[PLANT_COUNT];

#define PLANT_0_X 6
#define PLANT_0_Y 11

#define PLANT_1_X 10
#define PLANT_1_Y 12

#define PLANT_2_X 14
#define PLANT_2_Y 11

extern uint8_t watering_plant;

extern const unsigned char big_cloud_1_tile_map[3];
extern const unsigned char big_cloud_2_tile_map[3];
extern const unsigned char small_cloud_1_tile_map[2];
extern const unsigned char small_cloud_2_tile_map[2];

extern typedef struct sprite_data_t {
	uint8_t bank;
	uint8_t tile_count;
	uint8_t * tiles;
	uint8_t * metasprites;
} sprite_data_t;

extern uint8_t last_sprite;

#define UI_PALETTE 0
#define GREEN_PALETTE 1
#define BLUE_PALETTE 2
#define PINK_PALETTE 3
#define BROWN_PALETTE 4
#define GREY_PALETTE 5
#define GLOW_PALETTE 6

extern void set_banked_sprite_data(uint8_t bank, uint8_t vram, uint8_t tile_count, uint8_t * tiles);
extern void draw_banked_sprite(uint8_t bank, uint8_t * metasprites, uint8_t frame, uint8_t vram, uint8_t palette, uint8_t x, uint8_t y);
extern void draw_banked_sprite_flip(uint8_t bank, uint8_t * metasprites, uint8_t frame, uint8_t vram, uint8_t palette, uint8_t x, uint8_t y);

extern void set_banked_bkg_data(uint8_t bank, uint8_t vram, uint8_t tile_count, uint8_t * tiles);
extern void set_banked_bkg_tiles(uint8_t bank, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t * tile_map);
extern void restore_banked_bkg_tile_xy(uint8_t bank, uint8_t x, uint8_t y, uint8_t * tile_map);
