#include "png_process.h"

int read_png_file(char *file_name, Png *image){
    char header[8];

    FILE *fp = fopen(file_name, "rb");
    if (!fp){
        fprintf(stderr, "File cannot be opened \n");
        return 1;
    }

    if(fread(header, 1, 8, fp) != 8)
	    return 1;
    if(png_sig_cmp(header, 0, 8)){
        fprintf(stderr, "file is not PNG\n");
        return 1;
    }

    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if(!image->png_ptr){
        fprintf(stderr, "png_create_read_struct failed\n");
        return 1;
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if(!image->info_ptr){
        fprintf(stderr, "png_create_info_struct failed\n");
        return 1;
    }

    if(setjmp(png_jmpbuf(image->png_ptr))){
	fclose(fp);
	printf("error during png_init_io\n");
        return 1;
    }

    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);

    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);

    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);
	if(image->bit_depth == 16)
		png_set_strip_16(image->png_ptr); //Сужение глубины до 8
    
    if(setjmp(png_jmpbuf(image->png_ptr))){
        fprintf(stderr, "error during read_image\n");
        return 1;
    }

    image->row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * image->height);
    for(int i = 0; i<image->height; i++)
        image->row_pointers[i] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));

    png_read_image(image->png_ptr, image->row_pointers);
    fclose(fp);
	return 0;
}

