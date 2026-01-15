#include "raylib.h"
#include "weapons.h"

//==========================================
//---------------FUNCTIONS------------------

PlayerSword createPlayerSword () //inicia a espada
{
    return (PlayerSword)
    {
        .pos = {0}, //deixa a posição zerada por enquanto
        .dim = (Vector2){0,0}, //tamanho
        .cor = WHITE, //cor
        .up = true, //booleanos que podem ser usados para determinar as direções possiveis do ataque
        .down = true,
        .left = true,
        .right = true,

        .activated = false,

        //contagem de frames para os png depois
        .currentFrame = 0,
        .numberOfFrames =2,
        .contTime = 0.0f,
        .timeToTheNextFrame = 1.0f,
    };
}

void updatePlayerSword (Player *player) // atualiza a posição da espada ao atacar
{
    if (player->attackStatus.attackRight)
    {
        player->sword.pos = (Vector2){player->pos.x+player->dim.x,player->pos.y+player->dim.y/2};
        player->sword.dim = (Vector2){40,8};
    }
    else if (player->attackStatus.attackLeft)
    {
        player->sword.pos = (Vector2) {player->pos.x-player->dim.x-8,player->pos.y+player->dim.y/2};
        player->sword.dim = (Vector2){40,8};
    }
    else if (player->attackStatus.attackUp)
    {
        player->sword.pos = (Vector2){player->pos.x+(player->dim.x/2)-4, player->pos.y-40};
        player->sword.dim = (Vector2){8,40};
    }
    else if (player->attackStatus.attackDown)
    {
        player->sword.pos = (Vector2){player->pos.x+(player->dim.x/2)-4, player->pos.y+player->dim.y};
        player->sword.dim = (Vector2){8,40};
    }

}

void drawPlayerSword(Player *player) // desenhaa espada durante o ataque
{
    if (player->attackStatus.attackRight || player->attackStatus.attackLeft || player->attackStatus.attackUp || player->attackStatus.attackDown)
    {
        DrawRectangleV(player->sword.pos, player->sword.dim, player->sword.cor);
    }
}
