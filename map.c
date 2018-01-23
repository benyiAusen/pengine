#include "map.h"
#include "utilities.h"
#include "globals.h"

void map_init(map *mp, const char* filename)
{
    mp->tilemap = tmx_load(filename);

    if(!mp->tilemap)
    {
        utils_log_print(UTILS_LOG_TYPE_FATAL, "map_init()", "could not load the target map. ->");
        tmx_perror("tmx_load");
        global_has_fatal_error = 1;
    }
    else
        utils_log_print(UTILS_LOG_TYPE_INFO, "map_init()", "loaded map successfully.");
}

void *map_tmx_imgload_ptr(const char *filename)
{
    return IMG_LoadTexture(renderer, filename);
}

void map_draw_layer(tmx_map *tilemap, tmx_layer *layer)
{
    unsigned int     gid;
    float             op;
    tmx_tileset *tmxtset;
    tmx_image    *tmximg;

    SDL_Rect        src, dst;
    SDL_Texture     *tileset;

    op = layer->opacity;

    for(long y = 0; y < tilemap->height; y++)
    {
        for(long x = 0; x < tilemap->width; x++)
        {
            gid = map_clear_gid_flags(layer->content.gids[ (y * tilemap->width) + x ]);
            if(tilemap->tiles[gid] != 0)
            {
                tmxtset = tilemap->tiles[gid]->tileset;
                tmximg  = tilemap->tiles[gid]->image;

                src.x = tilemap->tiles[gid]->ul_x;
                src.y = tilemap->tiles[gid]->ul_y;

                src.w = dst.w = tmxtset->tile_width;
                src.h = dst.h = tmxtset->tile_height;

                dst.x = x * tmxtset->tile_width;
                dst.y = y * tmxtset->tile_height;

                if(tmximg)
                {
                    tileset = (SDL_Texture*)tmximg->resource_image;
                }
                else
                {
                    tileset = (SDL_Texture*)tmxtset->image->resource_image;
                }
                SDL_RenderCopy(renderer, tileset, &src, &dst);
            }
        }
    }

}

void map_draw_img_layer(tmx_image *img)
{
    SDL_Rect dim;
    dim.x = dim.y = 0;

    SDL_QueryTexture((SDL_Texture*)img->resource_image, NULL, NULL, &(dim.w), &(dim.h));
    SDL_RenderCopy(renderer, (SDL_Texture*)img->resource_image, NULL, &dim);
}

//void

unsigned int map_clear_gid_flags(unsigned int gid)
{
    return gid & TMX_FLIP_BITS_REMOVAL;
}

void map_unload(map *mp)
{
    tmx_map_free(mp->tilemap);
    utils_log_print(UTILS_LOG_TYPE_INFO, "map_unload()", "unloaded map from memory.");
}

