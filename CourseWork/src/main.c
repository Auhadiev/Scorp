#include "func_in_main.h"
#include "png_process.h"

int main(int argc, char **argv) {
    if (argc == 1){
        printHelp();
        return 0;
    }
    char color = 0;
    opterr = 0;
    int ch = 0;
    int opt = 0;
    int longIndex = 0;

    int flago = 0;
    char *output_file = (char*)malloc(sizeof(argv[argc-1])+1);
    strcpy(output_file, argv[argc-1]);
    for(int i = 0; i<argc; i++){
        if(!strcmp("-o", argv[i]) || !strcmp("--output", argv[i]))
            flago = 2;
    }

    globalArguments *argument = (globalArguments*)malloc(sizeof(globalArguments));
    argument->flagi = 0;
    argument->start[0] = 0;
    argument->start[1] = 0;
    argument->end[0] = 0;
    argument->end[1] = 0;
    argument->flagbw = 0;
    argument->flagc = 0;
    argument->flage = 0;
    argument->flagI = 0;
    argument->flags = 0;


    while((opt = getopt_long(argc, argv, optString, longOpts, &longIndex)) != -1){
        switch(opt){
            case 'i':
                if(argc - flago!= 9) {
                    printHelp();
                    return 0;
                }
                if(argc - optind == 0){
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                }else if(strcmp(argv[optind], "--start") && strcmp(argv[optind], "-s")){
                    printf("Use: -s/--start <x1> <y1> -e/--end <x2> <y2>\n");
                    free(argument);
                    return 0;
                }
                argument->flagi = 1;
                break;

            case 'b':
                if(argc - flago != 9) {
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                if(argc - optind == 0){
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                    }
                }else if(strcmp(argv[optind], "--start") && strcmp(argv[optind], "-s")){
                    printf("Use: -s/--start <x1> <y1> -e/--end <x2> <y2>\n");
                    free(argument);
                    free(output_file);
                    return 0;
                }
                argument->flagbw = 1;
                break;
            case 's':
                if(argument->flagbw != 1 && argument->flagi != 1){
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                }
                if(argc - optind == 0) {
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                }
                if(!isDigit(optarg)) {
                    printf("Неверный первый аргумент опции -s/--start (введено не целое число\n");
                    free(argument);
                    free(output_file);
                    return 0;
                }else if(!isDigit(argv[optind])){
                    printf("Неверный второй аргумент опции -s/--start (введено не целое число\n");
                    free(argument);
                    free(output_file);
                    return 0;
                }
                argument->flags = 1;
                argument->start[0] = atoi(optarg);
                argument->start[1] = atoi(argv[optind]);
                break;
            case 'e':
                if(argument->flags != 1){
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                }
                if(argc - optind == 0) {
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                }
                if(!isDigit(optarg)) {
                    printf("Неверный первый аргумент опции -e/--end (введено не целое число\n");
                    free(argument);
                    free(output_file);
                    return 0;
                }else if(!isDigit(argv[optind])){
                    printf("Неверный второй аргумент опции -e/--end (введено не целое число\n");
                    free(argument);
                    free(output_file);
                    return 0;
                }
                argument->end[0] = atoi(optarg);
                argument->end[1] = atoi(argv[optind]);
                break;
            case 'c':
                if(argc - flago!=7) {
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                }
                if(argc - optind == 0){
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                }
                if(strcmp(argv[optind], "--size") && strcmp(argv[optind], "-S")){
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                }
                if(!strcmp(optarg, "cn"))
                    ch = 1;
                else if(!strcmp(optarg, "tl"))
                    ch = 2;
                else if(!strcmp(optarg, "tr"))
                    ch = 3;
                else if(!strcmp(optarg, "br"))
                    ch = 4;
                else if(!strcmp(optarg, "bl"))
                    ch = 5;
                else{
                    printf("Некорректно выбрана точка. Выберете одну из пяти:\n"
                           "cn - центр\ntl - верхний левый угол\ntr - правый верхний угол\n"
                           "bl - левый нижний угол\nbr - правый нижний угол\n");
                    free(argument);
                    free(output_file);
                    return 0;
                }
                argument->flagc = 1;
                break;
            case 'E':
                if(argc - flago != 9){
		            printHelp();
		            free(argument);
                    free(output_file);
                    return 0;
                }
                if(argc - optind == 0){
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                }

                if(strcmp(argv[optind], "--size") && strcmp(argv[optind], "-S")){
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                }
                if(!strcmp(optarg, "cn"))
                    ch = 1;
                else if(!strcmp(optarg, "tl"))
                    ch = 2;
                else if(!strcmp(optarg, "tr"))
                    ch = 3;
                else if(!strcmp(optarg, "br"))
                    ch = 4;
                else if(!strcmp(optarg, "bl"))
                    ch = 5;
                else{
                    printf("Некорректно выбрана точка. Выберете одну из пяти:\n"
                           "cn - центр\ntl - верхний левый угол\ntr - правый верхний угол\n"
                           "bl - левый нижний угол\nbr - правый нижний угол\n");
                    free(argument);
                    free(output_file);
                    return 0;
                }
                argument->flage = 1;
                break;
            case 'S':
                if(argument->flagc != 1 && argument->flage != 1){
                    free(output_file);
                    free(argument);
                    printHelp();
                    return 0;
                }
                if(argc - optind == 0) {
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                }
                if(!isDigit(optarg)) {
                    printf("Неверный первый аргумент опции -S/--size (введено не целое число)\n");
                    free(argument);
                    free(output_file);
                    return 0;
                }else if(!isDigit(argv[optind])){
                    printf("Неверный второй аргумент опции -s/--size (введено не целое число)\n");
                    free(argument);
                    free(output_file);
                    return 0;
                }
                argument->start[0] = atoi(optarg);
                argument->start[1] = atoi(argv[optind]);
                break;
            case 'C':
                if(argument->flage != 1){
                    printHelp();
                    free(argument);
                    free(output_file);
                    return 0;
                }
			    if(!isValid(optarg)){
				    printf("Извините, но введённый цвет не поддерживается программой\n");
                    free(argument);
                    free(output_file);
				    return 0;
			    }
                    if(!strcmp(optarg, "black"))
                        color = 'l';
                    else if(!strcmp(optarg, "turquoise"))
                        color = 'i';
                    else
                        color = optarg[0];
                    break;
            case 'I':
                if(argc != 3){
                    free(argument);
                    free(output_file);
                    printHelp();
                    return 0;
                }
		        argument->flagI = 1;
                break;
            case 'o':
                output_file = (char*)realloc(output_file, sizeof(optarg)+1);
                strcpy(output_file, optarg);
                break;
            case '?':
                if(optopt == 's')
                    fprintf(stderr, "Option -s/--start needs two arguments\n");
                else if(optopt == 'e')
                    fprintf(stderr, "Option -e/--end needs two arguments\n");
                else if(optopt == 'S')
                    fprintf(stderr, "Option -S/--size needs two argument\n");
                else if(optopt == 'C')
                    fprintf(stderr, "Option -C/--color needs argument\n");
                else if(optopt == 'o')
                    fprintf(stderr, "Option -o/--output needs argument\n");
		        else
                    printHelp();
                free(argument);
                free(output_file);
                return 0;
            case 'h':
                printHelp();
                free(argument);
                free(output_file);
                return 0;
            default:
                free(argument);
                free(output_file);
                return 0;
        }

    }

    Png image;
    if(read_png_file(argv[argc-1], &image) == 1)
        return 0;
 
    if(argument->flagbw == 1)
        blackWhite(&image, argument->start[0], argument->start[1], argument->end[0], argument->end[1]);
    else if(argument->flagi == 1)
        inversion(&image, argument->start[0], argument->start[1], argument->end[0], argument->end[1]);
    else if(argument->flagc == 1) {
        if(argument->start[0] > image.width || argument->start[1] > image.height) {
            printf("Чтобы увеличить размеры картинки, используйте опцию -E/--expend <dot> -S/--size <new_width> <new_height> --color <color>\n");
            cleanMemory(&image);
            free(argument);
            free(output_file);
            return 0;
        }
        cut(&image, ch, argument->start[0], argument->start[1]);
    }
    else if(argument->flage == 1) {
        if (argument->start[0] < image.width || argument->start[1] < image.height) {
            printf("Чтобы уменьшить размеры картинки, используйте опцию -c/--cut <dot> -S/--size <new_width> <new_height>\n");
            cleanMemory(&image);
            free(argument);
            free(output_file);
            return 0;
        }
        expand(&image, ch, argument->start[0], argument->start[1], color);
    }
    else if(argument->flagI == 1){
        printInfo(&image);
        free(argument);
        free(output_file);
        cleanMemory(&image);
        return 0;
    }
    write_png_file(output_file, &image);
    free(argument);
    free(output_file);
    cleanMemory(&image);
    return 0;
}
