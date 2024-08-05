#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DA_APPEND(arr, len, cap, stride, value) \
    do { \
        size_t s = sizeof(stride); \
        if ((len) >= (cap)) { \
            (cap) = (cap)*2; \
            (arr) = realloc((arr), (cap)*s); \
            memset(((uint8_t*)arr)+((len)*s), '\0', (cap)-(len)); \
        } \
        (void)memcpy(((uint8_t*)arr)+(len)*s, (value), s); \
        ++(len); \
    } while (0)

#endif // UTILS_H
