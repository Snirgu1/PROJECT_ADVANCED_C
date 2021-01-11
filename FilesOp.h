#ifndef PROJECT_ADVANCED_C_FILESOP_H
#define PROJECT_ADVANCED_C_FILESOP_H
#include "Reconstraction.h"
/* ====== Functions Declarations ======*/
void WriteHistoryToFile(CList* lst_history, char* shortHistory[]);
void WriteDatabaseToBinFile(List* lst);
void getHistoryFromFile(char* short_term_history[] ,CList* history);
void ReadBinFile(char* fname,List* lstByCode, List* lstByPrice);
#endif