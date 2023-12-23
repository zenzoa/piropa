#define NO_MUSIC 0
#define DAY_MUSIC 1
#define NIGHT_MUSIC 2
#define DEATH_MUSIC 3

#define SFX_BEEP 0
#define SFX_TAP 1
#define SFX_DROP 2
#define SFX_PET 3
#define SFX_WASH 4
#define SFX_MEDS 5
#define SFX_EAT 6
#define SFX_HAPPY 7
#define SFX_SAD 8
#define SFX_MEEP1 9
#define SFX_MEEP2 10
#define SFX_MEEP3 11
#define SFX_EVOLVE 12
#define SFX_DIE 13
#define SFX_CHOMP 14
#define SFX_SWEEP 15

extern uint8_t current_music;

extern void update_audio(void);
extern void play_music(uint8_t new_music);
extern void play_sfx(uint8_t i);
