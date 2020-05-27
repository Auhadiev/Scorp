#include "../h_files/print_help.h"

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


