BANKREF_EXTERN(frog_bank)

extern uint16_t age;
extern uint8_t stage;
extern uint8_t personality;

extern uint8_t fullness;
extern uint16_t last_fullness_decrease;

extern uint8_t happiness;
extern uint16_t last_happiness_decrease;

extern uint8_t cleanliness;
extern uint16_t last_cleanliness_decrease;

extern uint8_t care_mistakes;
extern uint16_t empty_fullness_time;
extern uint16_t empty_happiness_time;
extern uint16_t empty_cleanliness_time;

extern uint8_t sickness_counter;
extern uint16_t last_sickness_increase;

extern uint8_t friendship_points;
extern uint16_t last_friendship_increase;

extern uint8_t friendship_level;

extern uint8_t vegetarian;
extern uint8_t carnivore;

extern void update_stats();
extern void reset_frog();
extern void draw_frog(uint8_t *last_sprite);
