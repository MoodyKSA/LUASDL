#include "SDL.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lua.h"

int main(int argc, char **argv)
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("SDL_Init(SDL_INIT_EVERYTHING) failed: %s", SDL_GetError());
        return 1;
    }
	printf("[!] SDL Initialized.\n");

	SDL_CreateWindowAndRenderer(320,240, SDL_WINDOW_RESIZABLE, &window, &renderer);

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "test.lua");    
	lua_close(L);

	while(0)
	{
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT) break;

		SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0x00);
		SDL_RenderPresent(renderer);
	}

	SDL_Delay(3000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
