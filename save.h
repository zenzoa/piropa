#define DATA_TIME_SPEED 0

#define DATA_IS_NIGHT 1

#define DATA_JAR_FULLNESS 2

#define DATA_NEXT_FRUIT 3
#define DATA_NUM_BLACKBERRIES 4
#define DATA_NUM_BLUEBERRIES 5
#define DATA_NUM_STRAWBERRIES 6

#define DATA_FROG_EVO 7
#define DATA_FROG_MIN 8
#define DATA_FROG_HOUR 9

#define DATA_HAPPY 10
#define DATA_FULL 11
#define DATA_CLEAN 12
#define DATA_ENERGY 13

#define DATA_HAPPY_TIMER 14
#define DATA_FULL_TIMER 15
#define DATA_CLEAN_TIMER 16
#define DATA_ENERGY_TIMER 17

#define DATA_FRUIT_EATEN 18
#define DATA_FLY_EATEN 19

#define DATA_PLANT_1_WATERED 20
#define DATA_PLANT_1_STAGE 21
#define DATA_PLANT_1_MIN 22

#define DATA_PLANT_2_WATERED 23
#define DATA_PLANT_2_STAGE 24
#define DATA_PLANT_2_MIN 25

#define DATA_PLANT_3_WATERED 26
#define DATA_PLANT_3_STAGE 27
#define DATA_PLANT_3_MIN 28

#define DATA_FLY1_STATE 29
#define DATA_FLY1_RESPAWN 30

#define DATA_FLY2_STATE 31
#define DATA_FLY2_RESPAWN 32

#define DATA_FLY3_STATE 33
#define DATA_FLY3_RESPAWN 34

extern void save_item(uint8_t item_id, uint8_t item_value);
extern uint8_t load_item(uint8_t item_id, uint8_t default_value);
