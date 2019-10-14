/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** malloc.c
*/

#include <limits.h>
#include <string.h>
#include "malloc.h"

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
void *heap = NULL;

size_t cmp(meta_t *meta)
{
    size_t disp = meta->size;
    meta_t *tmp = meta;

    while (tmp->isFree == 1) {
        tmp = (void*)tmp + tmp->size + MET;
        if (tmp->isFree != 0) {
            disp += tmp->size + MET;
            if (tmp->isFree == 2)
                meta->isFree = 2;
        }
    }
    meta->size = disp;
    return (disp);
}

meta_t *first_alloc(int len, size_t pageSize, meta_t *meta)
{
    heap = sbrk((((len + 18) / pageSize) + 1) * pageSize);
    meta = heap + len + MET;
    meta->size = ((((len + 18) / pageSize) + 1) * pageSize) - len - 18;
    meta->isFree = 2;
    meta = heap;
    meta->size = len;
    meta->isFree = 0;
    return meta;
}

meta_t *classic_alloc(int len, size_t pageSize, meta_t *meta)
{
    meta = heap;
    while (meta->isFree == 0 || (meta->isFree == 1 && cmp(meta) < len + MET)
    || meta->isFree != 2) {
        if (meta->isFree != 2)
            meta = (void*)meta + meta->size + MET;
    }
    if (meta->isFree == 1) {
            ((meta_t*)((void*)meta + len + MET))->isFree = 1;
    } else {
        if (meta->size <= (len + MET)) {
            sbrk(((len + MET - meta->size) / pageSize + 1) * pageSize);
            meta->size += ((len + MET - meta->size) / pageSize + 1) * pageSize;
        }
        ((meta_t*)((void*)meta + len + MET))->isFree = 2;
    }
    ((meta_t*)((void*)meta + len + MET))->size = meta->size - len - MET;
    meta->size = len;
    meta->isFree = 0;
    return meta;
}

void *malloc(size_t len)
{
    pthread_mutex_lock(&mut);
    static size_t pageSize = 0;
    meta_t *meta = NULL;

    if (pageSize == 0)
        pageSize = getpagesize();
    if (len <= 0) {
        pthread_mutex_unlock(&mut);
        return (NULL);
    }
    if (heap == NULL) {
        meta = first_alloc(len, pageSize, meta);
    } else {
        meta = classic_alloc(len, pageSize, meta);
    }
    pthread_mutex_unlock(&mut);
    return ((void *)((void*)meta + MET));
}