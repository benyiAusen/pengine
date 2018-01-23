#ifndef MAIN_H
#define MAIN_H

//"main.h": Contains the core functions and variables of the system core.

#include <SDL.h>
#include <SDL_image.h>


SDL_Event event;
unsigned char main_is_running;

void main_init_program();
void main_quit_program();

#endif
