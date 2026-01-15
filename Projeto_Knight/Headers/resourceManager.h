#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "raylib.h"

typedef struct MenuTextures
{
    Texture2D normalStartButton;
    Texture2D mouseStartButton;
    Texture2D clickStartButton;

    Texture2D normalLoadButton;
    Texture2D mouseLoadButton;
    Texture2D clickLoadButton;

    Texture2D Save1LoadButton;
    Texture2D Save2LoadButton;
    Texture2D Save3LoadButton;
    Texture2D BackMenuButton;

    Texture2D normalHelpButton;
    Texture2D mouseHelpButton;
    Texture2D clickHelpButton;

    Texture2D normalCloseButton;
    Texture2D mouseCloseButton;
    Texture2D clickCloseButton;


    Texture2D bigNormalStartButton;
    Texture2D bigMouseStartButton;

    Texture2D bigNormalLoadButton;
    Texture2D bigMouseLoadButton;

    Texture2D bigSave1LoadButton;
    Texture2D bigSave2LoadButton;
    Texture2D bigSave3LoadButton;
    Texture2D bigBackMenuButton;

    Texture2D bigNormalHelpButton;
    Texture2D bigMouseHelpButton;

    Texture2D bigNormalCloseButton;
    Texture2D bigMouseCloseButton;

}MenuTextures;

typedef struct PauseTextures
{
    Texture2D normalReturnButton;
    Texture2D mouseReturnButton;

    Texture2D normalSaveButton;
    Texture2D mouseSaveButton;

    Texture2D normalLeaveButton;
    Texture2D mouseLeaveButton;

    Texture2D FullscreenButton;

    Texture2D normalReturnButtonG;
    Texture2D mouseReturnButtonG;

    Texture2D normalSaveButtonG;
    Texture2D mouseSaveButtonG;

    Texture2D normalLeaveButtonG;
    Texture2D mouseLeaveButtonG;

    Texture2D MinimizeButton;

}PauseTextures;

typedef struct GameLobbyTextures
{
    Texture2D bench;
    Texture2D grass;
    Texture2D store;
    Texture2D storeWall;
    Texture2D storeBlock;
    Texture2D SpriteComputer;

}GameLobbyTextures;

typedef struct GameWorldTextures
{
    Texture2D defaultTile;

    Texture2D horizontalPowerA;
    Texture2D horizontalPowerB;

    Texture2D ticketRU;


    Texture2D glitch1;
    Texture2D glitch2;

    Texture2D skullBug[2];

    Texture2D sleepingBoss;
    Texture2D bossActive;

    Texture2D portal;


}GameWorldTextures;

typedef struct PlayerTextures
{

    Texture2D sevenHearts;
    Texture2D sixHearts;
    Texture2D fiveHearts;
    Texture2D fourHearts;
    Texture2D treeHearts;
    Texture2D twoHearts;
    Texture2D oneHearts;

    Texture2D hit7Heart;
    Texture2D hit6Heart;
    Texture2D hit5Heart;
    Texture2D hit4Heart;
    Texture2D hit3Heart;
    Texture2D hit2Heart;

    Texture2D sevenHeartsG;
    Texture2D sixHeartsG;
    Texture2D fiveHeartsG;
    Texture2D fourHeartsG;
    Texture2D treeHeartsG;
    Texture2D twoHeartsG;
    Texture2D oneHeartsG;

    Texture2D hit7HeartG;
    Texture2D hit6HeartG;
    Texture2D hit5HeartG;
    Texture2D hit4HeartG;
    Texture2D hit3HeartG;
    Texture2D hit2HeartG;

    Texture2D zeroAura;
    Texture2D oneAura;
    Texture2D twoAura;
    Texture2D treeAura;
    Texture2D fourAura;
    Texture2D fiveAura;
    Texture2D sixAura;
    Texture2D sevenAura;
    Texture2D eightAura;
    Texture2D nineAura;
    Texture2D tenAura;
    Texture2D elevenAura;
    Texture2D twelveAura;

    Texture2D zeroAuraG;
    Texture2D oneAuraG;
    Texture2D twoAuraG;
    Texture2D treeAuraG;
    Texture2D fourAuraG;
    Texture2D fiveAuraG;
    Texture2D sixAuraG;
    Texture2D sevenAuraG;
    Texture2D eightAuraG;
    Texture2D nineAuraG;
    Texture2D tenAuraG;
    Texture2D elevenAuraG;
    Texture2D twelveAuraG;

    Texture2D auraLeek;
    Texture2D auraLeekG;

    Texture2D ticketsRU1;
    Texture2D ticketsRU2;

    Texture2D ticketsRU1G;
    Texture2D ticketsRU2G;

    //------------------//

    Texture2D restingPlayer[2];
    Texture2D normalPlayer;
    Texture2D playerRunning[2];
    Texture2D playerJumping[2];
    Texture2D playerFalling[2];
    Texture2D playerDash;
    Texture2D playerDoubleJump;
    Texture2D playerChiclete;
    Texture2D playerAttack;
    Texture2D playerAttackUp;
    Texture2D playerJumpAttackUp;
    Texture2D playerAttackDown;
    Texture2D playerHealing;

    Texture2D swordAttack;



}PlayerTextures;

typedef struct CharmsTextures
{
    Texture2D gamerHeart;
    Texture2D programmerHands;
    Texture2D goldTickets;
    Texture2D debugSword;
    Texture2D plusEgo;

}CharmsTextures;

typedef struct ResourceManager
{
    MenuTextures menu;
    PauseTextures pause;
    GameLobbyTextures gl;
    GameWorldTextures gw;
    PlayerTextures player;
    CharmsTextures charm;

    Music defaultMusic;
    Music bossMusic;

}ResourceManager;

extern ResourceManager rm;

void loadResources();

void unloadResouces();



#endif // RESOURCEMANAGER_H
