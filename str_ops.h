#include<stdint.h>
#include<stdlib.h>
#include<string.h>

int str_hash(const void* in) {
    uint32_t hash = 5381;
    int c;
    const char* str = (char*)in;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

void str_free(void* str){
    free(str);
}

void *str_cp(const void *data) {
    size_t len = strlen(data);
    char* dest = malloc(len*sizeof(char));
    strcpy(dest, data);
    return dest;
}

int8_t str_cmp(const void *a, const void *b) {
   return strcmp(a, b);
}

ops str_ops = {
    .hash = str_hash,
    .free = str_free,
    .cp = str_cp,
    .cmp = str_cmp
};
