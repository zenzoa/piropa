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
	end
end

# remove old files
if test $clean
	set_color $text_color; echo ">> cleaning out old build files..."; set_color normal
	for file in *.{gb,pocket,sav}
		rm $file
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
	aseprite -b sprites/misc_8x8.aseprite --save-as sprites/misc_8x8/{slice}.png
	aseprite -b sprites/misc_16x8.aseprite --save-as sprites/misc_16x8/{slice}.png

	aseprite -b --all-layers sprites/backgrounds.aseprite --save-as sprites/backgrounds/{layer}.png
	aseprite -b --all-layers sprites/bg_bits.aseprite --save-as sprites/backgrounds/{layer}.png

	set_color $text_color; echo ">> convert png files to gbdk assets..."; set_color normal

	set sprite_args -spr8x8 -px 0 -py 0 -b 255 -keep_palette_order

	for file in sprites/frogs/*
		png2asset $file $sprite_args -sw 32 -sh 24
	end

	for file in sprites/hand/*
		png2asset $file $sprite_args -sw 24 -sh 16
	end

	for file in sprites/misc_8x8/*
		png2asset $file $sprite_args -sw 8 -sh 8
	end

	for file in sprites/misc_16x8/*
		png2asset $file $sprite_args -sw 16 -sh 8
	end

	set bg_args -map -noflip -b 255 -keep_palette_order

	for file in sprites/backgrounds/*
		png2asset $file $bg_args
	end
end

# build roms
set compiler_args -autobank -msm83:gb -Wl-yt0x10 -Wl-ya1 -o
set compiler_sources sprites/*/*.c *.c

if test $compile_gameboy_rom
	set_color $text_color; echo ">> building game boy rom..."; set_color normal
	lcc $compiler_args $project_name.gb $compiler_sources
end

if test $compile_pocket_rom
	set_color $text_color; echo ">> building analogue pocket rom..."; set_color normal
	lcc $compiler_args $project_name.pocket $compiler_sources
end

set_color $text_color; echo ">> all done!"; set_color normal
