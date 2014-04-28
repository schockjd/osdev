#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dest, void *src, size_t n) {
    uint8_t *srcPtr8 = (uint8_t *)src;
    uint8_t *destPtr8 = (uint8_t *)dest;
    while ((void *)srcPtr8 < src + n) {
        *destPtr8 = *srcPtr8;
        destPtr8++;
        srcPtr8++;
    }
    
    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    uint8_t *s1Ptr8 = (uint8_t *)s1;
    uint8_t *s2Ptr8 = (uint8_t *)s2;
    int i=0;
    while ((void *)s1Ptr8 < s1 + n && i==0) {
       i = *s2Ptr8 - *s1Ptr8;
    }
    return i;
}

void *memset(void *s, int c, size_t n) {
    uint8_t *sPtr8 = (uint8_t *)s;
    while ((void *)sPtr8 < s + n) {
        *sPtr8 = (uint8_t)c;
    }
    return s;
}
size_t strlen(const char* str) {
    size_t ret = 0;
    while (str[ret] != 0) 
        ret++;
    return ret;
}
