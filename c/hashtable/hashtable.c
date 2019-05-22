#include "hashtable.h"


void init_hash(struct hashtable *h, int hash_size, compare_value_f compare, free_value_f free)
{
    int i;

    h->hash_size = hash_size;
    h->alloc_count = 0;
    h->compare_f = compare;
    h->free_f = free;

    h->hash = (struct hashnode*)malloc(sizeof(struct hashnode) * hash_size);

    for(i=0; i<hash_size; i++)
    {
        list_init(&h->hash[i].list);
        h->hash[i].value_count = 0;

    }

}

unsigned int hash(struct hashtable *h, char *key)
{
    unsigned int k = 0;

    for(; *key; key++)
        k = *key+k*31;

    return k % h->hash_size;

}

void insert_hash(struct hashtable *h, char *key, void *value)
{
    int index = hash(h, key);
    struct hashlist *v, *n;

    n = (struct hashlist*)malloc(sizeof(struct hashlist));
    n->value = value;

    //sort insert
    /*
       list_iterate(v, &h->hash[index].list)
       {
       int ret = h->compare_f(key, v->value);
       if(ret < 0)
       {
       }

       }
       */

    list_add(&h->hash[index].list, n);

    h->alloc_count++;
    h->hash[index].value_count++;

}

void *delete_hash(struct hashtable *h, char *key)
{
    int index = hash(h, key);
    struct hashlist *v, *t;
    void *ret = NULL;

    list_iterate_safe(v, t, &h->hash[index].list)
    {
        if(!h->compare_f(key, v->value))
        {
            ret = v->value;
            list_del(v);
            h->free_f(v->value);
            free(v);

            h->hash[index].value_count--;
            h->alloc_count--;

            break;

        }

    }

    return ret;

}

void *get_hash(struct hashtable *h, char *key)
{
    int index = hash(h, key);
    struct hashlist *v;

    list_iterate(v, &h->hash[index].list)
    {
        if(!h->compare_f(key, v->value))
            return v->value;

    }

    return NULL;

}

void destory_hash(struct hashtable *h)
{
    int i;
    struct hashlist *v, *t;

    for(i=0; i<h->hash_size; i++)
    {
        list_iterate_safe(v, t, &h->hash[i].list)
        {
            list_del(v);
            h->free_f(v->value);
            free(v);

            h->hash[i].value_count--;
            h->alloc_count--;

        }

    }

    free(h->hash);

}
