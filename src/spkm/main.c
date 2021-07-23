//Simple Package Manager
#include <lldos/package.h>
#include <stdio.h>

int main(int argc, char **argv) {
    printf("LLDOS Simple Package Manager v1.0.0\n");

    package_list list = {0};

    if (!package_load_all("/lld/LLD_linux_dist", &list)) {
        fprintf(stderr, "Failed to load packages!\n");
        return -1;
    }

    for (package_list_entry *e = list.head; e != NULL; e = e->next) {
        printf("Package: %s %s\n", e->pck->name, e->pck->version);
        printf("\tSource: %s\n", e->pck->source);

        if (e->pck->deps.str) {
            printf("\tDeps:\n");

            for (str_list *l = &e->pck->deps; l && l->str; l = l->next) {
                printf("\t\t- %s\n", l->str);
            }
        }

        printf("\n");
    }
}
