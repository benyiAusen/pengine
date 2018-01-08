#ifndef MAP_H
#define MAP_H

#include <tmx.h>

typedef struct
{
    tmx_map *tilemap;
}
map;

void map_init(map *mp);

#endif

