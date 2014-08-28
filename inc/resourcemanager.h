#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "dtype.h"
#include "err.h"
#include "globals.h"

#define new_ResourceManager new_Hash
typedef Hash ResourceManager;
SDL_Texture *ResourceManager_load_image(ResourceManager rm, const char *image);

#endif
