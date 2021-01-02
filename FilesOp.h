#ifndef PROJECT_ADVANCED_C_FILESOP_H
#define PROJECT_ADVANCED_C_FILESOP_H
#include "DataBase.h"
#include "Reconstraction.h"

void WriteHistoryToFile(CList* lst_history, char* shortHistory[]);          /* writing history to txt file */
void WriteCListToFile(FILE* f,CList *lst_history);                          /* writing Cmd list to txt file */
void WriteCmdArrToFile(FILE* f,char* shortHistory[],int start_ind);         /* writing Cmd Array to txt file */
void WriteDatabaseToBinFile(List* lst);                                     /* writing apartments DB to Bin file */
void WriteAptToBinFile(FILE* f,LNode* curr);                                /* writing single apt to Bin file */

void getHistoryFromFile(char* short_term_history[] ,CList* history);        /* reading History from txt file */
char* get_line(FILE* f);                                                    /* get a single line from txt file*/

BOOL isBitISet(BYTE ch, int i);
void setBit(BYTE* currByte,int i);


int getSize(List *lst);
Uchar* CollectRoomsAndDate(Apt* apt);
BYTE ExtractRooms(Sint numOfRooms);
void ExtractDate(BYTE* res,BYTE* currByte,Apt* apt);
void CollectMonth(BYTE* currByte,Sint month);
void CollectYear(BYTE* res, BYTE* currByte,Sint year);
void CollectDay(BYTE* res, BYTE* currByte,Sint day);
void ReadBinFile(char* fname,List* lstByCode, List* lstByPrice);
void getRoomsAndDate(FILE* f,Sint* num_of_apts,Sint* year,Sint*month,Sint* day);
Apt *ReadSingleAptBin(FILE *f);

#endif
