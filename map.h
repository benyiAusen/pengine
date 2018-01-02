#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>

const int tile_size;

vec2 map_size;

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
    SDL_Texture *texture;
}
tile;

typedef struct
{
    tile tiles[map_size.x][map_size.y];
}
map;

map_tile_render(tile *tl);

#endif
