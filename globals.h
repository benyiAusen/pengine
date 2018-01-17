#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>

extern unsigned char global_has_fatal_error;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern double global_timenow;
extern double global_timelast;
extern double global_deltatime;
extern double global_timefactor;

#endif
