#ifndef FUNC_IN_MAIN_H
#define FUNC_IN_MAIN_H

#include "structures.h"
#include "png_process.h"

int isValid(char* color);

void cleanMemory(Png *image);

int isDigit(char *arg);

void printHelp();

void printInfo(Png *image);

int read_png_file(char *file_name, Png *image);

void write_png_file(char *file_name, Png *image);

#endif
