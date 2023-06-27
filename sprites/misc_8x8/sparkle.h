//AUTOGENERATED FILE FROM png2asset
#ifndef METASPRITE_sparkle_H
#define METASPRITE_sparkle_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define sparkle_TILE_ORIGIN 0
#define sparkle_TILE_W 8
#define sparkle_TILE_H 8
#define sparkle_WIDTH 8
#define sparkle_HEIGHT 8
#define sparkle_TILE_COUNT 4
#define sparkle_PALETTE_COUNT 1
#define sparkle_COLORS_PER_PALETTE 4
#define sparkle_TOTAL_COLORS 4
#define sparkle_PIVOT_X 4
#define sparkle_PIVOT_Y 4
#define sparkle_PIVOT_W 8
#define sparkle_PIVOT_H 8

BANKREF_EXTERN(sparkle)

extern const palette_color_t sparkle_palettes[4];
extern const uint8_t sparkle_tiles[64];

extern const metasprite_t* const sparkle_metasprites[4];

#endif
