
#ifndef PROJECT_RECONSTRACTION_H
#define PROJECT_RECONSTRACTION_H
#include "main_commands.h"
#include "DataBase.h"
void InitializeDataBase(List *lst,List* lstPrice,char** short_term_history,CList* history);
void checkReconstraction(char* line, List* lstByCode, List* lstByPrice, char** shortHistory, CList* history);
void InitializeSHistory(char** shortHistory);
void recordHistory(char* line, char** shortHistory, CList* history);
void findCommand(char *line, int num, List* lstByCode, List* lstByPrice, char** shortHistory, CList* history);
void switchCommand(char* line,char *command, List* lstByCode, List* lstByPrice, char** shortHistory, CList* history);
int checkNumLength(int num);
#endif
