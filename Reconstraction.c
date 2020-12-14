#include "Reconstraction.h"
/*
void checkReconstraction(char* line, List* lstByCode, List* lstByPrice)
{
    if(line[1] == '!')
        lastCommand;
    else if(line[1] >= 1 || line[1] <= 9)
        numCommand;
    else if(line[2] == '^')
        switchCommand;
}
*/
void InitializeSHistory(char** shortHistory)
{
    int i;
    for(i = 0; i < 7; i++)
    {
        shortHistory[i] = NULL;
    }
}