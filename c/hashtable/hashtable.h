#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "list.h"

struct hashlist {
    struct hashlist *n, *p;
    void *value;
};

struct hashnode {
    int value_count;
    struct hashlist list;
};

typedef int (*compare_value_f)(char *key, void *value);
typedef void (*free_value_f)(void *value);

struct hashtable {
    int hash_size;
    int alloc_count;
    compare_value_f compare_f;
    free_value_f free_f;
    struct hashnode *hash;
};

void init_hash(struct hashtable *hash, int hash_size, compare_value_f compare, free_value_f free);
unsigned int hash(struct hashtable *hash, char *key);
void insert_hash(struct hashtable *hash, char *key, void *value);
void *delete_hash(struct hashtable *hash, char *key);
void *get_hash(struct hashtable *hash, char *key);
void destory_hash(struct hashtable *hash);

#endif
