#include "png_process.h"

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


