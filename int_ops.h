#include<stdlib.h>

int int_hash(const void *in) {
    return *(int*)in;
}

void int_free(void *in) {
    free(in);
}

void* int_cp(const void *data) {
    int* dest = malloc(sizeof(int));
    *dest = *(int*)data;
    return dest;
}

int8_t int_cmp(const void *a, const void *b){
    int a_val = *(int*)a;
    int b_val = *(int*)b;
    if(a_val == b_val) return 0;
    return a_val > b_val ? 1 : -1;
}

ops int_ops = {
    .hash = int_hash,
    .free = int_free,
    .cp = int_cp,
    .cmp = int_cmp
};
