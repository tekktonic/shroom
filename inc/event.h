#ifndef EVENT_H
#define EVENT_H

enum Event_Type_e
{
    EVENT_COLLIDE,
    EVENT_PRESS,
    EVENT_RELEASE
};

typedef enum Event_Type_e Event_Type;
struct Event_s
{
    Event_Type type;
    void *data;
};



#endif
