#include "s21_grep.h"

int main(int argc, char *argv[]) {
  opt options = {0};
  parser(argc, argv, &options);
  char *pattern = argv[optind];
  optind++;
  int files_count = argc - optind;
  for (int i = optind; i < argc; i++) {
    char *filename = argv[i];
    reader(&options, filename, pattern, files_count);
  }
  return 0;
}

void parser(int argc, char *argv[], opt *options) {
  int o;
  while ((o = getopt(argc, argv, "+eivclnhsfo")) != -1) {
    switch (o) {
      case 'e':
        options->e = 1;
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f':
        options->f = 1;
        break;
      case 'o':
        options->o = 1;
        break;
      default:
        printf(
            "Usage [-e, -i, -v, -c, -l, -n, -h, -s, -f, -o] template "
            "[file_name]");
        exit(1);
    }
  }
}

void reader(opt *options, char *filename, char *pattern, int files_count) {
  FILE *fp = fopen(filename, "r");
  if (fp) {
    char text[buffer] = {0};
    int lines = 1, status, success = 0, loses = 0;
    int print_later = 0;
    int cflags = REG_EXTENDED;
    if (options->i) cflags = REG_ICASE;
    regex_t reg;
    regmatch_t pmatch[1];
    regcomp(&reg, pattern, cflags);
    while (fgets(text, buffer - 1, fp) != NULL) {
      status = regexec(&reg, text, 1, pmatch, 0);
      if (strchr(text, '\n') == NULL) strcat(text, "\n");

      if (!status) {
        success++;

        if (options->c || options->l) {
          print_later = 1;
          continue;
        }
        if (!options->h && !options->v) {
          if (files_count > 1) printf("%s:", filename);
        }
        if (options->n && !options->v) printf("%d:", lines);
        if (!options->v && !options->o) printf("%s", text);
        if (options->o && !options->v) {
          for (int i = (int)pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
            printf("%c", text[i]);
          }
          printf("\n");
        }

      } else if (options->v) {
        loses++;
        if (options->c || options->l) {
          print_later = 1;
          continue;
        }
        if (!options->h && files_count > 1) printf("%s:", filename);
        if (options->n) printf("%d:", lines);
        printf("%s", text);
      }
      lines++;
    }

    if (print_later) {
      if (!options->h && !options->l && files_count > 1)
        printf("%s:", filename);
      if (options->c && options->l) success = 1;
      if (options->c && !options->v) printf("%d\n", success);
      if (options->c && options->v && !options->l) printf("%d\n", loses);
      if (options->c && options->v && options->l) printf("1\n");
      if (options->l) printf("%s\n", filename);
    }

    regfree(&reg);
  } else {
    if (!options->s) fprintf(stderr, "Cannot open the file\n");
  }
}
