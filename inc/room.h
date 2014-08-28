#ifndef ROOM_H
#define ROOM_H
#include <jansson.h>

#include "dtype.h"
#include "window.h"
#include "entity_types.h"

#include "sprite.h"

#include "resourcemanager.h"
#include "entity.h"
#include "tonic.h"

Room new_Room(SDL_Renderer *renderer, ResourceManager rm, 
	       Window window, Sprite bg, char *mapname);
void Room_update(Room room);
void Room_react(Room room);
void Room_draw(Room room);

Vect rtos(Room room, Vect roomCoord);
#endif
