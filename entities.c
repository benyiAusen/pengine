#include "entities.h"
#include "globals.h"
#include "input.h"
#include "camera.h"
#include "utilities.h"

#define WALK_SPEED 6
#define GRAV_ACCEL 1
#define FALL_SPEED 12

void ent_init_player(ent_player *pyr, double x, double y)
{
    pyr->tx_src.x = pyr->tx_src.y = 0;
    pyr->tx_src.w = pyr->tx_src.h = pyr->tx_dst.w = pyr->tx_dst.h = 32;
    pyr->c_pos.x = x;
    pyr->c_pos.y = y;
    
    pyr->bbox.halfsize.x = 16;
    pyr->bbox.halfsize.y = 16;
    pyr->bbox_offset.y = pyr->bbox.halfsize.y;

    pyr->state = ENT_PLAYER_STANDING;
    pyr->iog = 1;
    pyr->sheet = utils_load_texture("assets/img/test0.png");
}

void ent_init_block(ent_block *block, unsigned char id, double x, double y)
{

}

void ent_init_sprite(ent_sprite *spr, unsigned char id, double x, double y)
{
    spr->type  = id;
    spr->c_pos.x = x;
    spr->c_pos.y = y;

    switch(spr->type)
    {
        case ENT_SPRITE_CAMERA:
            utils_log_print(UTILS_LOG_TYPE_INFO, "ent_init_sprite()","initialized ENT_SPRITE_CAMERA.");
            break;

        case ENT_SPRITE_HANDLER:
            utils_log_print(UTILS_LOG_TYPE_INFO, "ent_init_sprite()","initialized ENT_SPRITE_HANDLER.");
            break;

        default:
            utils_log_print(UTILS_LOG_TYPE_ERROR, "ent_init_sprite()","could not initialize sprite: invalid sprite type");
            break;
    }
}


void ent_update_player(ent_player *pyr)
{
    //step 1: physical integration
    pyr->tx_dst.x = level_cam.c_pos.x + pyr->c_pos.x;
    pyr->tx_dst.y = level_cam.c_pos.y + pyr->c_pos.y;

    //PAST       PRESENT
    pyr->p_pos = pyr->c_pos;
    pyr->p_vel = pyr->c_vel;

    pyr->wog =   pyr->iog;
    pyr->prw =   pyr->Prw;
    pyr->plw =   pyr->Plw;
    pyr->wac =   pyr->iac;

    pyr->c_pos.x += pyr->c_vel.x * global_deltatime;
    pyr->c_pos.y += pyr->c_vel.y * global_deltatime;


    pyr->bbox.center.x = pyr->c_pos.x + pyr->bbox_offset.x;
    pyr->bbox.center.y = pyr->c_pos.y + pyr->bbox_offset.y;
    
    //step 2: state-dependent actions
    switch(pyr->state)
    {
        case ENT_PLAYER_STANDING:
            if(!pyr->iog)
            {
                pyr->state = ENT_PLAYER_JUMPING;
                break;
            }
            if(input_keymarkers[INPUT_KEYLEFT] ^ input_keymarkers[INPUT_KEYRIGHT])
            {
                pyr->state = ENT_PLAYER_WALKING;
                break;
            }
            if(input_keymarkers[INPUT_KEYUP] && pyr->iog)
            {
                pyr->iog = 0;
                pyr->c_vel.y = -2 * FALL_SPEED;
                pyr->state = ENT_PLAYER_JUMPING;
                break;
            }
            
            pyr->c_vel.x = 0;

            break;
        
        case ENT_PLAYER_WALKING:
            if(!pyr->iog)
            {
                pyr->state = ENT_PLAYER_JUMPING;
                break;
            }
            if(input_keymarkers[INPUT_KEYLEFT] == input_keymarkers[INPUT_KEYRIGHT])
            {
                pyr->state = ENT_PLAYER_STANDING;
                break;
            }
            
            if(input_keymarkers[INPUT_KEYUP] && pyr->iog)
            {
                pyr->iog = 0;
                pyr->c_vel.y = -2 * FALL_SPEED;
                pyr->state = ENT_PLAYER_JUMPING;
                break;
            }
            
            if(input_keymarkers[INPUT_KEYLEFT])
            {
                pyr->c_vel.x = -5;
            }
            else if(input_keymarkers[INPUT_KEYRIGHT])
            {
                pyr->c_vel.x = 5;
            }
            break;

        case ENT_PLAYER_JUMPING:
            if(pyr->iog)
            {
                if(input_keymarkers[INPUT_KEYLEFT] == input_keymarkers[INPUT_KEYRIGHT])
                    pyr->state = ENT_PLAYER_STANDING;
                else
                    pyr->state = ENT_PLAYER_WALKING;
                break;
            }

            pyr->c_vel.y += GRAV_ACCEL * global_deltatime;
            
            if(pyr->c_vel.y > FALL_SPEED)
                pyr->c_vel.y = FALL_SPEED;
            
            if(pyr->c_pos.y > global_window_h - 32)
            {
                pyr->c_vel.y = 0;
                pyr->iog = 1;
            }
            
            if(input_keymarkers[INPUT_KEYLEFT] == input_keymarkers[INPUT_KEYRIGHT])
            {
                pyr->c_vel.x = 0;
            }
            if(input_keymarkers[INPUT_KEYLEFT])
            {
                pyr->c_vel.x = -WALK_SPEED;
            }
            else if(input_keymarkers[INPUT_KEYRIGHT])
            {
                pyr->c_vel.x = WALK_SPEED;
            }
            break;

        case ENT_PLAYER_HANGING:

            break;

        default:
            break;
    }
}

void ent_update_block(ent_block *blk)
{
    
}

void ent_update_sprite(ent_sprite *spr)
{
    //step 1: physical integration
    spr->tx_dst.x = spr->c_pos.x;
    spr->tx_dst.y = spr->c_pos.y;

    //PAST       PRESENT
    spr->p_pos = spr->c_pos;
    spr->p_vel = spr->c_vel;

    spr->wog =   spr->iog;
    spr->prw =   spr->Prw;
    spr->plw =   spr->Plw;
    spr->wac =   spr->iac;

    spr->c_pos.x += spr->c_vel.x * global_deltatime;
    spr->c_pos.y += spr->c_vel.y * global_deltatime;


    spr->bbox.center.x = spr->c_pos.x + spr->bbox_offset.x;
    spr->bbox.center.y = spr->c_pos.y + spr->bbox_offset.y;
 
    switch(spr->type)
    {
        case ENT_SPRITE_CAMERA:

            if(input_keymarkers[INPUT_KEYLEFT])
                spr->c_pos.x += 6 * global_deltatime;
            else if(input_keymarkers[INPUT_KEYRIGHT])
                spr->c_pos.x -= 6 * global_deltatime;
            break;
        
        case ENT_SPRITE_HANDLER:
            break;

        default:
            break;
    }
}

void ent_render(void *ent, ent_class class) //unsafe code lol. i'll add bounds checking when everything is ready.
{
    switch(class)
    {
        case ENT_PLAYER:
            SDL_RenderCopy(renderer, ((ent_player*)ent)->sheet, &((ent_player*)ent)->tx_src, &((ent_player*)ent)->tx_dst);
            break;

        case ENT_BLOCK:
            SDL_RenderDrawRect(renderer, &((ent_block*)ent)->drawbox);
            break;

        case ENT_SPRITE:
            switch(((ent_sprite*)ent)->type)
            {
                case ENT_SPRITE_CAMERA:
                case ENT_SPRITE_HANDLER:
                    break;

                default:
                    SDL_RenderCopy(renderer, ((ent_sprite*)ent)->sheet, &((ent_sprite*)ent)->tx_src, &((ent_sprite*)ent)->tx_dst);
                    break;
            }
            break;
    }
}

void ent_init_aabb(aabb *aabb, double xctr, double yctr, double xhls, double yhls)
{
    aabb->center.x = xctr;
    aabb->center.y = yctr;
    aabb->halfsize.x = xhls;
    aabb->halfsize.y = yhls;
}

unsigned char ent_test_aabb(aabb *A, aabb *B)
{
    if( fabs(A->center.x - B->center.x) > (A->halfsize.x + B->halfsize.x))
        return 0;
    if( fabs(A->center.y - B->center.y) > (A->halfsize.y + B->halfsize.y))
        return 0;
    return 1;
}

