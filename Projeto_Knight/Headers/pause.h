#ifndef PAUSE_H
#define PAUSE_H

#include "raylib.h"
#include "resourceManager.h"
#include "game.h"

void inputUpdateAndDrawPause(Game *game, bool* isFullscreen);

void inputUpdateAndDrawConfirm(Game *game);

void inputUpdateDeathScreen(Game *game);

void drawDeathScreen(GameWorld *gw);

#endif // PAUSE_H
