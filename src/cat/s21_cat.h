#ifndef C3_SIMPLEBASHUTILS_0_S21_CAT_H
#define C3_SIMPLEBASHUTILS_0_S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct options {
  int b, e, n, s, t, v;
} opt;

void parser(int argc, char *argv[], opt *options);
void reader(char *argv[], opt *options);

#endif  // C3_SIMPLEBASHUTILS_0_S21_CAT_H
