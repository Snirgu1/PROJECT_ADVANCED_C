//
// Created by Snir Gueta on 07/12/2020.
//
#include "DataBase.h"
// to follow the last apt code

Apt* AllocateApt(int code, char* address, int price, short int num_of_rooms, short int day, short int month, short int year, time_t Database_entry_date)
{
    Apt* apt;
    apt = (Apt*)check_malloc(sizeof(apt));
    apt->code = code;
    apt->address = address;
    apt->price = price;
    apt->num_of_rooms = num_of_rooms;
    apt->day = day;
    apt->month = month;
    apt->year = year;
    apt->Database_entry_date = Database_entry_date;

    return apt;
}

LNode *AllocateLNode(Apt *apt)
{
    LNode *node;
    node = (LNode*)check_malloc(sizeof(LNode));
    node->apartment = apt;
    node->next = node->prev = NULL;

    return node;
}

List AllocateEmptyList()
{
    List list;

    list.head = list.tail = NULL;
    return list;
}

void InitializeList(List* list)
{
    list->head = list->tail = NULL;
}

void AddToEmptyList (List *list, LNode *node)
{
    list->head = list->tail = node;
}

void AddToBeginningOfList (List *list, LNode *node)
{
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
}

void AddToEndOfList (List *list, LNode *node)
{
    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
}

void AddToInnerPlaceInList (LNode *prev, LNode *node)
{
    node->prev = prev;
    node->next = prev->next;
    prev->next = node;
    node->next->prev = node;
}

LNode* FindPlaceToInsertByX(List *list, Apt* apt)
{
    LNode *curr = list->head, *prev = NULL;

    while (curr /* & (curr->X </=/> apt->X */)
    {
        prev = curr;
        curr = curr->next;
    }

    return prev;
}

void AddToList (List *list, Apt* apt)
{
    LNode *prev;
    LNode* node = AllocateLNode(apt);

    if(list->head == NULL)
        AddToEmptyList(list, node);
    else{
        prev = FindPlaceToInsertByX(list, apt);
        if(prev == NULL)
            AddToBeginningOfList(list, node);
        else if (prev == list->tail)
            AddToEndOfList(list, node);
        else
            AddToInnerPlaceInList(prev, node);
    }
}

void DeleteFromInnerPlaceInList(LNode *prev)
{
    LNode *node = prev->next;

    prev->next = node->next;
    node->next->prev = prev;
    DeallocateListNode(node);
}

void DeallocateListNode(LNode *node)
{
    free(node->apartment);
    free(node);
}

void DeleteFromBeginningOfList(List *list)
{
    list->head = list->head->next;
    if(list->head == NULL)
    {
        DeallocateListNode(list->tail);
        list->tail = NULL;
    }
    else
    {
        DeallocateListNode(list->head->prev);
        list->head->prev = NULL;
    }
}

void DeleteFromEndOfList(List *list)
{
    if(list->tail == list->head) //assume list is not empty
    {
        DeallocateListNode(list->tail);
        list->tail = list->head = NULL;
        return;
    }
    list->tail = list->tail->prev;
    DeallocateListNode(list->tail->next);
    list->tail->next = NULL;
}

void DeleteFromList (List *list, Apt *apt)
{
    LNode *prev;

    if(list->head == NULL)
        fprintf(stderr, "List is empty, cannot delete ; \n");
        else
        {
            prev = FindPlaceToDeleteByX(list, apt);
            if(prev == list->tail)
            {
                fprintf(stderr, "Element for deletion not found! \n");
                return;
            }
            if(prev == NULL)
                DeleteFromBeginningOfList(list);
            else if(prev->next == list->tail)
                DeleteFromEndOfList(list);
            else
                DeleteFromInnerPlaceInList(prev);
        }
}

LNode *FindPlaceToDeleteByX(List *list, Apt* apt)
{
    LNode *curr = list->head, *prev = NULL;

    while(curr /* && (curr->X </=/> apt->X) */)
    {
        prev = curr;
        curr = curr->next;
    }

    return prev;
}

void PrintList(List *list)
{
    LNode *curr = list->head;

    while(curr)
    {
        PrintData(curr->apartment);
        curr = curr->next;
    }
}

void PrintData(Apt *apt)
{
    printf("Apt details:\n Code: %d\n Address: %s\n Number of rooms: %d\n Price: %d\n Entry date: %d.%d.%d, Database entry date: %d\n", apt->code, apt->address, apt->num_of_rooms, apt->price, apt->day, apt->month, apt->year, (int)apt->Database_entry_date);
}

void ClearList(List *list)
{
    while(list->head)
        DeleteFromBeginningOfList(list);
}

void* check_malloc (int num_of_bytes)
{
    void* new_arr;
    new_arr = malloc(num_of_bytes);
    if(new_arr == NULL)
    {
        printf("ERROR\n");
        exit(-1);
    }
    return new_arr;
}
