/*
** EPITECH PROJECT, 2018
** PSU_2018_malloc
** File description:
** side_malloc.c
*/

#include <limits.h>
#include <string.h>
#include "malloc.h"

void *malloc(size_t len);

meta_t *free_end(meta_t *info, size_t pageSize)
{
    if (info->size >= pageSize) {
        sbrk(-(pageSize * (info->size / pageSize)));
        info->size -= pageSize * (info->size / pageSize);
    }
    info->isFree = 2;
    if (info == heap) {
        sbrk(-(info->size + MET));
        heap = NULL;
    }
    return info;
}

void free(void *ptr)
{
    static size_t pageSize = 0;
    meta_t *info;
    meta_t *tmp;

    if (ptr == NULL)
        return;
    info = (meta_t *)(ptr - MET);
    tmp = ptr + info->size;
    pthread_mutex_lock(&mut);
    if (pageSize == 0)
        pageSize = getpagesize();
    info->isFree = 1;
    if (tmp->isFree == 1 || tmp->isFree == 2)
        info->size += tmp->size + MET;
    if (tmp->isFree == 2)
        info = free_end(info, pageSize);
    pthread_mutex_unlock(&mut);
}

void *calloc(size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0) {
        return NULL;
    }
    void *new = malloc(nmemb * size);

    if (new) {
        pthread_mutex_lock(&mut);
        new = memset(new, 0, size * nmemb);
        pthread_mutex_unlock(&mut);
    } else {
        return NULL;
    }
    return new;
}

void *realloc(void *ptr, size_t len)
{
    void *new;
    meta_t *meta;
    size_t min = 0;

    if (len == 0) {
        free(ptr);
        return NULL;
    }
    if (ptr == NULL)
        return malloc(len);
    meta = ptr - MET;
    min = (meta->size < len) ? meta->size: len;
    if (meta->size < len) {
        new = malloc(len);
        for (size_t i = 0; i < min; i++)
            ((char*)new)[i] = ((char*)ptr)[i];
        free(ptr);
    } else
        new = ptr;
    return new;
}