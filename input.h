//"input.h": Abstraction layer for hardware input scancodes.

#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

enum input_keydefs
{
    INPUT_KEYUP,
    INPUT_KEYDOWN,
    INPUT_KEYLEFT,
    
    INPUT_KEYRIGHT,
    INPUT_KEYACTION1,
    INPUT_KEYACTION2,
    
    INPUT_KEYACTION3,
    INPUT_KEYACTION4,
    INPUT_MOD_ESCAPE,

    INPUT_MOD_F1,
    INPUT_MOD_F2,
    INPUT_MOD_F3,

    INPUT_MOD_F4,
    INPUT_MOD_F5,
    INPUT_MOD_F6
};

unsigned char input_keymarkers[15];
unsigned char *key_states; //=NULL

void input_update_keymarkers();

#endif
