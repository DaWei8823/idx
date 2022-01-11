#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t (*hash) (const void *data);
    void (*key_free) (const void *data);
    void (*val_free) (const void *data);
    int8_t (*key_cmp) (const void *a, const void *b);
} ops;

typedef struct hash_map_s *hash_map;

hash_map create_hash_map(ops ops, int num_buckets);
int hash_map_put(hash_map s, const void *key, const void *val);
const void *hash_map_get(hash_map s, const void *key);
void hash_map_free(hash_map s);
