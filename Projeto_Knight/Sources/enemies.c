#include "raylib.h"
#include "enemies.h"
#include "collisions.h"
#include "resourceManager.h"

#define GRAVITY 20.0
#define MAX_SPEED_FALL 400.0

//===========================================
//----------------FUNCTIONS------------------

BasicEnemy createBasicEnemies(Vector2 pos)
{
    return (BasicEnemy)
    {
        .pos = pos,
        .speed = (Vector2) {0,0},
        .dim = (Vector2) {25,25},

        .cor = RED,
        .texture = 0,
        .contTime = 0.0f,
        .currentFrame = 0,

        .collisionRecs = {{0}},

        .knockbackStatus = (BasicEnemyKnockbackStatus)
        {
            .knockbackR = false,
            .knockbackL = false,
            .knockbackUp = false,
            .knockbackUn = false,
            .knockbackTime = 0.0f,
        },

        .life = 3,
        .dead = false,
        .haveCoins = true,

        .defaultSpeed = 100.0,

        .onFloor =false
    };
}

void updateBasicEnemies(BasicEnemy *enemy1, float delta)
{
    //=============HORIZONTAL=MOVES===============
    if (enemy1->knockbackStatus.knockbackTime<=0)
    {
        if (enemy1->onFloor)
        {
            enemy1->speed.x = enemy1->defaultSpeed;
            enemy1->speed.y = 0.0f;
        }

        if(enemy1->speed.y<40.0)
        {
            if (enemy1->speed.x>0 && enemy1->onFloor==false)
            {
                enemy1->pos.x = enemy1->pos.x-(enemy1->dim.x/2);
                enemy1->defaultSpeed = -enemy1->defaultSpeed;
                if(enemy1->texture==0)
                    enemy1->texture=1;
                else enemy1->texture=0;
            }
            else if (enemy1->speed.x<0 && enemy1->onFloor==false)
            {
                enemy1->pos.x = enemy1->pos.x+(enemy1->dim.x/2);
                enemy1->defaultSpeed = -enemy1->defaultSpeed;
                 if(enemy1->texture==0)
                    enemy1->texture=1;
                else enemy1->texture=0;
            }
        }
    }
    else
    {
        enemy1->knockbackStatus.knockbackTime -= delta; // conta o tempo
        enemy1->speed.x *= 0.9; // reduz a velocidade até o fim do tempo
    }


    //=============VERTICAL=MOVES=================

    enemy1->speed.y += GRAVITY;

    if(enemy1->speed.y>MAX_SPEED_FALL)
        enemy1->speed.y = MAX_SPEED_FALL;

    //=============UPDATE=POSITION================

    enemy1->pos.x += enemy1->speed.x * delta;
    enemy1->pos.y += enemy1->speed.y * delta;

    //=============UPDATE=HEAT=BOX================

    enemy1->collisionRecs  = createAndUpdateBasicEnemiesCollisionsRec(enemy1);

    //===============UPDATE=STATS=================

    if(enemy1->life<=0){enemy1->dead=true;}

}

AirBasicEnemy createAirBasicEnemies(Vector2 pos, int number)
{
    float defineSpeedDirection;

    if(number%2==0)
        {
            defineSpeedDirection = 75.0*-1;
        }
        else
            defineSpeedDirection = 75.0;



    return (AirBasicEnemy)
    {
        .pos = pos,
        .firstPos = pos,
        .speed = (Vector2) {0,0},
        .dim = (Vector2) {20,20},

        .cor = GREEN,
        .texture = 0,
        .glitching = false,
        .glitchTime = 0.25,
        .contGlitchTime = 0.0,

        .collisionRecs = {{0}},

        .knockbackStatus = (BasicEnemyKnockbackStatus)
        {
            .knockbackR = false,
            .knockbackL = false,
            .knockbackUp = false,
            .knockbackUn = false,
            .knockbackTime = 0.0f,
        },

        .life = 3,
        .dead = false,
        .haveCoins = true,

        .defaultSpeed = defineSpeedDirection,

    };
}


void updateAirBasicEnemies(AirBasicEnemy *enemy2, float delta)
{
    int xMin = enemy2->firstPos.x-200;
    int xMax = enemy2->firstPos.x+200;

    int yMin = enemy2->firstPos.y-300;
    int yMax = enemy2->firstPos.y+100;

    if(enemy2->speed.x == 0 )
        enemy2->speed.x = enemy2->defaultSpeed;
    if(enemy2->speed.y ==0 )
        enemy2->speed.y = enemy2->defaultSpeed;

    if (enemy2->knockbackStatus.knockbackTime<=0)
    {
        if(enemy2->pos.x<=xMin)
        {
            enemy2->speed.x = -enemy2->speed.x;
            enemy2->glitching =true;
            enemy2->contGlitchTime=0.0;
            if(enemy2->texture==1)
                enemy2->texture = 0;
            else enemy2->texture = 1;
        }
        if(enemy2->pos.x>=xMax)
        {
            enemy2->speed.x = -enemy2->speed.x;
            enemy2->glitching =true;
            enemy2->contGlitchTime=0.0;
            if(enemy2->texture==1)
                enemy2->texture = 0;
            else enemy2->texture = 1;
        }
        if(enemy2->pos.y<=yMin)
        {
            enemy2->speed.y = -enemy2->speed.y;
            enemy2->glitching =true;
            enemy2->contGlitchTime=0.0;
        }
        if(enemy2->pos.y>=yMax)
        {
            enemy2->speed.y = -enemy2->speed.y;
            enemy2->glitching =true;
            enemy2->contGlitchTime=0.0;
        }

    }
    else
    {
        enemy2->knockbackStatus.knockbackTime -= delta; // conta o tempo
        enemy2->speed.x *= 0.9; // reduz a velocidade até o fim do tempo
    }

    if(enemy2->glitching)
    {
        enemy2->contGlitchTime += delta;

        if(enemy2->contGlitchTime>=enemy2->glitchTime)
        {
            enemy2->contGlitchTime=0.0;
            enemy2->glitching = false;
        }
    }

    //=============UPDATE=POSITION================

    enemy2->pos.x += enemy2->speed.x * delta;
    enemy2->pos.y += enemy2->speed.y * delta;

    //=============UPDATE=HEAT=BOX================

    enemy2->collisionRecs  = createAndUpdateAirBasicEnemiesCollisionsRec(enemy2);

    //===============UPDATE=STATS=================

    if(enemy2->life<=0){enemy2->dead=true;}
}


//---------------------------------------------------
//===================================================
//----------------KNOCKBACK-FUNCTIOS-----------------

void applyKnockbackToBasicEnemies(BasicEnemy *enemy)
{
    if (enemy->knockbackStatus.knockbackR) //confere o tipo e direção
    {
        enemy->speed.x = -500.0; //aplica as forças
        enemy->speed.y = -200.0;
        enemy->knockbackStatus.knockbackTime = 0.5; // inicia o contador
    }
    if (enemy->knockbackStatus.knockbackL)
    {
        enemy->speed.x = 500.0;
        enemy->speed.y = -200.0;
        enemy->knockbackStatus.knockbackTime = 0.5;
    }
    if (enemy->knockbackStatus.knockbackUn)
    {
        if(enemy->speed.x<0)
        {
            enemy->speed.x = 200.0;
        }
        if(enemy->speed.x>0)
        {
            enemy->speed.x = -200.0;
        }
        enemy->speed.y = 300.0;
        enemy->knockbackStatus.knockbackTime = 0.5;
    }
     if (enemy->knockbackStatus.knockbackUp)
    {
        if(enemy->speed.x<0)
        {
            enemy->speed.x = 200.0;
        }
        if(enemy->speed.x>0)
        {
            enemy->speed.x = -200.0;
        }
        enemy->speed.y = -300.0;
        enemy->knockbackStatus.knockbackTime = 0.5;
    }

    enemy->knockbackStatus.knockbackL = false;
    enemy->knockbackStatus.knockbackR = false;
    enemy->knockbackStatus.knockbackUn = false;
    enemy->knockbackStatus.knockbackUp = false;
}

void applyKnockbackToAirBasicEnemies(AirBasicEnemy *enemy)
{
    if (enemy->knockbackStatus.knockbackR) //confere o tipo e direção
    {
        enemy->speed.x = -250.0; //aplica as forças
        enemy->speed.y = -100.0;
        enemy->knockbackStatus.knockbackTime = 0.5; // inicia o contador
    }
    if (enemy->knockbackStatus.knockbackL)
    {
        enemy->speed.x = 250.0;
        enemy->speed.y = -100.0;
        enemy->knockbackStatus.knockbackTime = 0.5;
    }
    if (enemy->knockbackStatus.knockbackUn)
    {
        if(enemy->speed.x<0)
        {
            enemy->speed.x = 100.0;
        }
        if(enemy->speed.x>0)
        {
            enemy->speed.x = -100.0;
        }
        enemy->speed.y = 150.0;
        enemy->knockbackStatus.knockbackTime = 0.5;
    }
     if (enemy->knockbackStatus.knockbackUp)
    {
        if(enemy->speed.x<0)
        {
            enemy->speed.x = 100.0;
        }
        if(enemy->speed.x>0)
        {
            enemy->speed.x = -100.0;
        }
        enemy->speed.y = -150.0;
        enemy->knockbackStatus.knockbackTime = 0.5;
    }

    enemy->knockbackStatus.knockbackL = false;
    enemy->knockbackStatus.knockbackR = false;
    enemy->knockbackStatus.knockbackUn = false;
    enemy->knockbackStatus.knockbackUp = false;
}



void applyKnockbackToEnemies(Enemies *enemies)
{
    //===========BASIC=ENEMIES==========

    for (int i=0; i<enemies->numberOfBasicEnemies;i++)
    {
        BasicEnemy *enemy1 = &enemies->enemy1[i];

        if (enemy1->dead==false && enemy1->knockbackStatus.knockbackTime<=0)
        {
            applyKnockbackToBasicEnemies(enemy1);
        }
    }

    for(int a=0;a<enemies->numberOfAirBasicEnemies;a++)
    {
        AirBasicEnemy *enemy2 = &enemies->enemy2[a];

        if (enemy2->dead==false && enemy2->knockbackStatus.knockbackTime<=0)
        {
            applyKnockbackToAirBasicEnemies(enemy2);
        }
    }
}

//-----------------------------------------------------
//=====================================================
//------------------MAIN-FUNCTION----------------------

void updateEnemies (Enemies *enemies, float delta)
{
    //===========BASIC=ENEMIES==========

    for (int i=0; i<enemies->numberOfBasicEnemies;i++)
    {
        BasicEnemy *enemy1 = &enemies->enemy1[i];

        if (enemy1->dead==false)
        {
            updateBasicEnemies(enemy1, delta);
        }

        enemy1->contTime+=delta;
        if(enemy1->contTime>=0.75)
        {
            if(enemy1->currentFrame==0)
                enemy1->currentFrame = 1;
            else
                enemy1->currentFrame = 0;

            enemy1->contTime = 0.0f;
        }
    }

    for(int a=0;a<enemies->numberOfAirBasicEnemies;a++)
    {
        AirBasicEnemy *enemy2 = &enemies->enemy2[a];

        if (enemy2->dead==false)
        {
            updateAirBasicEnemies(enemy2, delta);
        }
    }


}

//----------------------------------------------------------
//==========================================================
//-------------------DRAW-FUNCTIONS-------------------------

void drawBasicEnemies(BasicEnemy *enemy1)
{
    if(enemy1->texture==0)
        {
            DrawTexturePro(rm.gw.skullBug[enemy1->currentFrame],
                        (Rectangle){0,0,rm.gw.skullBug[enemy1->currentFrame].width,rm.gw.skullBug[enemy1->currentFrame].height},
                        (Rectangle){enemy1->pos.x,enemy1->pos.y,rm.gw.skullBug[enemy1->currentFrame].width,rm.gw.skullBug[enemy1->currentFrame].height},
                        (Vector2){12,12},
                         0.0f,
                         WHITE);
        }
        else
        {
            DrawTexturePro(rm.gw.skullBug[enemy1->currentFrame],
                        (Rectangle){0,0,-rm.gw.skullBug[enemy1->currentFrame].width,rm.gw.skullBug[enemy1->currentFrame].height},
                        (Rectangle){enemy1->pos.x,enemy1->pos.y,rm.gw.skullBug[enemy1->currentFrame].width,rm.gw.skullBug[enemy1->currentFrame].height},
                        (Vector2){12,12},
                         0.0f,
                         WHITE);
        }
}

void drawAirBasicEnemies (AirBasicEnemy *enemy2)
{
    //DrawRectangleV(enemy2->pos,enemy2->dim,enemy2->cor);
    if(enemy2->glitching==false)
    {
        if(enemy2->texture==0)
        {
            DrawTexturePro(rm.gw.glitch1,
                        (Rectangle){0,0,rm.gw.glitch1.width,rm.gw.glitch1.height},
                        (Rectangle){enemy2->pos.x,enemy2->pos.y,rm.gw.glitch1.width,rm.gw.glitch1.height},
                        (Vector2){8,8},
                         0.0f,
                         WHITE);
        }
        else
        {
            DrawTexturePro(rm.gw.glitch1,
                        (Rectangle){0,0,-rm.gw.glitch1.width,rm.gw.glitch1.height},
                        (Rectangle){enemy2->pos.x,enemy2->pos.y,rm.gw.glitch1.width,rm.gw.glitch1.height},
                        (Vector2){8,8},
                         0.0f,
                         WHITE);
        }
    }
    else
    {
        if(enemy2->texture==0)
        {
            DrawTexturePro(rm.gw.glitch2,
                        (Rectangle){0,0,rm.gw.glitch2.width,rm.gw.glitch2.height},
                        (Rectangle){enemy2->pos.x,enemy2->pos.y,rm.gw.glitch1.width,rm.gw.glitch1.height},
                        (Vector2){8,8},
                         0.0f,
                         WHITE);
        }
        else
        {
            DrawTexturePro(rm.gw.glitch2,
                        (Rectangle){0,0,-rm.gw.glitch2.width,rm.gw.glitch2.height},
                        (Rectangle){enemy2->pos.x,enemy2->pos.y,rm.gw.glitch1.width,rm.gw.glitch1.height},
                        (Vector2){8,8},
                         0.0f,
                         WHITE);
        }
    }
}


void drawEnemies(Enemies *enemies)
{
    //===========BASIC=ENEMIES==========

    for (int i=0; i<enemies->numberOfBasicEnemies;i++)
    {
        BasicEnemy *enemy1 = &enemies->enemy1[i];

        if (enemy1->dead==false)
        {
            drawBasicEnemies(enemy1);
        }
    }
        //--------AIR-BASIC-ENEMIES------

    for (int a=0; a<enemies->numberOfAirBasicEnemies;a++)
    {
        AirBasicEnemy *enemy2 = &enemies->enemy2[a];

        if (enemy2->dead==false)
        {
            drawAirBasicEnemies(enemy2);
        }
    }
}

//----------------------------------------------
//==============================================
//--------------------BOSS----------------------

    //======================================
    //---------------CREATE-----------------

Boss createBoss(Vector2 pos)
{
   return (Boss)
   {
       .pos = pos,
       .firstPos = pos,
       .speed = (Vector2){0,0},
       .atualX = 1,
       .atualY = 1,
       .dim = (Vector2){64,64},

       .collisionRecs = {{0}},
       .visionRecs = {{0}},

       .life = 12,
       .dead = false,
       .haveCoins = true,

       .cor = WHITE,

       .defaultSpeed = 100,

       .attack1 = false,
       .attack2Left = false,
       .attack2Right = false,
       .attack3 = false,

       .attack1Time = 1.0f,
       .attack2Time = 1.5f,
       .attack3Time = 10.0f,
       .contAttackTime = 0.0f,
       .attackCoolDown = 2.0f,
       .contAttackCoolDown = 0.0f,

       .sufferingDamege = false,
       .limitDamegeTime = 0.5,
       .contDamegeTime = 0.0,

       .playerUnderZone = false,
       .playerRightZone = false,
       .playerLeftZone = false,

   };

}

void updateBoss (Boss *boss, float delta)
{
    int xMin = boss->firstPos.x - 300;
    int xMax = boss->firstPos.x + 300;
    int yMin = boss->firstPos.y - 500;
    int yMax = boss->firstPos.y + 100;

    if(boss->dead==false)
    {
        if(boss->contAttackTime<=0)
        {
            boss->attack1 = false;
            boss->attack2Left = false;
            boss->attack2Right = false;
            boss->attack3 = false;
            boss->contAttackTime = 0.0;
            boss->contAttackCoolDown -= delta;
            if(boss->contAttackCoolDown<=0)
                boss->contAttackCoolDown = 0.0f;

        }
        else
        {
            boss->contAttackTime -= delta;

            if(boss->attack1)
            {
                boss->speed.x = 0;
                boss->speed.y = 400;
            }

            if(boss->attack2Left)
            {
                boss->speed.x = -400;
                boss->speed.y = 0;
            }

            if(boss->attack2Right)
            {
                boss->speed.x = 400;
                boss->speed.y = 0;
            }

            if(boss->attack3)
            {
                if(boss->atualY==1)
                    boss->speed.y = 400;
                if(boss->atualY==-1)
                    boss->speed.y = -400;

                if(boss->atualX==1)
                    boss->speed.x = 100;
                if(boss->atualX==-1)
                    boss->speed.x = -100;

            }
        }


        if(boss->pos.x<=xMin)
        {
            boss->pos.x = xMin;
            boss->contAttackTime = 0.0f;
            boss->atualX = 1;
            boss->speed.x = boss->defaultSpeed * boss->atualX;

        }
        else if(boss->pos.x>=xMax)
        {
            boss->pos.x = xMax;
            boss->contAttackTime = 0.0f;
            boss->atualX = -1;
            boss->speed.x = boss->defaultSpeed * boss->atualX;
        }

        if(boss->pos.y<=yMin)
        {
            boss->pos.y = yMin;
            boss->contAttackTime = 0.0f;
            boss->atualX = 1;
            boss->speed.y = boss->defaultSpeed * boss->atualY;
        }
        else if(boss->pos.y>=yMax)
        {
            boss->pos.y = yMax;
            boss->contAttackTime = 0.0f;
            boss->atualY = -1;
            boss->speed.y = boss->defaultSpeed * boss->atualY;
        }

        if(boss->contAttackTime<=0)
        {

            if(boss->speed.x != boss->defaultSpeed && boss->speed.x != -boss->defaultSpeed )
            {
                boss->speed.x = boss->defaultSpeed*boss->atualX;
            }
            if(boss->speed.y != boss->defaultSpeed && boss->speed.y != -boss->defaultSpeed )
            {
                boss->speed.y = boss->defaultSpeed*boss->atualY;
            }
        }

        if(boss->life == 12)
        {
             boss->speed.x = 0;
             boss->speed.y = 0;
        }
    }
    else
    {
        boss->speed.x *= 0.9;
        boss->speed.y += 20;
        if(boss->speed.y>=400) boss->speed.y = 400;
    }

    //=============UPDATE=POSITION================

    boss->pos.x += boss->speed.x * delta;
    boss->pos.y += boss->speed.y * delta;

    //=============UPDATE=HEAT=BOX================

    boss->collisionRecs  = createAndUpdateBossCollisionRec(boss);

    if (boss->dead==false && boss->life != 12)
        boss->visionRecs = createAndUpdateBossVisionRec(boss);

    //===============UPDATE=STATS=================

    if(boss->life<=0){boss->dead=true;}
}

BossVisionRec createAndUpdateBossVisionRec(Boss *boss)
{
    return (BossVisionRec)
    {
        .under = (Rectangle)
        {
            .x =  boss->pos.x,
            .y = boss->pos.y+boss->dim.y,
            .width = boss->dim.x,
            .height = 3*boss->dim.y,
        },
        .right = (Rectangle)
        {
            .x = boss->pos.x+boss->dim.x,
            .y = boss->pos.y,
            .width = 3*boss->dim.x,
            .height = boss->dim.y,
        },
        .left = (Rectangle)
        {
            .x = boss->pos.x-3*boss->dim.x,
            .y = boss->pos.y,
            .width = 3*boss->dim.x,
            .height = boss->dim.y,
        },
    };
}

void selectBossAttack(Boss *boss, Player *player)
{
    Rectangle playerRec = (Rectangle)
                        {
                            .x = player->pos.x,
                            .y = player->pos.y,
                            .width = player->dim.x,
                            .height = player->dim.y,
                        };

    if(CheckCollisionRecs(boss->visionRecs.under,playerRec))
    {
        boss->playerUnderZone = true;

        if(boss->contAttackCoolDown<=0)
        {

            if(GetRandomValue(0,1)==0)
            {
                boss->contAttackTime = boss->attack1Time;
                boss->attack1 = true;
            }

            boss->contAttackCoolDown = boss->attackCoolDown;
        }
    }
    else boss->playerUnderZone = false;

    if(CheckCollisionRecs(boss->visionRecs.left,playerRec))
    {
        boss->playerLeftZone = true;

        if(boss->contAttackCoolDown<=0)
        {

            if(GetRandomValue(0,1)==0)
            {
                boss->contAttackTime = boss->attack2Time;
                boss->attack2Left = true;
            }

            boss->contAttackCoolDown = boss->attackCoolDown;
        }
    }
    else boss->playerLeftZone = false;

    if(CheckCollisionRecs(boss->visionRecs.right,playerRec))
    {
        boss->playerRightZone = true;

        if(boss->contAttackCoolDown<=0)
        {

            if(GetRandomValue(0,1)==0)
            {
                boss->contAttackTime = boss->attack2Time;
                boss->attack2Right = true;
            }

            boss->contAttackCoolDown = boss->attackCoolDown;
        }
    }
    else boss->playerRightZone = false;


    if(boss->life<=10)
    {
        if(boss->contAttackCoolDown<=0)
        {

            if(GetRandomValue(0,4)==2)
            {
                boss->contAttackTime = boss->attack3Time;
                boss->attack3 = true;
            }

            boss->contAttackCoolDown = boss->attackCoolDown;
        }
    }


}


void drawBoss(Boss *boss)
{

    if(boss->life==12)
    {
        DrawTextureV(rm.gw.sleepingBoss, boss->pos, WHITE);
    }
    else
    {
        if(boss->dead==false)
        {
            if(boss->sufferingDamege)
                DrawTextureV(rm.gw.bossActive,boss->pos, RED);
            else
                DrawTextureV(rm.gw.bossActive,boss->pos, WHITE);
        }
        else
            DrawTextureV(rm.gw.portal,boss->pos, WHITE);
    }


    /*
    if(boss->playerUnderZone)
        DrawRectangleRec(boss->visionRecs.under,RED);
    else
        DrawRectangleRec(boss->visionRecs.under,ORANGE);

    if(boss->playerLeftZone)
        DrawRectangleRec(boss->visionRecs.left,RED);
    else
        DrawRectangleRec(boss->visionRecs.left,ORANGE);

    if(boss->playerRightZone)
        DrawRectangleRec(boss->visionRecs.right,RED);
    else
        DrawRectangleRec(boss->visionRecs.right,ORANGE);*/



}

