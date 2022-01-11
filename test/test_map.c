#include "map.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tests.h"

//int->string hash map

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

static ops i2s_map_ops = {
    .hash = echo,
    .key_free = nop,
    .val_free = free_adapter,
    .key_cmp = cmp, 
};

void test_hash_map() {
    hash_map m = create_hash_map(i2s_map_ops, 10);
    int a = 1;
    int b = 2;
    int c = 11;
    hash_map_put(m, &a, "one");
    hash_map_put(m, &b, "two");
    hash_map_put(m, &c, "eleven");

    const char *ra = hash_map_get(m, &a);
    const char *rb = hash_map_get(m, &b);
    const char *rc = hash_map_get(m, &c);
    assert(strcmp(ra, "one") == 0);
    assert(strcmp(rb, "two") == 0);
    assert(strcmp(rc, "eleven") == 0);
    
    hash_map_put(m, &c, "updated");
    const char *updated = hash_map_get(m, &c);
    assert(strcmp(updated, "updated") == 0);

    hash_map_free(m);
}
