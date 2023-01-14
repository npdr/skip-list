#include "linkedlist.h"

lnode *lnode_make(char *word, char *def, int lvl, lnode *up, lnode *down) {
  lnode *new_lnode = (lnode *)malloc(sizeof(lnode));
  strcpy(new_lnode->word, word);
  strcpy(new_lnode->def, def);
  new_lnode->up = up;
  new_lnode->down = down;
  new_lnode->before = NULL;
  new_lnode->next = NULL;
  if (up)
    up->down = new_lnode;
  if (down)
    down->up = new_lnode;
  new_lnode->lvl = lvl;
  new_lnode->size = 0;
  return new_lnode;
}

lnode *ll_insert(lnode **pos, char *word, char *def, int lvl, lnode *up,
                 lnode *down) {
  lnode *new_lnode = lnode_make(word, def, lvl, up, down);
  lnode *temp = (*pos)->next;

  (*pos)->next = new_lnode;
  new_lnode->before = (*pos);
  new_lnode->next = temp;
  if (temp)
    temp->before = new_lnode;

  (*pos)->size++;
  new_lnode->size = (*pos)->size;
  return new_lnode;
}

void ll_delete(lnode **pos) {
  lnode *temp = (*pos);
  (*pos)->before->next = temp->next;

  if (temp->next) {
    temp->next->before = temp->before;
  }

  temp->up = NULL;
  temp->down = NULL;
  temp->before = NULL;
  temp->next = NULL;
  temp = NULL;
}

void ll_print(lnode **ll) {
  lnode *temp = *ll;
  while (temp) {
    printf("%d# %s: %s-> ", temp->lvl, temp->word, temp->def);
    temp = temp->next;
  }
  printf("NULL\n");
}

/* return true if a is alphabetically before b, else false */
bool alphBefore(char *a, char *b) {
  if (strcmp(a, b) < 0)
    return true;
  return false;
}