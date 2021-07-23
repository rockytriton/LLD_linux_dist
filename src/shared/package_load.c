#include <lldos/package.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

#include <yaml.h>

/* Structure for YAML document:

name: glibc
version: 2.33
repo: core
is_group: false
no_source: false
source: http://ftp.gnu.org/gnu/glibc/glibc-2.33.tar.xz
deps: [

]
mkdeps: [
    
]
extras: [
    'http://www.linuxfromscratch.org/patches/lfs/10.1/glibc-2.33-fhs-1.patch',
    'https://www.iana.org/time-zones/repository/releases/tzdata2021a.tar.gz'
]

*/

typedef enum {
    INIT, KEY, VALUE, DEP, MKDEP, EXTRA
} parser_state;

void set_field_value(lldos_package *pck, char *name, char *value) {
    if (!strcmp(name, "name")) {
        pck->name = strdup(value);
    } else if (!strcmp(name, "version")) {
        pck->version = strdup(value);
    } else if (!strcmp(name, "repo")) {
        pck->repo = strdup(value);
    } else if (!strcmp(name, "source")) {
        pck->source = strdup(value);
    } else if (!strcmp(name, "is_group")) {
        pck->is_group = !strcmp(value, "true");
    } else if (!strcmp(name, "no_package")) {
        pck->no_package = !strcmp(value, "true");
    } else if (!strcmp(name, "deps")) {
        str_list_append(&pck->deps, value);
    } else if (!strcmp(name, "mkdeps")) {
        str_list_append(&pck->mkdeps, value);
    } else if (!strcmp(name, "extras")) {
        str_list_append(&pck->extras, value);
    }
}

lldos_package *parse_package(char *filename) {
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        perror("Failed to open package file");
        return 0;
    }

    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        perror("Failed to init parser!");
        fclose(fp);
        return 0;
    }

    yaml_parser_set_input_file(&parser, fp);

    lldos_package *pck = malloc(sizeof(lldos_package));

    if (!pck) {
        perror("Failed to allocate package");
        return 0;
    }

    memset(pck, 0, sizeof(lldos_package));

    parser_state state = INIT;
    char cur_field[1024];

    do {
        yaml_parser_scan(&parser, &token);

        switch(token.type) {
            case YAML_KEY_TOKEN: {
                state = KEY;
            } break;

            case YAML_VALUE_TOKEN: {
                state = VALUE;
            } break;

            case YAML_SCALAR_TOKEN: {
                char *data = token.data.scalar.value;

                if (state == KEY) {
                    snprintf(cur_field, sizeof(cur_field) - 1, "%s", data);
                } else if (state == VALUE) {
                    set_field_value(pck, cur_field, data);
                }
            }
        }
    } while(token.type != YAML_STREAM_END_TOKEN);

    fclose(fp);

    return pck;
}

lldos_package *package_load(char *root, char *name) {
    char full_path[1024];
    snprintf(full_path, sizeof(full_path) - 1, "%s/repo/%c/%s/.pck", root, *name, name);

    lldos_package *pck = parse_package(full_path);

    return pck;
}
