#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "raylib.h"
#include "player.h"
#include "enemies.h"
#include "blocks.h"
#include "collisions.h"
#include "coins.h"

//============================================
//-----------------STRUCTS--------------------

typedef struct GameWorld
{
    Player *player;

    bool nearDeadBoss;
    bool canLeaveFase;

    Enemies *enemies;
    int numberOfEnemies;

    Boss boss;

    Coins ticketsRU[800];
    int numberOfCoins;

    Skill skills[5];
    int numberOfSkills;

    Charm charms[5];
    int numberOfCharms;

    LostItens item[2];
    int itemLevelNumber;

    Block *blocks;
    int numberOfBlocks;

    Camera2D camera;

    float fadeScreenGW;

}GameWorld;


//============================================
//----------------FUNCTIONS-------------------

    //-------CREATE-DESTROYS------

GameWorld* createGameWorld(Player *player);

void destroysGameWorld (GameWorld *gw);

void loadMap (GameWorld *gw, const char* arquivo);

    //---------MAIN-FUNCTION---------

void inputAndUpdateGameWorld (GameWorld *gw, bool isFullscreen);

    //--------COLLISIONS---------

void makeCollisionPlayerBlock (GameWorld *gw);

void makeCollisionPlayerCoinsSkillsAndCharms (GameWorld *gw);

void makeCollisionEnemiesBlock (GameWorld *gw);

void makeCollisionEnemiesPlayer (GameWorld *gw);

void makeCollisionEnemiesWeapons (GameWorld *gw);

void makeCollisionEnemiesPlayerPowers (GameWorld *gw);

void makeCllisionBlockWeaponsAndPowers (GameWorld *gw);

    //-------COINS-------

void updateCoins(GameWorld *gw, float delta);


    //-------DRAW-AND-CAMERA-------

void drawGameWorld (GameWorld *gw,bool isFullscreen);

void updateCamera (Camera2D *camera, Player *player, bool isFullscreen);

#endif // GAMEWORLD_H
