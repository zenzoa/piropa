#include <gbdk/metasprites.h>

#include "clock.h"
#include "hand.h"
#include "sprites/frog_baby.h"
#include "sprites/frog_child.h"
#include "sprites/frog_teen.h"
#include "sprites/frog_teen_tail.h"
#include "sprites/frog_teen_apple.h"
#include "sprites/frog_normal.h"
#include "sprites/frog_axolotl.h"
#include "sprites/frog_apple.h"
#include "sprites/frog_mushroom.h"
#include "sprites/frog_dragon.h"

extern void init_frog();
extern void update_frog();
extern void draw_frog(uint8_t *last_used_sprite);
extern void update_age();
extern void set_frog_evolution(uint8_t new_evolution);
extern void set_frog_state(uint8_t new_state);
extern void get_frog_position(uint8_t *x, uint8_t *y);
