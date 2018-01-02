#ifndef ENTITY_H
#define ENTITY_H

//"entities.h": Contains all the needed code and data for a dynamic entity type.

#include <math.h>
#include <SDL.h>
#include <SDL_image.h>

double gravity;
double friction;

enum entity_states
{
    ENTITY_STATE_PUSHES_LEFT,
    ENTITY_STATE_PUSHED_LEFT,
    ENTITY_STATE_PUSHES_RIGHT,
    ENTITY_STATE_PUSHED_RIGHT,
    ENTITY_STATE_WAS_ON_GROUND,
    ENTITY_STATE_IS_ON_GROUND,
    ENTITY_STATE_WAS_ON_CEILING,
    ENTITY_STATE_IS_ON_CEILING
};

typedef struct
{
    double x, y;
}
vec2;

typedef struct
{
    vec2 center, halfsize;
}
aabb;

typedef struct
{
    SDL_Texture *tex;
    SDL_Rect dst;
    unsigned char state[8];
    aabb box;
    vec2 box_offset;

    vec2 prev_pos, curr_pos;
    vec2 prev_vel, curr_vel;

    vec2 scale;
}
entity;

void entity_aabb_init(aabb *box, vec2 c, vec2 h);
unsigned char entity_aabb_test(aabb *box);
void entity_init(entity *ent);
void entity_update(entity *ent);
void entity_render(entity *ent);

#endif

