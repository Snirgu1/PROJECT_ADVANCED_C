#ifndef PROJECT_ADVANCED_C_FILESOP_H
#define PROJECT_ADVANCED_C_FILESOP_H
#include "DataBase.h"

void WriteHistoryToFile(CList* lst_history, char* shortHistory[]);
void WriteCListToFile(FILE* f,CList *lst_history);
void WriteCmdArrToFile(FILE* f,char* shortHistory[],int start_ind);
#endif
