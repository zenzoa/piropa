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

extern uint8_t hand_state;
extern uint8_t hand_x;
extern uint8_t hand_y;
extern uint16_t hand_x_frac;
extern uint16_t hand_y_frac;
extern uint8_t sweep_count;

extern void move_hand_by_frac(int16_t dx_frac, int16_t dy_frac);
extern uint8_t is_hand_empty(void);
extern uint8_t is_hand_over_frog(void);
extern void set_hand_state(uint8_t new_state);
extern void setup_hand(void);
extern void draw_hand(uint8_t *last_sprite);
extern void update_hand(void);
