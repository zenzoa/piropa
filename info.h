BANKREF_EXTERN(info_bank)

extern uint8_t info_love;
extern uint8_t info_stomach;
extern uint8_t info_energy;
extern uint8_t info_age;
extern uint8_t info_weight;

extern void setup_info_data(void) NONBANKED;
extern void setup_info(void);
extern void handle_info_input(uint8_t button_pressed);
