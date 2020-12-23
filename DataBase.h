#ifndef PROJECT_DATABASE_H
#define PROJECT_DATABASE_H
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/* Define and MACROS */
#define Uchar unsigned char
#define Uint unsigned int
#define N 7
#define MEM_ALLOC_ERR (-1)
#define NUM_OF_DELIM 3
#define NUM_OF_FIND_COMMANDS 8
#define INCREASE 1
#define DECREASE (-1)
#define MAX_INIT 2147483647 // 2^31;
#define INITIAL 0
#define TRUE 1
#define MAXROOMS 15
#define FALSE 0
#define EXIT_PROG 1
#define BOOL int
#define FILE_ERROR 1
/* Data structure implementation */

typedef struct FindKeys{
    short int year,month,day;
    short int lastXdays_enter;
    short int minR;
    short int maxR;
    short int order;
    int maxP;
    int minP;
}Find_keys;

typedef struct Apartment{        /* apartment details */
    int code ;
    char* address;
    int price ;
    short int num_of_rooms;
    short int day, month,year;
    time_t Database_entry_date;
}Apt;

typedef struct LIST{             /* singly linked list struct (using also for sorted list) */
    struct ListNode* head;
    struct ListNode* tail;
}List;

typedef struct ListNode {        /* doubly linked list node struct */
    struct ListNode* prev;
    struct ListNode* next;
    Apt* apartment;
}LNode;

typedef struct Commands_List {   /* singly linked list struct (commands) */
    struct CListNode* head;
    struct CListNode* tail;
}CList;

typedef struct CListNode{      /* commands singly linked list nodes  */
    struct CListNode* next;
    char* command;
    int commandNum;
}CLnode;

/* Functions Implementation */

//void InitializeDataBase(List *lst,List* lstPrice,char** short_term_history,CList* history);
Apt* AllocateApt(char* line);
LNode *AllocateLNode(Apt *apt);
void InitializeList(List* list);
void InitializeClist(CList* Clst);
void AddToEmptyList (List *list, LNode *node);
void AddToBeginningOfList (List *list, LNode *node);
void AddToEndOfList (List *list, LNode *node);
void AddToInnerPlaceInList (LNode *prev, LNode *node);
LNode* FindPlaceToInsertByPrice(List *list, Apt* apt);
void AddToListByPrice (List *list, Apt* apt);
void DeleteFromInnerPlaceInList(LNode *prev);
void DeleteFromInnerPlaceInPriceList(LNode *prev);
void DeallocateListNode(LNode *node);
void DeleteFromBeginningOfList(List *list);
void DeleteFromBeginningOfPriceList(List *list);
void DeleteFromEndOfList(List *list);
void DeleteFromEndOfPriceList(List *list);
void DeleteFromList (List *list, List *listByPrice, int code);
void DeleteFromPriceList(List *list, LNode *prev);
LNode *FindPlaceToDeleteByCode(List *list, int code);
void PrintList(List *list);
void PrintData(Apt *apt);
void ClearList(List *list);
void* check_malloc (int num_of_bytes);
void DeleteFromBeginningOfPList(List *list);
CLnode* AllocateCLnode(char* command);
void AddToCList(CList *list, char* command);
void ClearCList(CList *list);
void DeleteFromBeginningOfCList(CList *list);
void DeallocateCListcell(CLnode *cell);
void PrintCList(CList *list);
void PrintShortHArray(char **array, CList *list);
#endif //PROJECT_DATABASE_H