#ifndef MAIN_H
#define MAIN_H

#include "structures.h"
#include "png_process.h"

void cleanMemory(Png *image);

int isDigit(char *arg);

int isValid(char* color);

void printHelp();

void printInfo(Png *image);

int read_png_file(char *file_name, Png *image);

void write_png_file(char *file_name, Png *image);

#endif
