#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"
#include "player.h"

//========================================
//-----------------STRUCTS----------------


    //------BASIC-ENEMY------

typedef struct BasicEnemyCollisionRec
{
    Rectangle upper;
    Rectangle under;
    Rectangle left;
    Rectangle right;

}BasicEnemyCollisionRec;

typedef struct BasicEnemyKnockbackStatus
{
    bool knockbackR;
    bool knockbackL;
    bool knockbackUp;
    bool knockbackUn;
    float knockbackTime;

}BasicEnemyKnockbackStatus;


typedef struct BasicEnemy
{
    Vector2 pos;
    Vector2 speed;
    Vector2 dim;

    BasicEnemyCollisionRec collisionRecs;

    BasicEnemyKnockbackStatus knockbackStatus;

    int life;
    bool dead;
    bool haveCoins;

    Color cor;
    int texture;
    float contTime;
    int currentFrame;

    float defaultSpeed; //velocidade padrão de movimetno

    bool onFloor;

}BasicEnemy;

    //-------AIR-BASIC-ENEMY-------

typedef struct AirBasicEnemy
{
    Vector2 pos;
    Vector2 firstPos;
    Vector2 speed;
    Vector2 dim;

    BasicEnemyCollisionRec collisionRecs;

    BasicEnemyKnockbackStatus knockbackStatus;

    int life;
    bool dead;
    bool haveCoins;

    Color cor;
    int texture;
    bool glitching;
    float glitchTime;
    float contGlitchTime;

    float defaultSpeed;

}AirBasicEnemy;


typedef struct Enemies
{
    BasicEnemy *enemy1;
    AirBasicEnemy enemy2[50];

    int numberOfAirBasicEnemies;
    int numberOfBasicEnemies;

}Enemies;

//------------------------------------------
//==========================================
//----------------FUNCTIONS-----------------

BasicEnemy createBasicEnemies (Vector2 pos);

AirBasicEnemy createAirBasicEnemies(Vector2 pos, int number);

void updateEnemies (Enemies *enemies, float delta);

void updateBasicEnemies(BasicEnemy *enemy1, float delta);

void updateAirBasicEnemies(AirBasicEnemy *enemy2, float delta);

void applyKnockbackToEnemies (Enemies *enemies);

void applyKnockbackToBasicEnemies (BasicEnemy *enemy);

void applyKnockbackToAirBasicEnemies (AirBasicEnemy *enemy);

void drawEnemies (Enemies *enemies);

void drawBasicEnemies (BasicEnemy *enemy1);

void drawAirBasicEnemies (AirBasicEnemy *enemy2);

//----------------------------------------------
//==============================================
//--------------------BOSS----------------------

    //======================================
    //---------------STRUCTS----------------

typedef struct BossCollisionRec
{
    Rectangle upper;
    Rectangle under;
    Rectangle right;
    Rectangle left;

}BossCollisionRec;

typedef struct BossVisionRec
{
    Rectangle under;
    Rectangle right;
    Rectangle left;

}BossVisionRec;

typedef struct Boss
{
    Vector2 pos;
    Vector2 firstPos;
    Vector2 speed;
    int atualX;
    int atualY;
    Vector2 dim;

    BossCollisionRec collisionRecs;
    BossVisionRec visionRecs;

    int life;
    bool dead;
    bool haveCoins;

    Color cor;

    float defaultSpeed;

    bool attack1;
    bool attack2Left;
    bool attack2Right;
    bool attack3;

    float attack1Time;
    float attack2Time;
    float attack3Time;
    float attackCoolDown;
    float contAttackTime;
    float contAttackCoolDown;

    bool sufferingDamege;
    float limitDamegeTime;
    float contDamegeTime;

    bool playerUnderZone;
    bool playerRightZone;
    bool playerLeftZone;

}Boss;

Boss createBoss (Vector2 pos);

void updateBoss (Boss *boss, float delta);

BossVisionRec createAndUpdateBossVisionRec(Boss *boss);

void selectBossAttack(Boss *boss, Player *player);

void drawBoss(Boss *boss);


#endif // ENEMIES_H
