#ifndef PROJECT_MAIN_COMMANDS_H
#define PROJECT_MAIN_COMMANDS_H
#include "FilesOp.h"
/* ====== Functions Declarations ======*/
void Test1(List* lst,List* lstPrice,char* short_term_history[] ,CList *history);
void Test2(List* lst,List* lstPrice,char* short_term_history[] ,CList *history);
void checkCommand(char* line, List* lstByCode, List* lstByPrice, char** shortHistory, CList* history);
void find(List* price_lst, List* code_lst, char* line);
void addApt(char* line, List* lstByCode, List* lstByPrice);
void buyApt(char* line, List* lstByCode, List* lstByPrice);
void deleteApt(char *line ,List *lstByPrice, List *lstByCode);
void exitProg(CList *history,char** shortHistory,List* lstByCode,List* lstByPrice);
#endif