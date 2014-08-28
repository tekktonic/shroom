#include "resourcemanager.h"


SDL_Texture *ResourceManager_load_image(ResourceManager rm, const char *image)
{
    size_t path_size = strlen(image) + strlen("resources/images/") + 1;
    char *path = malloc(path_size);

    strncpy(path, "resources/images/", path_size);
    strncat(path, image, path_size);

    if (!Hash_get(rm, image))
    {
	Hash_insert(rm, image, 
		    (void*)Maybe(IMG_LoadTexture(renderer, path), ESDL));
    }

    return (SDL_Texture*)Hash_get(rm, image);
}
