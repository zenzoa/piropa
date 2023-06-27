GBDK_HOME = /usr/share/gbdk/
LCC = $(GBDK_HOME)bin/lcc
PNG2ASSET = $(GBDK_HOME)bin/png2asset

PROJECT_NAME = piropa
GAMEBOY_ROM = $(PROJECT_NAME).gb
C_SOURCES := $(wildcard *.c)
C_SPRITES := $(wildcard sprites/*/*.c)

$(GAMEBOY_ROM): $(C_SOURCES) $(C_SPRITES)
	$(LCC) -autobank -msm83:gb -Wl-yt0x10 -Wl-ya1 -o $@ $(C_SPRITES) $(C_SOURCES)

all_sprites: $(patsubst sprites/%.png,sprites/%.c,$(shell find sprites/*/ -name '*.png'))

sprites/background/%.c: sprites/background/%.png
	$(PNG2ASSET) $< -map -noflip -keep_palette_order -b 255

sprites/hand/%.c: sprites/hand/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 24 -sh 16 -b 255

sprites/frog_angel/%.c: sprites/frog_angel/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 24 -sh 16 -b 255

sprites/frog_baby/%.c: sprites/frog_baby/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 32 -sh 32 -b 255
sprites/frog_child/%.c: sprites/frog_child/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 32 -sh 32 -b 255
sprites/frog_teen/%.c: sprites/frog_teen/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 32 -sh 32 -b 255
sprites/frog_teen_tail/%.c: sprites/frog_teen_tail/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 32 -sh 32 -b 255
sprites/frog_teen_apple/%.c: sprites/frog_teen_apple/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 32 -sh 32 -b 255
sprites/frog_adult/%.c: sprites/frog_adult/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 32 -sh 32 -b 255
sprites/frog_axo/%.c: sprites/frog_axo/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 32 -sh 32 -b 255
sprites/frog_apple/%.c: sprites/frog_apple/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 32 -sh 32 -b 255
sprites/frog_mush/%.c: sprites/frog_mush/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 32 -sh 32 -b 255
sprites/frog_dino/%.c: sprites/frog_dino/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 32 -sh 32 -b 255

sprites/misc_8x8/%.c: sprites/misc_8x8/%.png
	$(PNG2ASSET) $< -spr8x8 -keep_palette_order -sw 8 -sh 8 -b 255

sprites/misc_16x16/%.c: sprites/misc_16x16/%.png
	$(PNG2ASSET) $< -spr8x8 -keep_palette_order -sw 16 -sh 16 -b 255

clean_sprites:
	rm -f sprites/*/*.c sprites/*/*.h

clean:
	rm -f *.o *.lst *.map *.gb *.ihx *.sym *.cdb *.adb *.asm

all: clean clean_sprites all_sprites $(GAMEBOY_ROM)
