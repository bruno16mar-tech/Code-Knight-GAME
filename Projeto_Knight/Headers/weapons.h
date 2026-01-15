#ifndef WEAPONS_H
#define WEAPONS_H

#include "raylib.h"
#include "player.h"

//========================================
//----------------STRUCTS-----------------

typedef struct Weapons
{
    PlayerSword defaultSword;

}Weapons;

//-----------------------------------------
//=========================================
//----------------FUNCTIONS----------------

PlayerSword createPlayerSword ();

void updatePlayerSword (Player *player);

void drawPlayerSword (Player *player);



#endif // WEAPONS_H
