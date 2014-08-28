#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

void *Maybe(void *thing, char sdl)
{
    if (thing == NULL)
    {
	if (sdl)
	    fprintf(stderr, "Fatal SDL Error: %s\n", SDL_GetError());
	else
	    fprintf(stderr, "Fatal error, but unable to give more information\n");
	exit(1);
	return NULL; // not reached but prevents compiler warnings
    }
    return thing;
}
