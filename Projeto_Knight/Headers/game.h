#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "player.h"
#include"gameLobby.h"
#include "gameWorld.h"

typedef enum GameStatus
{
    MENU = 0,
    LOAD,
    HELP,
    PAUSE,
    LEAVE,
    CONFIRM,
    GAMELOBBY,
    GAMEWORLD,
    ENDGAME,

} GameStatus;

typedef struct Game
{
    GameStatus status;

    GameStatus lastStatus;

    Player player;

    GameLobby gl;
    Vector2 playerLobbyFirstPos;
    Vector2 playerLobbyReturnPos;

    GameWorld *gw;
    Vector2 playerGameWorldFirstPos;

    bool gameWorldInitiate;

    float fadeScreenMenus;

    float timeToCode;

    bool shouldClose;

    bool saveSlot1;
    bool saveSlot2;
    bool saveSlot3;


}Game;

Game createGame();

void initGame(Game *game, bool* isFullScreen);


#endif // GAME_H
