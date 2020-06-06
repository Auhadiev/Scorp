#include "func_in_main.h"

int isValid(char* color){
	char* colors[] = {"black", "white", "red", "green", "blue", "yellow", "purple", "turquoise"};
	for(int i = 0; i<8; i++){
		if(!strcmp(color, colors[i]))
			return 1;
	}
	return 0;
}

int isDigit(char *arg){
    for(int i = 0; i<strlen(arg); i++)
        if(!isdigit(arg[i]))
            return 0;
    return 1;
}

void cleanMemory(Png *image){
    for (int i = 0; i < image->height; i++)
        free(image->row_pointers[i]);
    free(image->row_pointers);
}

void printHelp(){
	printf("Используйте: ./my_paint [options] <file>\n\n"
		"Опции:\n\n"
        "Информация о картинке:\n-I/--info\n\n"
		"Инверсия цвета в указанной области\n"
		"-i/--inverse -s/--start <координаты левого верхнего угла прямоугольной области области [x1] [y1]> -e/--end <координаты правого нижнего угла прямоугольной области [x2] [y2]>\n\n"
		"Преобразвание области изображения в чёрно-белый\n"
		"-b/--blackwhite -s/--start <координаты левого верхнего угла прямоугольной области области [x1] [y1]> -e/--end <координаты правого нижнего угла прямоугольной области [x2] [y2]>\n\n"
		"Обрезка изображения относительно точки:\n"
		"-c/--cut [точка] -S/--size <новые размеры изображения [ширина] [высота]>\n\n"
		"Увеличение изображения с заливкой фона относительно точки:\n"
		"-E/--expand [точка] -S/--size <новые размеры изображения [ширина] [высота]> -C/--color [цвет заливки]\n\n"
		"Возможные точки для обрезки/увеличения изображения:\n"
		"tl - левый верхний угол\n"
		"tr - правый верхний угол\n"
		"br - правый нижний угол\n"
		"bl - левый нижний угол\n"
		"cn - центр\n\n"
		"Возможные цвета для заливки при увеличении изображения:\n"
		"black - чёрный\n"
		"white - белый\n"
		"red - красный\n"
		"green - зелёный\n"
		"blue - синий\n"
		"yellow - жёлтый\n"
		"purple - фиолетовый\n"
		"turquoise - бирюзовый\n\n"
		"Запись изображения в другой файл:\n"
		"-o/--output <file_name>\n");
}

void printInfo(Png *image){
    printf("Ширина: %d\n", image->width);
    printf("Высота: %d\n", image->height);
    printf("Глубина цвета: %d\n", image-> bit_depth);
    if(image->color_type == PNG_COLOR_TYPE_RGB)
        printf(" Тип цвета: RGB\n");
    else if(image->color_type == PNG_COLOR_TYPE_RGBA)
        printf("Тип цвета: RGBA\n");
}



