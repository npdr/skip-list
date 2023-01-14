#include "skiplist.h"
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// skiplist structure
struct skiplist_ {
  lnode *head;
  llist *ll_start;
  lnode *start;
  int size;
};

void testando() {
  skiplist *sl = sl_make();
  sl_insert(&sl, "a", "");
  sl_insert(&sl, "d", "");
  sl_insert(&sl, "c", "");
  sl_insert(&sl, "b", "");
  sl_print(&sl);
}

// inits the skiplist
skiplist *sl_make() {
  skiplist *sl = (skiplist *)malloc(sizeof(skiplist));

  lnode *start_lvl1 = lnode_make("", "", 1, NULL, NULL);
  lnode *start_lvl2 = lnode_make("", "", 2, NULL, start_lvl1);
  sl->start = start_lvl2;

  sl->size = 2;
  return sl;
}

// method for inserting a word and its definition inside the skip list
void sl_insert(skiplist **sl, char *word, char *def) {
  if (sl_search_word(sl, word, 0)) {
    printf("OPERACAO INVALIDA\r");
    return;
  }

  int lvl = random_lvl((*sl)->size);

  lnode *sl_temp = (*sl)->start;
  lnode *last_inserted = NULL;
  lnode *ll_temp = sl_temp;
  int lvl_temp = lvl;
  while (sl_temp) {
    // level to insert
    if (sl_temp->lvl == lvl_temp) {
      // base case
      if (sl_temp->size == 0) {
        if (sl_temp->lvl == lvl_temp) {
          last_inserted = ll_insert(&ll_temp, word, def, ll_temp->lvl,
                                    last_inserted, ll_temp->down);
          lvl_temp--;
        }
      } else {
        // keep looping until found a bigger word
        while (ll_temp->next && alphBefore(ll_temp->next->word, word)) {
          ll_temp = ll_temp->next;
        }

        // insert and jump to the lvl below
        last_inserted = ll_insert(&ll_temp, word, def, ll_temp->lvl,
                                  last_inserted, ll_temp->down);
        lvl_temp--;

        sl_temp = ll_temp->down;
        ll_temp = sl_temp;
      }
    } else {
      //  keep looping until found a bigger word
      while (ll_temp->next && alphBefore(ll_temp->next->word, word)) {
        ll_temp = ll_temp->next;
      }
      // jump to the lvl below
      sl_temp = ll_temp->down;
      ll_temp = sl_temp;
    }
  }

  // add a spare new lvl
  if (lvl == (*sl)->size) {
    (*sl)->size++;
    lnode *new_lvl = lnode_make("", "", (*sl)->size, NULL, (*sl)->start);
    (*sl)->start = new_lvl;
  }
}

// method for searching for a word inside the skip list
int sl_search_word(skiplist **sl, char *word, int print_flag) {
  int found_flag = 0;

  lnode *sl_temp = (*sl)->start;
  lnode *ll_temp = sl_temp;
  while (sl_temp) {
    // keep looping until found a bigger word
    while (ll_temp->next && alphBefore(ll_temp->next->word, word)) {
      ll_temp = ll_temp->next;
    }

    // update and jump to the lvl below
    if (ll_temp->next && !strcmp(ll_temp->next->word, word)) {
      found_flag = 1;
      if (print_flag)
        printf("%s %s\r", ll_temp->next->word, ll_temp->next->def);
      return found_flag;
    }

    sl_temp = ll_temp->down;
    ll_temp = sl_temp;
  }

  if (!found_flag && print_flag) {
    printf("OPERACAO INVALIDA\r");
  }
  return found_flag;
}

// method for updating a def of a word inside the skip list
void sl_update(skiplist **sl, char *word, char *def) {
  if (!sl_search_word(sl, word, 0)) {
    printf("OPERACAO INVALIDA\r");
    return;
  }

  lnode *updated;
  lnode *sl_temp = (*sl)->start;
  lnode *ll_temp = sl_temp;
  while (sl_temp) {
    // keep looping until found a bigger word
    while (ll_temp->next && alphBefore(ll_temp->next->word, word)) {
      ll_temp = ll_temp->next;
    }

    // update and jump to the lvl below
    if (ll_temp->next && !strcmp(ll_temp->next->word, word)) {
      strcpy(ll_temp->next->def, def);
      updated = lnode_make(ll_temp->next->word, def, ll_temp->next->lvl,
                           ll_temp->next->up, ll_temp->next->down);
    }

    sl_temp = ll_temp->down;
    ll_temp = sl_temp;
  }
}

// method for deleting for a word and its def inside the skip list
void sl_delete(skiplist **sl, char *word) {
  if (!sl_search_word(sl, word, 0)) {
    printf("OPERACAO INVALIDA\r");
    return;
  }
  int delete_flag = 0;
  lnode *sl_temp = (*sl)->start;
  lnode *ll_temp = sl_temp;
  while (sl_temp) {
    // keep looping until found a bigger word
    while (ll_temp->next && alphBefore(ll_temp->next->word, word)) {
      ll_temp = ll_temp->next;
    }

    // delete and jump to the lvl below
    if (ll_temp->next && !strcmp(ll_temp->next->word, word)) {
      delete_flag = 1;
      sl_temp = ll_temp->down;
      ll_delete(&ll_temp->next);
      ll_temp = sl_temp;
    } else {
      sl_temp = ll_temp->down;
      ll_temp = sl_temp;
    }
  }
  if (!delete_flag)
    printf("OPERACAO INVALIDA\r");
}

// method for searching words that starts with letter inside the skip list
void sl_search_letter(skiplist **sl, char letter) {
  int found_flag = 0;
  lnode *sl_temp = (*sl)->start;
  lnode *ll_temp = sl_temp;
  while (sl_temp) {
    // keep looping until found a bigger word
    while (ll_temp->next && ll_temp->next->word[0] < letter) {
      ll_temp = ll_temp->next;
    }

    // found letter
    if (ll_temp->next && ll_temp->next->word[0] == letter) {
      // if its on lvl 1
      if (ll_temp->next->lvl == 1) {
        // keep printing until next_letter != letter
        while (ll_temp->next) {
          if (ll_temp->next->word[0] == letter) {
            found_flag = 1;
            printf("%s %s\r", ll_temp->next->word, ll_temp->next->def);
            ll_temp = ll_temp->next;
          } else {
            return;
          }
        }
      }
      sl_temp = ll_temp->down;
      ll_temp = sl_temp;
    } else {
      sl_temp = ll_temp->down;
      ll_temp = sl_temp;
    }
  }
  if (!found_flag)
    printf("OPERCACAO INVALIDA\r");
}

// prints the skip list
void sl_print(skiplist **sl) {
  lnode *sl_temp = (*sl)->start;

  while (sl_temp) {
    printf("lvl#%d: ", sl_temp->lvl);
    ll_print(&sl_temp);
    sl_temp = sl_temp->down;
  }
  printf("\n");
}

int sl_get_size(skiplist *sl) { return sl->size; }

// flips a coin
bool flip_coin() {
  float coin = rand() / (float)RAND_MAX;
  if (coin > 0.5)
    return true;
  return false;
}

// return max lvl to insert in the skiplist
int random_lvl(int size) {
  int lvl = 1;
  while (flip_coin() && lvl < size)
    lvl++;
  return lvl;
}