#ifndef FTSTR_H
#define FTSTR_H

#include <unistd.h>

struct ftstr {
    char *value;
    size_t len;
    size_t cap;
};

struct ftstr ftstr_create(void);
struct ftstr ftstr_from_cstr(const char *value);
struct ftstr ftstr_from_ftstr(struct ftstr *value);
void ftstr_append_char(struct ftstr *str, char c);
void ftstr_append_cstr(struct ftstr *str, const char *value);
void ftstr_append_ftstr(struct ftstr *dest, struct ftstr *src);
struct ftstr *ftstr_from_split_on_delim(struct ftstr *str, char delim, size_t *len);
void ftstr_clear(struct ftstr *str);
void ftstr_dump(struct ftstr *str);

#endif // FTSTR_H
