#pragma once

#include <lldos/common.h>

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

typedef struct {
    char *name;
    char *version;
    char *repo;
    char *source;
    bool is_group;
    bool no_package;
    str_list deps;
    str_list mkdeps;
    str_list extras;

} lldos_package;

u32 lldos_package_to_string(lldos_package *pck, char *buffer, u32 max_size);

