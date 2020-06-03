#include "main.h"

void printInfo(Png *image){
    printf("Ширина: %d\n", image->width);
    printf("Высота: %d\n", image->height);
    printf("Глубина цвета: %d\n", image-> bit_depth);
    if(image->color_type == PNG_COLOR_TYPE_RGB)
        printf(" Тип цвета: RGB\n");
    else if(image->color_type == PNG_COLOR_TYPE_RGBA)
        printf("Тип цвета: RGBA\n");
}




