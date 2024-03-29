# piropa build script

set project_name "piropa"

set text_color yellow

# get args
for option in $argv
	switch $option
	case -clean
		set clean true
	case -sprites
		set sprites true
	case -gameboy
		set compile_gameboy_rom true
	case -pocket
		set compile_pocket_rom true
	case -sfx
		python3 hammer2cbt.py --fxammo 15 --fxnamelist sfx_filenames.txt sfx.sav 0 ./sfx/
	end
end

# remove old files
if test $clean
	set_color $text_color; echo ">> cleaning out old build files..."; set_color normal
	for file in *.{gb,pocket,sav,rtc,map,noi,cdb}
		if not file sfx.sav
			rm $file
		end
	end
	for file in sprites/*/*.{c,h,png}
		rm $file
	end
end

# convert sprites
if test $sprites
	set_color $text_color; echo ">> exporting aseprite slices as png files..."; set_color normal

	aseprite -b sprites/frogs.aseprite --save-as sprites/frogs/{slice}.png
	aseprite -b sprites/hand.aseprite --save-as sprites/hand/{slice}.png
	aseprite -b sprites/emotes.aseprite --save-as sprites/emotes/{slice}.png
	aseprite -b sprites/death.aseprite --save-as sprites/death/{slice}.png
	aseprite -b sprites/bugs_small.aseprite --save-as sprites/bugs_small/{slice}.png
	aseprite -b sprites/bugs_big.aseprite --save-as sprites/bugs_big/{slice}.png
	aseprite -b sprites/arrows.aseprite --save-as sprites/arrows/{slice}.png

	aseprite -b sprites/bg_bits.aseprite --save-as sprites/backgrounds/{slice}.png
	aseprite -b --all-layers sprites/backgrounds.aseprite --save-as sprites/backgrounds/{layer}.png

	set_color $text_color; echo ">> convert png files to gbdk assets..."; set_color normal

	set sprite_map_args -map -noflip -keep_duplicate_tiles -keep_palette_order -no_palettes -b 255
	set sprite_args -spr8x8 -px 0 -py 0 -keep_palette_order -no_palettes -b 255

	for file in sprites/frogs/*
		png2asset $file $sprite_map_args
	end

	for file in sprites/hand/*
		png2asset $file $sprite_map_args
	end

	for file in sprites/emotes/*
		png2asset $file $sprite_map_args
	end

	for file in sprites/death/*
		png2asset $file $sprite_args -sw 16 -sh 16
	end

	for file in sprites/bugs_small/*
		png2asset $file $sprite_args -sw 8 -sh 8
	end

	for file in sprites/bugs_big/*
		png2asset $file $sprite_args -sw 16 -sh 8
	end

	for file in sprites/arrows/*
		png2asset $file $sprite_args -sw 8 -sh 8
	end

	for file in sprites/backgrounds/*
		png2asset $file -map -noflip -keep_palette_order -b 255
	end
end

# build roms
set compiler_args -autobank -Wl-yt0x1B -Wl-ya1 -Wm-yc -Ihugedriver/include -Wl-lhugedriver/gbdk/hUGEDriver.lib -o
set compiler_sources sprites/*/*.c music/*.c sfx/*.c *.c

if test $compile_gameboy_rom
	set_color $text_color; echo ">> building game boy rom..."; set_color normal
	lcc -msm83:gb $compiler_args $project_name.gb $compiler_sources
end

if test $compile_pocket_rom
	set_color $text_color; echo ">> building analogue pocket rom..."; set_color normal
	lcc -msm83:ap $compiler_args $project_name.pocket $compiler_sources
end

set_color $text_color; echo ">> all done!"; set_color normal
