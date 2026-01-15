#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "raylib.h"
#include "gameWorld.h"
#include "gameLobby.h"
#include "game.h"

typedef struct GameWindow
{
    int width;
    int height;

    Game game;

    bool initiate;
    //bool shouldClose;

    bool endFase;

}GameWindow;

GameWindow* createGameWindow(int width, int height);

void initGameWindow (GameWindow *gameWindow);

#endif // GAMEWINDOW_H
