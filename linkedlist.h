#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LEN 60
#define MAX_DEF_LEN 200
typedef struct lnode_ lnode;
typedef struct llist_ llist;

struct lnode_ {
  char word[MAX_WORD_LEN];
  char def[MAX_DEF_LEN];
  int lvl, size;
  lnode *up, *down;
  lnode *before, *next;
};
lnode *lnode_make(char *word, char *def, int lvl, lnode *up, lnode *down);
lnode *ll_insert(lnode **ll, char *word, char *def, int lvl, lnode *up,
                 lnode *down);
void ll_delete(lnode **pos);
void ll_update(lnode **ll, char *word, char *new_word, char *new_def);
void ll_print(lnode **ll);
bool alphBefore(char *a, char *b);