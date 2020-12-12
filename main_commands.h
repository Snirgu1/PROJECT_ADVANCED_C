#ifndef PROJECT_ADVANCED_C_MAIN_COMMANDS_H
#define PROJECT_ADVANCED_C_MAIN_COMMANDS_H
#include "DataBase.h"

void checkCommand(char* line, List* lstByCode, List* lstByPrice);

/* ===== FIND FUNCTIONS =====*/
void find(List* apartment, char* line);

/* ===== ADD FUNCTIONS =====*/
Apt* CreApt(char* line); /* TEST ONLY !!!! _ NOT EFFICIENT */
LNode* CreateLnode(Apt* apt);
void addApt(char* line, List* lstByCode, List* lstByPrice);

/* ===== BUY FUNCTIONS =====*/


/* ===== DELETE FUNCTIONS =====*/



/* ===== EXIT FUNCTIONS =====*/


#endif
