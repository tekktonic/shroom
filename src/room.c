#include "room.h"


Room new_Room(SDL_Renderer *renderer, ResourceManager rm, Window window, Sprite bg, char *mapname)
{
    Room ret = malloc(sizeof(struct Room_s));




    assert(renderer);
    ret->renderer = renderer;
    assert(window);
    ret->window = window;
    ret->toReact= new_List(0);
    ret->entities = new_List(0);
    ret->background = bg;

    ret->gravity = cpv(0, -200);

    ret->sox = ret->soy = 0;

    ret->space = cpSpaceNew();
    cpSpaceSetGravity(ret->space, ret->gravity);

    // room's ready, now to populate it

    json_t *maproot, *entities;
    json_error_t jerror;

    maproot = json_load_file(mapname, 0, &jerror);
    json_check(maproot, jerror);
    assert(json_is_object(maproot));

    ret->width = json_integer_value(json_object_get(maproot, "w"));
    ret->height = json_integer_value(json_object_get(maproot, "h"));
    entities = json_object_get(maproot, "entities");
				     

    for (unsigned int i = 0; i < json_array_size(entities); i++)
    {
	json_t *elem, *args, *typeo;
	char *type;
	elem = json_array_get(entities, i);

	assert(json_is_object(elem));

	typeo = json_object_get(elem, "type");
	assert(json_is_string(typeo));

	type = (char*)json_string_value(typeo);

	if (strcmp(type, "player") == 0)
	    List_enqueue(ret->entities, new_Player(rm, ret,
						    json_integer_value(
							json_object_get(elem, "x")),
						    json_integer_value(
							json_object_get(elem, "y"))));
	else if (strcmp(type, "box") == 0)
	    List_enqueue(ret->entities, new_Box(rm, ret,
						    json_integer_value(
							json_object_get(elem, "x")),
						    json_integer_value(
							json_object_get(elem, "y")),
						     json_real_value(
							 json_object_get(elem, "angle"))));
	else if (strcmp(type, "platform") == 0)
	    List_enqueue(ret->entities, new_Platform(rm, ret,
						    json_integer_value(
							json_object_get(elem, "x")),
						    json_integer_value(
							json_object_get(elem, "y")),
						     json_real_value(
							 json_object_get(elem, "angle"))));
    }

    return ret;
}

void Room_update(Room room)
{
    cpVect focusPos; 
    for (List cur = room->entities; cur != NULL; cur = cur->cdr)
    {
	((Entity)cur->car)->update((Entity)cur->car);
    }

    cpSpaceStep(room->space, 1.0 / 60.0);
    
    // alright, time to update the camera
    focusPos = cpBodyGetPos(room->cameraFocus->body);
    if (focusPos.x - room->sox > 150)
	room->sox++;
}

void Room_react(Room room)
{
     for(List cur = room->toReact; cur->cdr != NULL; cur = cur->cdr)
    {
	if (((Entity)cur->car)->react)
	    ((Entity)cur->car)->react((Entity)cur->car);
    }
}

void Room_draw(Room room)
{
    List cur = room->entities;

    SDL_Rect original = {.x = 0, .y = 0, .w = room->window->ow, .h = room->window->oh};
    SDL_Rect bg = Window_Scale(room->window, &original);
    SDL_RenderCopy(renderer, room->background.image, NULL, &bg);
    while (cur)
    {
	((Entity)cur->car)->draw((Entity)cur->car, room->renderer, room->window);
	cur = cur->cdr;
    }
}

cpVect rtos (Room room, cpVect roomCoord) // convert a room coordinate to a screen one
{
    return cpv(roomCoord.x - room->sox, roomCoord.y - room->soy);
}
