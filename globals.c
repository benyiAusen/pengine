#include "globals.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

unsigned char global_has_fatal_error = 0;
double global_timenow = 0;
double global_timelast = 0;
double global_deltatime = 0;
double global_timefactor = 0.083333333333; //1 m/s = 4 blocks/s
