#include <stdlib.h>
#include <stdio.h>

#include "ftstr.h"
#include "utils.h"

struct ftstr
ftstr_create(void) {
    struct ftstr str = {
        .value = malloc(sizeof(char)),
        .cap = 1,
        .len = 0,
    };
    str.value[0] = '\0';
    return str;
}

struct ftstr
ftstr_from_cstr(const char *value) {
    struct ftstr str = ftstr_create();
    for (size_t i = 0; value[i]; ++i)
        ftstr_append_char(&str, value[i]);
    return str;
}

struct ftstr
ftstr_from_ftstr(struct ftstr *value){
    struct ftstr str = ftstr_create();
    for(size_t i = 0; i < value->len; ++i)
        ftstr_append_char(&str, value->value[i]);
    return str;
}

void
ftstr_append_char(struct ftstr *str, char c) {
    DA_APPEND(str->value, str->len, str->cap, char, &c);
}

void
ftstr_append_cstr(struct ftstr *str, const char *value) {
    while (*value)
        ftstr_append_char(str, *(value++));
}

void
ftstr_append_ftstr(struct ftstr *dest, struct ftstr *src) {
    for (size_t i = 0; i < src->len; ++i)
        ftstr_append_char(dest, src->value[i]);
}

void
ftstr_clear(struct ftstr *str) {
    memset(str->value, '\0', str->len);
    str->len = 0;
}

struct ftstr *
ftstr_from_split_on_delim(struct ftstr *str, char delim, size_t *len) {
    // create buffer
    struct ftstr *lst = malloc(sizeof(struct ftstr)*10);
    size_t lstlen = 0;
    size_t lstcap = 1;

    // loop until string lengths
    struct ftstr buf = ftstr_create();
    for (size_t i = 0; i < str->len; ++i) {
        // iterate over the characters
        char c = str->value[i];
        // if current character does not equal the delimiter
        if(c == delim) {
            struct ftstr newstr = ftstr_from_ftstr(&buf);
            DA_APPEND(lst, lstlen, lstcap, struct ftstr, &newstr);
            ftstr_clear(&buf);
            //free(newstr.value);
        }
        else {
            ftstr_append_char(&buf, c);
        }
    }
    if (buf.len != 0) {
        struct ftstr newstr = ftstr_from_ftstr(&buf);
        DA_APPEND(lst, lstlen, lstcap, struct ftstr, &newstr);
    }

    *len = lstlen;
    return lst;
}

void
ftstr_dump(struct ftstr *str) {
    printf("%s", str->value);
}
