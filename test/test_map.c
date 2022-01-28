#include "map.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "int_ops.h"
#include "str_ops.h"
#include "tests.h"

//int->string hash map


void test_hash_map() {
    hash_map m = create_hash_map(int_ops, str_ops, 10);
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
    
    //hash_map_put(m, &c, "updated");
    //const char *updated = hash_map_get(m, &c);
    //assert(strcmp(updated, "updated") == 0);

    hash_map_free(m);
}
