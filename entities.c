#include "entities.h"
#include "globals.h"
#include "input.h"

double gravity = 9.819625466667;
double friction = 0.961746494023;


void entity_aabb_init(aabb *box, vec2 c, vec2 h)
{
    box->center = c;
    box->halfsize = h;
}

unsigned char entity_aabb_test(aabb *box)
{
    if ( fabs(box->center.x - box->center.x) > box->halfsize.x + box->halfsize.x ) return 0;
    if ( fabs(box->center.y - box->center.y) > box->halfsize.y + box->halfsize.y ) return 0;
    return 1;
}

void entity_init(entity *ent)
{
    ent->tex = utils_load_texture("assets/img/test0.png");
    ent->curr_pos.x = 0;
    ent->curr_pos.y = 0;
    ent->box.halfsize.x = 16, ent->box.halfsize.y = 16;
    ent->dst.w = 2 * ent->box.halfsize.x;
    ent->dst.h = 2 * ent->box.halfsize.y;
    ent->dst.x = ent->curr_pos.x;
    ent->dst.y = ent->curr_pos.y;
}

void entity_update(entity *ent)
{
    ent->prev_pos = ent->curr_pos;
    ent->prev_vel = ent->curr_vel;

    ent->state[ENTITY_STATE_WAS_ON_GROUND] = ent->state[ENTITY_STATE_IS_ON_GROUND];
    ent->state[ENTITY_STATE_WAS_ON_CEILING] = ent->state[ENTITY_STATE_IS_ON_CEILING];
    ent->state[ENTITY_STATE_PUSHED_LEFT] = ent->state[ENTITY_STATE_PUSHES_LEFT];
    ent->state[ENTITY_STATE_PUSHED_RIGHT] = ent->state[ENTITY_STATE_PUSHES_RIGHT];

    ent->curr_pos.x += ent->curr_vel.x * global_deltatime;
    ent->curr_pos.y += ent->curr_vel.y * global_deltatime;

    if (ent->curr_pos.y > 576)
    {
        ent->curr_pos.y = 576;
        ent->state[ENTITY_STATE_IS_ON_GROUND] = 1;
    }
    else
        ent->state[ENTITY_STATE_IS_ON_GROUND] = 0;
    
    ent->box.center.x = ent->curr_pos.x + ent->box_offset.x;
    ent->box.center.y = ent->curr_pos.y + ent->box_offset.y;

    
    if(input_keymarkers[INPUT_KEYUP])
        ent->curr_vel.y = -gravity * 2;
    else
        ent->curr_vel.y = gravity;

    if(input_keymarkers[INPUT_KEYLEFT])
        ent->curr_vel.x = -4;
    else if(input_keymarkers[INPUT_KEYRIGHT])
        ent->curr_vel.x = 4;
    else
        ent->curr_vel.x = 0;
    
    ent->dst.x = ent->curr_pos.x;
    ent->dst.y = ent->curr_pos.y;
}

void entity_render(entity *ent)
{
    SDL_RenderCopy(renderer, ent->tex, NULL, &ent->dst);
}
