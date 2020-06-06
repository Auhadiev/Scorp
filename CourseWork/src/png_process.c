#include "png_process.h"

void blackWhite(Png *image, int x1, int y1, int x2, int y2) {
    int ch = 0;
    if(x2 > image->width) {
        ch++;
        x2 = image->width;
    }
    if(y2 > image->height) {
        ch++;
        y2 = image->height;
    }
    if(ch)
        printf("You have gone beyond the picture!\n");

    if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGB){
        fprintf(stderr, "input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA\n");
        return;
    }

    if (png_get_color_type(image->png_ptr, image->info_ptr) != PNG_COLOR_TYPE_RGBA){
        fprintf(stderr, "color_type of input file must be PNG_COLOR_TYPE_RGBA\n");
        return;
    }

    int mid = 0;
    for (int i = y1; i < y2; i++) {
        png_byte *row = image->row_pointers[i];
        for (int j = x1;j < x2; j++) {
                png_byte *ptr = &(row[j * 4]);
                mid = (ptr[0]+ptr[1]+ptr[2])/3;
                ptr[0] = mid;
                ptr[1] = mid;
                ptr[2] = mid;
        }
    }
}

void cut(Png *image, int check, int x, int y){
    int dx = 0, dy = 0;
    switch(check){
        case 1: //Центр
            dx = (image->width - x)/2;
            dy = (image->height - y)/2;
            break;
        case 2: //tl
            break;
        case 3: //tr
            dx = image->width - x;
            break;
        case 4: //br
            dx = image->width - x;
            dy = image->height - y;
            break;
        case 5: //bl
            dy = image->height - y;
            break;
    }
    png_bytep* buffer = (png_bytep*)malloc(sizeof(png_bytep) * image->height);
    for(int i = 0; i<image->height; i++)
        buffer[i] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));

    for (int i = 0; i < image->height; i++)
        for (int j = 0; j < image->width; j++) {
            buffer[i][j*4] = image->row_pointers[i][j * 4];
            buffer[i][j*4+1] = image->row_pointers[i][j * 4 + 1];
            buffer[i][j*4+2] = image->row_pointers[i][j * 4 + 2];
            buffer[i][j*4+3] = image->row_pointers[i][j * 4 + 3];
        }
    
    for(int i = 0; i<y; i++)
        image->row_pointers[i] = (png_byte*)realloc(image->row_pointers[i], x*4);
    image->row_pointers = (png_bytep*)realloc(image->row_pointers, sizeof(png_byte*)*y);

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            image->row_pointers[i][j*4] = buffer[i+dy][j * 4 + dx*4];
            image->row_pointers[i][j*4+1] = buffer[i+dy][j * 4 + 1 + dx*4];
            image->row_pointers[i][j*4+2] = buffer[i + dy][j * 4 + 2 +dx*4];
            image->row_pointers[i][j*4+3] = buffer[i + dy][j * 4 + 3 + dx*4];
        }
    }

    for(int i = 0; i<image->height; i++)
        free(buffer[i]);
    free(buffer);
    image->height = y;
    image->width = x;
}

void expand(Png *image, int check, int x, int y, char color){
    int dx = 0, dy = 0, r = 0, g = 0, b = 0;

    switch(color){
        case 'r':
            r = 255;
            break;
        case 'g':
            g = 255;
            break;
        case 'b':
            b = 255;
            break;
        case 'y':
            r = 255;
            g = 255;
            break;
        case 'p':
            r = 255;
            b = 255;
            break;
        case 'i':
            g = 255;
            b = 255;
	    break;
        case 'w':
            r = 255;
            g = 255;
            b = 255;
            break;
        case 'l':
            break;
    }

    switch(check){
        case 1: //Центр
            dx = (x - image->width)/2;
            dy = (y - image->height)/2;
            break;
        case 2: //tl
            break;
        case 3: //tr
            dx = x - image->width;
            break;
        case 4: //br
            dx = x - image->width;
            dy = y - image->height;
            break;
        case 5: //bl
            dy = y - image->height;
            break;
    }
    png_bytep* buffer = (png_bytep*)malloc(sizeof(png_bytep) * image->height);
    for(int i = 0; i<image->height; i++)
        buffer[i] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));

    for (int i = 0; i < image->height; i++)
        for (int j = 0; j < image->width; j++) {
            buffer[i][j*4] = image->row_pointers[i][j * 4];
            buffer[i][j*4+1] = image->row_pointers[i][j * 4 + 1];
            buffer[i][j*4+2] = image->row_pointers[i][j * 4 + 2];
            buffer[i][j*4+3] = image->row_pointers[i][j * 4 + 3];
        }

    image->row_pointers = (png_bytep*)realloc(image->row_pointers, sizeof(png_byte*)*y);
    for(int i = 0; i<y; i++)
        image->row_pointers[i] = (png_byte*)realloc(image->row_pointers[i], x*4);

    for(int i = 0; i<y; i++)
        for(int j = 0; j<x; j++){
            image->row_pointers[i][j*4] = r;
            image->row_pointers[i][j*4+1] = g;
            image->row_pointers[i][j*4+2] = b;
            image->row_pointers[i][j*4+3] = 255;
        }

    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            image->row_pointers[i+dy][j*4 + dx*4] = buffer[i][j * 4];
            image->row_pointers[i+dy][j*4+1 +dx*4] = buffer[i][j * 4 + 1];
            image->row_pointers[i+dy][j*4+2 + dx*4] = buffer[i][j * 4 + 2];
            image->row_pointers[i+dy][j*4+3 +dx*4] = buffer[i][j * 4 + 3];
        }
    }

    for(int i = 0; i<image->height; i++)
        free(buffer[i]);
    free(buffer);
    image->height = y;
    image->width = x;
}

void inversion(Png *image, int x1, int y1, int x2, int y2) {
    int ch = 0;
    if(x2 > image->width) {
        ch++;
        x2 = image->width;
    }
    if(y2 > image->height) {
        ch++;
        y2 = image->height;
    }
    if(ch)
        printf("You have gone beyond the picture!\n");

    if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGB){
        fprintf(stderr, "input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA\n");
        return;
    }

    if (png_get_color_type(image->png_ptr, image->info_ptr) != PNG_COLOR_TYPE_RGBA){
        fprintf(stderr, "color_type of input file must be PNG_COLOR_TYPE_RGBA\n");
        return;
    }

    for (int i = y1; i < y2; i++) {
        png_byte *row = image->row_pointers[i];
        for (int j = x1;j < x2; j++) {
            png_byte *ptr = &(row[j * 4]);
            ptr[0] = ~ptr[0];
            ptr[1] = ~ptr[1];
            ptr[2] = ~ptr[2];
        }
    }
}

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
void write_png_file(char *file_name, Png *image) {

    FILE *fp = fopen(file_name, "wb");
    if (!fp){
        fprintf(stderr, "File cannot be opened\n");
        return;
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        printf("png_create_write_struct failed\n");
        return;
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf("png_create_info_struct failed\n");
        return;
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("error during init_io\n");
	return;
    }

    png_init_io(image->png_ptr, fp);


    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("error during writing header\n");
        return;
    }

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);


    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("error during writing bytes\n");
        return;
    }

    png_write_image(image->png_ptr, image->row_pointers);


    if (setjmp(png_jmpbuf(image->png_ptr))){
        fprintf(stderr, "error during end of write\n");
        return;
    }

    png_write_end(image->png_ptr, NULL);


    fclose(fp);
}







