#include <stdbool.h>
#include <SDL.h>

#include "err.h"
#include "dtype.h"
#include "resourcemanager.h"
#include "sprite.h"
#include "globals.h"
#include "window.h"
#include "room.h"
#include "event.h"

#include "direction.h"


int main(void)
{
    bool running = true;
    SDL_Event e;
    // I could do SDL_CreateWindowAndRenderer, but then I lose the ability to use Maybes

    Window window;


    ResourceManager rm;

    SDL_Texture *bg;
    Sprite cursor;

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS);
    atexit(&SDL_Quit);

    window = new_Window(Maybe(SDL_CreateWindow("RPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE), ESDL));
    renderer = Maybe(SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED), ESDL);

    rm = Maybe(new_ResourceManager(), ENORMAL);
    SDL_ShowCursor(0);
    
    bg = ResourceManager_load_image(rm, "savanna.jpg");
    cursor = new_Sprite(rm, "cursor.png");
//    Room room = Maybe(new_Room(renderer, rm, window, new_Sprite(rm, "bg.png"), "resources/maps/1.json"), ENORMAL);

//    Entity player = room->entities->car;

    while (running)
    {
	const uint8_t *keystate;
	while (SDL_PollEvent(&e))
	{
	    switch (e.type) {
	    case SDL_QUIT:
		running = false;
		break;
	    case SDL_WINDOWEVENT:

		if (e.window.event != SDL_WINDOWEVENT_RESIZED)
		{
		    Window_ResizedCB(window);
		}
		break;
	    }
	}

	SDL_GetMouseState(&cursor.rect.x, &cursor.rect.y);
	SDL_RenderCopy(renderer, bg, NULL, NULL);
	SDL_RenderCopy(renderer, cursor.image, NULL, &cursor.rect);//&cursorPos);
	SDL_RenderPresent(renderer);
    
	SDL_Delay(1000 / 60);

    }
    SDL_DestroyWindow(window->window);

    return 0;
}
