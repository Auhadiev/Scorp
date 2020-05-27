p = ./src/

all: my_paint

my_paint: $(p)main.c $(p)write_png.c $(p)read_png.c $(p)inversion.c $(p)is_digit.c $(p)is_valid.c $(p)blackwhite.c $(p)cut.c $(p)expand.c
	gcc $(p)main.c $(p)clean_memory.c $(p)print_help.c $(p)print_info.c $(p)write_png.c $(p)read_png.c $(p)inversion.c $(p)is_digit.c $(p)is_valid.c $(p)blackwhite.c $(p)cut.c $(p)expand.c -lpng -o my_paint

clean:
	rm -rf my_paint
