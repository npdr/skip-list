#include <stdbool.h>
#define MAX_SKIPLIST_LEN 50
typedef struct snode_ snode;
typedef struct skiplist_ skiplist;
skiplist *sl_make();
int sl_search_word(skiplist **sl, char *word, int print_flag);
void sl_search_letter(skiplist **sl, char letter);
void sl_insert(skiplist **sl, char *word, char *def);
void sl_delete(skiplist **sl, char *word);
void sl_update(skiplist **sl, char *word, char *new_def);
void sl_print(skiplist **sl);
int sl_get_size(skiplist *sl);
bool flip_coin();
int random_lvl(int size);

void testando();