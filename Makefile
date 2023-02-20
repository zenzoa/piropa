GBDK_HOME = /usr/share/gbdk/
LCC = $(GBDK_HOME)bin/lcc

PROJECT_NAME = piropa
BINARY = $(PROJECT_NAME).gb
C_SOURCES := $(wildcard *.c)
C_SPRITES := $(wildcard sprites/*.c)

$(BINARY): $(C_SOURCES) $(C_SPRITES)
	$(LCC) -autobank -Wl-yt0x0f -o $@ $(C_SPRITES) $(C_SOURCES)

clean:
	rm -f *.o *.lst *.map *.gb *.ihx *.sym *.cdb *.adb *.asm

