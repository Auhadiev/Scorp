#include "main.h"

int isDigit(char *arg){
    for(int i = 0; i<strlen(arg); i++)
        if(!isdigit(arg[i]))
            return 0;
    return 1;
}




