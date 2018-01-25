#ifndef ENTITY_H
#define ENTITY_H

//"entities.h": Contains all the needed code and data for a dynamic entity type.

#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include "utilities.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef enum
{
    ENT_PLAYER,
    ENT_BLOCK,
    ENT_SPRITE
}ent_class;

enum
{
    ENT_PLAYER_STANDING,
    ENT_PLAYER_JUMPING,
    ENT_PLAYER_WALKING,
    ENT_PLAYER_HANGING
};

enum
{
    ENT_BLOCK_SOLID,
    ENT_BLOCK_ONEWAY,
    ENT_BLOCK_DEATH
};

enum
{
    ENT_SPRITE_CAMERA,
    ENT_SPRITE_HANDLER,
    ENT_SPRITE_ENEMY1,
    ENT_SPRITE_ENEMY2,
    ENT_SPRITE_POWERUP
};

typedef struct
{
    vec2 center;
    vec2 halfsize;
}
aabb;

//There are three kinds of objects in this engine:

//Player: Controllable entities. Players interact with sprites or other players and collide the world map for movement and support.
typedef struct
{
    unsigned char state;
    unsigned char   prw; //p: pushed, P: Pushes | lw: left wall, rw: right wall | w: was, i: is | og: on ground, ac: at ceiling
    unsigned char   Prw;

    unsigned char   plw;
    unsigned char   Plw;

    unsigned char   wog;
    unsigned char   iog;

    unsigned char   wac;
    unsigned char   iac;
    
    vec2          p_pos;
    vec2          c_pos;

    vec2          p_vel;
    vec2          c_vel;
    
    aabb           bbox;
    vec2    bbox_offset;

    SDL_Rect     tx_dst;
    SDL_Rect     tx_src;
    SDL_Texture  *sheet;
}
ent_player;

//Block: Objects of the world map. They interact with both players and sprites.
typedef struct
{
    unsigned char  type;
    vec2          c_pos;
    
    aabb           bbox;
    SDL_Rect    drawbox;
}
ent_block;

//Sprite: Dynamic entity that interacts with the player, other sprites or the world.
typedef struct
{
    unsigned char  type;
    unsigned char state;

    unsigned char   plw;
    unsigned char   Plw;

    unsigned char   prw;
    unsigned char   Prw;

    unsigned char   wog;
    unsigned char   iog;

    unsigned char   wac;
    unsigned char   iac;

    vec2          p_pos;
    vec2          c_pos;

    vec2          p_vel;
    vec2          c_vel;

    aabb           bbox;
    vec2    bbox_offset;

    SDL_Rect     tx_dst;
    SDL_Rect     tx_src;
    SDL_Texture  *sheet;
}
ent_sprite;




void ent_init_player(ent_player *pyr, double x, double y);
void ent_init_block(ent_block *blk, unsigned char id, double x, double y);
void ent_init_sprite(ent_sprite *spr, unsigned char id, double x, double y);

void ent_update_player(ent_player *pyr);
void ent_update_block(ent_block *blk);
void ent_update_sprite(ent_sprite *spr);

void ent_render(void *ent, ent_class class);

void ent_init_aabb(aabb *aabb, double xctr, double yctr, double xhls, double yhls);
unsigned char ent_test_aabb(aabb *A, aabb *B);

#endif

