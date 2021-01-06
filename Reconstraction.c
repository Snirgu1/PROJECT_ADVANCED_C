#include "Reconstraction.h"

static int commandNum = 1;
static int i = 0;

void checkReconstraction(char* line, List* lstByCode, List* lstByPrice, char** shortHistory, CList* history)
{
    int len;
    int num;
    if(line[0] == '!')
        checkCommand(shortHistory[6], lstByCode, lstByPrice, shortHistory, history);
    else
    {
        num = atoi(line);
        len = checkNumLength(num);
        if( *(line + len) == '\0')
            findCommand(NULL,num, lstByCode, lstByPrice, shortHistory, history);
        else
            findCommand(line+len+1, num, lstByCode, lstByPrice, shortHistory, history);
    }
}

int checkNumLength(int num)
{
    int  counter = 1 ;
    while( num > 10 )
    {
        counter++;
        num= num/10;
    }
    return counter;
}

void switchCommand(char *line, char *command, List *lstByCode, List *lstByPrice, char **shortHistory, CList *history)
{
    if(line == NULL)
    {
        checkCommand(command, lstByCode, lstByPrice, shortHistory, history);
        return;
    }
    char *newCommand, *newParameter, *oldParameter, *temp, *currCommand,*tempLine;
    tempLine = strdup(line);
    oldParameter = strtok(tempLine, "^");
    newParameter = strtok(NULL, "^");
    temp = strstr(command, oldParameter);
    newCommand = (char*)check_malloc(strlen(command) - strlen(oldParameter) + strlen(newParameter));
    strncpy(newCommand, command, strlen(command) - strlen(temp));
    while(temp != NULL) {
        currCommand = strdup(temp+strlen(oldParameter));
        newCommand[strlen(command) - strlen(temp)] = '\0';
        temp = strstr(temp + strlen(oldParameter), oldParameter);
        strcat(newCommand, newParameter);
        if(temp != NULL && temp[strlen(oldParameter)] == ' ')
            strncat(newCommand, currCommand, strlen(currCommand) - strlen(temp));
        else if (temp != NULL){
            temp = strstr(temp + strlen(oldParameter), oldParameter);
            if(temp != NULL)
                strncat(newCommand, currCommand, strlen(currCommand) - strlen(temp));
        }
    }
    strcat(newCommand, currCommand);
    checkCommand(newCommand, lstByCode, lstByPrice, shortHistory, history);
    free(tempLine);
}

void findCommand(char *line, int num, List* lstByCode, List* lstByPrice, char** shortHistory, CList* history)
{
    CLnode *curr = history->head;
    while(curr != NULL)
    {
        if(curr->commandNum == num)
        {
            switchCommand(line, curr->command, lstByCode, lstByPrice, shortHistory, history);
            break;
        }
        curr = curr->next;
    }
    if(curr == NULL)
        switchCommand(line, shortHistory[N-(commandNum-num)], lstByCode, lstByPrice, shortHistory, history);
}

void InitializeSHistory(char** shortHistory)
{
    int i;
    for(i = 0; i < 7; i++)
    {
        shortHistory[i] = NULL;
    }
}

void recordHistory(char* line, char** shortHistory, CList* history)
{
    int j, k;
    if(i != 7){
        shortHistory[i] = strdup(line);
        commandNum++;
        i++;
    }
    else{
        AddToCList(history, shortHistory[0]);
        for (j = 0, k = 1; j < 6; j++, k++)
            shortHistory[j] = shortHistory[k];
        shortHistory[6] = strdup(line);
        commandNum++;
    }
}

void InitializeDataBase(List *lst,List* lstPrice,char** short_term_history,CList* history)
{
    InitializeList(lst);
    InitializeList(lstPrice);
    InitializeSHistory(short_term_history);
    InitializeClist(history);
}