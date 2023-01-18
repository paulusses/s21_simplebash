#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} flags;

int s21_cat(int argc, char *argv[], flags *lst);
void create_lst(flags *lst);
int file_handler(char *argv[], flags *lst);

int main(int argc, char *argv[]) {
  int err = 1;
  flags lst;
  create_lst(&lst);
  err = s21_cat(argc, argv, &lst);
  if (lst.b) {
    lst.n = 0;
  }
  while (optind < argc) {
    err = file_handler(argv, &lst);
    optind++;
  }
  return err;
}

void create_lst(flags *lst) {
  lst->b = 0;
  lst->e = 0;
  lst->n = 0;
  lst->s = 0;
  lst->t = 0;
  lst->v = 0;
}

int s21_cat(int argc, char *argv[], flags *lst) {
  int c;
  int res = 0;
  int idx = 0;
  static struct option options[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };
  while ((c = getopt_long(argc, argv, "bEnsTvet", options, &idx)) != -1) {
    switch (c) {
      case 'b':
        lst->b = 1;
        break;
      case 'E':
        lst->e = 1;
        break;
      case 'n':
        lst->n = 1;
        break;
      case 's':
        lst->s = 1;
        break;
      case 'T':
        lst->t = 1;
        break;
      case 'v':
        lst->v = 1;
        break;
      case 'e':
        lst->e = 1;
        lst->v = 1;
        break;
      case 't':
        lst->t = 1;
        lst->v = 1;
        break;
      case '?':
        res = -1;
        break;
    }
  }
  return res;
}

int file_handler(char *argv[], flags *lst) {
  FILE *file;
  int res = 0;
  file = fopen(argv[optind], "r");
  if (file != NULL) {
    int str_cnt = 1;
    int empty_cnt = 0;
    int last_sym = '\n';
    while (1) {
      int symbol = fgetc(file);
      if (symbol == EOF) {
        break;
      }
      if (lst->s && symbol == '\n' && last_sym == '\n') {
        empty_cnt++;
        if (empty_cnt > 1) {
          continue;
        }
      } else {
        empty_cnt = 0;
      }
      if (last_sym == '\n' && ((lst->b && symbol != '\n') || lst->n)) {
        printf("%6d\t", str_cnt++);
      }
      if (lst->t && symbol == '\t') {
        printf("^");
        symbol = 'I';
      }
      if (lst->e && symbol == '\n') {
        printf("$");
      }
      if (lst->v && symbol != '\n' && symbol != '\t') {
        if ((symbol >= 0 && symbol < 32)) {
          printf("^");
          symbol += 64;
        } else if (symbol >= 128 && symbol <= 254) {
          printf("M-");
          symbol -= 64;
        } else if (symbol == 127) {
          printf("^");
          symbol -= 64;
        } else if (symbol == 255) {
          printf("M-");
          symbol -= 192;
        }
      }
      printf("%c", symbol);
      last_sym = symbol;
    }
    fclose(file);
  } else {
    printf("s21_cat: %s: No such file or directory\n", argv[optind]);
    res = -1;
  }
  return res;
}
