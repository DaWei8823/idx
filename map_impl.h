#pragma once
#include "map.h"
#include<stdlib.h>

//termmap: term -> filemap
//filemap: file -> intset
//intset:  int -> nothing??
//reversefile file -> tokens

static void nop(const void *_) {}

static uint32_t echo(const void *data) {
    const int *ptr = data;
    return *ptr;
}

static void free_adapter(const void *data) {
    free((void*)data);
}

static int8_t cmp(const void *a, const void *b) {
    const int* x = a;
    const int* y = b;
    if(*x == *y) 
        return 0;
    return *x > *y ? 1 : -1;
}

ops intset_ops = {
    .hash = echo,
    .key_free =   
};

uint32_t str_hash(char* str) {
{
    uint32_t hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

uint32_t str_free(char* str){
    free(str);

