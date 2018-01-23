#include "utilities.h"
#include "globals.h"

void utils_log_print(utils_log_type type, char *function, char *message)
{
	char *str_type;

	switch(type)
	{
	case UTILS_LOG_TYPE_INFO:
		str_type = "INFO";
                break;

	case UTILS_LOG_TYPE_WARNING:
		str_type = "WARNING";
                break;

	case UTILS_LOG_TYPE_ERROR:
		str_type = "ERROR";
                break;

        case UTILS_LOG_TYPE_FATAL:
                str_type = "FATAL";
                break;
	default:
		str_type = "???";
	}
	printf("\n[%s, %s]: %s", function, str_type, message);
}


char *utils_get_version()
{
    static char vbuf[5]; //4 chars + NUL terminator = 5 bytes long.
    
    for(unsigned char i=0; i<4; i++)
        vbuf[i] = global_program_version[i];
    
    //overwrite the 4th char with the platform letter.
    vbuf[4] = global_program_envchar;

    return vbuf;
}

SDL_Texture *utils_load_texture(char *file_path)
{
    SDL_Surface *tmp = IMG_Load(file_path);
    
    if(!tmp)
		utils_log_print(UTILS_LOG_TYPE_ERROR, "*utils_load_texture()", (char*)SDL_GetError());
	else
		utils_log_print(UTILS_LOG_TYPE_INFO, "main_init_program()", "image loaded.");
    
    SDL_Texture *tmp2 = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    return tmp2;
}
