GBDK_HOME = /usr/share/gbdk/
LCC = $(GBDK_HOME)bin/lcc
PNG2ASSET = $(GBDK_HOME)bin/png2asset

PROJECT_NAME = piropa
BINARY = $(PROJECT_NAME).gb
C_SOURCES := $(wildcard *.c)
C_SPRITES := $(wildcard sprites/*/*.c)

$(BINARY): $(C_SOURCES) $(C_SPRITES)
	$(LCC) -autobank -Wl-yt0x0f -o $@ $(C_SPRITES) $(C_SOURCES)

all_sprites: $(patsubst sprites/%.png,sprites/%.c,$(shell find sprites/*/ -name '*.png'))

sprites/background/%.c: sprites/background/%.png
	$(PNG2ASSET) $< -map -noflip

sprites/hand/%.c: sprites/hand/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 24 -sh 16 -b 255

sprites/frog/%.c: sprites/frog/%.png
	$(PNG2ASSET) $< -spr8x8 -sw 32 -sh 32 -b 255

clean_sprites:
	rm -f sprites/*/*.c sprites/*/*.h

clean:
	rm -f *.o *.lst *.map *.gb *.ihx *.sym *.cdb *.adb *.asm
