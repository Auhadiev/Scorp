#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define PNG_DEBUG 3
#include <png.h>

typedef struct GlobalArguments_t{
    int start[2];
    int end[2];
    int flagi;
    int flagbw;
    int flagc;
    int flage;
    int flagI;
    int flags;
}globalArguments;

static const char *optString = "C:is:e:bIhc:E:S:o:?";

static const struct option longOpts[]= {
    {"inverse", no_argument, NULL, 'i'},
    {"start", required_argument, NULL, 's'},
    {"end", required_argument, NULL, 'e'},
    {"blackWhite", no_argument, NULL, 'b'},
    {"info", no_argument, NULL, 'I'},
    {"help", no_argument, NULL, 'h'},
    {"cut", required_argument, NULL, 'c'},
    {"size", required_argument, NULL, 'S'},
    {"expand", required_argument, NULL, 'E'},
    {"color", required_argument, NULL, 'C'},
    {"output", required_argument, NULL, 'o'},
	{NULL, no_argument, NULL, '0'}
};

typedef struct PNG_t{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
}Png;

#endif
