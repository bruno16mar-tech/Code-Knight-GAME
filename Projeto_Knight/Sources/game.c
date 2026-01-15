#include <string.h>
#include <stdio.h>
#include "raylib.h"
#include "game.h"
#include "player.h"
#include "resourceManager.h"
#include "menu.h"
#include "pause.h"
#include "save.h"

void drawEndGame (Game *game);

Game createGame()
{
    Game newGame = (Game)
    {
        .status = MENU,
        .lastStatus = MENU,
        .player = createNewPlayer((Vector2){32,32}, BLUE),
        .gameWorldInitiate = false,
        .fadeScreenMenus = 0.0,
        .timeToCode = 0.0,


        .saveSlot1 = false,
        .saveSlot2 = false,
        .saveSlot3 = false,

        .playerLobbyFirstPos = (Vector2){0,0},
        .playerLobbyReturnPos = (Vector2){0,0},
        .playerGameWorldFirstPos = (Vector2){0,0}
    };

    loadResources();

    return newGame;

}


void initGame(Game *game, bool* isFullScreen)
{

    game->gl.player = &game->player;

        bool bossBattleActive = false;

    if (game->gw != NULL)
    {
        if (game->gw->boss.life < 12 && game->gw->boss.dead == false && !game->player.status.dead && game->status==GAMEWORLD)
        {
            bossBattleActive = true;
        }
        else if (game->gw->boss.dead == true)
            bossBattleActive = false;

    }

    if (bossBattleActive)
    {
        if (IsMusicStreamPlaying(rm.defaultMusic)) StopMusicStream(rm.defaultMusic);

        if (!IsMusicStreamPlaying(rm.bossMusic)) PlayMusicStream(rm.bossMusic);


        SetMusicVolume(rm.bossMusic, 0.3f);
        UpdateMusicStream(rm.bossMusic);
    }
    else
    {
        if (IsMusicStreamPlaying(rm.bossMusic)) StopMusicStream(rm.bossMusic);

        if (!IsMusicStreamPlaying(rm.defaultMusic)) PlayMusicStream(rm.defaultMusic);

        SetMusicVolume(rm.defaultMusic, 0.3f);
        UpdateMusicStream(rm.defaultMusic);
    }

    switch(game->status)
    {
        case MENU:
            inputUpdateAndDrawMenu(game, *isFullScreen);
            break;

        case LOAD:
            inputUpdateAndDrawLoad(game, *isFullScreen);
            break;

        case HELP:
            inputUpdateAndDrawHelp(game, *isFullScreen);
            break;

        case PAUSE:
            inputUpdateAndDrawPause(game, isFullScreen);
            break;

        case CONFIRM:
            inputUpdateAndDrawConfirm(game);
            break;

        case GAMELOBBY:

            game->timeToCode -= GetFrameTime();
            if(game->timeToCode<=0)
                game->timeToCode = 0.0;

            if(IsKeyPressed(KEY_ENTER) && game->gl.nearComputer && game->timeToCode==0.0 && game->player.progress<3)
            {
                game->status = GAMEWORLD;
                game->player.inLevel = true;

                if(game->gameWorldInitiate)
                {
                    game->gw->player->pos = game->playerGameWorldFirstPos;
                }
            }

            if(IsKeyPressed(KEY_ESCAPE))
            {
                game->lastStatus = game->status;
                game->status = PAUSE;
            }


            if(game->player.progress>=3 && IsKeyPressed(KEY_ENTER) && game->gl.nearComputer)
            {
                game->status = ENDGAME;

                /*if(game->gl.fadeScreenGL2<=0)
                {
                    game->status = MENU;
                    game->saveSlot1=false;
                    game->saveSlot2=false;
                    game->saveSlot3=false;
                    resetPlayer(game->gw->player);
                    resetGameLobby(&game->gl, game->playerLobbyFirstPos);
                    //destroysGameWorld(game->gw);
                    game->gameWorldInitiate = false;
                }*/
            }
            else
            {
                inputAndUpdateGameLobby(&game->gl, *isFullScreen);

                drawGameLobby(&game->gl, *isFullScreen);
            }


           if(game->gl.player->status.resting && game->gl.gameIsSaved==false)
           {
                if(game->saveSlot1)
                    saveGame("save1", game->player);
                else if(game->saveSlot2)
                    saveGame("save2", game->player);
                else if (game->saveSlot3)
                    saveGame("save3", game->player);


                game->gl.gameIsSaved=true;
           }


            break;

        case GAMEWORLD:

            //---------CRIA MUNDO--------

            if(game->gameWorldInitiate==false)
            {
                game->gw = createGameWorld(&game->player);

                game->gameWorldInitiate = true;
            }

            //---SALVA POSIÇÃO INICIAL---

            if (game->playerGameWorldFirstPos.x==0 && game->playerGameWorldFirstPos.y ==0 && game->gameWorldInitiate)
            {
                game->playerGameWorldFirstPos = game->gw->player->pos;
            }

            //---------PAUSE---------

            if(IsKeyPressed(KEY_ESCAPE))
            {
                game->lastStatus = game->status;
                game->status = PAUSE;
            }

            //---------FIM DE JOGO----------

            if(game->gw->player->status.dead && GetKeyPressed() && game->gw->fadeScreenGW>=1)
            {
                game->status = MENU;
                game->saveSlot1=false;
                game->saveSlot2=false;
                game->saveSlot3=false;
                resetPlayer(game->gw->player);
                resetGameLobby(&game->gl, game->playerLobbyFirstPos);
                destroysGameWorld(game->gw);
                game->gameWorldInitiate = false;
                game->gw = NULL;
            }
            else
            {
            //-----------UPDATE MUNDO--------

            inputAndUpdateGameWorld(game->gw, *isFullScreen);

            //---------DESENHA MUNDO--------

            drawGameWorld(game->gw, *isFullScreen);
            }

            //--------TROCA MUNDO--------

            if(IsKeyPressed(KEY_ENTER)&& game->gw->canLeaveFase)
            {
                game->status = GAMELOBBY;
                game->player.inLevel = false;
                game->lastStatus = GAMEWORLD;

                if(game->playerLobbyReturnPos.x != 0 || game->playerLobbyReturnPos.y != 0) {
                    game->gl.player->pos = game->playerLobbyReturnPos;
                } else {
                    game->gl.player->pos = game->playerLobbyFirstPos;
                }

                game->gl.player->speed.y = -200;
                game->gl.player->speed.x = -100;
                game->player.progress++;

                game->timeToCode = 2.0;

                destroysGameWorld(game->gw);

                game->gameWorldInitiate = false;
                game->gw = NULL;

            }

            break;

        case ENDGAME:
            {
                drawEndGame(game);

                if(GetKeyPressed() && game->gl.fadeScreenGL2>=1)
                {
                    game->status = MENU;
                    game->saveSlot1=false;
                    game->saveSlot2=false;
                    game->saveSlot3=false;
                    resetPlayer(&game->player);
                    resetGameLobby(&game->gl, game->playerLobbyFirstPos);
                }
            }
            break;
        case LEAVE:
            game->shouldClose = true;
            break;
    }
}


void drawEndGame (Game *game)
{

    BeginDrawing();

    ClearBackground (SKYBLUE);

    game->gl.fadeScreenGL2 += 0.2f*GetFrameTime();

        if(game->gl.fadeScreenGL2>=1.0f) game->gl.fadeScreenGL2 = 1.0f;

        DrawRectangle(0,0,1920, 1080, (Color){0,0,0,(unsigned char)(game->gl.fadeScreenGL2*200)});

        DrawText("COMPILACAO CONCLUIDA\n\tFIM DE JOGO", ((GetScreenWidth()/2) - 400), ((GetScreenHeight()/2) - 34), 64, GREEN);

    EndDrawing();
}
