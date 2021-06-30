#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef struct str_list_ {
    char *str;
    struct str_list_ *next;
} str_list;

str_list *str_list_append(str_list *l, char *s);
void str_list_copy(str_list *to, str_list *from);
str_list *str_list_from_str(char *str, char *sep);
void str_list_free(str_list *l, bool free_head);

bool create_package_path(char *root, char *name);
