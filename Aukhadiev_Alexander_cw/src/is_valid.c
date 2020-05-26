#include "../h_files/is_valid.h"

int isValid(char* color){
	if(!strcmp(color, "black") || !strcmp(color, "white") || !strcmp(color, "red") || !strcmp(color, "green") || !strcmp(color, "blue") || !strcmp(color, "yellow") || !strcmp(color, "purple") || !strcmp(color, "turquoise"))
		return 1;
	else
		return 0;
}



