#ifndef CUST_ENTITIES_H
#define CUST_ENTITIES_H

#include "entity_types.h"
#include "sprite.h"

struct KillableSprite_s
{
    Sprite sprite;
    int hp;
};

typedef struct KillableSprite_s *KillableSprite;

struct Player_s
{
    KillableSprite ks;
};

struct Enemy_s
{
    KillableSprite ks;
};

#endif
