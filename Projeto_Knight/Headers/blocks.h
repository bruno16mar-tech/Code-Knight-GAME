#ifndef BLOCKS_H
#define BLOCKS_H

#include "raylib.h"

//====================================
//---------------STRUCTS--------------

typedef struct Block
{
    Vector2 pos;
    Vector2 dim;
    Color cor;

}Block;

typedef struct Grass
{
    Vector2 pos;
    Vector2 dim;
    Color cor;

}Grass;

typedef struct StoreBlock
{
    Vector2 pos;
    Vector2 dim;
    Color cor;

}StoreBlock;

//-------------------------------------
//=====================================
//--------------FUNCTIONS--------------

Block createBlock (Vector2 pos);

void drawBlock (Block *block);

Grass createGrass (Vector2 pos);

void drawGrass (Grass *grass);

StoreBlock createStoreBlock (Vector2 pos);

void drawStoreBlock (StoreBlock *storeBlock);
#endif // BLOCKS_H
