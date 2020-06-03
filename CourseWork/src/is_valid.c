#include "main.h"

int isValid(char* color){
	char* colors[] = {"black", "white", "red", "green", "blue", "yellow", "purple", "turquoise"};
	for(int i = 0; i<8; i++){
		if(!strcmp(color, colors[i]))
			return 1;
	}
	return 0;
}



