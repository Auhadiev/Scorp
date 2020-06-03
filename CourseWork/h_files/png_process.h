#ifndef PNG_PROCESS_H
#define PNG_PROCESS_H

#include "structures.h"

void blackWhite(Png *image, int x1, int y1, int x2, int y2);

void cut(Png *image, int check, int x, int y);

void expand(Png *image, int check, int x, int y, char color);

void inversion(Png *image, int x1, int y1, int x2, int y2);

int read_png_file(char *file_name, Png *image);

void write_png_file(char *file_name, Png *image);

#endif
