#include "main.h"
#include "utilities.h"
#include "globals.h"
#include "input.h"
#include "entities.h"
#include "map.h"

int main(int argc, char **argv)
{
    //initialization
    main_init_program();

    entity k;
    entity_init(&k);
    


    while(main_is_running)
    {
        //update deltatime
        global_timelast = global_timenow;
        global_timenow = SDL_GetPerformanceCounter();
        global_deltatime = ((global_timenow - global_timelast) * 1000 / (double)SDL_GetPerformanceFrequency()) * global_timefactor;
        
        //update events
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                main_is_running = 0;
            default:
                break;
            }
        }

        //update
        key_states = (unsigned char*)SDL_GetKeyboardState(NULL);
        input_update_keymarkers();
       
        entity_update(&k);

        //logic
        if(input_keymarkers[INPUT_MOD_ESCAPE])
            main_is_running = 0;

        //rendering
        SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x40, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	entity_render(&k);

        SDL_RenderPresent(renderer);
    }

    main_quit_program();
    return 0;
}

void main_init_program()
{
    char welcome_msg[60];    
    sprintf(welcome_msg, "platformer WIP engine version %s, running on %s.", MAIN_VERSION, MAIN_ENV);

    utils_log_print(UTILS_LOG_TYPE_INFO, "main_init_program()", welcome_msg);    

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        utils_log_print(UTILS_LOG_TYPE_ERROR, "main_init_program()", (char*)SDL_GetError());
    else
        utils_log_print(UTILS_LOG_TYPE_INFO, "main_init_program()", "SDL2 online.");

    IMG_Init(IMG_INIT_PNG);
    utils_log_print(UTILS_LOG_TYPE_INFO, "main_init_program()", "SDL2 Image online.");

    main_is_running = 1;
    SDL_GetPerformanceCounter();

    window = SDL_CreateWindow( "SDL Platformer in C", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 600, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void main_quit_program()
{
    utils_log_print(UTILS_LOG_TYPE_INFO, "main_init_program()", "terminating main program. goodbye.\n");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
