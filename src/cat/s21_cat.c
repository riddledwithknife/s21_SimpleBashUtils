#include "s21_cat.h"

int main(int argc, char *argv[]) {
  opt options = {0};
  parser(argc, argv, &options);
  reader(argv, &options);
}

void parser(int argc, char *argv[], opt *options) {
  int o;
  static struct option long_option[] = {{"number", 0, 0, 'n'},
                                        {"number-nonblank", 0, 0, 'b'},
                                        {"squeeze-blank", 0, 0, 's'},
                                        {0, 0, 0, 0}};

  while ((o = getopt_long(argc, argv, "+benstvTE", long_option, NULL)) != -1) {
    switch (o) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      default:
        printf("Usage: cat [-b, -e, -n, -s, -t, -v, -T, -E] [File]\n");
        break;
    }
    if (options->b && options->n) options->n = 0;
  }
}

void reader(char *argv[], opt *options) {
  FILE *f = fopen(argv[optind], "r");
  if (f) {
    int str_count = 1;
    int empty_str_count = 0;
    int last = '\n';
    while (!feof(f)) {
      int c = fgetc(f);
      if (c == EOF) break;
      if (options->s && c == '\n' && last == '\n') {
        empty_str_count++;
        if (empty_str_count > 1) {
          continue;
        }
      } else {
        empty_str_count = 0;
      }
      if (last == '\n' && ((options->b && c != '\n') || options->n))
        printf("%6d\t", str_count++);
      if (options->t && c == '\t') {
        printf("^");
        c = 'I';
      }
      if (options->e && c == '\n') printf("$");
      if (options->v) {
        if ((c >= 0 && c < 9) || (c > 10 && c < 32) || (c > 126 && c <= 160)) {
          printf("^");
          if (c > 126) {
            c -= 64;
          } else {
            c += 64;
          }
        }
      }
      printf("%c", c);
      last = c;
    }
    fclose(f);
  } else {
    printf("Usage: cat [-b, -e, -n, -s, -t, -v, -T, -E] [File]\n");
    exit(1);
  }
}
