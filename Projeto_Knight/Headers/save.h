#ifndef SAVE_H
#define SAVE_H

void saveGame ( char saveName[6], Player player);

Player loadGame(char saveName[6]);

bool checkEmptySaveSlot (char saveName[6]);

#endif // SAVE_H
