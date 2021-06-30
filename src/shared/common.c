#include <lldos/common.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

str_list *str_list_append(str_list *l, char *s) {
    if (!l) {
        return 0;
    }

    if (!l->str) {
        l->str = strdup(s);
        return l;
    }

    while(l) {
        if (!l->next) {
            l->next = malloc(sizeof(str_list));
            l->next->next = 0;
            l->next->str = strdup(s);

            return l->next;
        }

        l = l->next;
    }
}

void str_list_free(str_list *l, bool free_head) {
    if (!l) {
        return;
    }

    if (l->str) {
        free(l->str);
    }

    str_list *p = l->next;

    if (free_head) {
        free(l);
    }

    while(p) {
        str_list *cur = p;

        if (p->str) {
            free(p->str);
        }

        p = p->next;

        free(cur);
    }
}

void str_list_copy(str_list *to, str_list *from) {
    to->str = strdup(from->str);

    str_list *lf = from->next;
    str_list *lt = to;

    while(lf) {
        lt = malloc(sizeof(str_list));
        to->next = lt;
        lt->str = strdup(lf->str);
        to = lt;

        lf = lf->next;
    }
}

str_list *str_list_from_str(char *str, char *sep) {
    if (!str || strlen(str) < 1) {
        return 0;
    }

    str_list *list = malloc(sizeof(str_list));
    str_list *head = list;

    list->next = 0;
    char *tok = strtok(str, sep);

    while(tok) {
        list->str = strdup(tok);

        tok = strtok(NULL, sep);

        if (!tok) {
            break;
        }

        str_list *next = malloc(sizeof(str_list));
        next->next = NULL;
        next->str = NULL;
        list->next = next;

        list = next;
    }

    return head;
}

bool create_package_path(char *root, char *name) {
    char path[1024];
    sprintf(path, "%s/repo/%c", root, name[0]);

    if (access(path, F_OK) != 0) {
        if (mkdir(path, 0775)) {
            fprintf(stderr, "Failed to create repo path\n");
            return false;
        }
    }

    sprintf(path, "%s/repo/%c/%s", root, name[0], name);

    if (access(path, F_OK) != 0) {
        if (mkdir(path, 0775)) {
            fprintf(stderr, "Failed to create repo path\n");
            return false;
        }
    }

    return true;
}
