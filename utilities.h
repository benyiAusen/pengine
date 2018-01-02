#ifndef UTILITIES_H
#define UTILITIES_H

//"utilities.h": Contains all necessary headers and global functions for the entire program.

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#define utils_array_size(a) sizeof(a)/sizeof(a[0])

typedef enum
{
	UTILS_LOG_TYPE_INFO,
	UTILS_LOG_TYPE_WARNING,
	UTILS_LOG_TYPE_ERROR
}
utils_log_type;

typedef struct
{
    double x, y;
}
vec2;

void utils_clear_uint8_array(unsigned char *array);
void utils_log_print(utils_log_type type, char *function, char *message);
SDL_Texture *utils_load_texture(char *file_path);

#endif
