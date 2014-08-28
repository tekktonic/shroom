#ifndef SPRITE_H
#define SPRITE_H
#include <stdlib.h>
#include <SDL.h>
#include <math.h>

#include "resourcemanager.h"

typedef struct
{
    SDL_Texture *image;
    SDL_Rect rect;
} Sprite;

Sprite new_Sprite(ResourceManager rm, const char *image);
#endif
