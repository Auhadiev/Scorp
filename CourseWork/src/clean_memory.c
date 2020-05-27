#include "../h_files/clean_memory.h"

void cleanMemory(Png *image){
    for (int i = 0; i < image->height; i++)
        free(image->row_pointers[i]);
    free(image->row_pointers);
}
