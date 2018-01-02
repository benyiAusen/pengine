#include "map.h"
#include "globals.h"

//Rudimentary tilemap support with support for maps up to 65535 x 65535 tiles big.

const int tile_size = 32;
vec2i map_size;

//vec2i map_size.x = 5;
//vec2i map_size.y = 5;

tile_type test[0xFFFF][0xFFFF] =
{
    {0,0,0,0,1},
    {1,0,0,1,1},
    {0,0,0,0,1},
    {0,0,0,0,1},
    {1,1,1,1,1}
};

void map_tiles_init(map *mp)
{
    for(int y=0; y<map_size.y; y++)
    {
        for(int x=0; x<map_size.x; x++)
        {
            mp->tiles[x][y].pos.x = 32 * x;
            mp->tiles[x][y].pos.y = 32 * x;
            mp->tiles[x][y].type = test[x][y];
            mp->tiles[x][y].texture = utils_load_texture("assets/test1.png");
        }
    }
}

void map_tiles_render(map *mp)
{
    
    for(int y=0; y<map_size.y; y++)
    {
        for(int x=0; x<map_size.x; x++)
        {
            SDL_RenderCopy(renderer, mp->tiles[x][y].texture, NULL, &mp->tiles[x][y].dst);
        }
    }
}

