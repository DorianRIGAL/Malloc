/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** malloc.h
*/

#ifndef MALLOC_H_
#define MALLOC_H_

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *heap;
pthread_mutex_t mut;

typedef struct __attribute__ ((packed)) meta_s {
    size_t size;
    char isFree;
} meta_t;

#define MET sizeof(meta_t)

char *start_base(long long nb, char *base);

#endif