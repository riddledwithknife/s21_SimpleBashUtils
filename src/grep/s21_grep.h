#ifndef C3_SIMPLEBASHUTILS_0_S21_GREP_H
#define C3_SIMPLEBASHUTILS_0_S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buffer 4096

typedef struct options {
    int e, i, v, c, l, n, h, s, f, o;
} opt;

void parser(int argc, char *argv[], opt *options);
void reader(opt *options, char *filename, char *pattern, int files_count);

#endif //C3_SIMPLEBASHUTILS_0_S21_GREP_H
