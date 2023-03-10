//AUTOGENERATED FILE FROM png2asset
#ifndef METASPRITE_hand_H
#define METASPRITE_hand_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define hand_TILE_ORIGIN 0
#define hand_TILE_W 8
#define hand_TILE_H 8
#define hand_WIDTH 16
#define hand_HEIGHT 16
#define hand_TILE_COUNT 4
#define hand_PALETTE_COUNT 1
#define hand_COLORS_PER_PALETTE 4
#define hand_TOTAL_COLORS 4
#define hand_PIVOT_X 8
#define hand_PIVOT_Y 8
#define hand_PIVOT_W 16
#define hand_PIVOT_H 16

BANKREF_EXTERN(hand)

extern const palette_color_t hand_palettes[4];
extern const uint8_t hand_tiles[64];

extern const metasprite_t* const hand_metasprites[1];

#endif
