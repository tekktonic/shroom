#ifndef ENTITY_TYPES_H
#define ENTITY_TYPES_H
#include <SDL.h>
#include <stdbool.h>

#include "sprite.h"
#include "window.h"
struct Room_s;

struct Entity_s
{
    void (*react)(struct Entity_s *entity);
    void (*update)(struct Entity_s *entity, int dt);
    void (*draw)(struct Entity_s *entity, SDL_Renderer *renderer, Window window);
    Queue events;

    struct Room_s *room;
    void *data;
};

typedef struct Entity_s *Entity;
struct Room_s
{
    List entities;
    Sprite background;
    SDL_Renderer *renderer;
    Window window;
    int width, height;
    int sox, soy; // screen x and y offsets from the world
    Entity cameraFocus;
    Queue toReact;
};
typedef struct Room_s *Room;

#include "custom_entities.h"

#endif
