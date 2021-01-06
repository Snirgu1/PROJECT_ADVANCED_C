#ifndef PROJECT_MAIN_COMMANDS_H
#define PROJECT_MAIN_COMMANDS_H
#include "FilesOp.h"
#include "DataBase.h"
#include "Reconstraction.h"

void Test1(List* lst,List* lstPrice,char* short_term_history[] ,CList *history);
void Test2(List* lst,List* lstPrice,char* short_term_history[] ,CList *history);
void checkCommand(char* line, List* lstByCode, List* lstByPrice, char** shortHistory, CList* history);

/* ===== FIND FUNCTIONS =====*/
void find(List* price_lst, List* code_lst, char* line);
void collectKeysSearch(char* line,Find_keys *keys);
void findAndPrint(List* price_lst,List* code_lst,Find_keys* keys);
BOOL checkAptMatch(Apt* apt,Find_keys* keys);
BOOL isEarlier(short int year,short int month ,short int day,Find_keys* keys);
BOOL checkDataBaseEntryDate(time_t Database_entry_date, short int days_ago);


/* ===== ADD FUNCTIONS =====*/
Apt* CreApt(char* line); /* TEST ONLY !!!! _ NOT EFFICIENT */
void addApt(char* line, List* lstByCode, List* lstByPrice);

/* ===== BUY FUNCTIONS =====*/
void buyApt(char* line, List* lstByCode, List* lstByPrice);

/* ===== DELETE FUNCTIONS =====*/
void deleteApt(char *line ,List *lstByPrice, List *lstByCode);

BOOL InTimeRange(Apt* apt,int days_ago);
int collectDaysRange(char* line);

/* ===== EXIT FUNCTIONS =====*/
void exitProg(CList *history,char** shortHistory,List* lstByCode,List* lstByPrice);

#endif //PROJECT_MAIN_COMMANDS_H