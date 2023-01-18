#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF 1024

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int file_cnt;
} flags;

void s21_grep(flags *lst, int argc, char **argv, char *pattern);
void init_lst(flags *lst);
int parse_flags(int argc, char *argv[], flags *lst, char *template);
void file_handler(flags *lst, FILE *fp, regex_t reg_exp, char *file);
void match_template(flags *lst, char *template, char *file);
int f_handler(char *template, char *pattern);

int main(int argc, char *argv[]) {
  flags lst;
  init_lst(&lst);
  int res = 0;
  char template[BUFF] = {0};
  memset(&lst, 0, sizeof(lst));
  res = parse_flags(argc, argv, &lst, template);
  if ((argc >= 3) && (res != 1)) {
    s21_grep(&lst, argc, argv, template);
  }
  return res;
}

void s21_grep(flags *lst, int argc, char **argv, char *pattern) {
  char buffer[BUFF] = {0};
  int f_flg = 0;
  if (!lst->f && !lst->e) snprintf(buffer, BUFF, "%s", argv[optind++]);
  if (lst->f) f_flg = f_handler(buffer, pattern);
  if (!lst->f && lst->e) snprintf(buffer, BUFF, "%s", pattern);
  if (f_flg != -1) {
    lst->file_cnt = argc - optind;
    for (int i = optind; i < argc; i++) {
      if (lst->file_cnt > 1 && !lst->l && i == optind + 1) printf("\n");
      match_template(lst, buffer, argv[i]);
    }
  }
}

void init_lst(flags *lst) {
  lst->e = 0;
  lst->i = 0;
  lst->v = 0;
  lst->c = 0;
  lst->l = 0;
  lst->n = 0;
  lst->h = 0;
  lst->s = 0;
  lst->f = 0;
  lst->o = 0;
  lst->file_cnt = 0;
}

int parse_flags(int argc, char *argv[], flags *lst, char *template) {
  int i = 0, res = 0;
  while ((i = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (i) {
      case 'e':
        lst->e = 1;
        snprintf(template, BUFF, "%s", optarg);
        break;
      case 'i':
        lst->i = 1;
        break;
      case 'v':
        lst->v = 1;
        break;
      case 'c':
        lst->c = 1;
        break;
      case 'l':
        lst->l = 1;
        break;
      case 'n':
        lst->n = 1;
        break;
      case 'h':
        lst->h = 1;
        break;
      case 's':
        lst->s = 1;
        break;
      case 'f':
        lst->f = 1;
        snprintf(template, BUFF, "%s", optarg);
        break;
      case 'o':
        lst->o = 1;
        break;
      default:
        res = 1;
    }
  }
  return res;
}

void file_handler(flags *lst, FILE *fp, regex_t reg_exp, char *file) {
  char buffer[BUFF] = {0};
  regmatch_t pmatch[1];
  int l_cnt = 0, n_cnt = 1;
  while (fgets(buffer, BUFF - 1, fp) != NULL) {
    int state = regexec(&reg_exp, buffer, 1, pmatch, 0);
    int match = 0;
    if (state == 0 && !lst->v) match = 1;
    if (state == REG_NOMATCH && lst->v) match = 1;
    if (match && lst->file_cnt > 1 && !lst->h && !lst->l) printf("%s:", file);
    if (match && !lst->l && !lst->c && lst->n) printf("%d:", n_cnt);
    if (match && !lst->l && !lst->c && !lst->o) printf("%s", buffer);
    if (lst->o && match) {
      for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
        printf("%c", buffer[i]);
      }
      printf("\n");
    }
    l_cnt += match;
    n_cnt++;
  }
  if (lst->l && l_cnt > 0) printf("%s\n", file);
  if (lst->c && !lst->l) printf("%d\n", l_cnt);
}

void match_template(flags *lst, char *template, char *file) {
  int reg_flg = (lst->i) ? REG_ICASE | REG_EXTENDED : REG_EXTENDED;
  regex_t reg_exp;
  FILE *fp;
  fp = fopen(file, "r");
  if (fp == NULL) {
  } else {
    regcomp(&reg_exp, template, reg_flg);
    file_handler(lst, fp, reg_exp, file);
    regfree(&reg_exp);
    fclose(fp);
  }
}

int f_handler(char *template, char *pattern) {
  FILE *fp;
  fp = fopen(pattern, "r");
  int idx = 0;
  if (fp == NULL) {
    idx = -1;
  } else {
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
      if (ch == 13 || ch == 10) template[idx++] = '|';
      if (ch != 13 && ch != 10) template[idx++] = ch;
    }
    if (template[idx - 1] == '|') template[idx - 1] = '\0';
    fclose(fp);
  }
  return (idx == -1) ? -1 : (idx + 1);
}
