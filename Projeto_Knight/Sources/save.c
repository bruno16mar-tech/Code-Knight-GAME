#include <stdio.h>
#include "raylib.h"
#include "player.h"

void saveGame (char saveName[6], Player player)
{
    FILE *arq;

    if(!(arq = fopen(TextFormat("saves/%s.bin", saveName), "wb")))
        printf("Erro de abertura no save.\n");
    else
    {
        if(fwrite(&player,sizeof(Player), 1,arq)!= 1)
            printf("Erro no save.\n");
    }
    fclose(arq);

}

Player loadGame(char saveName[6])
{
    FILE *arq;
    Player player;

    if(!(arq = fopen(TextFormat("saves/%s.bin", saveName), "rb")))
        printf("Erro de abertura no save.\n");
    else
    {
        if(fread(&player,sizeof(Player), 1,arq)!= 1)
            printf("Erro no save.\n");
    }
    fclose(arq);

    return player;
}


bool checkEmptySaveSlot (char saveName[6])
{
    FILE *arq;
    bool emptySlot;

    if(!(arq = fopen(TextFormat("saves/%s.bin", saveName), "rb")))
        printf("Erro de abertura.\n");
    else
    {
        fseek(arq,0L, SEEK_END);
        long int size = ftell(arq);

        if (size==0)
            emptySlot = true;
        else
            emptySlot = false;
    }
    fclose(arq);

    return emptySlot;
}
