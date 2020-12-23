#include "FilesOp.h"


void WriteHistoryToFile(CList* lst_history, char* shortHistory[])
{
    FILE *f = fopen("HistoryDoc.txt","w");
    if(!f)
    {
        fprintf(stderr,"open txt file \"HistoryDoc.txt\" failed\n");
        exit(FILE_ERROR);
    }
    if(lst_history->head == NULL )    /* if database B (Cmd LIST) is empty , write only database A (shortTerm) to file */
    {
        WriteCmdArrToFile(f,shortHistory,1);
    }
    else                            /* there is more than 7 commands, write the arr and the Clist */
    {
        WriteCListToFile(f,lst_history);
        WriteCmdArrToFile(f,shortHistory,lst_history->tail->commandNum + 1);
    }
    fclose(f);
}
void WriteCListToFile(FILE* f,CList *lst_history)
{
    CLnode *curr = lst_history->head ;
    while(curr != NULL)
    {
        fprintf(f,"%d: %s\n",curr->commandNum, curr->command);
        curr = curr->next;
    }
}
void WriteCmdArrToFile(FILE* f,char* shortHistory[],int start_ind)
{
    int  i = 0 ;
    int curr_cmd_ind = start_ind ;
    while( shortHistory[i] != NULL  && i < 7)
    {
        fprintf(f,"%d: %s\n",curr_cmd_ind,shortHistory[i]);
        curr_cmd_ind++;
        i++;
    }
}


