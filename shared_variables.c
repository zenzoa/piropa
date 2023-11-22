#include <gbdk/platform.h>

uint8_t saved_bank;

uint8_t has_save;
uint8_t is_time_to_save;

#define SPEED_FAST 0
#define SPEED_MEDIUM 1
#define SPEED_SLOW 2
uint8_t game_speed = SPEED_MEDIUM;

#define TITLE 0
#define FIELD 1
#define POND 2
#define GARDEN 3
#define INFO 4
#define INVENTORY 5
uint8_t current_scene;
uint8_t last_scene;

uint8_t is_night;

uint8_t restore_x;
uint8_t restore_y;

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
uint8_t hand_state;

uint8_t hand_x;
uint8_t hand_y;
uint16_t hand_x_frac;
uint16_t hand_y_frac;

uint8_t frog_x;
uint8_t frog_y;

uint16_t age;
uint8_t age_part;

#define EGG 0
#define TADPOLE 1
#define FROGLET 2
#define TEEN 3
#define ADULT 4
#define DEAD 5
uint8_t life_stage;

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
uint8_t stage;

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
uint8_t anim;

uint8_t emote;

uint8_t is_evolving;

uint8_t stomach;
uint8_t bowels;
uint8_t weight;
uint8_t hygiene;
uint8_t energy;
uint8_t love;
uint8_t medicine;
uint8_t health;
uint8_t sickness;

#define MAX_POOPS 6
uint8_t poop_count;
uint8_t poops_to_add;
uint8_t poops_scene[MAX_POOPS];
uint8_t poops_x[MAX_POOPS];
uint8_t poops_y[MAX_POOPS];

#define FLY_COUNT 5
uint8_t fly_alive[FLY_COUNT];
uint8_t fly_respawn[FLY_COUNT];
#define DRAGONFLY_COUNT 1
uint8_t dragonfly_alive[DRAGONFLY_COUNT];
uint8_t dragonfly_respawn[DRAGONFLY_COUNT];
#define FIREFLY_COUNT 3
uint8_t firefly_alive[FIREFLY_COUNT];
uint8_t firefly_respawn[FIREFLY_COUNT];
#define BUTTERFLY_COUNT 3
uint8_t butterfly_alive[BUTTERFLY_COUNT];
uint8_t butterfly_respawn[BUTTERFLY_COUNT];

#define PLANT_COUNT 3
uint8_t plant_age[PLANT_COUNT];
uint8_t plant_stage[PLANT_COUNT];
uint8_t plant_is_watered[PLANT_COUNT];

#define PLANT_0_X 6
#define PLANT_0_Y 11

#define PLANT_1_X 10
#define PLANT_1_Y 12

#define PLANT_2_X 14
#define PLANT_2_Y 11

uint8_t watering_plant;

const unsigned char big_cloud_1_tile_map[3] = { 0x70, 0x71, 0x72 };
const unsigned char big_cloud_2_tile_map[3] = { 0x73, 0x74, 0x75 };
const unsigned char small_cloud_1_tile_map[2] = { 0x70, 0x72 };
const unsigned char small_cloud_2_tile_map[2] = { 0x73, 0x75 };
