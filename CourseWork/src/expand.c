#include "png_process.h"

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

