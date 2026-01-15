#include <stdio.h>
#include "raylib.h"
#include "menu.h"
#include "resourceManager.h"
#include "save.h"

const int X_MENU_BUTTON = 200;
const int Y_START_BUTTON = 100;
const int Y_LOAD_BUTTON = 160;
const int Y_HELP_BUTTON = 220;
const int Y_CLOSE_BUTTON = 280;

void inputUpdateAndDrawMenu(Game *game, bool isFullscreen)
{

    Vector2 mousePosition = GetMousePosition();

    Rectangle startArea = {0};
    Rectangle loadArea = {0};
    Rectangle helpArea = {0};
    Rectangle closeArea = {0};

    if(isFullscreen==false)
    {
        startArea = (Rectangle) {X_MENU_BUTTON, Y_START_BUTTON, (int) rm.menu.bigNormalStartButton.width, (int) rm.menu.bigNormalStartButton.height};
        loadArea = (Rectangle) {X_MENU_BUTTON, Y_LOAD_BUTTON, (int) rm.menu.bigNormalLoadButton.width, (int) rm.menu.bigNormalLoadButton.height};
        helpArea = (Rectangle) {X_MENU_BUTTON, Y_HELP_BUTTON, (int) rm.menu.bigNormalHelpButton.width, (int) rm.menu.bigNormalHelpButton.height};
        closeArea = (Rectangle) {X_MENU_BUTTON, Y_CLOSE_BUTTON, (int) rm.menu.bigNormalCloseButton.width, (int) rm.menu.bigNormalCloseButton.height};
    }
    else
    {
        startArea = (Rectangle){X_MENU_BUTTON*3+140, Y_START_BUTTON, (int) rm.menu.bigNormalStartButton.width, (int) rm.menu.bigNormalStartButton.height};
        loadArea = (Rectangle){X_MENU_BUTTON*3+140, Y_LOAD_BUTTON, (int) rm.menu.bigNormalLoadButton.width, (int) rm.menu.bigNormalLoadButton.height};
        helpArea = (Rectangle){X_MENU_BUTTON*3+140, Y_HELP_BUTTON, (int) rm.menu.bigNormalHelpButton.width, (int) rm.menu.bigNormalHelpButton.height};
        closeArea = (Rectangle) {X_MENU_BUTTON*3+140, Y_CLOSE_BUTTON, (int) rm.menu.bigNormalCloseButton.width, (int) rm.menu.bigNormalCloseButton.height};
    }

    bool mouseOnStartButton = CheckCollisionPointRec(mousePosition, startArea);
    bool mouseOnLoadButton = CheckCollisionPointRec(mousePosition, loadArea);
    bool mouseOnHelpButton = CheckCollisionPointRec(mousePosition, helpArea);
    bool mouseOnCloseButton = CheckCollisionPointRec(mousePosition, closeArea);

    if(mouseOnStartButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        game->status = GAMELOBBY;

        game->gl = createGameLobby(&game->player);

        game->playerLobbyFirstPos = game->player.pos;

        game->playerLobbyReturnPos = game->gl.posComputer;

        printf("Posicao Retorno (M) -> X: %.2f, Y: %.2f\n",
               game->playerLobbyReturnPos.x,
               game->playerLobbyReturnPos.y);

        game->gl.player->pos = game->playerLobbyFirstPos;

        if(checkEmptySaveSlot("save1"))
            game->saveSlot1 = true;
        else if (checkEmptySaveSlot("save2"))
            game->saveSlot2 = true;
        else if (checkEmptySaveSlot("save3"))
            game->saveSlot3 = true;
    }

    else if(mouseOnLoadButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = LOAD;

    else if(mouseOnHelpButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = HELP;

    else if(mouseOnCloseButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = LEAVE;

    //------------------------------------------------------------------

    BeginDrawing();
    ClearBackground(BLACK);

    if(isFullscreen==false)
    {
        if (mouseOnStartButton)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                DrawTexture(rm.menu.clickStartButton, X_MENU_BUTTON, Y_START_BUTTON, WHITE);
            else
                DrawTexture(rm.menu.bigMouseStartButton, X_MENU_BUTTON, Y_START_BUTTON, WHITE);
        }
        else
            DrawTexture(rm.menu.bigNormalStartButton, X_MENU_BUTTON, Y_START_BUTTON, WHITE);
                // Botao de Carregar jogo
        if (mouseOnLoadButton)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                DrawTexture(rm.menu.clickLoadButton, X_MENU_BUTTON, Y_LOAD_BUTTON, WHITE);
            else
                DrawTexture(rm.menu.bigMouseLoadButton, X_MENU_BUTTON, Y_LOAD_BUTTON, WHITE);
        }
        else
            DrawTexture(rm.menu.bigNormalLoadButton, X_MENU_BUTTON, Y_LOAD_BUTTON, WHITE);
                // Botao de Ajuda
        if (mouseOnHelpButton)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                DrawTexture(rm.menu.clickHelpButton, X_MENU_BUTTON, Y_HELP_BUTTON, WHITE);
            else
                DrawTexture(rm.menu.bigMouseHelpButton, X_MENU_BUTTON, Y_HELP_BUTTON, WHITE);
        }
        else
            DrawTexture(rm.menu.bigNormalHelpButton, X_MENU_BUTTON, Y_HELP_BUTTON, WHITE);
        // Botao de Fechar jogo
        if (mouseOnCloseButton)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawTexture(rm.menu.clickCloseButton, X_MENU_BUTTON, Y_CLOSE_BUTTON, WHITE);
                //if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            }
            else
                DrawTexture(rm.menu.bigMouseCloseButton, X_MENU_BUTTON, Y_CLOSE_BUTTON, WHITE);
        }
        else
            DrawTexture(rm.menu.bigNormalCloseButton, X_MENU_BUTTON, Y_CLOSE_BUTTON, WHITE);
    }
    else
    {
        if (mouseOnStartButton)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                DrawTexture(rm.menu.clickStartButton, X_MENU_BUTTON, Y_START_BUTTON, WHITE);
            else
                DrawTexture(rm.menu.bigMouseStartButton, X_MENU_BUTTON*3+140, Y_START_BUTTON, WHITE);
        }
        else
            DrawTexture(rm.menu.bigNormalStartButton, X_MENU_BUTTON*3+140, Y_START_BUTTON, WHITE);
                // Botao de Carregar jogo
        if (mouseOnLoadButton)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                DrawTexture(rm.menu.clickLoadButton, X_MENU_BUTTON, Y_LOAD_BUTTON, WHITE);
            else
                DrawTexture(rm.menu.bigMouseLoadButton, X_MENU_BUTTON*3+140, Y_LOAD_BUTTON, WHITE);
        }
        else
            DrawTexture(rm.menu.bigNormalLoadButton, X_MENU_BUTTON*3+140, Y_LOAD_BUTTON, WHITE);
                // Botao de Ajuda
        if (mouseOnHelpButton)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                DrawTexture(rm.menu.clickHelpButton, X_MENU_BUTTON, Y_HELP_BUTTON, WHITE);
            else
                DrawTexture(rm.menu.bigMouseHelpButton, X_MENU_BUTTON*3+140, Y_HELP_BUTTON, WHITE);
        }
        else
            DrawTexture(rm.menu.bigNormalHelpButton, X_MENU_BUTTON*3+140, Y_HELP_BUTTON, WHITE);
        // Botao de Fechar jogo
        if (mouseOnCloseButton)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawTexture(rm.menu.clickCloseButton, X_MENU_BUTTON, Y_CLOSE_BUTTON, WHITE);
                //if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            }
            else
                DrawTexture(rm.menu.bigMouseCloseButton, X_MENU_BUTTON*3+140, Y_CLOSE_BUTTON, WHITE);
        }
        else
            DrawTexture(rm.menu.bigNormalCloseButton, X_MENU_BUTTON*3+140, Y_CLOSE_BUTTON, WHITE);
    }

    EndDrawing();
}



const int X_SLOTS_BUTTON = 200;
const int Y_SLOT1_BUTTON = 100;
const int Y_SLOT2_BUTTON = 160;
const int Y_SLOT3_BUTTON = 220;
const int Y_GOTOMENU_BUTTON = 280;

void inputUpdateAndDrawLoad(Game *game, bool isFullscreen)
{

    Vector2 mousePosition = GetMousePosition();

    Rectangle startArea = {X_SLOTS_BUTTON, Y_SLOT1_BUTTON, (int) rm.menu.bigNormalStartButton.width, (int) rm.menu.bigNormalStartButton.height};
    Rectangle loadArea = {X_SLOTS_BUTTON, Y_SLOT2_BUTTON, (int) rm.menu.bigNormalLoadButton.width, (int) rm.menu.bigNormalLoadButton.height};
    Rectangle helpArea = {X_SLOTS_BUTTON, Y_SLOT3_BUTTON, (int) rm.menu.bigNormalHelpButton.width, (int) rm.menu.bigNormalHelpButton.height};
    Rectangle closeArea = {X_SLOTS_BUTTON, Y_GOTOMENU_BUTTON, (int) rm.menu.bigNormalCloseButton.width, (int) rm.menu.bigNormalCloseButton.height};

    bool mouseOnStartButton = CheckCollisionPointRec(mousePosition, startArea);
    bool mouseOnLoadButton = CheckCollisionPointRec(mousePosition, loadArea);
    bool mouseOnHelpButton = CheckCollisionPointRec(mousePosition, helpArea);
    bool mouseOnCloseButton = CheckCollisionPointRec(mousePosition, closeArea);

    if(mouseOnStartButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if(checkEmptySaveSlot("save1")==false)
        {
            game->status = GAMELOBBY;
            game->saveSlot1 =true;
            game->player = loadGame("save1");

                game->playerLobbyFirstPos = game->player.pos;

                game->gl = createGameLobby(&game->player);

                game->playerLobbyReturnPos = game->gl.posComputer;

                printf("Posicao Retorno (M) -> X: %.2f, Y: %.2f\n",
                       game->playerLobbyReturnPos.x,
                       game->playerLobbyReturnPos.y);

                game->gl.player->pos = game->playerLobbyFirstPos;
        }
    }

    else if(mouseOnLoadButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if(checkEmptySaveSlot("save2")==false)
        {
            game->status = GAMELOBBY;
            game->saveSlot2 =true;
            game->player = loadGame("save2");

                game->playerLobbyFirstPos = game->player.pos;

                game->gl = createGameLobby(&game->player);

                game->playerLobbyReturnPos = game->gl.posComputer;

                printf("Posicao Retorno (M) -> X: %.2f, Y: %.2f\n",
                       game->playerLobbyReturnPos.x,
                       game->playerLobbyReturnPos.y);

                game->gl.player->pos = game->playerLobbyFirstPos;
        }
    }

    else if(mouseOnHelpButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if(checkEmptySaveSlot("save3")==false)
        {
            game->status = GAMELOBBY;
            game->saveSlot3 =true;
            game->player = loadGame("save3");

                game->playerLobbyFirstPos = game->player.pos;

                game->gl = createGameLobby(&game->player);

                game->playerLobbyReturnPos = game->gl.posComputer;

                printf("Posicao Retorno (M) -> X: %.2f, Y: %.2f\n",
                       game->playerLobbyReturnPos.x,
                       game->playerLobbyReturnPos.y);

                game->gl.player->pos = game->playerLobbyFirstPos;
        }
    }

    else if(mouseOnCloseButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = MENU;

    //------------------------------------------------------------------

    BeginDrawing();
    ClearBackground(BLACK);

    if (mouseOnStartButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DrawTexture(rm.menu.clickStartButton, X_SLOTS_BUTTON, Y_SLOT1_BUTTON, WHITE);
        else
            DrawTexture(rm.menu.bigSave1LoadButton, X_SLOTS_BUTTON, Y_SLOT1_BUTTON, WHITE);
    }
    else
        DrawTexture(rm.menu.bigSave1LoadButton, X_SLOTS_BUTTON, Y_SLOT1_BUTTON, WHITE);
            // Botao de Carregar jogo
    if (mouseOnLoadButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DrawTexture(rm.menu.clickLoadButton, X_SLOTS_BUTTON, Y_SLOT2_BUTTON, WHITE);
        else
            DrawTexture(rm.menu.bigSave2LoadButton, X_SLOTS_BUTTON, Y_SLOT2_BUTTON, WHITE);
    }
    else
        DrawTexture(rm.menu.bigSave2LoadButton, X_SLOTS_BUTTON, Y_SLOT2_BUTTON, WHITE);
            // Botao de Ajuda
    if (mouseOnHelpButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DrawTexture(rm.menu.clickHelpButton, X_SLOTS_BUTTON, Y_SLOT3_BUTTON, WHITE);
        else
            DrawTexture(rm.menu.bigSave3LoadButton, X_SLOTS_BUTTON, Y_SLOT3_BUTTON, WHITE);
    }
    else
        DrawTexture(rm.menu.bigSave3LoadButton, X_SLOTS_BUTTON, Y_SLOT3_BUTTON, WHITE);




    // Botao de Fechar jogo
    if (mouseOnCloseButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawTexture(rm.menu.clickCloseButton, X_SLOTS_BUTTON, Y_GOTOMENU_BUTTON, WHITE);
            //if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        }
        else
            DrawTexture(rm.menu.bigBackMenuButton, X_SLOTS_BUTTON, Y_GOTOMENU_BUTTON, WHITE);
    }

    else
        DrawTexture(rm.menu.bigBackMenuButton, X_SLOTS_BUTTON, Y_GOTOMENU_BUTTON, WHITE);

    EndDrawing();
}



void inputUpdateAndDrawHelp(Game *game, bool isFullscreen)
{

    if (IsKeyPressed(KEY_BACKSPACE))
        {
            game->status = MENU;
        }

    //------------------------------------------------------------------

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    if (isFullscreen){
        DrawText("SEJA BEM VINDO(A) AO CODE KNIGHT!!", 10 * 2.4, 10 * 2.4, (int)(35 * 2.4), DARKPURPLE);

        DrawText("Uma breve historia:", 10 * 2.4, 45 * 2.4, (int)(10 * 2.4), DARKPURPLE);
        DrawText("Voce eh um programador que esta desenvolvendo um programa que ira revolucionar completamente a", 10 * 2.4, 55 * 2.4, (int)(15 * 2.4), PURPLE);
        DrawText("industria, porem voce ficou de saco cheio de corrigir os bugs no seu codigo por vias normais.", 10 * 2.4, 70 * 2.4, (int)(15 * 2.4), PURPLE);
        DrawText("Agora, com determinacao e coragem, voce vai CORRIGIR os bugs e erros... NA MARRA!!!", 10 * 2.4, 85 * 2.4, (int)(15 * 2.4), PURPLE);


        DrawText("Um guia rapido de como jogar:", 10 * 2.4, 105 * 2.4, (int)(10 * 2.4), GRAY);


        DrawText("Use as setas (<-  ->) para movimentacao horizontal", 10 * 2.4, 115 * 2.4, (int)(20 * 2.4), BLACK);
        DrawText("Use 'Z' para saltar", 10 * 2.4, 135 * 2.4, (int)(20 * 2.4), BLACK);
        DrawText("Use 'X' para atacar", 10 * 2.4, 155 * 2.4, (int)(20 * 2.4), BLACK);
        DrawText("Use a seta para cima para interagir", 10 * 2.4, 175 * 2.4, (int)(20 * 2.4), BLACK);
        DrawText("Combine as setas verticais com o ataque para direciona-lo", 10 * 2.4, 195 * 2.4, (int)(20 * 2.4), BLACK);
        DrawText("Segure 'A' para curar sua vida", 10 * 2.4, 215 * 2.4, (int)(20 * 2.4), BLACK);
        DrawText("Use 'F' para usar sua habilidade", 10 * 2.4, 235 * 2.4, (int)(20 * 2.4), BLACK);
        DrawText("Aperte 'Tab' para acessar seu inventario", 10 * 2.4, 255 * 2.4, (int)(20 * 2.4), BLACK);

        DrawText("Aperte 'Esc' para pausar seu jogo", 10 * 2.4, 275 * 2.4, (int)(20 * 2.4), BLACK);

        DrawText("JOGABILIDADE", 10 * 2.4, 300 * 2.4, (int)(25 * 2.4), MAROON);
        DrawText("Por mais que voce tenha coragem, eh preciso estrategia! Dentro de um codigo, os bugs batem de volta,", 10 * 2.4, 325 * 2.4, (int)(15 * 2.4), RED);
        DrawText("entao tome cuidado! Se os inimigos te baterem demais, voce morre! (Ta achando que a vida eh um jogo?)", 10 * 2.4, 340 * 2.4, (int)(15 * 2.4), RED);
        DrawText("Mas nao se preoupe, voce pode usar sua Aura para se curar e usar habilidades poderosas. Ao derrotar", 10 * 2.4, 355 * 2.4, (int)(15 * 2.4), RED);
        DrawText("inimigos, voce 'farma' Aura e ganha Tickets (do RU), use-os com sabedoria! Alem disso, amuletos e", 10 * 2.4, 370 * 2.4, (int)(15 * 2.4), RED);
        DrawText("itens tambem estao espalhados por ai, pegue-os e experimente, os efeitos sao surpreendentes.", 10 * 2.4, 385 * 2.4, (int)(15 * 2.4), RED);
        DrawText("Por ultimo,no final de cada fase, ha um poderoso chefe. Decore seus padroes, desvie com velocidade", 10 * 2.4, 400 * 2.4, (int)(15 * 2.4), RED);
        DrawText("e venca-o para retornar a tranquilidade da vila. La voce salva seu progresso, compra e maneja", 10 * 2.4, 415 * 2.4, (int)(15 * 2.4), RED);
        DrawText("amuletos e tira um descanso merecido!", 10 * 2.4, 430 * 2.4, (int)(15 * 2.4), RED);
    }
    else {

        DrawText("SEJA BEM VINDO(A) AO CODE KNIGHT!!", 10 , 10 , (int)(35 ), DARKPURPLE);

        DrawText("Uma breve historia:", 10 , 45 , (int)(10 ), DARKPURPLE);
        DrawText("Voce eh um programador que esta desenvolvendo um programa que ira revolucionar completamente a", 10 , 55 , (int)(15 ), PURPLE);
        DrawText("industria, porem voce ficou de saco cheio de corrigir os bugs no seu codigo por vias normais.", 10 , 70 , (int)(15 ), PURPLE);
        DrawText("Agora, com determinacao e coragem, voce vai CORRIGIR os bugs e erros... NA MARRA!!!", 10 , 85 , (int)(15 ), PURPLE);

        DrawText("Um guia rapido de como jogar:", 10 , 105 , (int)(10 ), GRAY);

        DrawText("Use as setas (<-  ->) para movimentacao horizontal", 10 , 115 , (int)(20 ), BLACK);
        DrawText("Use 'Z' para saltar", 10 , 135 , (int)(20 ), BLACK);
        DrawText("Use 'X' para atacar", 10 , 155 , (int)(20 ), BLACK);
        DrawText("Use a seta para cima para interagir", 10 , 175 , (int)(20 ), BLACK);
        DrawText("Combine as setas verticais com o ataque para direciona-lo", 10 , 195 , (int)(20 ), BLACK);
        DrawText("Segure 'A' para curar sua vida", 10 , 215 , (int)(20 ), BLACK);
        DrawText("Use 'F' para usar sua habilidade", 10 , 235 , (int)(20 ), BLACK);
        DrawText("Aperte 'Tab' para acessar seu inventario", 10 , 255 , (int)(20 ), BLACK);

        DrawText("Aperte 'Esc' para pausar seu jogo", 10 , 275 , (int)(20 ), BLACK);

        DrawText("JOGABILIDADE", 10 , 300 , (int)(25 ), MAROON);
        DrawText("Por mais que voce tenha coragem, eh preciso estrategia! Dentro de um codigo, os bugs batem de volta,", 10 , 325 , (int)(15 ), RED);
        DrawText("entao tome cuidado! Se os inimigos te baterem demais, voce morre! (Ta achando que a vida eh um jogo?)", 10 , 340 , (int)(15 ), RED);
        DrawText("Mas nao se preoupe, voce pode usar sua Aura para se curar e usar habilidades poderosas. Ao derrotar", 10 , 355 , (int)(15 ), RED);
        DrawText("inimigos, voce 'farma' Aura e ganha Tickets (do RU), use-os com sabedoria! Alem disso, amuletos e", 10 , 370 , (int)(15 ), RED);
        DrawText("itens tambem estao espalhados por ai, pegue-os e experimente, os efeitos sao surpreendentes.", 10 , 385 , (int)(15 ), RED);
        DrawText("Por ultimo,no final de cada fase, ha um poderoso chefe. Decore seus padroes, desvie com velocidade", 10 , 400 , (int)(15 ), RED);
        DrawText("e venca-o para retornar a tranquilidade da vila. La voce salva seu progresso, compra e maneja", 10 , 415 , (int)(15 ), RED);
        DrawText("amuletos e tira um descanso merecido!", 10 , 430 , (int)(15 ), RED);
    }

    EndDrawing();
}
