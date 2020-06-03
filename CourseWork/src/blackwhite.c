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



