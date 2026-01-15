#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "coins.h"
#include "resourceManager.h"


Skill createSkill(Vector2 pos, int number)
{
    return (Skill)
    {
        .pos = pos,
        .dim = (Vector2){16,16},
        .cor = BLUE,
        .skilNumber = number,
        .available = true,
        .playerNext = false,
    };
}

Charm createCharm(Vector2 pos, int number)
{
    return (Charm)
    {
        .pos = pos,
        .dim = (Vector2){10,10},
        .cor = VIOLET,
        .charmNumber = number,
        .available = true,
        .playerNext = false,
    };
}

LostItens createLostItens(Vector2 pos, int number)
{
    return (LostItens)
    {
        .posXdim = (Rectangle)
        {
            .x = pos.x,
            .y = pos.y,
            .width = 22,
            .height = 16,
        },
        .cor = SKYBLUE,
        .itemNumber = number,
        .available = true,
        .playerNext =  false,
    };
}

void drawSkills(Skill *skill)
{
    if(skill->available)
    {
        DrawRectangleV(skill->pos, skill->dim,skill->cor);
        if (skill->playerNext)
        {
            DrawText(TextFormat("PEGAR: W"), skill->pos.x-16,skill->pos.y-16,5, GREEN);
        }
    }
}

void drawCharms(Charm *charm)
{
    Vector2 updatePos = (Vector2){charm->pos.x-11,charm->pos.y-11};

    if(charm->available)
    {
        //DrawRectangleV(charm->pos, charm->dim,charm->cor);

        switch(charm->charmNumber)
        {
        case 0:
            DrawTextureV(rm.charm.gamerHeart,updatePos,charm->cor );
            break;
        case 1:
            DrawTextureV(rm.charm.programmerHands,updatePos,charm->cor );
            break;
        case 2:
            DrawTextureV(rm.charm.plusEgo, updatePos,charm->cor );
            break;
        case 3:
            DrawTextureV(rm.charm.goldTickets, updatePos,charm->cor );
            break;
        case 4:
            DrawTextureV(rm.charm.debugSword,updatePos,charm->cor );
            break;
        }


        if (charm->playerNext && charm->charmNumber<3)
        {
            DrawText(TextFormat("PEGAR"), charm->pos.x-16,charm->pos.y-16,5, GREEN);
        }
        else if (charm->playerNext && charm->charmNumber==3)
        {
             DrawText(TextFormat("COMPRAR:\n50 ticketsRU"), charm->pos.x-32,charm->pos.y-16,5, GREEN);
        }
        else if (charm->playerNext && charm->charmNumber==4)
        {
             DrawText(TextFormat("COMPRAR:\n100 ticketsRU"), charm->pos.x-32,charm->pos.y-16,5, GREEN);
        }
    }
}

void drawLostItens(LostItens *lostItem)
{
    if(lostItem->available)
    {
        DrawRectangleRec(lostItem->posXdim, lostItem->cor);
        if(lostItem->playerNext)
        {
            DrawText(TextFormat("PEGAR"), lostItem->posXdim.x-16,lostItem->posXdim.y-16,5, SKYBLUE);
        }
    }
}


//=====================================
//-------------TICKETSRU---------------

Coins summonCoinsForBasicEnemies(BasicEnemy *enemy, int number)
{

    return (Coins)
    {
        .pos = (Vector2){enemy->pos.x+(enemy->dim.x/2),enemy->pos.y+(enemy->dim.y/2)},
        .dim = (Vector2){8,8},
        .speed = (Vector2){100*number,-500},
        .friction = 0.95f,
        .cor = YELLOW,
        .available = true,
    };
}

Coins summonCoinsForAirBasicEnemies(AirBasicEnemy *enemy, int number)
{

    return (Coins)
    {
        .pos = (Vector2){enemy->pos.x+(enemy->dim.x/2),enemy->pos.y+(enemy->dim.y/2)},
        .dim = (Vector2){8,8},
        .speed = (Vector2){100*number,-500},
        .friction = 0.95f,
        .cor = YELLOW,
        .available = true,
    };
}

Coins summonCoinsForBoss(Boss *boss, int number)
{
    return (Coins)
    {
        .pos = (Vector2){boss->pos.x+(boss->dim.x/2),boss->pos.y+(boss->dim.y/2)},
        .dim = (Vector2){8,8},
        .speed = (Vector2){10*number,-500},
        .friction = 0.95f,
        .cor = YELLOW,
        .available = true,
    };
}



void drawCoins(Coins *coin)
{
    if(coin->available)
        DrawTextureV(rm.gw.ticketRU,coin->pos,coin->cor);
}
