#ifndef PROJECT_ADVANCED_C_MAIN_COMMANDS_H
#define PROJECT_ADVANCED_C_MAIN_COMMANDS_H
#include "DataBase.h"
#include "Reconstraction.h"

void checkCommand(char* line, List* lstByCode, List* lstByPrice);

/* ===== FIND FUNCTIONS =====*/
void find(List* apartment, char* line);

/* ===== ADD FUNCTIONS =====*/
Apt* CreApt(char* line); /* TEST ONLY !!!! _ NOT EFFICIENT */
void addApt(char* line, List* lstByCode, List* lstByPrice);

/* ===== BUY FUNCTIONS =====*/
void buyApt(char* line, List* lstByCode, List* lstByPrice);
int getCode(char *line);


/* ===== DELETE FUNCTIONS =====*/



/* ===== EXIT FUNCTIONS =====*/


#endif
