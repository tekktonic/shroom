#include "dtype.h"
#define FREE_WRAP(x) (free_func ? free_func(x) : NULL )

List new_List(int count, ...)
{
    List ret = malloc(sizeof(struct List_s));
    List cur = ret;
    va_list args;
    assert(cur != NULL);

    if (count)
    {
	va_start(args, count);


	while(count--)
	{
	    cur->car = va_arg(args, void*);
	    if (count)
	    {
		cur->cdr = malloc(sizeof(struct List_s));
		assert(cur->cdr != NULL);
		cur = cur->cdr;
	    }
	}
	va_end(args);
    }
    else
	cur->car = NULL;
    cur->cdr = NULL;
    return ret;
}

void List_enqueue(List list1, void *item)
{
    List cur = list1;

    do
    {
	if (cur->car == NULL)
	{
	    cur->car = item;
	    return;
	}

	if (cur->cdr != NULL)
	{
	    cur = cur->cdr;
	}

    } while(cur->cdr != NULL);

    cur->cdr = new_List(1, item);
}

void *List_dequeue(List list)
{
    List cur = list;
    List last = cur;

    void *ret;
    for(; cur->cdr != NULL; cur = cur->cdr)
	last = cur;
    ret = cur->car;
    last->cdr = NULL;

    free(cur);
    return ret;
}

void List_push(List *list, void *item)
{
    List new = new_List(1, item);
    new->cdr = *list;
    *list = new;
}

void *List_pop(List *list)
{
    void *ret = (*list)->car;
    List oldcar = *list;
    *list = (*list)->cdr;
    free(oldcar);
    return ret;
}

int List_len(List list)
{
    int i = 0;
    for(;list->cdr != NULL;)
    {
	list = list->cdr;
	++i;
    }
    return i + 1;
}

void List_delete(List list, int index, void (*free_func)(void *))
{
    List cur = list;
    List last = cur;

    int i = 0;
    for (; i < index && cur->cdr != NULL; cur = cur->cdr, ++i)
	last = cur;

    if (i == index)
    {
	last->cdr = cur->cdr;
	FREE_WRAP(cur->car);
	free(cur);
	cur = NULL;
    }
}

void List_free(List list, void (*free_func)(void *))
{
    if (list == NULL)
	return;
    else if (list->cdr)
	List_free(list->cdr, free_func);
    else
    {
	if (free_func)
	{
	    free_func(list->car);
	}
	free(list);
    }
}

List List_map(List list, void *(*f)(void*))
{
    List ret = new_List(0);
    for(;list->cdr != NULL; list = list->cdr)
    {
	void *item = f(list->car);
	List_enqueue(ret, item);
    }
    return ret;
}

bool List_contains(List list, void *data)
{
    for(;list->cdr != NULL; list = list->cdr)
    {
	if (list->car == data)
	    return true;
    }

    return false;
}

Hash new_Hash(void)
{
    Hash ret = malloc(sizeof(struct Bucket));
    assert(ret);
    ret->next = NULL;
    memset(ret->keys, '\0', BUCKET_SIZE * sizeof(char*)); // make sure we get some decent null checks
    memset(ret->values, '\0', BUCKET_SIZE * sizeof(void*));
    return ret;
}

int hash(const char *string)
{
    int len = strlen(string) + 1; // strlen doesn't include null
    int sum = 0;
    for (int i = 0; i < len; ++i)
    {
	sum += (int)string[i];
    }

    return sum % BUCKET_SIZE;
}

void Hash_insert(Hash h, const char *key, void *value)
{
    int offset = hash(key);

    if (!h->keys[offset] || strcmp(h->keys[offset], key) == 0) // If either we already have an entry for the key or there are no keys there
    {
	h->keys[offset] = key;
	h->values[offset] = value;
    }
    else
    {
	if (!h->next)
	{
	    h->next = new_Hash();
	}
	Hash_insert(h->next, key, value);
    }
}   



void *Hash_get(Hash h, const char *key)
{
    int offset = hash(key);

    if (h->keys[offset] != NULL)
    {
	if (strcmp(h->keys[offset], key) == 0)
	{
	    return h->values[offset];
	}
	else if (h->next)
	{
	    return Hash_get(h->next, key);
	}
    }

    return NULL;
}
