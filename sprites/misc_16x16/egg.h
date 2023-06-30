//AUTOGENERATED FILE FROM png2asset
#ifndef METASPRITE_egg_H
#define METASPRITE_egg_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define egg_TILE_ORIGIN 0
#define egg_TILE_W 8
#define egg_TILE_H 8
#define egg_WIDTH 16
#define egg_HEIGHT 16
#define egg_TILE_COUNT 4
#define egg_PALETTE_COUNT 1
#define egg_COLORS_PER_PALETTE 4
#define egg_TOTAL_COLORS 4
#define egg_PIVOT_X 8
#define egg_PIVOT_Y 8
#define egg_PIVOT_W 16
#define egg_PIVOT_H 16

BANKREF_EXTERN(egg)

extern const palette_color_t egg_palettes[4];
extern const uint8_t egg_tiles[64];

extern const metasprite_t* const egg_metasprites[2];

#endif