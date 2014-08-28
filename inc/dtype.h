#ifndef DTYPE_H
#define DTYPE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <stdbool.h>

#ifndef BUCKET_SIZE
#define BUCKET_SIZE 10
#endif

struct List_s;
typedef struct List_s *List;
typedef struct Bucket *Hash;

typedef List Queue;
typedef List Stack;

struct List_s
{
    void *car;
    List cdr;
};

struct Bucket
{
    const char *keys[BUCKET_SIZE];
    void *values[BUCKET_SIZE];
    struct Bucket *next;
};

struct Vect_s
{
    int x, y;
};

typedef struct Vect_s Vect;

List new_List(int count, ...);

void List_enqueue(List list, void *item);
void *List_dequeue(List list);
void List_push(List *list, void *item);
void *List_pop(List *list);
int List_len(List list);
void List_delete(List list, int index, void (*free_func)(void *));
void List_free(List list, void (*free_func)(void *));
List List_map(List list, void *(*f)(void*));
bool List_contains(List list, void *data);

Hash new_Hash(void);
void Hash_insert(Hash hash, const char *key, void *value);
void *Hash_get(Hash hash, const char *key);

Vect vect(int x, int y);
#endif
