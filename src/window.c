#include "window.h"

Window new_Window(SDL_Window *win)
{
    Window ret = malloc(sizeof(struct Window_s));
    ret->window = win;
    SDL_GetWindowSize(win, &ret->ow, &ret->oh);
    ret->sx = ret->sy = 1.0f;
    return ret;
}

void Window_ResizedCB(Window win)
{
    int nw, nh;
    SDL_GetWindowSize(win->window, &nw, &nh);
    win->sx = (double)nw / (double)win->ow;
    win->sy = (double)nh / (double)win->oh;
}

SDL_Rect Window_Scale(Window win, SDL_Rect *rect)
{
    SDL_Rect ret;
    ret.x = rect->x * win->sx;
    ret.y = rect->y * win->sy;
    ret.w = rect->w * win->sx;
    ret.h = rect->h * win->sy;

    return ret;
}
