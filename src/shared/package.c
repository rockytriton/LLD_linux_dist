#include <lldos/package.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

void copy_str_list(str_list *l, char *buffer) {
    while(l && l->str) {
        strcat(buffer, "  '");
        strcat(buffer, l->str);
        strcat(buffer, "',\n");

        l = l->next;
    }
}

u32 lldos_package_to_string(lldos_package *pck, char *buffer, u32 max_size) {
    char str_deps[2048];
    char str_mkdeps[2048];
    char str_extras[2048];
    
    strcpy(str_deps, "");
    strcpy(str_mkdeps, "");
    strcpy(str_extras, "");

    copy_str_list(&pck->deps, str_deps);
    copy_str_list(&pck->mkdeps, str_mkdeps);
    copy_str_list(&pck->extras, str_extras);

    return snprintf(buffer, max_size, 
        "name: %s\n"
        "version: %s\n"
        "repo: core\n"
        "source: %s\n"
        "is_group: %s\n"
        "no_package: %s\n"
        "deps: [\n"
        "%s\n"
        "]\n"
        "mkdeps: [\n"
        "%s\n"
        "]\n"
        "extras: [\n"
        "%s\n"
        "]\n",
        pck->name, pck->version, pck->source, (pck->is_group ? "true" : "false"), 
        (pck->no_package ? "true" : "false"), str_deps, str_mkdeps, str_extras
        );
}
