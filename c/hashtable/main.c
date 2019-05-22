#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "hashtable.h"

#define T_FILE      1
#define T_DIR       2
#define T_LINK      3
#define T_OTHER     4

struct data
{
    char name[256];
    int type;
    int size;

};

struct hashtable g_hash;

const char *type_str(int type)
{
    switch(type)
    {
        case T_FILE:
            return "regular file";
        case T_DIR:
            return "directory";
        case T_LINK:
            return "symbollic link";
        case T_OTHER:
            return "other file";

    }

    return "unkown file";

}

int compare_data(char *key, void *value)
{
    struct data* data = (struct data*)value;

    return strcmp(key, data->name);

}

void free_data(void *value)
{
    free(value);

}

off_t get_file_size(char* path)
{
    int ret;
    off_t size;
    struct stat buf;

    ret = stat(path, &buf);
    if(-1 == ret)
        return 0;

    return buf.st_size;

}

int main(int argc, char *argv[])
{
    int i;

    init_hash(&g_hash, 107, compare_data, free_data);

    for(i=1; i<argc; i++)
    {
        struct data *data = (struct data*)malloc(sizeof(struct data));
        struct stat st;

        sprintf(data->name, "%s", argv[i]);

        if(-1 == lstat(data->name, &st))
            continue;

        if(S_ISREG(st.st_mode))
            data->type = T_FILE;
        else if(S_ISDIR(st.st_mode))
            data->type = T_DIR;
        else if(S_ISLNK(st.st_mode))
            data->type = T_LINK;
        else
            data->type = T_OTHER;

        data->size = st.st_size;

        insert_hash(&g_hash, argv[i], data);

    }

    while(1)
    {
        char cmdline[256] = {0, };

        printf("> ");
        fgets(cmdline, sizeof(cmdline), stdin);
        cmdline[strlen(cmdline)-1] = '\0';

        if(0 == strcmp("quit", cmdline))
            break;

        struct data *ret = (struct data*)get_hash(&g_hash, cmdline);

        if(NULL != ret)
        {
            printf("%s(%d) : %s\n", ret->name, ret->size, type_str(ret->type));

        }
        else
        {
            fprintf(stderr, "%s : not found!\n", cmdline);

        }

    }

    destory_hash(&g_hash);

    return 0;
}
