#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "raylib.h"
#include "player.h"
#include "blocks.h"
#include "weapons.h"
#include "enemies.h"
#include "coins.h"

//=======================================
//------COLLISIONS-PLAYER-FUNCITONS------

PlayerCollisionRec updatePlayerCollisionRecs(Player *player);

void DrawPlayerRecCollisionUnder(PlayerCollisionRec *recCollision);

//------CHECK-COLLISION-TYPES-----

bool checkPlayerBlockCollision_Upper(PlayerCollisionRec *collisionRec, Block *block);
bool checkPlayerBlockCollision_Under(PlayerCollisionRec *collisionRec, Block *block);
bool checkPlayerBlockCollision_Left(PlayerCollisionRec *collisionRec, Block *block);
bool checkPlayerBlockCollision_Right(PlayerCollisionRec *collisionRec, Block *block);

bool checkPlayerBasicEnemiesCollision_Upper(PlayerCollisionRec *collisionRec, BasicEnemy *enemy);
bool checkPlayerBasicEnemiesCollision_Under(PlayerCollisionRec *collisionRec, BasicEnemy *enemy);
bool checkPlayerBasicEnemiesCollision_Left(PlayerCollisionRec *collisionRec, BasicEnemy *enemy);
bool checkPlayerBasicEnemiesCollision_Right(PlayerCollisionRec *collisionRec, BasicEnemy *enemy);

bool checkPlayerAirBasicEnemiesCollision_Upper(PlayerCollisionRec *collisionRec, AirBasicEnemy *enemy);
bool checkPlayerAirBasicEnemiesCollision_Under(PlayerCollisionRec *collisionRec, AirBasicEnemy *enemy);
bool checkPlayerAirBasicEnemiesCollision_Left(PlayerCollisionRec *collisionRec, AirBasicEnemy *enemy);
bool checkPlayerAirBasicEnemiesCollision_Right(PlayerCollisionRec *collisionRec, AirBasicEnemy *enemy);

//========================================
//------COLLISIONS-ATTACKS-FUNCTIONS------

Rectangle createAndUpdatePlayerSwordCollisionRec(Player *player);
Rectangle deletePlayerSwordCollisionRec(Player *player);

bool checkBasicEnemiesPlayerSwordCollision_Left(BasicEnemyCollisionRec *collisionRec, PlayerSword *playerSword);
bool checkBasicEnemiesPlayerSwordCollision_Right(BasicEnemyCollisionRec *collisionRec, PlayerSword *playerSword);
bool checkBasicEnemiesPlayerSwordCollision_Up(BasicEnemyCollisionRec *collisionRec, PlayerSword *playerSword);
bool checkBasicEnemiesPlayerSwordCollision_default(BasicEnemy *enemy, PlayerSword *playerSword);
bool checkAirBasicEnemiesPlayerSwordCollision_default(AirBasicEnemy *enemy, PlayerSword *playerSword);

bool checkPlayerSwordBlocksCollision(Rectangle sword, Rectangle block);

    //--------ESPECIAL----------

bool checkBasicEnemiesHorizontalPowerCollision(BasicEnemy *enemy, HorizontalPower *power);
bool checkAirBasicEnemiesHorizontalPowerCollision(AirBasicEnemy *enemy, HorizontalPower *power);
bool checkBlocksHorizontalPowerCollision(Rectangle block, HorizontalPower *power);

bool checkSkillsPlayer(Skill *skill, Player *player);
bool checkCharmsPlayer(Charm *charms, Player *player);

bool checkSkillsPlayerClose(Skill *skill, Player *player);
bool checkCharmsPlayerClose(Charm *charms, Player *player);

//----------------------------------------
//========================================
//------COLLISIONS-ENEMIES-FUNCTIONS------

void createAndUpdateEnemiesCollisionRecs(Enemies *enemies);

BasicEnemyCollisionRec createAndUpdateBasicEnemiesCollisionsRec(BasicEnemy *enemy);

BasicEnemyCollisionRec createAndUpdateAirBasicEnemiesCollisionsRec(AirBasicEnemy *enemy);

bool checkBasicEnemiesBlockCollision_Upper(BasicEnemyCollisionRec *collisionRecs, Block *block);
bool checkBasicEnemiesBlockCollision_Under(BasicEnemyCollisionRec *collisionRecs, Block *block);
bool checkBasicEnemiesBlockCollision_Left(BasicEnemyCollisionRec *collisionRecs, Block *block);
bool checkBasicEnemiesBlockCollision_Right(BasicEnemyCollisionRec *collisionRecs, Block *block);

//----------------------------------------
//========================================
//------COLLISIONS-BOSS-FUNCTIONS------

BossCollisionRec createAndUpdateBossCollisionRec(Boss *boss);

bool checkBossBlockCollision_Upper(BossCollisionRec *collisionRecs, Block *block);
bool checkBossBlockCollision_Under(BossCollisionRec *collisionRecs, Block *block);
bool checkBossBlockCollision_Left(BossCollisionRec *collisionRecs, Block *block);
bool checkBossBlockCollision_Right(BossCollisionRec *collisionRecs, Block *block);


//----------------------------------------------
//==============================================
//--------------COINS-COLLISION-----------------

bool checkCoinsBlocksCollision(Coins *coin, Block *block);

bool checkCoinsPlayerCollision(Coins *coin, Player *player);




#endif // COLLISIONS_H
