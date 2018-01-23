#ifndef GLOBALS_H
#define GLOBALS_H


//multi platform stuff
#ifdef __linux__
#define GLOBAL_ENVCH 'L'

#elif __apple__
#define GLOBAL_ENVCH 'M'

#elif _WIN32
#define _CRT_SECURE_NO_WARNINGS //Silence unneeded Visual C warnings.
#define GLOBAL_ENVCH 'W'
#endif

#include <SDL.h>

extern unsigned char global_has_fatal_error;

extern char *global_program_version;
extern char global_program_envchar;

extern unsigned short global_window_w;
extern unsigned short global_window_h;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern double global_timenow;
extern double global_timelast;
extern double global_deltatime;
extern double global_timefactor;

#endif
