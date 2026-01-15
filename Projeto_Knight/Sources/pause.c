#include "raylib.h"
#include "pause.h"
#include "player.h"

const int X_PAUSE_BUTTON = 354;
const int Y_RETURN_BUTTON = 175;
const int Y_SAVE_BUTTON = 230;
const int Y_LEAVE_BUTTON = 285;
const int Y_FULLSCREEN_BUTTON = 340;

void inputUpdateAndDrawPause(Game *game, bool* isFullscreen)
{
    Vector2 mousePosition = GetMousePosition();

    Rectangle returnArea = {0};
    Rectangle saveArea = {0};
    Rectangle leaveArea = {0};
    Rectangle fullScreenArea = {0};

    if(*isFullscreen==false)
    {
        returnArea = (Rectangle) {X_PAUSE_BUTTON, Y_RETURN_BUTTON, (int) rm.pause.normalReturnButton.width, (int) rm.pause.normalReturnButton.height};
        saveArea = (Rectangle){X_PAUSE_BUTTON, Y_SAVE_BUTTON, (int) rm.pause.normalSaveButton.width, (int) rm.pause.normalSaveButton.height};
        leaveArea = (Rectangle){X_PAUSE_BUTTON, Y_LEAVE_BUTTON, (int) rm.pause.normalLeaveButton.width, (int) rm.pause.normalLeaveButton.height};
        fullScreenArea = (Rectangle){X_PAUSE_BUTTON+((int) rm.pause.normalLeaveButton.width/2),Y_FULLSCREEN_BUTTON,(int)rm.pause.FullscreenButton.width,(int)rm.pause.FullscreenButton.height};
    }
    else
    {
        returnArea = (Rectangle){X_PAUSE_BUTTON*2+140, Y_RETURN_BUTTON*2, (int) rm.pause.normalReturnButtonG.width, (int) rm.pause.normalReturnButtonG.height};
        saveArea = (Rectangle){X_PAUSE_BUTTON*2+140, Y_SAVE_BUTTON*2, (int) rm.pause.normalSaveButtonG.width, (int) rm.pause.normalSaveButtonG.height};
        leaveArea = (Rectangle){X_PAUSE_BUTTON*2+140, Y_LEAVE_BUTTON*2, (int) rm.pause.normalLeaveButtonG.width, (int) rm.pause.normalLeaveButtonG.height};
        fullScreenArea = (Rectangle){X_PAUSE_BUTTON*2+100+((int) rm.pause.normalLeaveButton.width/2),Y_FULLSCREEN_BUTTON*2,(int)rm.pause.MinimizeButton.width,(int)rm.pause.MinimizeButton.height};
    }

    bool mouseOnReturnButton = CheckCollisionPointRec(mousePosition, returnArea);
    bool mouseOnSaveButton = CheckCollisionPointRec(mousePosition, saveArea);
    bool mouseOnLeaveButton = CheckCollisionPointRec(mousePosition, leaveArea);
    bool mouseOnFullscreenButton = CheckCollisionPointRec(mousePosition, fullScreenArea);

    if(mouseOnReturnButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        game->status = game->lastStatus;
    }

    if(mouseOnLeaveButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = CONFIRM;

    if(mouseOnFullscreenButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        *isFullscreen = !(*isFullscreen);

    //---------------------------------------------------

    BeginDrawing();
    //ClearBackground(LIGHTGRAY);

    if(*isFullscreen==false)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));
        DrawRectangle(266, 0, 266, 450, BLACK);
        DrawText("JOGO PAUSADO!!", 300, 40, 25, WHITE);

        if (mouseOnReturnButton)
            DrawTexture(rm.pause.mouseReturnButton, X_PAUSE_BUTTON, Y_RETURN_BUTTON, WHITE);
        else
            DrawTexture(rm.pause.normalReturnButton, X_PAUSE_BUTTON, Y_RETURN_BUTTON, WHITE);


        if (mouseOnSaveButton)
            DrawTexture(rm.pause.mouseSaveButton, X_PAUSE_BUTTON, Y_SAVE_BUTTON, WHITE);
        else
            DrawTexture(rm.pause.normalSaveButton, X_PAUSE_BUTTON, Y_SAVE_BUTTON, WHITE);


        if (mouseOnLeaveButton)
            DrawTexture(rm.pause.mouseLeaveButton, X_PAUSE_BUTTON, Y_LEAVE_BUTTON, WHITE);
        else
            DrawTexture(rm.pause.normalLeaveButton, X_PAUSE_BUTTON, Y_LEAVE_BUTTON, WHITE);

        if (mouseOnFullscreenButton)
            DrawTexture(rm.pause.FullscreenButton, X_PAUSE_BUTTON+((int) rm.pause.normalLeaveButton.width/2), Y_FULLSCREEN_BUTTON, WHITE);
        else
            DrawTexture(rm.pause.FullscreenButton, X_PAUSE_BUTTON+((int) rm.pause.normalLeaveButton.width/2), Y_FULLSCREEN_BUTTON, WHITE);
    }
    else
    {
        DrawRectangle(0, 0, 1920, 1080, Fade(BLACK, 0.6f));
        DrawRectangle(266*2, 0, 266*2, 450*2, BLACK);
        DrawText("JOGO PAUSADO!!", 300*2+140, 40*2, 25*2, WHITE);

        if (mouseOnReturnButton)
            DrawTexture(rm.pause.mouseReturnButtonG, X_PAUSE_BUTTON*2+140, Y_RETURN_BUTTON*2, WHITE);
        else
            DrawTexture(rm.pause.normalReturnButtonG, X_PAUSE_BUTTON*2+140, Y_RETURN_BUTTON*2, WHITE);


        if (mouseOnSaveButton)
            DrawTexture(rm.pause.mouseSaveButtonG, X_PAUSE_BUTTON*2+140, Y_SAVE_BUTTON*2, WHITE);
        else
            DrawTexture(rm.pause.normalSaveButtonG, X_PAUSE_BUTTON*2+140, Y_SAVE_BUTTON*2, WHITE);


        if (mouseOnLeaveButton)
            DrawTexture(rm.pause.mouseLeaveButtonG, X_PAUSE_BUTTON*2+140, Y_LEAVE_BUTTON*2, WHITE);
        else
            DrawTexture(rm.pause.normalLeaveButtonG, X_PAUSE_BUTTON*2+140, Y_LEAVE_BUTTON*2, WHITE);

        if (mouseOnFullscreenButton)
            DrawTexture(rm.pause.MinimizeButton, X_PAUSE_BUTTON*2+100+((int) rm.pause.normalLeaveButton.width/2), Y_FULLSCREEN_BUTTON*2, WHITE);
        else
            DrawTexture(rm.pause.MinimizeButton, X_PAUSE_BUTTON*2+100+((int) rm.pause.normalLeaveButton.width/2), Y_FULLSCREEN_BUTTON*2, WHITE);
    }


    EndDrawing();

}

void inputUpdateAndDrawConfirm(Game *game)
{
    Vector2 mousePosition = GetMousePosition();

    Rectangle yesArea = {((GetScreenWidth()/2)-73), ((GetScreenHeight()/2)+15),32,15};
    Rectangle noArea = {((GetScreenWidth()/2)+41), ((GetScreenHeight()/2)+15),32,15};

    bool mouseOnYesButton = CheckCollisionPointRec(mousePosition, yesArea);
    bool mouseOnNoButton = CheckCollisionPointRec(mousePosition, noArea);

    if ( mouseOnNoButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = PAUSE;

    if (mouseOnYesButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        game->status = MENU;
        game->saveSlot1 = false;
        game->saveSlot2 = false;
        game->saveSlot3 = false;
        if(game->lastStatus==GAMEWORLD)
        {
            destroysGameWorld(game->gw);
            game->gameWorldInitiate = false;
        }
        else if(game->lastStatus==GAMELOBBY)
        {
            resetGameLobby(&game->gl,game->playerLobbyFirstPos);
        }
        resetPlayer(&game->player);
    }


    //-----------------------------------------------

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    DrawRectangle(((GetScreenWidth()/2) - 200), ((GetScreenHeight()/2) - 50), 400, 100, BLACK);
    DrawText("Voce deseja mesmo sair?", ((GetScreenWidth()/2) - 62), ((GetScreenHeight()/2) - 34), 5, WHITE);
    DrawText("Todo o progresso nao salvo sera perdido!", ((GetScreenWidth()/2) - 150), ((GetScreenHeight()/2) - 16), 15, RED);
    DrawText("SIM", ((GetScreenWidth()/2) - 71), ((GetScreenHeight()/2) + 15), 15, WHITE);
    DrawText("NAO", ((GetScreenWidth()/2) + 43), ((GetScreenHeight()/2) + 15), 15, WHITE);

    EndDrawing();
}

void inputUpdateDeathScreen(Game *game)
{
    Vector2 mousePosition = GetMousePosition();

    Rectangle yesArea = {((GetScreenWidth()/2)-73), ((GetScreenHeight()/2)+15),32,15};
    Rectangle noArea = {((GetScreenWidth()/2)+41), ((GetScreenHeight()/2)+15),32,15};

    bool mouseOnYesButton = CheckCollisionPointRec(mousePosition, yesArea);
    bool mouseOnNoButton = CheckCollisionPointRec(mousePosition, noArea);

    if ( mouseOnNoButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = MENU;

    if (mouseOnYesButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        game->status = GAMELOBBY;
        game->player.pos = game->playerLobbyFirstPos;
        destroysGameWorld(game->gw);
    }

}


    //-----------------------------------------------
void drawDeathScreen(GameWorld *gw)
{
    Rectangle yesAreaDebug = {((GetScreenWidth()/2)-73), ((GetScreenHeight()/2)+15),32,15};
    DrawRectangleLinesEx(yesAreaDebug, 1, RED); // Desenha a borda da área de clique em vermelho


    //DrawRectangle(((GetScreenWidth()/2) - 200), ((GetScreenHeight()/2) - 50), 400, 100, BLACK);
    DrawText("VOCÊ MORREU", ((GetScreenWidth()/2) - 62), ((GetScreenHeight()/2) - 34), 64, RED);
    DrawText("Tentar novamente?", ((GetScreenWidth()/2) - 150), ((GetScreenHeight()/2) - 16), 15, WHITE);
    DrawText("SIM", ((GetScreenWidth()/2) - 71), ((GetScreenHeight()/2) + 15), 15, WHITE);
    DrawText("NAO", ((GetScreenWidth()/2) + 43), ((GetScreenHeight()/2) + 15), 15, WHITE);
}

