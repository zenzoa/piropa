#include <gbdk/platform.h>

uint8_t has_save;

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

#define EGG 0
#define TADPOLE 1
#define FROGLET 2
#define TEEN 3
#define ADULT 4
#define DEAD 5
uint8_t life_stage;

uint8_t is_evolving;

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
