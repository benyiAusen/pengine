#ifndef MAIN_H
#define MAIN_H

//"main.h": Contains the core functions and variables of the system core.

#include <SDL.h>
#include <SDL_image.h>

#define MAIN_VERSION "1.0"

    #ifdef __linux__
    #define MAIN_ENV "Linux"

    #elif __apple__
    #define MAIN_ENV "macOS"

    #elif _WIN32
    #define MAIN_ENV "Windows"
    #define _CRT_SECURE_NO_WARNINGS

#endif

SDL_Event event;
unsigned char main_is_running;

void main_init_program();
void main_quit_program();

#endif
