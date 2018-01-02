#include "input.h"

unsigned char input_keymarkers[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char *key_states = NULL;

void input_update_keymarkers()
{
    //UP key
    if(key_states[SDL_SCANCODE_UP])
        input_keymarkers[INPUT_KEYUP] = 1;
    else
        input_keymarkers[INPUT_KEYUP] = 0;

    //DOWN key
    if(key_states[SDL_SCANCODE_DOWN])
        input_keymarkers[INPUT_KEYDOWN] = 1;
    else
        input_keymarkers[INPUT_KEYDOWN] = 0;

    //LEFT key
    if(key_states[SDL_SCANCODE_LEFT])
        input_keymarkers[INPUT_KEYLEFT] = 1;
    else
        input_keymarkers[INPUT_KEYLEFT] = 0;

    //RIGHT key
    if(key_states[SDL_SCANCODE_RIGHT])
        input_keymarkers[INPUT_KEYRIGHT] = 1;
    else
        input_keymarkers[INPUT_KEYRIGHT] = 0;

    //ACTION1 key
    if(key_states[SDL_SCANCODE_MINUS])
        input_keymarkers[INPUT_KEYACTION1] = 1;
    else
        input_keymarkers[INPUT_KEYACTION1] = 0;

    //ACTION2 key
    if(key_states[SDL_SCANCODE_Q])
        input_keymarkers[INPUT_KEYACTION2] = 1;
    else
        input_keymarkers[INPUT_KEYACTION2] = 0;
    
    //ACTION3 key
    if(key_states[SDL_SCANCODE_J])
        input_keymarkers[INPUT_KEYACTION3] = 1;
    else    
        input_keymarkers[INPUT_KEYACTION3] = 0;

    //ACTION4 key
    if(key_states[SDL_SCANCODE_K])
        input_keymarkers[INPUT_KEYACTION4] = 1;
    else
        input_keymarkers[INPUT_KEYACTION4] = 0;
    
    //MOD_ESCAPE key
    if(key_states[SDL_SCANCODE_ESCAPE])
        input_keymarkers[INPUT_MOD_ESCAPE] = 1;
    else
        input_keymarkers[INPUT_MOD_ESCAPE] = 0;
}
