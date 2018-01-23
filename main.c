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

    map g;
    map_init(&g, "assets/map/map0.tmx");

    while(main_is_running)
    {
        //check if a fatal error has happened, and quit if it has
        if(global_has_fatal_error)
        {
            utils_log_print(UTILS_LOG_TYPE_INFO, "main()", "closing due to fatal error...");
            main_quit_program();
            return 1;
        }

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
        map_draw(&g);
	entity_render(&k);

        SDL_RenderPresent(renderer);
    }

    main_quit_program();
    return 0;
}

void main_init_program()
{
    char welcome_msg[60];    
    sprintf(welcome_msg, "pengine: SDL2 Platformer written in C, version %s", utils_get_version());

    utils_log_print(UTILS_LOG_TYPE_INFO, "main_init_program()", welcome_msg);    

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        utils_log_print(UTILS_LOG_TYPE_FATAL, "main_init_program()", (char*)SDL_GetError());
        global_has_fatal_error = 1;
    }
    else
        utils_log_print(UTILS_LOG_TYPE_INFO, "main_init_program()", "SDL2 online.");

    IMG_Init(IMG_INIT_PNG);
    utils_log_print(UTILS_LOG_TYPE_INFO, "main_init_program()", "SDL2 Image online.");

    main_is_running = 1;
    SDL_GetPerformanceCounter();

    window = SDL_CreateWindow( "pengine: SDL Platformer Engine written in C", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, global_window_w, global_window_h, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    tmx_img_load_func = (void*(*)(const char*))map_tmx_imgload_ptr;
    tmx_img_free_func = (void (*)(void*))      SDL_DestroyTexture;
}

void main_quit_program()
{
    utils_log_print(UTILS_LOG_TYPE_INFO, "main_quit_program()", "terminating main program. goodbye.\n");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
