#include "SDL.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lua.h"

#include "stdlib.h"
#include "math.h"

#define PI 3.14159265
#define WIDTH 640
#define HEIGHT 480

#define MAX_BOX 32
#define LOOP_BOX() for(int i=0; i < MAX_BOX; i++)

typedef struct
{
  double x;
  double y;
} VECTOR3;

int main(int argc, char **argv)
{

  VECTOR3 center;
  center.x = WIDTH/2;
  center.y = HEIGHT/2;

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      SDL_Log("SDL_Init(SDL_INIT_EVERYTHING) failed: %s", SDL_GetError());
      return 1;
  }
  printf("[!] SDL Initialized.\n");
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE|SDL_WINDOW_MAXIMIZED, &window, &renderer);


  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  luaL_dofile(L, "test.lua");
  lua_close(L);


  SDL_Rect rect, background;
  rect.x = 0;
  rect.y = 0;
  rect.w = 5;
  rect.h = 5;

  background.x = 0;
  background.y = 0;
  background.w = WIDTH;
  background.h = HEIGHT;

  double  degree, rot, val, radius, angle;
  radius = 100.0;
  val = (PI / 180); // TWO_PI
  degree = 360 / (MAX_BOX);
  while(1)
  {
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT) break;

    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0x00);
    SDL_RenderFillRect(renderer, &background);

    angle = 0;
    while(angle <= MAX_BOX)
    {
      SDL_SetRenderDrawColor(renderer,0xFF,0x00,0x00,0xFF);
      SDL_RenderFillRect(renderer, &rect);

      rect.x = center.x + radius * sin( (degree * val)*angle );
      rect.y = center.y + radius * cos( (degree * val)*angle );
      angle++;
    }

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
