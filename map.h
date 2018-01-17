#ifndef MAP_H
#define MAP_H

#include <tmx.h>

typedef struct
{
    SDL_Texture *tileset_src;
    tmx_map     *tilemap;
    unsigned char     id;
}
map;

void map_init(map *mp, const char *filename);

//I have to use function pointers due to the way tmxlib works. i'll make a wrapper someday to ease readability.
void *map_tmx_imgload_ptr(const char *filename);
void map_draw_layer(tmx_map *tilemap, tmx_layer *layer);
void map_draw_img_layer(tmx_image *img);
void map_clear_gid_flags(unsigned int gid);
void map_unload(map *mp);

#endif

