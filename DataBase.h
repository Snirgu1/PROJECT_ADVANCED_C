#ifndef PROJECT_ADVANCED_C_DATABASE_H
#define PROJECT_ADVANCED_C_DATABASE_H
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

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

typedef struct Apartment{        /* apartment details */
    int code ;
    char* address;
    int price ;
    short int num_of_rooms;
    short int day, month,year;
    time_t Database_entry_date;
}apt;

typedef struct LIST{             /* singly linked list struct (using also for sorted list) */
    struct ListNode* head;
    struct ListNode* tail;
}List;

typedef struct ListNode {        /* single linked list node struct */
    struct ListNode* prev;
    struct ListNode* next;
    apt* apartment;
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





#endif
