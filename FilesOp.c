#include "FilesOp.h"


void WriteHistoryToFile(CList* lst_history, char* shortHistory[])
{
    FILE *f = fopen("HistoryDoc.txt","w");
    fclose(f);
}
