# justfile
target := file_name(justfile_directory())
jobs := `nproc`
emulator := "mgba"

run: build
    {{emulator}} -l 14 {{target}}.gba --scale 4 &

build:
    make -f Makefile -j{{jobs}}


clean:
    make -f Makefile clean

compiledb:
	make -f Makefile clean 
	mkdir -p build
	bear --output build/compile_commands.json -- make -f Makefile -j{{jobs}}

fmt:
	find source \
		\( -path "*/gen/*" -o -path "*/external/*" \) -prune \
		-o \
		\( -name "*.c" -o -name "*.h" -o -name "*.cpp" -o -name "*.hpp" \) \
		-exec clang-format -style=file -i {} +

fclean:
	rm *.sav
	rm *.gba
	rm *.elf

gen_basemap:
	tiled --export-map gba assets/maps/base_map.tmx source/maps/basemap.c

gen_tilespng:
	aseprite -b assets/artworks/roguetiles.aseprite --save-as graphics/basetiles.png
