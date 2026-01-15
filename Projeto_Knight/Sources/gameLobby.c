#include "raylib.h"
#include "gameLobby.h"
#include "blocks.h"
#include "collisions.h"
#include "gameWindow.h"
#include "resourceManager.h"
#include "coins.h"

void makeLobbyCollisionPlayerGrass(GameLobby *gl);
void makeLobbyCollisionPlayerStoreBlock(GameLobby *gl);
bool checkPlayerGrassCollision_Upper(PlayerCollisionRec *collisionRecs, Grass *grass);
bool checkPlayerGrassCollision_Under(PlayerCollisionRec *collisionRecs, Grass *grass);
bool checkPlayerGrassCollision_Left(PlayerCollisionRec *collisionRecs, Grass *grass);
bool checkPlayerGrassCollision_Right(PlayerCollisionRec *collisionRecs, Grass *grass);
bool checkPlayerStoreBlockCollision_Upper(PlayerCollisionRec *collisionRecs, StoreBlock *block);
bool checkPlayerStoreBlockCollision_Under(PlayerCollisionRec *collisionRecs, StoreBlock *block);
bool checkPlayerStoreBlockCollision_Left(PlayerCollisionRec *collisionRecs, StoreBlock *block);
bool checkPlayerStoreBlockCollision_Right(PlayerCollisionRec *collisionRecs, StoreBlock *block);

GameLobby createGameLobby(Player *player)
{
    GameLobby gl = (GameLobby)
    {
        .player = player,
        .numberOfBlocks= 0,
        .camera = (Camera2D)
        {
            .target={GetScreenWidth()/2, GetScreenHeight()/2},
            .offset = {0,0},
            .rotation = 0.0f,
            .zoom = 1.0f,
        },

        .nearBanch = false,
        .nearRoom = false,
        .nearComputer = false,
        .roomCamera = false,
        .gameIsSaved = false,

        .contRestTime = 0.0f,
        .restTime = 1.0f,

        .fadeScreenGL = 1.0f,
        .fadeScreenGL2 = 0.0f,
    };

    loadLobby(&gl,"maps/Vila.txt");

    return gl;

}

void loadLobby(GameLobby *gl, const char* arquivo)
{
    char *dados = LoadFileText(arquivo);
    if(!dados){return;}

    char *atual = dados;

    int contLines = 0;
    int contColumn = 0;
    int contBlocks = 0;
    int contGrass = 0;
    int contStoreBlocks = 0;
    int contCharms =0;

    while(*atual != '\0')
    {
        switch(*atual)
        {
            case '\n':
                contLines++;
                contColumn=0;
                break;

            case 'J':
            case 'j':
                gl->player->pos = (Vector2){contColumn*32,contLines*32};
                contColumn++;
                break;
            case 'F':
                gl->StoreWall = (Rectangle)
                {
                    .x = (contColumn-1)*32,
                    .y = (contLines-2)*32,
                    .width = 352,
                    .height = 192,
                };
                contColumn++;
                break;
            case 'C':
                gl->storeBlocks[contStoreBlocks] = createStoreBlock(
                        (Vector2){contColumn*32, contLines*32}
                    );
                 contColumn++;
                 contStoreBlocks++;
                 gl->numberOfStoreBlocks++;
                 break;
            case 'c': //charms
                if(contCharms==0)
                {
                    gl->storeCharms[contCharms] = createCharm(
                        (Vector2){contColumn*32+10, contLines*32}, contCharms+3
                    );
                }
                else
                {
                    gl->storeCharms[contCharms] = createCharm(
                            (Vector2){contColumn*32, contLines*32}, contCharms+3
                        );
                }
                contColumn++;
                contCharms++;
                gl->numberOfStoreCharms++;
                break;
            case 'p':
            case 'P':
                gl->blocks[contBlocks] = createBlock(
                    (Vector2){contColumn*32,contLines*32}
                );
                contColumn++;
                contBlocks++;
                gl->numberOfBlocks++;
                break;

            case 'G':
                gl->grass[contGrass] = createGrass(
                    (Vector2){contColumn*32,contLines*32}
                );
                contColumn++;
                contGrass++;
                gl->numberOfGrass++;
                break;

            case 'B':
                gl->Banch = (Rectangle)
                {
                    .x = contColumn*32,
                    .y = contLines*32,
                    .width = 32,
                    .height = 32,
                };
                contColumn++;
                break;

            case 'S':
                gl->Room = (Rectangle)
                {
                    .x = contColumn*32,
                    .y = contLines*32,
                    .width = 32,
                    .height = 32,
                };
                contColumn++;
                break;

             case 's':
                gl->Store = (Rectangle)
                {
                    .x = contColumn*32,
                    .y = contLines*32,
                    .width = 32,
                    .height = 32,
                };
                contColumn++;
                break;

            case 'M':
                gl->Computer = (Rectangle)
                {
                    .x = contColumn*32,
                    .y = contLines*32,
                    .width = 32,
                    .height = 32,
                };
                gl->posComputer = (Vector2){contColumn*32,contLines*32};
                contColumn++;
                break;

             case 'D':
                gl->DoorR = (Rectangle)
                {
                    .x = contColumn*32,
                    .y = contLines*32,
                    .width = 32,
                    .height = 32,
                };
                contColumn++;
                break;

            default:
                contColumn++;
                break;
        }

        atual++;
    }

    UnloadFileText(dados);

}

void inputAndUpdateGameLobby(GameLobby *gl, bool isFullscreen)
{
    int controlTP = 0;


    //-------------------------//
    float delta = GetFrameTime();
    //-------------------------//

    if(gl->player->status.resting==false)
        inputAndUpdatePlayer(gl->player, delta);

    updateInventory (gl->player);



    if(CheckCollisionRecs((Rectangle){.x = gl->player->pos.x,  .y = gl->player->pos.y, .width = gl->player->dim.x, .height = gl->player->dim.y}, gl->Banch))
        {
            if(IsKeyPressed(KEY_UP) && gl->player->status.resting==false)
            {
                gl->player->status.resting = true;
                gl->player->pos.x = gl->Banch.x+16;
                gl->player->pos.y += 10;
            }

            gl->nearBanch = true;

        }
        else gl->nearBanch = false;

    if(gl->player->status.resting)
    {
        gl->contRestTime+= GetFrameTime();

        if(gl->contRestTime>=gl->restTime)
        {
            gl->player->status.life++;
            gl->contRestTime = 0.0;
        }

        if(gl->player->status.life>=gl->player->status.maxLife)
            gl->player->status.life = gl->player->status.maxLife;
    }


    if(gl->player->status.resting && (IsKeyPressed(KEY_LEFT)||IsKeyPressed(KEY_RIGHT)))
    {
        gl->player->status.resting = false;
        gl->gameIsSaved = false;
    }



    if(CheckCollisionRecs((Rectangle){.x = gl->player->pos.x,  .y = gl->player->pos.y, .width = gl->player->dim.x, .height = gl->player->dim.y}, gl->Room))
        {
            if(IsKeyPressed(KEY_UP) && controlTP==0)
            {
                gl->player->speed.y = 0.0;
                gl->player->pos.x = gl->DoorR.x;
                gl->player->pos.y = gl->DoorR.y;
                gl->roomCamera = true;
                controlTP = 1;
            }

            gl->nearRoom = true;

        }
        else gl->nearRoom = false;

    if(CheckCollisionRecs((Rectangle){.x = gl->player->pos.x,  .y = gl->player->pos.y, .width = gl->player->dim.x, .height = gl->player->dim.y}, gl->DoorR))
        {
            if(IsKeyPressed(KEY_UP)&& controlTP==0)
            {
                gl->player->speed.y = 0.0;
                gl->player->pos.x = gl->Room.x;
                gl->player->pos.y = gl->Room.y;
                gl->roomCamera = false;
                controlTP = 1;
            }

            gl->nearRoomDoor = true;

        }
        else gl->nearRoomDoor = false;

    if(CheckCollisionRecs((Rectangle){.x = gl->player->pos.x,  .y = gl->player->pos.y, .width = gl->player->dim.x, .height = gl->player->dim.y}, gl->Computer))
        {
            gl->nearComputer = true;
        }
        else gl->nearComputer = false;

    makeLobbyCollisionPlayerBlock(gl);
    makeLobbyCollisionPlayerGrass(gl);
    makeLobbyCollisionPlayerStoreBlock(gl);
    takeCharms(gl);

    updateLobbyCamera(&gl->camera, gl->player, isFullscreen, gl->roomCamera);
}

void makeLobbyCollisionPlayerBlock(GameLobby *gl)
{
    Player *player = gl->player;
    PlayerCollisionRec *collisionRec = &gl->player->collisionRecs;

    for(int i =0; i<gl->numberOfBlocks; i++)
    {
        Block *block = &gl->blocks[i];

            //colisão por cima

            if(checkPlayerBlockCollision_Under(collisionRec ,block))
            {
                player->pos.y = block->pos.y-player->dim.y;
                player->status.onFloor = true;
                player->speed.y = 0.0f;
            }
            else if ( player->speed.y>0.0f)
                player->status.onFloor = false;


            if(checkPlayerBlockCollision_Upper(collisionRec ,block))
            {
                player->pos.y = block->pos.y + block->dim.y;
                player->speed.y = 0.0f;
            }

            if(checkPlayerBlockCollision_Right(collisionRec ,block))
            {
                player->pos.x = block->pos.x-player->dim.x;
                player->chiclete.rightWall = true;
            }

            if(checkPlayerBlockCollision_Left(collisionRec ,block))
            {
                player->pos.x=block->pos.x+block->dim.x;
                player->chiclete.leftWall = true;
            }
    }

}

void makeLobbyCollisionPlayerGrass(GameLobby *gl)
{
    Player *player = gl->player;
    PlayerCollisionRec *collisionRec = &gl->player->collisionRecs;

    for(int i =0; i<gl->numberOfGrass; i++)
    {
        Grass *grass = &gl->grass[i];

            //colisão por cima

            if(checkPlayerGrassCollision_Under(collisionRec ,grass))
            {
                player->pos.y = grass->pos.y-player->dim.y;
                player->status.onFloor = true;
                player->speed.y = 0.0f;
            }
            else if ( player->speed.y>0.0f)
                player->status.onFloor = false;


            if(checkPlayerGrassCollision_Upper(collisionRec ,grass))
            {
                player->pos.y = grass->pos.y + grass->dim.y;
                player->speed.y = 0.0f;
            }

            if(checkPlayerGrassCollision_Right(collisionRec ,grass))
            {
                player->pos.x = grass->pos.x-player->dim.x;
                player->chiclete.rightWall = true;
            }

            if(checkPlayerGrassCollision_Left(collisionRec ,grass))
            {
                player->pos.x=grass->pos.x+grass->dim.x;
                player->chiclete.leftWall = true;
            }
    }
}

void makeLobbyCollisionPlayerStoreBlock(GameLobby *gl)
{
    Player *player = gl->player;
    PlayerCollisionRec *collisionRec = &gl->player->collisionRecs;

    for(int i =0; i<gl->numberOfStoreBlocks; i++)
    {
        StoreBlock *block = &gl->storeBlocks[i];

            //colisão por cima

            if(checkPlayerStoreBlockCollision_Under(collisionRec ,block))
            {
                player->pos.y = block->pos.y-player->dim.y;
                player->status.onFloor = true;
                player->speed.y = 0.0f;
            }
            else if ( player->speed.y>0.0f)
                player->status.onFloor = false;


            if(checkPlayerStoreBlockCollision_Upper(collisionRec ,block))
            {
                player->pos.y = block->pos.y + block->dim.y;
                player->speed.y = 0.0f;
            }

            if(checkPlayerStoreBlockCollision_Right(collisionRec ,block))
            {
                player->pos.x = block->pos.x-player->dim.x;
                player->chiclete.rightWall = true;
            }

            if(checkPlayerStoreBlockCollision_Left(collisionRec ,block))
            {
                player->pos.x=block->pos.x+block->dim.x;
                player->chiclete.leftWall = true;
            }
    }

}

void makeLobbyCollisionBlocksPowersAndWeapons(GameLobby *gl)
{
    Player *player = gl->player;


    for(int i =0; i<gl->numberOfBlocks; i++)
    {
        Block *blocks = &gl->blocks[i];

        Rectangle block = (Rectangle)
        {
            .x = blocks->pos.x,
            .y = blocks->pos.y,
            .width = blocks->dim.x,
            .height = blocks->dim.y,
        };

        //------DEFAULT-SWORD-------

        if(player->inventory.equippedWeapons.defaultSword && (player->attackStatus.attackLeft || player->attackStatus.attackRight) && player->sword.activated)
        {

            Rectangle swordCollisionRec = player->sword.swordCollisionRec;

            if (checkPlayerSwordBlocksCollision(swordCollisionRec,block)&& player->status.lookingAtL)
            {
                 player->knockbackStatus.swordKnockbackL = true;
                 player->sword.activated = false;
            }

            if (checkPlayerSwordBlocksCollision(swordCollisionRec,block)&& player->status.lookingAtR)
            {
                 player->knockbackStatus.swordKnockbackR = true;
                 player->sword.activated = false;
            }
        }

        //-------HORIZONTAL-POWER-------

        if(player->powers.usingHorizontalPower)
        {
            HorizontalPower *power = &player->powers.horizontalPower;

            if(checkBlocksHorizontalPowerCollision(block, power))
            {
                power->contTime+=5.0;
            }
        }
    }

}


void takeCharms(GameLobby *gl)
{
    Player *player = gl->player;

    for(int h=0;h<gl->numberOfStoreCharms;h++)
    {
        Charm *charm = &gl->storeCharms[h];

        if(charm->available)
        {
            int number = charm->charmNumber;

            if(checkCharmsPlayerClose(charm, player))
                charm->playerNext = true;
            else charm->playerNext = false;

            if(checkCharmsPlayer(charm, player)&& IsKeyPressed(KEY_UP))
            {
                switch(number)
                {
                    case 3:
                        if(player->status.ticketsRU>=50)
                        {
                             player->inventory.colectedCharms.goldTickets = true;
                             charm->available=false;
                             player->status.ticketsRU -= 50;
                        }
                        break;
                    case 4:
                        if(player->status.ticketsRU>=100)
                        {
                            player->inventory.colectedCharms.debugSword = true;
                            charm->available=false;
                            player->status.ticketsRU -= 100;
                        }


                        break;
                    default:
                        break;
                }


            }
        }
    }

}

void updateLobbyCamera(Camera2D *camera, Player *player, bool isFullscreen, bool roomCamera)
{
    if(isFullscreen==false)
    {
        if(roomCamera==false)
        {
            if (player->pos.x <= 704 && player->pos.y <= 372)
            {
                camera->target= (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                camera->rotation = 0.0f;
                camera->zoom = 1.0f;
            }
            else if (player->pos.x >= 448 && player->pos.x < 896 && player->pos.y > 384 && player->pos.y <= 800)
            {
                camera->target= (Vector2) {592,player->pos.y+(player->dim.y/2)-100};
                camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                camera->rotation = 0.0f;
                camera->zoom = 1.5f;
            }
            else
            {
                if(player->pos.x <= 1152)
                {
                    camera->target= (Vector2) {1152,660};
                    camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                    camera->rotation = 0.0f;
                    camera->zoom = 1.3f;
                }
                else if(player->pos.x >= 2624-32)
                {
                    camera->target= (Vector2) {2624-32,660};
                    camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                    camera->rotation = 0.0f;
                    camera->zoom = 1.3f;
                }
                else
                {
                    camera->target= (Vector2) {player->pos.x+(player->dim.x/2),660};
                    camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                    camera->rotation = 0.0f;
                    camera->zoom = 1.3f;
                }
            }
        }
        else if(roomCamera)
        {
            camera->target= (Vector2) {player->pos.x+(player->dim.x/2),player->pos.y+(player->dim.y/2)-64};
            camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
            camera->rotation = 0.0f;
            camera->zoom = 1.3f;
        }
    }
    else
    {
       if(roomCamera==false)
        {
            if (player->pos.x <= 704 && player->pos.y <= 372)
            {
                camera->target= (Vector2) {400,200};
                camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                camera->rotation = 0.0f;
                camera->zoom = 2.5f;
            }
            else if (player->pos.x >= 448 && player->pos.x < 896 && player->pos.y > 384 && player->pos.y <= 800)
            {
                camera->target= (Vector2) {592,player->pos.y+(player->dim.y/2)-100};
                camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                camera->rotation = 0.0f;
                camera->zoom = 3.5f;
            }
            else
            {
                if(player->pos.x <= 1300)
                {
                    camera->target= (Vector2) {1150,680};
                    camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                    camera->rotation = 0.0f;
                    camera->zoom = 3.3f;
                }
                else if(player->pos.x >= 2480)
                {
                    camera->target= (Vector2) {2480,612};
                    camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                    camera->rotation = 0.0f;
                    camera->zoom = 2.3f;
                }
                else
                {
                    camera->target= (Vector2) {player->pos.x+(player->dim.x/2),612};
                    camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                    camera->rotation = 0.0f;
                    camera->zoom = 2.3f;
                }
            }
        }
        else if(roomCamera)
        {
            camera->target= (Vector2) {3442,686};
            camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
            camera->rotation = 0.0f;
            camera->zoom = 4.5f;
        }
    }
}




void drawGameLobby (GameLobby *gl, bool isFullscreen)
{

    BeginDrawing();

    ClearBackground (SKYBLUE);

    BeginMode2D(gl->camera);

    DrawTexture(rm.gl.bench,gl->Banch.x,gl->Banch.y, WHITE);

    DrawTexturePro(rm.gl.storeWall,
                    (Rectangle){0,0,rm.gl.storeWall.width, rm.gl.storeWall.height},
                    (Rectangle) {gl->StoreWall.x,gl->StoreWall.y+10,rm.gl.storeWall.width+64,rm.gl.storeWall.height+64},
                    (Vector2){0.0f,0.0f},
                    0.0f,
                    WHITE);

    for (int s =0; s<gl->numberOfStoreBlocks; s++)
    {
        drawStoreBlock(&gl->storeBlocks[s]);
    }

    //DrawRectangleRec(gl->Room, WHITE);

    DrawTexturePro(rm.gl.store,
                    (Rectangle){0,0,rm.gl.store.width, rm.gl.store.height},
                    (Rectangle) {gl->Room.x-32,gl->Room.y-96,rm.gl.store.width,rm.gl.store.height},
                    (Vector2){0.0f,0.0f},
                    0.0f,
                    WHITE);

    //DrawRectangleRec(gl->Store, RED);
    //DrawRectangleRec(gl->DoorR, WHITE);
    //DrawRectangleRec(gl->Computer, BLACK);

    DrawTexture(rm.gl.SpriteComputer,gl->Computer.x,gl->Computer.y-32, WHITE);

    for(int h=0;h<gl->numberOfStoreCharms;h++)
    {
        drawCharms(&gl->storeCharms[h]);
    }

    drawPlayer(gl->player);

    if(gl->nearBanch && gl->player->status.resting==false)
        DrawText(TextFormat("DESCANSAR"), gl->Banch.x,gl->Banch.y-16,15, WHITE);

    if(gl->nearRoom)
        DrawText(TextFormat("ENTRAR"), gl->Room.x,gl->Room.y-16,15, WHITE);

    if(gl->nearRoomDoor)
        DrawText(TextFormat("SAIR"), gl->DoorR.x,gl->DoorR.y-16,15, WHITE);

    if(gl->nearComputer)
        DrawText(TextFormat("PRESS ENTER"), gl->Computer.x-32,gl->Computer.y-48,15, GREEN);

    for (int i =0; i<gl->numberOfBlocks; i++)
    {
        drawBlock(&gl->blocks[i]);
    }
    for (int g =0; g<gl->numberOfGrass; g++)
    {
        drawGrass(&gl->grass[g]);
    }

    EndMode2D();

    drawHud(gl->player, isFullscreen);

        gl->fadeScreenGL -= 0.2f*GetFrameTime();
        if(gl->fadeScreenGL<0.0f) gl->fadeScreenGL = 0.0f;

        DrawRectangle(0,0,1920, 1080, (Color){0,0,0,(unsigned char)(gl->fadeScreenGL*255)});

        if(gl->fadeScreenGL>0.0f)
            DrawText("CODEKNIGHT", ((GetScreenWidth()/2) - 240), ((GetScreenHeight()/2) - 34), 64, GREEN);

    if(gl->player->status.openInventory)
        drawInventory(gl->player,isFullscreen);

    EndDrawing();
}

void resetGameLobby(GameLobby *gl, Vector2 startPos)
{
    if(!gl) return;

    // 1. Reseta Posição e Estados do Player no Lobby
    gl->player->pos = startPos;
    gl->player->speed = (Vector2){0, 0};
    gl->player->status.resting = false; // Garante que ele não nasça "sentado"
    gl->player->status.onFloor = false;

    // 2. Reseta Flags de Interação
    gl->nearBanch = false;
    gl->nearRoom = false;
    gl->nearComputer = false;
    gl->nearRoomDoor = false;

    // 3. Reseta Câmera e Visualização
    gl->roomCamera = false; // Garante que sai do modo "quarto"
    gl->fadeScreenGL = 1.0f; // Reinicia o fade preto para clarear suavemente
    gl->fadeScreenGL2 = 1.0f;

    // Reseta valores padrão da câmera
    gl->camera.zoom = 1.0f;
    gl->camera.rotation = 0.0f;
    gl->camera.offset = (Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    gl->camera.target = gl->player->pos; // Foca imediatamente no player
}

    //============PLAYER-GRASS==============

//------------UPPERplayer-COLLISION-------------
bool checkPlayerGrassCollision_Upper(PlayerCollisionRec *collisionRecs, Grass *grass)
{
    return CheckCollisionRecs(collisionRecs->upper,(Rectangle){.x = grass->pos.x, .y = grass->pos.y, .width = grass->dim.x, .height = grass->dim.y});
}
//------------UNDERplayer-COLLISION-------------
bool checkPlayerGrassCollision_Under(PlayerCollisionRec *collisionRecs, Grass *grass)
{
    return CheckCollisionRecs(collisionRecs->under,(Rectangle){.x = grass->pos.x, .y = grass->pos.y, .width = grass->dim.x, .height = grass->dim.y});
}
//-----------LEFTplayer-COLLISION---------------
bool  checkPlayerGrassCollision_Left(PlayerCollisionRec *collisionRecs, Grass *grass)
{
    return CheckCollisionRecs(collisionRecs->left,(Rectangle){.x = grass->pos.x, .y = grass->pos.y, .width = grass->dim.x, .height = grass->dim.y});
}
//-----------RIGHTplayer-COLLISION--------------
bool  checkPlayerGrassCollision_Right(PlayerCollisionRec *collisionRecs, Grass *grass)
{
    return CheckCollisionRecs(collisionRecs->right,(Rectangle){.x = grass->pos.x, .y = grass->pos.y, .width = grass->dim.x, .height = grass->dim.y});
}

     //============PLAYER-STOREBLOCKS==============

//------------UPPERplayer-COLLISION-------------
bool checkPlayerStoreBlockCollision_Upper(PlayerCollisionRec *collisionRecs, StoreBlock *block)
{
    return CheckCollisionRecs(collisionRecs->upper,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}
//------------UNDERplayer-COLLISION-------------
bool checkPlayerStoreBlockCollision_Under(PlayerCollisionRec *collisionRecs, StoreBlock *block)
{
    return CheckCollisionRecs(collisionRecs->under,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}
//-----------LEFTplayer-COLLISION---------------
bool  checkPlayerStoreBlockCollision_Left(PlayerCollisionRec *collisionRecs, StoreBlock *block)
{
    return CheckCollisionRecs(collisionRecs->left,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}
//-----------RIGHTplayer-COLLISION--------------
bool  checkPlayerStoreBlockCollision_Right(PlayerCollisionRec *collisionRecs, StoreBlock *block)
{
    return CheckCollisionRecs(collisionRecs->right,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}
