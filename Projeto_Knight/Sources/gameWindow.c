#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "gameWindow.h"
#include "resourceManager.h"

GameWindow* createGameWindow(int width, int height)
{
    GameWindow *gameWindow = (GameWindow*) malloc(sizeof(GameWindow));
    if (!gameWindow){return NULL;}

    gameWindow->width = width;
    gameWindow->height = height;
    gameWindow->initiate = false;
    //gameWindow->shouldClose = false;

    return gameWindow;
}

void initGameWindow(GameWindow *gameWindow)
{
    if(!gameWindow){return;} //checa para não dar crashs

    if(!gameWindow->initiate)
    {
        gameWindow->initiate = true;

        //======FULL-SCREEN-CONFIG======

        bool isFullScreen = true;

        //-------------------------------

        InitWindow (gameWindow->width, gameWindow->height, "JOGO2.0");

        SetExitKey(KEY_NULL);

        InitAudioDevice();

        gameWindow->game = createGame();

        SetTextureFilter(rm.gl.storeWall, TEXTURE_FILTER_POINT);

        printf("Posicao Retorno (M) -> X: %.2f, Y: %.2f\n",
               gameWindow->game.playerLobbyReturnPos.x,
               gameWindow->game.playerLobbyReturnPos.y);

        SetTargetFPS(60);


        while (!WindowShouldClose() && gameWindow->game.shouldClose==false)
        {
            //----FULL-SCREEN-CONFIG----

            if(isFullScreen)
            {
                    SetWindowSize(1920,1080);
                    SetWindowPosition(0,0);
            }
            else
            {
                SetWindowSize(gameWindow->width, gameWindow->height);
                SetWindowPosition(
                    (1920-gameWindow->width)/2,
                    (1080-gameWindow->height)/2
                );
            }

            //-----------------------------

            initGame(&gameWindow->game, &isFullScreen);

        }
        CloseWindow();
        unloadResouces();
        CloseAudioDevice();
        if(gameWindow->game.gameWorldInitiate)
            destroysGameWorld(gameWindow->game.gw);

    }
}
