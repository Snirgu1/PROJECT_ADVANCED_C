#ifndef PROJECT_ADVANCED_C_DATABASE_H
#define PROJECT_ADVANCED_C_DATABASE_H
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

/* Define and MACROS */
#define Uchar unsigned char
#define Uint unsigned int
#define N 7
#define NUM_OF_RECON_COMMANDS 5
#define MEM_ALLOC_ERR (-1)
#define NUM_OF_DELIM 2
#define NUM_OF_FIND_COMMANDS 8
#define INCREASE 1
#define DECREASE 1
#define INITIAL (-1)

/* Data structure implementation */
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

typedef struct ListNode {        /* single linked list node struct */
    struct ListNode* prev;
    struct ListNode* next;
    Apt* apartment;
}LNode ;

typedef struct Commands_List {   /* singly linked list struct (commands) */
    struct Clnode* head;
    struct Clnode* tail;
}CList;

typedef struct CListNode{      /* commands singly linked list nodes  */
    struct ListNode* next;
    char* command;
    int code;
}Clnode;

/* Functions Implementation */
Apt* AllocateApt(int code, char* address, int price, short int num_of_rooms, short int day, short int month, short int year, time_t Database_entry_date);
LNode *AllocateLNode(Apt *apt);
List AllocateEmptyList();
void InitializeList(List* list);
void AddToEmptyList (List *list, LNode *node);
void AddToBeginningOfList (List *list, LNode *node);
void AddToEndOfList (List *list, LNode *node);
void AddToInnerPlaceInList (LNode *prev, LNode *node);
LNode* FindPlaceToInsertByX(List *list, Apt* apt);
void AddToList (List *list, Apt* apt);
void DeleteFromInnerPlaceInList(LNode *prev);
void DeallocateListNode(LNode *node);
void DeleteFromBeginningOfList(List *list);
void DeleteFromEndOfList(List *list);
void DeleteFromList (List *list, Apt *apt);
LNode *FindPlaceToDeleteByX(List *list, Apt* apt);
void PrintList(List *list);
void PrintData(Apt *apt);
void ClearList(List *list);
void* check_malloc (int num_of_bytes);

#endif
