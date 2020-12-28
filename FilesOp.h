#ifndef PROJECT_ADVANCED_C_FILESOP_H
#define PROJECT_ADVANCED_C_FILESOP_H
#include "DataBase.h"
#include "Reconstraction.h"

void WriteHistoryToFile(CList* lst_history, char* shortHistory[]);
void WriteCListToFile(FILE* f,CList *lst_history);
void WriteCmdArrToFile(FILE* f,char* shortHistory[],int start_ind);

void WriteDatabaseToBinFile(List* lst);
void WriteApt(FILE* f,LNode* curr);

void getHistoryFromFile(char* short_term_history[] ,CList* history);
char* get_line(FILE* f);

BOOL isBitISet(BYTE ch, int i);
void setBit(BYTE* currByte,int i);


int getSize(List *lst);
Uchar* CollectRoomsAndDate(Apt* apt);
BYTE ExtractRooms(Sint numOfRooms);
void ExtractDate(BYTE* res,BYTE* currByte,Apt* apt);
void CollectMonth(BYTE* currByte,Sint month);
void CollectYear(BYTE* res, BYTE* currByte,Sint year);
void CollectDay(BYTE* res, BYTE* currByte,Sint day);
void readBinFile(char* fname);
void getRoomsAndDate(FILE* f,Sint* num_of_apts,Sint* year,Sint*month,Sint* day);





#endif
