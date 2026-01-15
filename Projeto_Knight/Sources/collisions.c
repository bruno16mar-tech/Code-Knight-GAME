#include "raylib.h"
#include "collisions.h"

//===============================================
//-----------PLAYER-COLLISION-FUNCTIONS----------

//-----------------------------------------------
//                    CREATE
//-----------------------------------------------

PlayerCollisionRec updatePlayerCollisionRecs(Player *player)
{
    return (PlayerCollisionRec){
                .upper = (Rectangle){
                        .x = player->pos.x+(player->dim.x/2)-8,
                        .y = player->pos.y,
                        .width = 16,
                        .height = 6
                        },
                .under = (Rectangle){
                        .x = player->pos.x+(player->dim.x/2)-8,
                        .y = player->pos.y+player->dim.y-6,
                        .width = 16,
                        .height = 6
                        },
                .left = (Rectangle){
                        .x = player->pos.x,
                        .y = player->pos.y+(player->dim.y/2)-3,
                        .width = 6,
                        .height = 6
                        },
                .right = (Rectangle){
                        .x = player->pos.x+player->dim.x-6,
                        .y = player->pos.y+(player->dim.y/2)-3,
                        .width = 6,
                        .height = 6
                        }
    };
}

void DrawPlayerRecCollisionUnder(PlayerCollisionRec *recCollision)
{
    DrawRectangleRec(recCollision->under, WHITE);
}


    //============PLAYER-SWORD===============

Rectangle createAndUpdatePlayerSwordCollisionRec(Player *player)
{
    return (Rectangle){.x = player->sword.pos.x, .y = player->sword.pos.y, .width = player->sword.dim.x, .height = player->sword.dim.y};
}

Rectangle deletePlayerSwordCollisionRec(Player *player)
{
    return (Rectangle){.x = player->pos.x+(player->dim.x/2), .y = player->pos.y+(player->dim.y/2), .width = 0, .height =0};
}

//--------------------------------------------//
//                    MAKE                    //
//--------------------------------------------//

    //============PLAYER-BLOCK==============

//------------UPPERplayer-COLLISION-------------
bool checkPlayerBlockCollision_Upper(PlayerCollisionRec *collisionRecs, Block *block)
{
    return CheckCollisionRecs(collisionRecs->upper,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}
//------------UNDERplayer-COLLISION-------------
bool checkPlayerBlockCollision_Under(PlayerCollisionRec *collisionRecs, Block *block)
{
    return CheckCollisionRecs(collisionRecs->under,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}
//-----------LEFTplayer-COLLISION---------------
bool  checkPlayerBlockCollision_Left(PlayerCollisionRec *collisionRecs, Block *block)
{
    return CheckCollisionRecs(collisionRecs->left,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}
//-----------RIGHTplayer-COLLISION--------------
bool  checkPlayerBlockCollision_Right(PlayerCollisionRec *collisionRecs, Block *block)
{
    return CheckCollisionRecs(collisionRecs->right,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}

    //=============PLAYER-ENEMIES=============

        //----------BASIC-ENEMIES----------

bool checkPlayerBasicEnemiesCollision_Upper(PlayerCollisionRec *collisionRec, BasicEnemy *enemy)
{
    return CheckCollisionRecs(collisionRec->upper,(Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y});
}
//------------COLISÃO POR BAIXO-------------
bool checkPlayerBasicEnemiesCollision_Under(PlayerCollisionRec *collisionRec, BasicEnemy *enemy)
{
    return CheckCollisionRecs(collisionRec->under,(Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y});
}

bool checkPlayerBasicEnemiesCollision_Left(PlayerCollisionRec *collisionRec, BasicEnemy *enemy)
{
    return CheckCollisionRecs(collisionRec->left,(Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y});
}

bool checkPlayerBasicEnemiesCollision_Right(PlayerCollisionRec *collisionRec, BasicEnemy *enemy)
{
    return CheckCollisionRecs(collisionRec->right,(Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y});
}

    //-----AIR-BASIC-ENEMIES-----

 bool checkPlayerAirBasicEnemiesCollision_Upper(PlayerCollisionRec *collisionRec, AirBasicEnemy *enemy)
{
    return CheckCollisionRecs(collisionRec->upper,(Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y});
}
//------------COLISÃO POR BAIXO-------------
bool checkPlayerAirBasicEnemiesCollision_Under(PlayerCollisionRec *collisionRec, AirBasicEnemy *enemy)
{
    return CheckCollisionRecs(collisionRec->under,(Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y});
}

bool checkPlayerAirBasicEnemiesCollision_Left(PlayerCollisionRec *collisionRec, AirBasicEnemy *enemy)
{
    return CheckCollisionRecs(collisionRec->left,(Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y});
}

bool checkPlayerAirBasicEnemiesCollision_Right(PlayerCollisionRec *collisionRec, AirBasicEnemy *enemy)
{
    return CheckCollisionRecs(collisionRec->right,(Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y});
}






    //=============PLAYER-SWORD===============

bool checkBasicEnemiesPlayerSwordCollision_Left(BasicEnemyCollisionRec *collisionRec, PlayerSword *playerSword)
{
    return CheckCollisionRecs(collisionRec->left,(Rectangle){.x = playerSword->pos.x, .y = playerSword->pos.y, .width = playerSword->dim.x, .height = playerSword->dim.y});
}

bool checkBasicEnemiesPlayerSwordCollision_Right(BasicEnemyCollisionRec *collisionRec, PlayerSword *playerSword)
{
    return CheckCollisionRecs(collisionRec->right,(Rectangle){.x = playerSword->pos.x, .y = playerSword->pos.y, .width = playerSword->dim.x, .height = playerSword->dim.y});
}

bool checkBasicEnemiesPlayerSwordCollision_Up(BasicEnemyCollisionRec *collisionRec, PlayerSword *playerSword)
{
    return CheckCollisionRecs(collisionRec->upper,(Rectangle){.x = playerSword->pos.x, .y = playerSword->pos.y, .width = playerSword->dim.x, .height = playerSword->dim.y});
}

        //---BASIC-ENEMY---

bool checkBasicEnemiesPlayerSwordCollision_default(BasicEnemy *enemy, PlayerSword *playerSword)
{
    return CheckCollisionRecs((Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y },(Rectangle){.x = playerSword->pos.x, .y = playerSword->pos.y, .width = playerSword->dim.x, .height = playerSword->dim.y});
}

        //---AIR-BASIC-ENEMY---

 bool checkAirBasicEnemiesPlayerSwordCollision_default(AirBasicEnemy *enemy, PlayerSword *playerSword)
{
    return CheckCollisionRecs((Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y },(Rectangle){.x = playerSword->pos.x, .y = playerSword->pos.y, .width = playerSword->dim.x, .height = playerSword->dim.y});
}

        //---BLOCKS---

bool checkPlayerSwordBlocksCollision(Rectangle swordCollisionRec, Rectangle block)
{
    return CheckCollisionRecs(swordCollisionRec, block);
}

    //================PLAYER-POWERS===============

bool checkBasicEnemiesHorizontalPowerCollision(BasicEnemy *enemy, HorizontalPower *power)
{
    return CheckCollisionRecs((Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y },(Rectangle){.x = power->pos.x, .y = power->pos.y, .width = power->dim.x, .height = power->dim.y});
}

bool checkAirBasicEnemiesHorizontalPowerCollision(AirBasicEnemy *enemy, HorizontalPower *power)
{
    return CheckCollisionRecs((Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y },(Rectangle){.x = power->pos.x, .y = power->pos.y, .width = power->dim.x, .height = power->dim.y});
}

bool checkBlocksHorizontalPowerCollision(Rectangle block, HorizontalPower *power)
{
    return CheckCollisionRecs(block,(Rectangle){.x = power->pos.x, .y = power->pos.y, .width = power->dim.x, .height = power->dim.y});
}

//-------------------------------------------------
//=================================================
//-----------------SKILLS-AND-CHARMS---------------

bool checkSkillsPlayer(Skill *skill, Player *player)
{
    return CheckCollisionRecs((Rectangle){.x = skill->pos.x, .y = skill->pos.y, .width = skill->dim.x, .height = skill->dim.y},(Rectangle){.x = player->pos.x, .y = player->pos.y, .width = player->dim.x, .height = player->dim.y} );
}


bool checkCharmsPlayer(Charm *charms, Player *player)
{
    return CheckCollisionRecs((Rectangle){.x = charms->pos.x, .y = charms->pos.y, .width = charms->dim.x, .height = charms->dim.y},(Rectangle){.x = player->pos.x, .y = player->pos.y, .width = player->dim.x, .height = player->dim.y} );
}


bool checkSkillsPlayerClose(Skill *skill, Player *player)
{
    return CheckCollisionRecs((Rectangle){.x = skill->pos.x - 32, .y = skill->pos.y - 32, .width = skill->dim.x + 32, .height = skill->dim.y + 32},(Rectangle){.x = player->pos.x, .y = player->pos.y, .width = player->dim.x, .height = player->dim.y} );
}


bool checkCharmsPlayerClose(Charm *charms, Player *player)
{
    return CheckCollisionRecs((Rectangle){.x = charms->pos.x - 32, .y = charms->pos.y - 32, .width = charms->dim.x + 32, .height = charms->dim.y + 64},(Rectangle){.x = player->pos.x, .y = player->pos.y, .width = player->dim.x, .height = player->dim.y} );
}



//----------------------------------------------------
//====================================================
//-----------ENEMIES-COLLISIONS-FUNCTIONS-------------

//----------------------------------------------------
//                      CREATE
//----------------------------------------------------

    //------BASIC-ENEMIES-----

BasicEnemyCollisionRec createAndUpdateBasicEnemiesCollisionsRec(BasicEnemy *enemy)
{
    return (BasicEnemyCollisionRec){
                .upper = (Rectangle){
                        .x = enemy->pos.x+(enemy->dim.x/2)-3,
                        .y = enemy->pos.y,
                        .width = 6,
                        .height = 6
                        },
                .under = (Rectangle){
                        .x = enemy->pos.x+(enemy->dim.x/2)-3,
                        .y = enemy->pos.y+enemy->dim.y-6,
                        .width = 6,
                        .height = 6
                        },
                .left = (Rectangle){
                        .x = enemy->pos.x,
                        .y = enemy->pos.y+(enemy->dim.y/2)-3,
                        .width = 6,
                        .height = 6
                        },
                .right = (Rectangle){
                        .x = enemy->pos.x+enemy->dim.x-6,
                        .y = enemy->pos.y+(enemy->dim.y/2)-3,
                        .width = 6,
                        .height = 6
                        }
    };
}


BasicEnemyCollisionRec createAndUpdateAirBasicEnemiesCollisionsRec(AirBasicEnemy *enemy)
{
    return (BasicEnemyCollisionRec){
                .upper = (Rectangle){
                        .x = enemy->pos.x+(enemy->dim.x/2)-3,
                        .y = enemy->pos.y,
                        .width = 6,
                        .height = 6
                        },
                .under = (Rectangle){
                        .x = enemy->pos.x+(enemy->dim.x/2)-3,
                        .y = enemy->pos.y+enemy->dim.y-6,
                        .width = 6,
                        .height = 6
                        },
                .left = (Rectangle){
                        .x = enemy->pos.x,
                        .y = enemy->pos.y+(enemy->dim.y/2)-3,
                        .width = 6,
                        .height = 6
                        },
                .right = (Rectangle){
                        .x = enemy->pos.x+enemy->dim.x-6,
                        .y = enemy->pos.y+(enemy->dim.y/2)-3,
                        .width = 6,
                        .height = 6
                        }
    };
}

    //------MAIN-FUNCTION-FOR-ENEMIES------

void createAndUpdateEnemiesCollisionRecs(Enemies *enemies)
{
    for (int i=0; i<enemies->numberOfBasicEnemies;i++)
    {
        BasicEnemy *enemy1 = &enemies->enemy1[i];

        if (enemy1->dead==false)
        {
            createAndUpdateBasicEnemiesCollisionsRec(enemy1);
        }
    }

    for (int a=0; a<enemies->numberOfBasicEnemies;a++)
    {
        AirBasicEnemy *enemy2 = &enemies->enemy2[a];

        if (enemy2->dead==false)
        {
            createAndUpdateAirBasicEnemiesCollisionsRec(enemy2);
        }
    }
}

//---------------------------------------------//
//                    MAKE                     //
//---------------------------------------------//

    //-----BASIC-ENEMIES-BLOCK-COLLISION-----

//------------COLISÃO POR CIMA-------------
bool checkBasicEnemiesBlockCollision_Upper(BasicEnemyCollisionRec *collisionRec, Block *block)
{
    return CheckCollisionRecs(collisionRec->upper,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}
//------------COLISÃO POR BAIXO-------------
bool checkBasicEnemiesBlockCollision_Under(BasicEnemyCollisionRec *collisionRec, Block *block)
{
    return CheckCollisionRecs(collisionRec->under,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}

bool checkBasicEnemiesBlockCollision_Left(BasicEnemyCollisionRec *collisionRec, Block *block)
{
    return CheckCollisionRecs(collisionRec->left,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}

bool checkBasicEnemiesBlockCollision_Right(BasicEnemyCollisionRec *collisionRec, Block *block)
{
    return CheckCollisionRecs(collisionRec->right,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}

//----------------------------------------
//========================================
//------COLLISIONS-BOSS-FUNCTIONS---------

BossCollisionRec createAndUpdateBossCollisionRec(Boss *boss)
{
    return (BossCollisionRec)
            {
                .upper = (Rectangle){
                        .x = boss->pos.x+(boss->dim.x/2)-24,
                        .y = boss->pos.y,
                        .width = 48,
                        .height = 6
                        },
                .under = (Rectangle){
                        .x = boss->pos.x+(boss->dim.x/2)-24,
                        .y = boss->pos.y+boss->dim.y-6,
                        .width = 48,
                        .height = 6
                        },
                .left = (Rectangle){
                        .x = boss->pos.x,
                        .y = boss->pos.y+(boss->dim.y/2)-24,
                        .width = 6,
                        .height = 48
                        },
                .right = (Rectangle){
                        .x = boss->pos.x+boss->dim.x-6,
                        .y = boss->pos.y+(boss->dim.y/2)-24,
                        .width = 6,
                        .height = 48
                        }
            };
}

bool checkBossBlockCollision_Upper(BossCollisionRec *collisionRec, Block *block)
{
   return CheckCollisionRecs(collisionRec->upper,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}

bool checkBossBlockCollision_Under(BossCollisionRec *collisionRec, Block *block)
{
    return CheckCollisionRecs(collisionRec->under,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}

bool checkBossBlockCollision_Left(BossCollisionRec *collisionRec, Block *block)
{
    return CheckCollisionRecs(collisionRec->left,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}

bool checkBossBlockCollision_Right(BossCollisionRec *collisionRec, Block *block)
{
    return CheckCollisionRecs(collisionRec->right,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}


//----------------------------------------------
//==============================================
//--------------COINS-COLLISION-----------------

bool checkCoinsBlocksCollision(Coins *coin, Block *block)
{
    return CheckCollisionRecs((Rectangle){.x = coin->pos.x, .y = coin->pos.y, .width = coin->dim.x, .height = coin->dim.y}, (Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}

bool checkCoinsPlayerCollision(Coins *coin, Player *player)
{
    return CheckCollisionRecs((Rectangle){.x = coin->pos.x, .y = coin->pos.y, .width = coin->dim.x, .height = coin->dim.y}, (Rectangle){.x = player->pos.x, .y = player->pos.y, .width = player->dim.x, .height = player->dim.y});
}






