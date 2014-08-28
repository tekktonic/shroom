#include "sprite.h"

Sprite new_Sprite(ResourceManager rm, const char *image)
{
    Sprite sprite;
    sprite.image = ResourceManager_load_image(rm, image);
    SDL_QueryTexture(sprite.image, NULL, NULL, &sprite.rect.w, &sprite.rect.h);
    return sprite;
}
