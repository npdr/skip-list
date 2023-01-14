#include "skiplist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  //testando();

  skiplist *sl = sl_make();

  char cmd[50];
  while (scanf("%s", cmd) != EOF) {
    char word[50] = {}, def[200] = {}, letter;

    if (!strcmp(cmd, "remocao")) {
      scanf("%s\r", word);
      sl_delete(&sl, word);

    } else if (!strcmp(cmd, "busca")) {
      scanf("%s\r", word);
      sl_search_word(&sl, word, 1);

    } else if (!strcmp(cmd, "impressao")) {
      scanf(" %c\r\n", &letter);
      sl_search_letter(&sl, letter);

    } else if (!strcmp(cmd, "insercao")) {
      scanf("%s %[^\r\n]", word, def);
      sl_insert(&sl, word, def);

    } else if (!strcmp(cmd, "alteracao")) {
      scanf("%s %[^\r\n]", word, def);
      sl_update(&sl, word, def);

    } else {
      printf("%s input error\n", cmd);
      return 0;
    }
  }
  return 0;
}