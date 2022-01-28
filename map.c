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
    ops key_ops;
    ops val_ops;
};

static inline hash_map_node *create_node(
    hash_map map,
    const void *key, 
    const void *val, 
    hash_map_node *next); 

hash_map create_hash_map(ops key_ops, ops val_ops, int num_buckets) {
    hash_map_node** buckets = malloc(sizeof(struct hash_map_node_s*)*num_buckets);
    if(buckets == NULL)
        return NULL;

    hash_map s = malloc(sizeof(struct hash_map_s));
    if(s == NULL)
        return NULL;

    s->num_buckets = num_buckets;
    s->buckets = buckets;
    s->key_ops = key_ops;
    s->val_ops = val_ops;
    return s;
}

int hash_map_put(hash_map m, const void *key, const void *val) {
    uint32_t bucket = m->key_ops.hash(key) % m->num_buckets;
    hash_map_node* node = m->buckets[bucket];
    
    if(node == NULL || m->key_ops.cmp(key, node->key) < 0) {
        hash_map_node *new = create_node(m, key, val, node);
       if(!new)
           return -1;
       m->buckets[bucket] = new;
       return 0;
    }

    while(node->next && m->key_ops.cmp(key, node->next->key) > 0)
        node = node->next;
    
    if(node->next && m->key_ops.cmp(key, node->next->key) == 0) {
        m->val_ops.free((void*)node->next->val);
        node->next->val = m->val_ops.cp(val);
        return 0;
    }

    hash_map_node *new = create_node(m, key, val, node->next);
    if(!new)
        return -1;
    node->next = new;
    
    return 0;
}

const void *hash_map_get(hash_map s, const void *key) {
    uint32_t bucket = s->key_ops.hash(key) % s->num_buckets;
    hash_map_node* node = s->buckets[bucket];
    while(node != NULL && s->key_ops.cmp(key, node->key) >  0)
        node = node->next;

    return node ? node->val : NULL;
}

void hash_map_free(hash_map m) {
    for(int i = 0; i < m->num_buckets; i++) {
        hash_map_node* node = m->buckets[i];
        if(!node)
            continue;

        while(node) {
            hash_map_node* next = node->next;
            m->key_ops.free((void*)node->key);
            m->val_ops.free((void*)node->val);
            free(node);
            node = next;
        }
    }
}


static inline hash_map_node *create_node(
    hash_map m,
    const void *key, 
    const void *val, 
    hash_map_node *next) {
    hash_map_node *node = malloc(sizeof(struct hash_map_node_s));
    if(!node)
        return NULL;

    node->key = m->key_ops.cp(key);
    node->val = m->val_ops.cp(val);
    node->next = next;
    return node; 
}
