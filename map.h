#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include "utilities.h"

const int tile_size;

vec2i map_size;

typedef enum
{
    TILE_EMPTY,
    TILE_SOLID,
    TILE_ONEWAY
}
tile_type;

typedef struct
{
    vec2 pos;
    tile_type type;
    SDL_Rect dst;
    SDL_Texture *texture;
}
tile;

typedef struct
{
    tile tiles[0xFFFF][0xFFFF];
}
map;

void map_tiles_init(map *mp);
void map_tiles_render(map *mp);

#endif
