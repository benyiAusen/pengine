#include "map.h"
#include "utilities.h"
#include "globals.h"

void map_init(map *mp)
{
    mp->tilemap = tmx_load("assets/test_map.tmx");

    if(!mp->tilemap)
        utils_log_print(UTILS_LOG_TYPE_ERROR, "map_init()", "FATAL - could not load the target map.");
}
