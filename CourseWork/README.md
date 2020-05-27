Для запуска вам потребуются:

1. Компилятор gcc (при написании программы использовалась версия 7.5.0, установка: sudo apt install build-essential)
2. Библиотека libpng (установка: sudo apt-get install libpng-dev)
3. Используйте команду make для сборки программы

Использование:

./my_paint [options] <file>

Опции:

Информация о картинке:
-I/--info

Инверсия цвета в указанной области
-i/--inverse -s/--start <координаты левого верхнего угла прямоугольной области области [x1] [y1]> -e/--end <координаты правого нижнего угла прямоугольной области [x2] [y2]>

Преобразвание области изображения в чёрно-белый
-b/--blackwhite -s/--start <координаты левого верхнего угла прямоугольной области области [x1] [y1]> -e/--end <координаты правого нижнего угла прямоугольной области [x2] [y2]>

Обрезка изображения относительно точки:
-c/--cut [точка] -S/--size <новые размеры изображения [ширина] [высота]>

Увеличение изображения с заливкой фона относительно точки:
-E/--expand [точка] -S/--size <новые размеры изображения [ширина] [высота]> -C/--color [цвет заливки]

Возможные точки для обрезки/увеличения изображения:
tl - левый верхний угол
tr - правый верхний угол
br - правый нижний угол
bl - левый нижний угол
cn - центр

Возможные цвета для заливки при увеличении изображения:
black - чёрный
white - белый
red - красный
green - зелёный
blue - синий
yellow - жёлтый
purple - фиолетовый
turquoise - бирюзовый
