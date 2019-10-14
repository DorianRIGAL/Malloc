/*
** EPITECH PROJECT, 2018
** PSU_2018_malloc
** File description:
** show_alloc_mem.c
*/

#include <unistd.h>
#include "malloc.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    for (unsigned int i = 0; str != NULL && str[i] != '\0'; i++)
        my_putchar(str[i]);
}

void my_putnbr(long long nbr)
{
    int n;

        if (nbr < 0) {
            nbr = - nbr;
            my_putchar('-');
        }
        n = nbr % 10;
        nbr = nbr / 10;
        if (nbr > 0)
            my_putnbr(nbr);
        my_putchar(n + '0');
}

void my_put_hexa(long long nb, char *base, int i)
{
    int modulo;

    if (nb < 0)
        nb = -nb;
    modulo = nb % 16;
    nb = nb / 16;
    if (nb > 0)
        my_put_hexa(nb, base, i + 1);
    my_putchar(base[modulo]);
}

void show_alloc_mem(void)
{
    meta_t *meta = heap;
    size_t tmp;

    my_putstr("break : 0x");
    my_put_hexa((int long long)sbrk(0), "0123456789ABCDEF", 0);
    my_putstr("\n");
    if (heap == NULL)
        return;
    while (meta->isFree != 2) {
        tmp = meta->size;
        my_putstr("0x");
        my_put_hexa((int long long)((void *)meta + 9), "0123456789ABCDEF", 0);
        my_putstr(" - 0x");
        meta = (void*)meta + meta->size + MET;
        my_put_hexa((int long long)((void *)meta - 1), "0123456789ABCDEF", 0);
        my_putstr(" : ");
        my_putnbr(tmp);
        my_putstr(" bytes\n");
    }
}