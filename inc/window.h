#ifndef WINDOW_H
#define WINDOW_H
#include <SDL.h>
#include <stdlib.h>

struct Window_s
{
    SDL_Window *window;
    int ow, oh; // original width and height
    double sx, sy;
};

typedef struct Window_s *Window;

Window new_Window(SDL_Window *win);

void Window_ResizedCB(Window win);

SDL_Rect Window_Scale(Window win, SDL_Rect *rect);

#endif
