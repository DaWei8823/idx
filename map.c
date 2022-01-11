#include "map.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct hash_map_node_s {
    struct hash_map_node_s *next;
    const void *key;
    const void *val;
} hash_map_node;

struct hash_map_s {
    uint num_buckets;
    hash_map_node** buckets;
    ops ops;
};

static inline hash_map_node *create_node(
    const void *key, 
    const void *val, 
    hash_map_node *next); 

hash_map create_hash_map(ops ops, int num_buckets) {
    hash_map_node** buckets = malloc(sizeof(struct hash_map_node_s*)*num_buckets);
    if(buckets == NULL)
        return NULL;

    hash_map s = malloc(sizeof(struct hash_map_s));
    if(s == NULL)
        return NULL;

    s->num_buckets = num_buckets;
    s->buckets = buckets;
    s->ops = ops;
    return s;
}

int hash_map_put(hash_map s, const void *key, const void *val) {
    uint32_t bucket = s->ops.hash(key) % s->num_buckets;
    hash_map_node* node = s->buckets[bucket];
    
    if(node == NULL || s->ops.key_cmp(key, node->key) < 0) {
       hash_map_node *new = create_node(key, val, node);
       if(!new)
           return -1;
       s->buckets[bucket] = new;
       return 0;
    }

    while(node->next && s->ops.key_cmp(key, node->next->key) > 0)
        node = node->next;
    
    if(node->next && s->ops.key_cmp(key, node->next->key) == 0) {
        node->next->val = val;
        return 0;
    }

    hash_map_node *new = create_node(key, val, node->next);
    if(!new)
        return -1;
    node->next = new;
    
    return 0;
}

const void *hash_map_get(hash_map s, const void *key) {
    uint32_t bucket = s->ops.hash(key) % s->num_buckets;
    hash_map_node* node = s->buckets[bucket];
    while(node != NULL && s->ops.key_cmp(key, node->key) >  0)
        node = node->next;

    return node ? node->val : NULL;
}

void hash_map_free(hash_map s) {
    for(int i = 0; i < s->num_buckets; s++) {
        hash_map_node* node = s->buckets[i];
        if(!node)
            continue;

        while(node) {
            hash_map_node* next = node->next;
            s->ops.key_free(node->key);
            s->ops.val_free(node->val);
            free(node);
            node = next;
        }
    }
}


static inline hash_map_node *create_node(
    const void *key, 
    const void *val, 
    hash_map_node *next) {
    hash_map_node *node = malloc(sizeof(struct hash_map_node_s));
    if(!node)
        return NULL;
    node->key = key;
    node->val = val;
    node->next = next;
    return node; 
}
