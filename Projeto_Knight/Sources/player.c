#include "raylib.h"
#include "player.h"
#include "weapons.h"
#include "collisions.h"
#include "resourceManager.h"

#define GRAVITY 1500.0
#define MAX_SPEED_FALL 400.0

//===============================================
//----------------CREATE-PLAYER------------------

Player createNewPlayer (Vector2 dim, Color cor)
{
    Player newPlayer = (Player)
        {
            .pos = {0},
            .speed = {0},
            .dim = dim,
            .cor = cor,

            .collisionRecs = {{0}},

            .status = (PlayerStatus)
            {
                .life = 5,
                .maxLife = 5,
                .dead = false,
                .aura = 0,
                .healing = false,
                .healingTime = 1.5f,
                .contHealingTime = 0.0,
                .sufferingDamege = false,
                .resting = false,
                .ticketsRU = 0,
                .defaultSpeed = 200.0,
                .onFloor = false,
                .lookingAtR = true,
                .lookingAtL = false,
                .nextToCharm = false,
                .nextToSkill = false,
                .invulnerable = false,
                .invulnerableTime = 2.0f,
                .contInvulnerableTime = 0.0f,

            },

            .powers = (SpecialAttacks)
            {
                .horizontalPowerActive = false,
                .usingHorizontalPower = false,
                .horizontalPower = (HorizontalPower)
                {
                    .pos = {0},
                    .dim = {0},
                    .speed = (Vector2){0,0},
                    .cor = WHITE,
                    .currentFrame = 0,
                    .numberOfFrames=0,
                    .contTime=0.0,
                    .contTextureTime=0.0,
                    .attackTime = 4.0,
                    .timeToTheNextFrame=0.25,
                },
            },

            .inventory = (PlayerInventory)
            {
                .colectedCharms = (PlayerCharms)
                {
                    .goldTickets = false,
                    .debugSword = false,
                    .plusEgo = false,
                    .gamerHeart = false,
                    .programmerHands = false,
                },
                .equippedCharms = (PlayerCharms)
                {
                    .goldTickets = false,
                    .debugSword = false,
                    .plusEgo = false,
                    .gamerHeart = false,
                    .programmerHands = false,
                },
                .equippedWeapons = (PlayerWeapons)
                {
                    .defaultSword = true,
                },
                .teclaTab = false,
                .doubleJump = false,
                //.chiclete = true,

            },



            .sword = createPlayerSword(),


            .knockbackStatus = (KnockbackStatus)
            {
                .swordKnockbackR = false,
                .swordKnockbackL = false,
                .swordKnockbackUp = false,
                .knockbackR = false,
                .knockbackL = false,
                .knockbackUp = false,
                .knockbackUn = false,
                .knockbackTime = 0.0f,
            },

            .jumpStatus = (JumpStatus)
            {
                .canJump = false,
                .wasOnFloor = false,
                .canDoubleJump = false,
                .defaultJumpForce = 400.0f,
                .jumpBoostForce = 20.0f,
                .isJumping = false,
                .jumpTime = 0.0f,
                .jumpTimeMax = 0.25f,
            },

            .dashStatus = (DashStatus)
            {
                .canDash = true,
                .dashSpeed = 400.0,
                .dashTime = 0.0f,
            },

            .attackStatus = (AttackStatus)
            {
                .attacking = false,
                .attackRight = false,
                .attackLeft = false,
                .attackUp = false,
                .attackDown = false,
                .attackTime = 0.35f,
                .timeToTheNextAttack = 1.0f,
                .contTimeToNextAttack = 0.0f,
            },

            .currentFrame = 0,
            .numberOfFrames = 0,
            .contTime = 0.0f,
            .timeToTheNextFrame = 0.5f,

            .progress = 3,
            .inLevel = false,

        };

        return newPlayer;
}

//-----------------------------------------------
//===============================================
//---------------INPUT-AND-UPDATE----------------

void inputAndUpdatePlayer(Player *player, float delta)
{
    if(player->inventory.equippedCharms.plusEgo)
    {
        if(player->status.aura>=25)
            player->status.aura=25;
    }
    else
        if(player->status.aura>=13)
            player->status.aura=13;

    if(player->inventory.equippedCharms.gamerHeart)
    {
        player->status.maxLife = 7;
        if(player->status.life>=7)
            player->status.life =7;
    }
    else
    {
        player->status.maxLife = 5;
        if(player->status.life>=5)
            player->status.life =5;
    }





    //============MOVESET============
    //-------HORIZONTAL-MOVES--------

    if (player->knockbackStatus.knockbackTime<=0 && player->status.healing==false ) // confere se não está sofrendo um knockback
    {
        if(player->dashStatus.dashTime<=0)
        {
            if(IsKeyDown(KEY_RIGHT)) //indo para a direita
            {
                player->speed.x = player->status.defaultSpeed; //começa o movimento
                player->status.lookingAtR = true; //esta olhando para a direita
                player->status.lookingAtL = false; // não esta olhando para a esquerda
            }
            else if (IsKeyDown(KEY_LEFT))// indo para a esquerda
            {
                player->speed.x = -player->status.defaultSpeed; //começa o movimento negativo
                player->status.lookingAtR = false; // não esta olhando para a direita
                player->status.lookingAtL = true; // esta olhando para a esquerda
            }
            else
            {
                player->speed.x *= 0.8f;
                if(player->speed.x<10.0f && player->speed.x>-10.0f)
                    player->speed.x =0.0f; // se não esta se movendo velocidade é zero
            }
        }
    }
    else // caso esteja sofrendo um knockback
    {
        player->knockbackStatus.knockbackTime -= delta; // conta o tempo
        player->speed.x *= 0.9; // reduz a velocidade até o fim do tempo
    }

    if(player->inventory.teclaTab)
    {
        if(player->dashStatus.canDash)
        {
            if(IsKeyPressed(KEY_LEFT_SHIFT) && player->status.lookingAtL)
            {
                player->dashStatus.canDash =false;
                player->speed.x = -player->dashStatus.dashSpeed;
                player->speed.y = 0.0;
                player->dashStatus.dashTime = 0.25f;
            }

            if(IsKeyPressed(KEY_LEFT_SHIFT) && player->status.lookingAtR)
            {
                player->dashStatus.canDash =false;
                player->speed.x = player->dashStatus.dashSpeed;
                player->speed.y = 0.0;
                player->dashStatus.dashTime = 0.25f;
            }
        }
        else
        {
            player->dashStatus.dashTime -= delta;
            if(player->dashStatus.dashTime<=-0.5 && player->status.onFloor)
                player->dashStatus.canDash = true;
        }
    }

    //-----------ATTACKS-----------

    if (IsKeyPressed(KEY_X) && player->status.lookingAtR && player->status.lookingUp==false && player->status.lookingDown==false && player->attackStatus.attacking==false && player->status.healing==false) // confere se a tecla do ataque foi acionada, a direção, e se ja esta atacando
    {
        player->attackStatus.attackRight = true; //inicia o ataque
        player->attackStatus.contTimeToNextAttack = 0.0f; //recomeça o timer
        player->attackStatus.attacking = true; // esta atacando

        player->sword.activated =true;
    }
    else
    {
        player->attackStatus.contTimeToNextAttack += delta; //conta tempo

        if( player->attackStatus.contTimeToNextAttack >= player->attackStatus.attackTime) //confere se ja passou o tempo da animação
        {
            player->attackStatus.attackRight = false; //encerra o ataque
            player->sword.activated =false;
        }

        if(player->attackStatus.contTimeToNextAttack >= player->attackStatus.timeToTheNextAttack) // ja pode dar o proximo ataque?
        {
            player->attackStatus.attacking = false; //encerra por completo a ação
            player->attackStatus.contTimeToNextAttack = 0.0f; // zera o contador
        }

    }

    if (IsKeyPressed(KEY_X) && player->status.lookingAtL && player->status.lookingUp==false && player->status.lookingDown==false && player->attackStatus.attacking==false && player->status.healing==false) // confere se a tecla do ataque foi acionada, a direção, e se ja esta atacando
    {
        player->attackStatus.attackLeft = true;
        player->attackStatus.contTimeToNextAttack = 0.0f;
        player->attackStatus.attacking = true;

        player->sword.activated =true;
    }
    else
    {
        player->attackStatus.contTimeToNextAttack += delta;

        if( player->attackStatus.contTimeToNextAttack >= player->attackStatus.attackTime)
        {
            player->attackStatus.attackLeft = false;
            player->sword.activated =false;
        }

        if(player->attackStatus.contTimeToNextAttack >= player->attackStatus.timeToTheNextAttack)
        {
            player->attackStatus.attacking = false;
            player->attackStatus.contTimeToNextAttack = 0.0f;
        }

    }

            //-----ESPECIAL-ATTACKS-----

    if (IsKeyPressed(KEY_F)&& player->powers.horizontalPowerActive && player->powers.usingHorizontalPower==false  && player->status.healing==false)
    {
        if(player->inventory.equippedCharms.plusEgo)
        {
            if(player->status.aura>=12)
            {
                player->status.aura-= 12;

                player->powers.usingHorizontalPower=true;

                player->powers.horizontalPower.contTextureTime = 0.0f;

                player->powers.horizontalPower.dim = (Vector2){32,32};

                player->powers.horizontalPower.pos = (Vector2){player->pos.x+player->dim.x, player->pos.y-player->powers.horizontalPower.dim.y/2};

                if (player->status.lookingAtL)
                {
                    player->powers.horizontalPower.speed.x = -400;
                    player->powers.direction = 0;
                    player->powers.horizontalPower.pos = (Vector2){player->pos.x, player->pos.y-player->powers.horizontalPower.dim.y/2};

                }
                else
                {
                    player->powers.horizontalPower.speed.x = 400;
                    player->powers.direction = 1;
                    player->powers.horizontalPower.pos = (Vector2){player->pos.x+player->dim.x, player->pos.y-player->powers.horizontalPower.dim.y/2};
                }
            }
        }
        else
        {
            if(player->status.aura>=3)
            {
                player->status.aura -= 3;

                player->powers.usingHorizontalPower=true;

                player->powers.horizontalPower.contTextureTime = 0.0f;

                player->powers.horizontalPower.dim = (Vector2){32,32};

                player->powers.horizontalPower.pos = (Vector2){player->pos.x+player->dim.x, player->pos.y-player->powers.horizontalPower.dim.y/2};

                if (player->status.lookingAtL)
                {
                    player->powers.horizontalPower.speed.x = -400;
                    player->powers.direction = 0;
                    player->powers.horizontalPower.pos = (Vector2){player->pos.x, player->pos.y-player->powers.horizontalPower.dim.y/2};

                }
                else
                {
                    player->powers.horizontalPower.speed.x = 400;
                    player->powers.direction = 1;
                    player->powers.horizontalPower.pos = (Vector2){player->pos.x+player->dim.x, player->pos.y-player->powers.horizontalPower.dim.y/2};
                }
            }
        }
    }
    else
    {
        if(player->powers.usingHorizontalPower)
        {
            player->powers.horizontalPower.contTime += delta;
        }
        if(player->powers.horizontalPower.contTime>=player->powers.horizontalPower.attackTime)
        {
            player->powers.usingHorizontalPower= false;
            player->powers.horizontalPower.contTime = 0.0f;
        }
    }

    //--------------SKILLS--------------
    if(player->inventory.equippedCharms.plusEgo==false)
    {
        if(player->status.onFloor && player->status.aura>=6 && IsKeyPressed(KEY_A))
        {
            player->status.healing = true;
        }

        if(player->status.healing && IsKeyDown(KEY_A) && player->status.aura>=3)
        {
            player->status.contHealingTime += delta;

            if(player->status.contHealingTime>=player->status.healingTime)
            {
                    if(player->status.life<player->status.maxLife)
                        player->status.life++;

                    player->status.aura-=3;
                    player->status.contHealingTime=0.0;
            }

        }
    }
    else
    {

        if(player->status.onFloor && player->status.aura>=12 && IsKeyPressed(KEY_A))
        {
            player->status.healing = true;
        }

        if(player->status.healing && IsKeyDown(KEY_A) && player->status.aura>=12)
        {
            player->status.contHealingTime += delta;

            if(player->status.contHealingTime>=player->status.healingTime*3)
            {
                    if(player->status.life<player->status.maxLife)
                        player->status.life+=4;

                    player->status.aura-=12;
                    player->status.contHealingTime=0.0;
            }

        }
    }

    if (IsKeyReleased(KEY_A)&& player->status.healing)
    {
        player->status.healing = false;
        player->status.contHealingTime = 0.0f;
    }







    //----------VERTICAL-MOVES----------

    if(IsKeyDown(KEY_DOWN))
    {
        player->status.lookingDown=true;
    }
    else if(IsKeyDown(KEY_UP))
    {
        player->status.lookingUp=true;
    }

    if(IsKeyReleased(KEY_DOWN))
    {
        player->status.lookingDown=false;
    }
    else if(IsKeyReleased(KEY_UP))
    {
        player->status.lookingUp=false;
    }

    //---------ATTACKS---------

    if (IsKeyPressed(KEY_X) && player->status.lookingUp && player->attackStatus.attacking==false && player->status.healing==false) // confere se a tecla do ataque foi acionada, a direção, e se ja esta atacando
    {
        player->attackStatus.attackUp = true; //inicia o ataque
        player->attackStatus.contTimeToNextAttack = 0.0f; //recomeça o timer
        player->attackStatus.attacking = true; // esta atacando

        player->sword.activated =true;
    }
    else
    {
        player->attackStatus.contTimeToNextAttack += delta; //conta tempo

        if( player->attackStatus.contTimeToNextAttack >= player->attackStatus.attackTime) //confere se ja passou o tempo da animação
        {
            player->attackStatus.attackUp = false; //encerra o ataque
            player->sword.activated =false;
        }

        if(player->attackStatus.contTimeToNextAttack >= player->attackStatus.timeToTheNextAttack) // ja pode dar o proximo ataque?
        {
            player->attackStatus.attacking = false; //encerra por completo a ação
            player->attackStatus.contTimeToNextAttack = 0.0f; // zera o contador
        }
    }

    if (IsKeyPressed(KEY_X) && player->status.lookingDown && player->status.onFloor==false && player->attackStatus.attacking==false && player->status.healing==false) // confere se a tecla do ataque foi acionada, a direção, e se ja esta atacando
    {
        player->attackStatus.attackDown = true; //inicia o ataque
        player->attackStatus.contTimeToNextAttack = 0.0f; //recomeça o timer
        player->attackStatus.attacking = true; // esta atacando

        player->sword.activated =true;
    }
    else
    {
        player->attackStatus.contTimeToNextAttack += delta; //conta tempo

        if( player->attackStatus.contTimeToNextAttack >= player->attackStatus.attackTime) //confere se ja passou o tempo da animação
        {
            player->attackStatus.attackDown = false; //encerra o ataque
            player->sword.activated =false;
        }

        if(player->attackStatus.contTimeToNextAttack >= player->attackStatus.timeToTheNextAttack) // ja pode dar o proximo ataque?
        {
            player->attackStatus.attacking = false; //encerra por completo a ação
            player->attackStatus.contTimeToNextAttack = 0.0f; // zera o contador
        }
    }


    //---------GRAVITY---------

    if(player->dashStatus.dashTime<=0)
        player->speed.y+=GRAVITY*delta; //soma sempre a gravidade na velocidade

    if (player->speed.y>MAX_SPEED_FALL) // define uma velocidade max para o player n passar pelo chão
        player->speed.y = MAX_SPEED_FALL;

    //---------JUUMPSET--------

    if (player->knockbackStatus.knockbackTime<=0 && player->status.healing==false)
    {
        if(player->status.onFloor) // se o jogador esta no chão
        {
            player->jumpStatus.canJump=true; // pode pular
            player->jumpStatus.isJumping = false; // nao esta pulando
            player->jumpStatus.canDoubleJump = false;
            player->jumpStatus.wasOnFloor = true;
        }
        else
        {
            player->jumpStatus.canJump=false; //se não, não pode pular
            if(player->jumpStatus.wasOnFloor)
            {
                if(player->inventory.doubleJump)
                    player->jumpStatus.canDoubleJump = true;
                player->jumpStatus.wasOnFloor = false;
            }
        }

        if (IsKeyPressed(KEY_Z)&&player->jumpStatus.canDoubleJump && player->inventory.doubleJump) //se pode pular e a tecla for acionada
        {
            player->speed.y = -player->jumpStatus.defaultJumpForce; // realiza o pulo
            player->jumpStatus.isJumping = true;
            player->jumpStatus.jumpTime = 0.0f; //  pulando
            player->jumpStatus.canDoubleJump = false; // e não pode pular enquanto esta pulando
            player->status.onFloor = false;
            player->jumpStatus.wasOnFloor = false;
        }

        if (IsKeyPressed(KEY_Z)&&player->jumpStatus.canJump) //se pode pular e a tecla for acionada
        {
            player->speed.y += -player->jumpStatus.defaultJumpForce; // realiza o pulo
            player->jumpStatus.isJumping = true; //  pulando
            player->jumpStatus.jumpTime = 0.0f;
            player->jumpStatus.canJump = false; // e não pode pular enquanto esta pulando
            player->status.onFloor = false;
            player->jumpStatus.wasOnFloor = false;



                player->jumpStatus.canDoubleJump = true;

        }

        if(IsKeyDown(KEY_Z)&& player->jumpStatus.isJumping) //se esta pulamndo e atecla continua pressionada
        {
            player->jumpStatus.jumpTime += delta; // conta um tempo max do bonus

            if(player->jumpStatus.jumpTime<player->jumpStatus.jumpTimeMax) //se esta dentro do tempo
            {
                player->speed.y += -player->jumpStatus.jumpBoostForce; //soma o bonus ao pulo
            }
        }

        if(IsKeyReleased(KEY_Z))// Se a tecla for solta
        {
            player->jumpStatus.isJumping=false;  //não esta mais pulando
            player->jumpStatus.jumpTime =  0.0f; //zera o timer
        }
    }

    if(player->inventory.chiclete)
    {
        if(player->inventory.equippedCharms.programmerHands==false)
        {
                if(!player->chiclete.leftWall && !player->chiclete.rightWall && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
                        player->chiclete.contChicleteTime = 0.0f;

                if(player->chiclete.leftWall)
                {

                    if(IsKeyDown(KEY_LEFT)&& player->chiclete.contChicleteTime<=0.5)
                    {
                        player->speed.y = 0.0f;

                        player->chiclete.contChicleteTime += delta;
                        player->chiclete.canUseChiclete = false;
                        player->jumpStatus.wasOnFloor = true;

                    }
                    else
                    {
                        player->chiclete.leftWall = false;

                        if(!player->chiclete.leftWall && !IsKeyDown(KEY_A))
                            player->chiclete.contChicleteTime = 0.0f;

                    }

                }

                if(player->chiclete.rightWall)
                {

                    if(IsKeyDown(KEY_RIGHT)&& player->chiclete.contChicleteTime<=0.5)
                    {
                        player->speed.y = 0.0f;

                        player->chiclete.contChicleteTime += delta;
                        player->chiclete.canUseChiclete = false;
                        player->jumpStatus.wasOnFloor = true;

                    }
                    else
                    {
                        player->chiclete.rightWall = false;

                        if(!player->chiclete.rightWall && !IsKeyDown(KEY_D))
                            player->chiclete.contChicleteTime = 0.0f;
                    }
                }
        }
        else
        {
                if(player->chiclete.leftWall)
                {

                    if(IsKeyDown(KEY_LEFT))
                    {
                        player->speed.y = 0.0f;
                        player->chiclete.canUseChiclete = false;
                        player->jumpStatus.wasOnFloor = true;

                    }
                    else
                    {
                        player->chiclete.leftWall = false;
                    }

                }
                else if (player->chiclete.rightWall)
                {
                    if(IsKeyDown(KEY_RIGHT))
                    {
                        player->speed.y = 0.0f;
                        player->chiclete.canUseChiclete = false;
                        player->jumpStatus.wasOnFloor = true;

                    }
                    else
                    {
                        player->chiclete.rightWall = false;
                    }
                }
        }

    }

    if(!player->chiclete.leftWall && !player->chiclete.rightWall)
            {
                player->chiclete.canUseChiclete = true;
            }


//------------------------------------------------------------
//============================================================
//---------------------UPDATE-POSITION------------------------

    player->pos.x += (player->speed.x * delta); // atualiza a posição de acordo com a velocidade (usa o delta para normalizar de acordo com o FPS)

    if(player->dashStatus.dashTime<=0)
        player->pos.y += (player->speed.y * delta);

//-------------------------------------------------------------
//=============================================================
//---------------------UPDATE-FUNCTIONS------------------------

    player->collisionRecs =  updatePlayerCollisionRecs(player);

    updatePlayerSword(player);

    if(player->sword.activated)
    {
        player->sword.swordCollisionRec = createAndUpdatePlayerSwordCollisionRec(player);
    }
    else
        player->sword.swordCollisionRec = deletePlayerSwordCollisionRec(player);

    if(player->status.invulnerable)
    {
        player->status.contInvulnerableTime +=delta;

        if(player->status.contInvulnerableTime>=player->status.invulnerableTime)
        {
            player->status.invulnerable = false;
            player->status.contInvulnerableTime = 0.0f;
        }
    }

    if(player->powers.usingHorizontalPower==true)
    {
        player->powers.horizontalPower.pos.x += player->powers.horizontalPower.speed.x * delta;
    }
    else
    {
        player->powers.horizontalPower.dim = (Vector2){0,0};
        player->powers.horizontalPower.pos = (Vector2){0,0};
    }


}

//------------------------------------------------------------
//============================================================
//-----------------------KNOCKBACK----------------------------

void applyKnockbackToPlayer(Player *player)
{
    if (player->knockbackStatus.knockbackL) //confere o tipo e direção
    {
        player->speed.x = -500.0; //aplica as forças
        player->speed.y = -200.0;
        player->status.sufferingDamege = true;
        player->knockbackStatus.knockbackTime = 0.5; // inicia o contador
    }
    else if (player->knockbackStatus.knockbackR)
    {
        player->speed.x = 500.0;
        player->speed.y = -200.0;
        player->status.sufferingDamege = true;
        player->knockbackStatus.knockbackTime = 0.5;
    }
    else if (player->knockbackStatus.knockbackUn)
    {
        if(player->status.lookingAtL)
        {
            player->speed.x = 200.0;
        }
        if(player->status.lookingAtR)
        {
            player->speed.x = -200.0;
        }
        player->speed.y = 300.0;
        player->status.sufferingDamege = true;
        player->knockbackStatus.knockbackTime = 0.5;
    }
    else if (player->knockbackStatus.knockbackUp)
    {
        if(player->status.lookingAtL)
        {
            player->speed.x = 200.0;
        }
        if(player->status.lookingAtR)
        {
            player->speed.x = -200.0;
        }
        player->speed.y = -300.0;
        player->status.sufferingDamege = true;
        player->knockbackStatus.knockbackTime = 0.5;
    }
    else if (player->knockbackStatus.swordKnockbackL)
    {
        player->speed.x = 300.0;
        player->speed.y = -200.0;
        player->knockbackStatus.knockbackTime = 0.5;
    }
    else if (player->knockbackStatus.swordKnockbackR)
    {
        player->speed.x = -300.0;
        player->speed.y = -200.0;
        player->knockbackStatus.knockbackTime = 0.5;
    }
    else if (player->knockbackStatus.swordKnockbackUp)
    {
        player->speed.y = -300.0;
        player->knockbackStatus.knockbackTime = 0.5;
    }

    //após aplicar qualquer knockback zera os status
    player->knockbackStatus.knockbackL = false;
    player->knockbackStatus.knockbackR = false;
    player->knockbackStatus.knockbackUn = false;
    player->knockbackStatus.knockbackUp = false;
    player->knockbackStatus.swordKnockbackL = false;
    player->knockbackStatus.swordKnockbackR = false;
    player->knockbackStatus.swordKnockbackUp = false;

    if(player->knockbackStatus.knockbackTime<=0.25)
        player->status.sufferingDamege = false;

}

//-------------------------------------------------------
//=======================================================
//---------------------DRAW-PLAYER-----------------------
void drawPlayer(Player *player)
{
    //DrawRectangleV(player->pos,player->dim,player->cor);
    player->contTime += GetFrameTime();
    if(player->contTime>=player->timeToTheNextFrame)
    {
        player->contTime = 0.0;
        if(player->currentFrame==0)
            player->currentFrame =1;
        else
            player->currentFrame =0;
    }



    if(player->powers.usingHorizontalPower)
    {
        player->powers.horizontalPower.contTextureTime += GetFrameTime();

        if(player->powers.horizontalPower.contTextureTime>=player->powers.horizontalPower.timeToTheNextFrame)
        {
            if(player->powers.horizontalPower.currentFrame==0)
                player->powers.horizontalPower.currentFrame = 1;
            else
            {
                 player->powers.horizontalPower.currentFrame = 0;
            }

            player->powers.horizontalPower.contTextureTime=0.0;
        }


        if(player->powers.direction==1)
        {
            if(player->powers.horizontalPower.currentFrame==0)
                DrawTextureV(rm.gw.horizontalPowerA,player->powers.horizontalPower.pos, player->powers.horizontalPower.cor);
            else
                DrawTextureV(rm.gw.horizontalPowerB,player->powers.horizontalPower.pos, player->powers.horizontalPower.cor);
        }
        else
        {
            if(player->powers.horizontalPower.currentFrame==0)
                DrawTexturePro(rm.gw.horizontalPowerA,
                        (Rectangle){0,0,-rm.gw.horizontalPowerA.width,rm.gw.horizontalPowerA.height},
                        (Rectangle){player->powers.horizontalPower.pos.x,player->powers.horizontalPower.pos.y,rm.gw.horizontalPowerA.width,rm.gw.horizontalPowerA.height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
            else
                DrawTexturePro(rm.gw.horizontalPowerB,
                        (Rectangle){0,0,-rm.gw.horizontalPowerA.width,rm.gw.horizontalPowerA.height},
                        (Rectangle){player->powers.horizontalPower.pos.x,player->powers.horizontalPower.pos.y,rm.gw.horizontalPowerA.width,rm.gw.horizontalPowerA.height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
        }
    }

    if(player->status.healing)
    {
        if(player->status.lookingAtR)
        {
             DrawTexturePro(rm.player.playerHealing,
                    (Rectangle){0,0,rm.player.playerHealing.width,rm.player.playerHealing.height},
                    (Rectangle){player->pos.x,player->pos.y,rm.player.playerHealing.width,rm.player.playerHealing.height},
                    (Vector2){16,16},
                     0.0f,
                     WHITE);
        }
        else
        {
             DrawTexturePro(rm.player.playerHealing,
                    (Rectangle){0,0,-rm.player.playerHealing.width,rm.player.playerHealing.height},
                    (Rectangle){player->pos.x,player->pos.y,rm.player.playerHealing.width,rm.player.playerHealing.height},
                    (Vector2){16,16},
                     0.0f,
                     WHITE);
        }
    }
    else if(player->status.resting==false)
    {
        if(player->speed.x==0 && player->status.onFloor && player->attackStatus.attacking==false)
        {
            if(player->status.lookingAtR)
            {
                DrawTexturePro(rm.player.normalPlayer,
                        (Rectangle){0,0,rm.player.normalPlayer.width,rm.player.normalPlayer.height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.normalPlayer.width,rm.player.normalPlayer.height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
            }
            else
            {
                DrawTexturePro(rm.player.normalPlayer,
                        (Rectangle){0,0,-rm.player.normalPlayer.width,rm.player.normalPlayer.height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.normalPlayer.width,rm.player.normalPlayer.height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
            }
        }
        else if(player->speed.x!=0 && player->status.onFloor && player->dashStatus.dashTime<=0.0 && player->attackStatus.attacking==false)
        {
            if(player->status.lookingAtR)
            {
                DrawTexturePro(rm.player.playerRunning[player->currentFrame],
                            (Rectangle){0,0,rm.player.playerRunning[player->currentFrame].width,rm.player.playerRunning[player->currentFrame].height},
                            (Rectangle){player->pos.x,player->pos.y,rm.player.playerRunning[player->currentFrame].width,rm.player.playerRunning[player->currentFrame].height},
                            (Vector2){16,16},
                             0.0f,
                             WHITE);
            }
            else
            {
                 DrawTexturePro(rm.player.playerRunning[player->currentFrame],
                            (Rectangle){0,0,-rm.player.playerRunning[player->currentFrame].width,rm.player.playerRunning[player->currentFrame].height},
                            (Rectangle){player->pos.x,player->pos.y,rm.player.playerRunning[player->currentFrame].width,rm.player.playerRunning[player->currentFrame].height},
                            (Vector2){16,16},
                             0.0f,
                             WHITE);
            }
        }
        else if(player->jumpStatus.isJumping && player->jumpStatus.canDoubleJump && player->attackStatus.attacking==false)
        {

            if(player->status.lookingAtR)
            {
                DrawTexturePro(rm.player.playerJumping[player->currentFrame],
                        (Rectangle){0,0,rm.player.playerJumping[player->currentFrame].width,rm.player.playerJumping[player->currentFrame].height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.playerJumping[player->currentFrame].width,rm.player.playerJumping[player->currentFrame].height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
            }
            else
            {
                 DrawTexturePro(rm.player.playerJumping[player->currentFrame],
                        (Rectangle){0,0,-rm.player.playerJumping[player->currentFrame].width,rm.player.playerJumping[player->currentFrame].height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.playerJumping[player->currentFrame].width,rm.player.playerJumping[player->currentFrame].height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
            }
        }
        else if(player->status.onFloor==false && player->jumpStatus.isJumping==false && player->dashStatus.dashTime<=0.0 && player->chiclete.canUseChiclete && player->attackStatus.attacking==false)
        {

            if(player->status.lookingAtR)
            {
                DrawTexturePro(rm.player.playerFalling[0],
                        (Rectangle){0,0,rm.player.playerFalling[0].width,rm.player.playerFalling[0].height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.playerFalling[0].width,rm.player.playerFalling[0].height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
            }
            else
            {
                 DrawTexturePro(rm.player.playerFalling[0],
                        (Rectangle){0,0,-rm.player.playerFalling[0].width,rm.player.playerFalling[0].height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.playerFalling[0].width,rm.player.playerFalling[0].height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
            }
        }
        else if(player->dashStatus.dashTime>=0.0 && player->attackStatus.attacking==false && player->inventory.teclaTab)
        {
            if(player->status.lookingAtR)
            {
                 DrawTexturePro(rm.player.playerDash,
                        (Rectangle){0,0,rm.player.playerDash.width,rm.player.playerDash.height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.playerDash.width,rm.player.playerDash.height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
            }
            else
            {
                 DrawTexturePro(rm.player.playerDash,
                        (Rectangle){0,0,-rm.player.playerDash.width,rm.player.playerDash.height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.playerDash.width,rm.player.playerDash.height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
            }

        }
        else if(player->chiclete.contChicleteTime<=0.5f && player->chiclete.canUseChiclete==false && player->attackStatus.attacking==false && player->inventory.chiclete)
        {
            if(player->status.lookingAtR)
            {
                 DrawTexturePro(rm.player.playerChiclete,
                        (Rectangle){0,0,-rm.player.playerChiclete.width,rm.player.playerChiclete.height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.playerChiclete.width,rm.player.playerChiclete.height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
            }
            else
            {
                 DrawTexturePro(rm.player.playerChiclete,
                        (Rectangle){0,0,rm.player.playerChiclete.width,rm.player.playerChiclete.height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.playerChiclete.width,rm.player.playerChiclete.height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
            }

        }
        else if(player->status.onFloor==false && player->jumpStatus.canJump==false && player->jumpStatus.canDoubleJump==false && player->jumpStatus.isJumping && player->chiclete.contChicleteTime==0.0 && player->attackStatus.attacking==false && player->inventory.doubleJump)
        {
            if(player->status.lookingAtR)
            {
                 DrawTexturePro(rm.player.playerDoubleJump,
                        (Rectangle){0,0,rm.player.playerDoubleJump.width,rm.player.playerDoubleJump.height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.playerDoubleJump.width,rm.player.playerDoubleJump.height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
            }
            else
            {
                 DrawTexturePro(rm.player.playerDoubleJump,
                        (Rectangle){0,0,-rm.player.playerDoubleJump.width,rm.player.playerDoubleJump.height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.playerDoubleJump.width,rm.player.playerDoubleJump.height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
            }

        }
         else if(player->attackStatus.attacking)
        {
            if(player->status.lookingAtR)
            {
                if(player->status.lookingUp)
                {
                    if(player->status.onFloor==false)
                    {
                        DrawTexturePro(rm.player.playerJumpAttackUp,
                            (Rectangle){0,0,rm.player.playerJumpAttackUp.width,rm.player.playerJumpAttackUp.height},
                            (Rectangle){player->pos.x,player->pos.y,rm.player.playerJumpAttackUp.width,rm.player.playerJumpAttackUp.height},
                            (Vector2){16,16},
                             0.0f,
                             WHITE);
                    }
                    else
                    {
                        DrawTexturePro(rm.player.playerAttackUp,
                            (Rectangle){0,0,rm.player.playerAttackUp.width,rm.player.playerAttackUp.height},
                            (Rectangle){player->pos.x,player->pos.y,rm.player.playerAttackUp.width,rm.player.playerAttackUp.height},
                            (Vector2){16,16},
                             0.0f,
                             WHITE);
                    }
                }
                else if (player->status.lookingDown)
                {
                    DrawTexturePro(rm.player.playerAttackDown,
                            (Rectangle){0,0,rm.player.playerAttackDown.width,rm.player.playerAttackDown.height},
                            (Rectangle){player->pos.x,player->pos.y,rm.player.playerAttackDown.width,rm.player.playerAttackDown.height},
                            (Vector2){16,16},
                             0.0f,
                             WHITE);
                }
                else
                {
                    DrawTexturePro(rm.player.playerAttack,
                        (Rectangle){0,0,rm.player.playerAttack.width,rm.player.playerAttack.height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.playerAttack.width,rm.player.playerAttack.height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
                }
            }
            else if (player->status.lookingAtL)
            {
                if(player->status.lookingUp)
                {
                    if(player->status.onFloor==false)
                    {
                        DrawTexturePro(rm.player.playerJumpAttackUp,
                            (Rectangle){0,0,-rm.player.playerJumpAttackUp.width,rm.player.playerJumpAttackUp.height},
                            (Rectangle){player->pos.x,player->pos.y,rm.player.playerJumpAttackUp.width,rm.player.playerJumpAttackUp.height},
                            (Vector2){16,16},
                             0.0f,
                             WHITE);
                    }
                    else
                    {
                        DrawTexturePro(rm.player.playerAttackUp,
                            (Rectangle){0,0,-rm.player.playerAttackUp.width,rm.player.playerAttackUp.height},
                            (Rectangle){player->pos.x,player->pos.y,rm.player.playerAttackUp.width,rm.player.playerAttackUp.height},
                            (Vector2){16,16},
                             0.0f,
                             WHITE);
                    }
                }
                else if (player->status.lookingDown)
                {
                    DrawTexturePro(rm.player.playerAttackDown,
                            (Rectangle){0,0,-rm.player.playerAttackDown.width,rm.player.playerAttackDown.height},
                            (Rectangle){player->pos.x,player->pos.y,rm.player.playerAttackDown.width,rm.player.playerAttackDown.height},
                            (Vector2){16,16},
                             0.0f,
                             WHITE);
                }
                else
                {
                    DrawTexturePro(rm.player.playerAttack,
                        (Rectangle){0,0,-rm.player.playerAttack.width,rm.player.playerAttack.height},
                        (Rectangle){player->pos.x,player->pos.y,rm.player.playerAttack.width,rm.player.playerAttack.height},
                        (Vector2){16,16},
                         0.0f,
                         WHITE);
                }
            }


            if(player->attackStatus.attackRight)
            {
                 DrawTexturePro(rm.player.swordAttack,
                        (Rectangle){0,0,rm.player.swordAttack.width,rm.player.swordAttack.height},
                        (Rectangle){player->sword.pos.x+5,player->sword.pos.y-24,rm.player.swordAttack.width,rm.player.swordAttack.height},
                        (Vector2){16,8},
                         0.0f,
                         WHITE);
            }
            else if(player->attackStatus.attackLeft)
            {
                 DrawTexturePro(rm.player.swordAttack,
                        (Rectangle){0,0,-rm.player.swordAttack.width,rm.player.swordAttack.height},
                        (Rectangle){player->sword.pos.x+5,player->sword.pos.y-24,rm.player.swordAttack.width,rm.player.swordAttack.height},
                        (Vector2){16,8},
                         0.0f,
                         WHITE);
            }
            else if(player->attackStatus.attackUp)
            {
                 DrawTexturePro(rm.player.swordAttack,
                        (Rectangle){0,0,rm.player.swordAttack.width,rm.player.swordAttack.height},
                        (Rectangle){player->sword.pos.x-24,player->sword.pos.y+36,rm.player.swordAttack.width,rm.player.swordAttack.height},
                        (Vector2){16,8},
                         270.0f,
                         WHITE);
            }
            else if(player->attackStatus.attackDown)
            {
                 DrawTexturePro(rm.player.swordAttack,
                        (Rectangle){0,0,rm.player.swordAttack.width,rm.player.swordAttack.height},
                        (Rectangle){player->sword.pos.x+32,player->sword.pos.y+5,rm.player.swordAttack.width,rm.player.swordAttack.height},
                        (Vector2){16,8},
                         90.0f,
                         WHITE);
            }

        }

    }
    else
    {
        if(player->status.lookingAtR)
            {
                DrawTexturePro(rm.player.restingPlayer[player->currentFrame],
                            (Rectangle){0,0,rm.player.restingPlayer[player->currentFrame].width,rm.player.restingPlayer[player->currentFrame].height},
                            (Rectangle){player->pos.x,player->pos.y-10,rm.player.restingPlayer[player->currentFrame].width,rm.player.restingPlayer[player->currentFrame].height},
                            (Vector2){16,16},
                             0.0f,
                             WHITE);
            }
            else
            {
                 DrawTexturePro(rm.player.restingPlayer[player->currentFrame],
                            (Rectangle){0,0,-rm.player.restingPlayer[player->currentFrame].width,rm.player.restingPlayer[player->currentFrame].height},
                            (Rectangle){player->pos.x,player->pos.y-10,rm.player.restingPlayer[player->currentFrame].width,rm.player.restingPlayer[player->currentFrame].height},
                            (Vector2){16,16},
                             0.0f,
                             WHITE);
            }
    }

    //drawPlayerSword(player);

}


void drawHud (Player *player, bool isFullscreen)
{
    int fps = GetFPS();

    //DrawText(TextFormat("Lives: %02i", player->status.life), 20,20,20, GREEN);


    //DrawText(TextFormat("Aura: %02i", player->status.aura), 20,50,20, GREEN);





    if(isFullscreen==false)
    {

        switch(player->status.life)
        {
        case 7:
            DrawTexture(rm.player.sevenHearts, 20,20,WHITE);
            break;
        case 6:
             if(player->status.sufferingDamege)
            {
                DrawTexture(rm.player.hit7Heart, 20,20,WHITE);
            }
            else
            {
                DrawTexture(rm.player.sixHearts, 20,20,WHITE);
            }
            break;
        case 5:
             if(player->status.sufferingDamege)
            {
                DrawTexture(rm.player.hit6Heart, 20,20,WHITE);
            }
            else
            {
                DrawTexture(rm.player.fiveHearts, 20,20,WHITE);
            }
            break;
        case 4:
            if(player->status.sufferingDamege)
            {
                DrawTexture(rm.player.hit5Heart, 20,20,WHITE);
            }
            else
            {
                DrawTexture(rm.player.fourHearts, 20,20,WHITE);
            }
            break;
        case 3:
            if(player->status.sufferingDamege)
            {
                DrawTexture(rm.player.hit4Heart, 20,20,WHITE);
            }
            else
            {
                DrawTexture(rm.player.treeHearts, 20,20,WHITE);
            }
            break;
        case 2:
            if(player->status.sufferingDamege)
            {
                DrawTexture(rm.player.hit3Heart, 20,20,WHITE);
            }
            else
            {
                DrawTexture(rm.player.twoHearts, 20,20,WHITE);
            }
            break;
        case 1:
            if(player->status.sufferingDamege)
            {
                DrawTexture(rm.player.hit2Heart, 20,20,WHITE);
            }
            else
            {
                DrawTexture(rm.player.oneHearts, 20,20,WHITE);
            }
            break;
        default:
            break;
        }

        switch(player->status.aura)
        {
        case 0:
        case 1:
            DrawTexture(rm.player.zeroAura, 10,60,WHITE);
            break;
        case 2:
        case 3:
            DrawTexture(rm.player.oneAura, 10,60,WHITE);
            break;
        case 4:
        case 5:
            DrawTexture(rm.player.twoAura, 10,60,WHITE);
            break;
        case 6:
        case 7:
            DrawTexture(rm.player.treeAura, 10,60,WHITE);
            break;
        case 8:
        case 9:
            DrawTexture(rm.player.fourAura, 10,60,WHITE);
            break;
        case 10:
        case 11:
            DrawTexture(rm.player.fiveAura, 10,60,WHITE);
            break;
        case 12:
        case 13:
            DrawTexture(rm.player.sixAura, 10,60,WHITE);
            break;
        case 14:
        case 15:
            DrawTexture(rm.player.sevenAura, 10,60,WHITE);
            break;
        case 16:
        case 17:
            DrawTexture(rm.player.eightAura, 10,60,WHITE);
            break;
        case 18:
        case 19:
            DrawTexture(rm.player.nineAura, 10,60,WHITE);
            break;
        case 20:
        case 21:
            DrawTexture(rm.player.tenAura, 10,60,WHITE);
            break;
        case 22:
        case 23:
            DrawTexture(rm.player.elevenAura, 10,60,WHITE);
            break;
        case 24:
        case 25:
            DrawTexture(rm.player.twelveAura, 10,60,WHITE);
            break;
        default:
            break;
        }

        if(player->inLevel)
        {
            DrawTexture(rm.player.ticketsRU2, 60, 60, WHITE);
        }
        else
            DrawTexture(rm.player.ticketsRU1, 60, 60, WHITE);


         DrawText(TextFormat("%02i", player->status.ticketsRU), 128,87,18, BLACK);

         if(player->powers.usingHorizontalPower)
            DrawTexture(rm.player.auraLeek,10,60,WHITE);

    }
    else
    {
        switch(player->status.life)
        {
        case 7:
            DrawTexture(rm.player.sevenHeartsG, 20,20,WHITE);
            break;
        case 6:
            if(player->status.sufferingDamege)
            {
                DrawTexture(rm.player.hit7HeartG, 20,20,WHITE);
            }
            else
            {
                DrawTexture(rm.player.sixHeartsG, 20,20,WHITE);
            }
            break;
        case 5:
            if(player->status.sufferingDamege)
            {
                DrawTexture(rm.player.hit6HeartG, 20,20,WHITE);
            }
            else
            {
                DrawTexture(rm.player.fiveHeartsG, 20,20,WHITE);
            }
            break;
        case 4:
            if(player->status.sufferingDamege)
            {
                DrawTexture(rm.player.hit5HeartG, 20,20,WHITE);
            }
            else
            {
                DrawTexture(rm.player.fourHeartsG, 20,20,WHITE);
            }
            break;
        case 3:
            if(player->status.sufferingDamege)
            {
                DrawTexture(rm.player.hit4HeartG, 20,20,WHITE);
            }
            else
            {
                DrawTexture(rm.player.treeHeartsG, 20,20,WHITE);
            }
            break;
        case 2:
            if(player->status.sufferingDamege)
            {
                DrawTexture(rm.player.hit3HeartG, 20,20,WHITE);
            }
            else
            {
                DrawTexture(rm.player.twoHeartsG, 20,20,WHITE);
            }
            break;
        case 1:
            if(player->status.sufferingDamege)
            {
                DrawTexture(rm.player.hit2HeartG, 20,20,WHITE);
            }
            else
            {
                DrawTexture(rm.player.oneHeartsG, 20,20,WHITE);
            }
            break;
        }

         switch(player->status.aura)
        {
        case 0:
        case 1:
            DrawTexturePro(rm.player.zeroAuraG,
                        (Rectangle){0,0,rm.player.zeroAuraG.width,rm.player.zeroAuraG.height},
                        (Rectangle){90,130,rm.player.zeroAuraG.width,rm.player.zeroAuraG.height},
                        (Vector2){rm.player.zeroAuraG.width/2.0f,rm.player.zeroAuraG.height/2.0f},
                         90.0f,
                         WHITE);
            break;
        case 2:
        case 3:
             DrawTexturePro(rm.player.oneAuraG,
                        (Rectangle){0,0,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Rectangle){90,130,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Vector2){rm.player.oneAuraG.width/2.0f,rm.player.oneAuraG.height/2.0f},
                         90.0f,
                         WHITE);
            break;
        case 4:
        case 5:
             DrawTexturePro(rm.player.twoAuraG,
                        (Rectangle){0,0,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Rectangle){90,130,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Vector2){rm.player.oneAuraG.width/2.0f,rm.player.oneAuraG.height/2.0f},
                         90.0f,
                         WHITE);
            break;
        case 6:
        case 7:
             DrawTexturePro(rm.player.treeAuraG,
                        (Rectangle){0,0,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Rectangle){90,130,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Vector2){rm.player.oneAuraG.width/2.0f,rm.player.oneAuraG.height/2.0f},
                         90.0f,
                         WHITE);
            break;
        case 8:
        case 9:
             DrawTexturePro(rm.player.fourAuraG,
                        (Rectangle){0,0,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Rectangle){90,130,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Vector2){rm.player.oneAuraG.width/2.0f,rm.player.oneAuraG.height/2.0f},
                         90.0f,
                         WHITE);
            break;
        case 10:
        case 11:
             DrawTexturePro(rm.player.fiveAuraG,
                        (Rectangle){0,0,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Rectangle){90,130,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Vector2){rm.player.oneAuraG.width/2.0f,rm.player.oneAuraG.height/2.0f},
                         90.0f,
                         WHITE);
            break;
        case 12:
        case 13:
             DrawTexturePro(rm.player.sixAuraG,
                        (Rectangle){0,0,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Rectangle){90,130,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Vector2){rm.player.oneAuraG.width/2.0f,rm.player.oneAuraG.height/2.0f},
                         90.0f,
                         WHITE);
            break;
        case 14:
        case 15:
            DrawTexturePro(rm.player.sevenAuraG,
                        (Rectangle){0,0,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Rectangle){90,130,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Vector2){rm.player.oneAuraG.width/2.0f,rm.player.oneAuraG.height/2.0f},
                         90.0f,
                         WHITE);
            break;
        case 16:
        case 17:
            DrawTexturePro(rm.player.eightAuraG,
                        (Rectangle){0,0,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Rectangle){90,130,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Vector2){rm.player.oneAuraG.width/2.0f,rm.player.oneAuraG.height/2.0f},
                         90.0f,
                         WHITE);
            break;
        case 18:
        case 19:
            DrawTexturePro(rm.player.nineAuraG,
                        (Rectangle){0,0,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Rectangle){90,130,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Vector2){rm.player.oneAuraG.width/2.0f,rm.player.oneAuraG.height/2.0f},
                         90.0f,
                         WHITE);
            break;
        case 20:
        case 21:
            DrawTexturePro(rm.player.tenAuraG,
                        (Rectangle){0,0,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Rectangle){90,130,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Vector2){rm.player.oneAuraG.width/2.0f,rm.player.oneAuraG.height/2.0f},
                         90.0f,
                         WHITE);
            break;
        case 22:
        case 23:
            DrawTexturePro(rm.player.elevenAuraG,
                        (Rectangle){0,0,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Rectangle){90,130,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Vector2){rm.player.oneAuraG.width/2.0f,rm.player.oneAuraG.height/2.0f},
                         90.0f,
                         WHITE);
            break;
        case 24:
        case 25:
            DrawTexturePro(rm.player.twelveAuraG,
                        (Rectangle){0,0,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Rectangle){90,130,rm.player.oneAuraG.width,rm.player.oneAuraG.height},
                        (Vector2){rm.player.oneAuraG.width/2.0f,rm.player.oneAuraG.height/2.0f},
                         90.0f,
                         WHITE);
            break;
        default:
            break;
        }




        if(player->inLevel)
        {
            DrawTexture(rm.player.ticketsRU2G, 180, 65, WHITE);
        }
        else
            DrawTexture(rm.player.ticketsRU1G, 180, 65, WHITE);

        DrawText(TextFormat("%02i", player->status.ticketsRU), 320,115,35, BLACK);


        if(player->powers.usingHorizontalPower)
            DrawTexturePro(rm.player.auraLeekG,
                        (Rectangle){0,0,rm.player.auraLeekG.width,rm.player.auraLeekG.height},
                        (Rectangle){90,130,rm.player.auraLeekG.width,rm.player.auraLeekG.height},
                        (Vector2){rm.player.auraLeekG.width/2.0f,rm.player.auraLeekG.height/2.0f},
                         90.0f,
                         WHITE);
    }



    //DrawText(TextFormat("Amuletos: "), 20,80,20, GREEN);
    DrawText(TextFormat("FPS: %03i",fps),20,5,20,GREEN);
}

void updateInventory (Player *player)
{
    if( IsKeyPressed(KEY_TAB))
    {
        player->status.openInventory = !player->status.openInventory;
    }

    if(player->status.resting)
    {
        if(player->status.openInventory)
        {
            if(player->inventory.colectedCharms.gamerHeart && IsKeyPressed(KEY_ONE))
            {
                player->inventory.equippedCharms.gamerHeart = true;
                player->inventory.equippedCharms.goldTickets = false;
                player->inventory.equippedCharms.plusEgo = false;
                player->inventory.equippedCharms.programmerHands = false;
                player->inventory.equippedCharms.debugSword = false;
            }

            if(player->inventory.colectedCharms.goldTickets && IsKeyPressed(KEY_TWO))
            {
                player->inventory.equippedCharms.gamerHeart = false;
                player->inventory.equippedCharms.goldTickets = true;
                player->inventory.equippedCharms.plusEgo = false;
                player->inventory.equippedCharms.programmerHands = false;
                player->inventory.equippedCharms.debugSword = false;
            }

            if(player->inventory.colectedCharms.plusEgo && IsKeyPressed(KEY_THREE))
            {
                player->inventory.equippedCharms.gamerHeart = false;
                player->inventory.equippedCharms.goldTickets = false;
                player->inventory.equippedCharms.plusEgo = true;
                player->inventory.equippedCharms.programmerHands = false;
                player->inventory.equippedCharms.debugSword = false;
            }

            if(player->inventory.colectedCharms.programmerHands && IsKeyPressed(KEY_FOUR))
            {
                player->inventory.equippedCharms.gamerHeart = false;
                player->inventory.equippedCharms.goldTickets = false;
                player->inventory.equippedCharms.plusEgo = false;
                player->inventory.equippedCharms.programmerHands = true;
                player->inventory.equippedCharms.debugSword = false;
            }

            if(player->inventory.colectedCharms.debugSword && IsKeyPressed(KEY_FIVE))
            {
                player->inventory.equippedCharms.gamerHeart = false;
                player->inventory.equippedCharms.goldTickets = false;
                player->inventory.equippedCharms.plusEgo = false;
                player->inventory.equippedCharms.programmerHands = false;
                player->inventory.equippedCharms.debugSword = true;
            }
        }
    }

}


void drawInventory(Player *player, bool isFullscreen)
{
    const Rectangle RETANGULOS_SLOTS[5] =
    {
        {40, 10, 80, 80},
        {200, 10, 80, 80},
        {360, 10, 80, 80},
        {520, 10, 80, 80},
        {680, 10, 80, 80}
    };

    DrawRectangle(0, 0, GetScreenWidth(), 120, BLACK);

    for (int i = 0; i < 5; i++)
    {
        Rectangle slot_retangulo = RETANGULOS_SLOTS[i];

        // Desenha o Slot Branco
        DrawRectangleRec(slot_retangulo, WHITE);
    }

    if (player->inventory.colectedCharms.gamerHeart)
    {
        if(player->inventory.equippedCharms.gamerHeart)
            DrawTexturePro(rm.charm.gamerHeart,
                    (Rectangle){0,0,rm.charm.gamerHeart.width, rm.charm.gamerHeart.height},
                    (Rectangle) {40,10,rm.charm.gamerHeart.width+64,rm.charm.gamerHeart.height+64},
                    (Vector2){0.0f,0.0f},
                    0.0f,
                    GREEN);
        else
        {
           DrawTexturePro(rm.charm.gamerHeart,
                    (Rectangle){0,0,rm.charm.gamerHeart.width, rm.charm.gamerHeart.height},
                    (Rectangle) {40,10,rm.charm.gamerHeart.width+64,rm.charm.gamerHeart.height+64},
                    (Vector2){0.0f,0.0f},
                    0.0f,
                    WHITE);
        }
    }

    if (player->inventory.colectedCharms.goldTickets)
    {
        if(player->inventory.equippedCharms.goldTickets)
            DrawTexturePro(rm.charm.goldTickets,
                    (Rectangle){0,0,rm.charm.goldTickets.width, rm.charm.goldTickets.height},
                    (Rectangle) {200,10,rm.charm.goldTickets.width+64,rm.charm.goldTickets.height+64},
                    (Vector2){0.0f,0.0f},
                    0.0f,
                    GREEN);
        else
        {
           DrawTexturePro(rm.charm.goldTickets,
                    (Rectangle){0,0,rm.charm.goldTickets.width, rm.charm.goldTickets.height},
                    (Rectangle) {200,10,rm.charm.goldTickets.width+64,rm.charm.goldTickets.height+64},
                    (Vector2){0.0f,0.0f},
                    0.0f,
                    WHITE);
        }
    }
    if (player->inventory.colectedCharms.plusEgo)
    {
        if(player->inventory.equippedCharms.plusEgo)
            DrawTexturePro(rm.charm.plusEgo,
                    (Rectangle){0,0,rm.charm.plusEgo.width, rm.charm.plusEgo.height},
                    (Rectangle) {360,10,rm.charm.plusEgo.width+64,rm.charm.plusEgo.height+64},
                    (Vector2){0.0f,0.0f},
                    0.0f,
                    GREEN);
        else
        {
           DrawTexturePro(rm.charm.plusEgo,
                    (Rectangle){0,0,rm.charm.plusEgo.width, rm.charm.plusEgo.height},
                    (Rectangle) {360,10,rm.charm.plusEgo.width+64,rm.charm.plusEgo.height+64},
                    (Vector2){0.0f,0.0f},
                    0.0f,
                    WHITE);
        }
    }

    if (player->inventory.colectedCharms.programmerHands)
    {
        if(player->inventory.equippedCharms.programmerHands)
            DrawTexturePro(rm.charm.programmerHands,
                    (Rectangle){0,0,rm.charm.programmerHands.width, rm.charm.programmerHands.height},
                    (Rectangle) {520,10,rm.charm.programmerHands.width+64,rm.charm.programmerHands.height+64},
                    (Vector2){0.0f,0.0f},
                    0.0f,
                    GREEN);
        else
        {
           DrawTexturePro(rm.charm.programmerHands,
                    (Rectangle){0,0,rm.charm.programmerHands.width, rm.charm.programmerHands.height},
                    (Rectangle) {520,10,rm.charm.programmerHands.width+64,rm.charm.programmerHands.height+64},
                    (Vector2){0.0f,0.0f},
                    0.0f,
                    WHITE);
        }
    }
    if (player->inventory.colectedCharms.debugSword)
    {
         if(player->inventory.equippedCharms.debugSword)
            DrawTexturePro(rm.charm.debugSword,
                    (Rectangle){0,0,rm.charm.debugSword.width, rm.charm.debugSword.height},
                    (Rectangle) {680,10,rm.charm.debugSword.width+64,rm.charm.debugSword.height+64},
                    (Vector2){0.0f,0.0f},
                    0.0f,
                    GREEN);
        else
        {
           DrawTexturePro(rm.charm.debugSword,
                    (Rectangle){0,0,rm.charm.debugSword.width, rm.charm.debugSword.height},
                    (Rectangle) {680,10,rm.charm.debugSword.width+64,rm.charm.debugSword.height+64},
                    (Vector2){0.0f,0.0f},
                    0.0f,
                    WHITE);
        }
    }

}




//---------------------------------------------------------
//=========================================================
//-------------------PLAYER-DEATH--------------------------


void resetPlayer(Player *player)
{
    player->pos = (Vector2){0,0};
    player->speed = (Vector2){0,0};
    player->status.life = 5;
    player->status.maxLife = 5;
    player->status.dead = false;
    player->status.aura = 0;
    player->status.healing = false;
    player->status.healingTime = 1.5;
    player->status.resting = false;
    player->status.ticketsRU = 0;
    player->status.defaultSpeed = 200.0;
    player->status.onFloor = false;
    player->status.lookingAtL = false;
    player->status.lookingAtR = false;
    player->status.nextToCharm = false;
    player->status.nextToSkill = false;
    player->status.invulnerable = false;
    player->status.invulnerableTime = 2.0f;
    player->powers.horizontalPowerActive = false;
    player->powers.usingHorizontalPower = false;
    player->inventory.chiclete = false;
    player->inventory.doubleJump = false;
    player->inventory.teclaTab = false;
    player->inventory.equippedCharms.goldTickets = false;
    player->inventory.equippedCharms.debugSword = false;
    player->inventory.equippedCharms.plusEgo = false;
    player->inventory.equippedCharms.programmerHands = false;
    player->inventory.equippedCharms.gamerHeart = false;
    player->inventory.colectedCharms.goldTickets = false;
    player->inventory.colectedCharms.debugSword = false;
    player->inventory.colectedCharms.plusEgo = false;
    player->inventory.colectedCharms.programmerHands = false;
    player->inventory.colectedCharms.gamerHeart = false;
    player->inventory.equippedWeapons.defaultSword = true;
    player->knockbackStatus.swordKnockbackR = false;
    player->knockbackStatus.swordKnockbackL = false;
    player->knockbackStatus.swordKnockbackUp = false;
    player->knockbackStatus.knockbackR = false;
    player->knockbackStatus.knockbackL = false;
    player->knockbackStatus.knockbackUp = false;
    player->knockbackStatus.knockbackUn = false;
    player->jumpStatus.canJump = true;
    player->jumpStatus.canDoubleJump = false;
    player->jumpStatus.wasOnFloor = false;
    player->jumpStatus.defaultJumpForce = 400.0f;
    player->jumpStatus.jumpBoostForce = 20.0f;
    player->jumpStatus.isJumping = false;
    player->dashStatus.canDash = true;
    player->attackStatus.attacking = false;
    player->attackStatus.attackRight = false;
    player->attackStatus.attackDown = false;
    player->attackStatus.attackLeft = false;
    player->attackStatus.attackUp = false;
    player->attackStatus.attackTime = 0.35f;
    player->currentFrame = 0;
    player->progress =0;
    player->inLevel = false;
}



