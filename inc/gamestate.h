#ifndef GAMESTATE_H
#define GAMESTATE_H

typedef struct GameState
{
    struct GameState *last;
    struct GameState (*controller)(struct GameState *last);

    SDL_Renderer *renderer;
    Window window;
    void *data;
};
#endif
