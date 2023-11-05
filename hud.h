BANKREF_EXTERN(hud_bank)

extern uint8_t medicine_is_held;
extern uint8_t soap_is_held;
extern uint8_t broom_is_held;
extern uint8_t moon_is_held;

extern void setup_hud_data(void) NONBANKED;
extern void setup_hud(void);
extern void draw_hud(void);

extern void drop_all(uint8_t except);

extern uint8_t is_hand_over_medicine(void);
extern uint8_t hold_medicine(void);

extern uint8_t is_hand_over_soap(void);
extern uint8_t hold_soap(void);

extern uint8_t is_hand_over_broom(void);
extern uint8_t hold_broom(void);

extern uint8_t is_hand_over_moon(void);
extern uint8_t hold_moon(void);
