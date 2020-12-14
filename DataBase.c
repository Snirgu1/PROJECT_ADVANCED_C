//
// Created by Snir Gueta on 07/12/2020.
//
#include "DataBase.h"

static int code = 0;
// to follow the last apt code

 /*
Apt* AllocateApt(char* line)
{
    Apt* apt;
    apt = (Apt*)check_malloc(sizeof(apt));

    apt->code = code;
    code++;
    apt->address = address;
    apt->price = price;
    apt->num_of_rooms = num_of_rooms;
    apt->day = day;
    apt->month = month;
    apt->year = year;
    apt->Database_entry_date = Database_entry_date;

    return apt;
}
 */

LNode *AllocateLNode(Apt *apt)
{
    LNode *node = (LNode*)check_malloc(sizeof(LNode));
    node->apartment = apt;
    node->next = node->prev = NULL;

    return node;
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

LNode* FindPlaceToInsertByPrice(List *list, Apt* apt)
{
    LNode *curr = list->head, *prev = NULL;

    while (curr && (curr->apartment->price < apt->price))
    {
        prev = curr;
        curr = curr->next;
    }

    return prev;
}

LNode* FindPlaceToInsertByCode(List *list, Apt* apt)
{
    LNode *curr = list->head, *prev = NULL;

    while (curr && (curr->apartment->code < apt->code))
    {
        prev = curr;
        curr = curr->next;
    }

    return prev;
}

void AddToListByPrice (List *list, Apt* apt)
{
    LNode *prev;
    LNode* node = AllocateLNode(apt);

    if(list->head == NULL)
        AddToEmptyList(list, node);
    else{
        prev = FindPlaceToInsertByPrice(list, apt);
        if(prev == NULL)
            AddToBeginningOfList(list, node);
        else if (prev == list->tail)
            AddToEndOfList(list, node);
        else
            AddToInnerPlaceInList(prev, node);
    }
}

void AddToListByCode (List *list, Apt* apt)
{
    LNode *prev;
    LNode* node = AllocateLNode(apt);

    if(list->head == NULL)
        AddToEmptyList(list, node);
    else{
        prev = FindPlaceToInsertByCode(list, apt);
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

void DeleteFromInnerPlaceInPriceList(LNode *prev)
{
    LNode *node = prev->next;

    prev->next = node->next;
    node->next->prev = prev;
    free(node);
}

void DeallocateListNode(LNode *node)
{
    free(node->apartment->address);
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

void DeleteFromBeginningOfPriceList(List *list)
{
    list->head = list->head->next;
    if(list->head == NULL)
    {
        free(list->tail);
        list->tail = NULL;
    }
    else
    {
        free(list->head->prev);
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

void DeleteFromEndOfPriceList(List *list)
{
    if(list->tail == list->head) //assume list is not empty
    {
        free(list->tail);
        list->tail = list->head = NULL;
        return;
    }
    list->tail = list->tail->prev;
    free(list->tail->next);
    list->tail->next = NULL;
}

void DeleteFromList (List *list, List *listByPrice, int code)
{
    LNode *prevC, *prevP;

    if(list->head == NULL)
        fprintf(stderr, "List is empty, cannot delete ; \n");
    else
        {
            prevC = FindPlaceToDeleteByCode(list, code);
            prevP = FindPlaceToDeleteByCode(listByPrice, code);
            if(prevC == list->tail)
            {
                fprintf(stderr, "Element for deletion not found! \n");
                return;
            }
            if(prevC == NULL)
                DeleteFromBeginningOfList(list);
            else if(prevC->next == list->tail)
                DeleteFromEndOfList(list);
            else
                DeleteFromInnerPlaceInList(prevC);
            DeleteFromPriceList(listByPrice, prevP);
        }
}

void DeleteFromPriceList(List *list, LNode *prev)
{
    if(prev == NULL)
        DeleteFromBeginningOfPriceList(list);
    else if(prev->next == list->tail)
        DeleteFromEndOfPriceList(list);
    else
        DeleteFromInnerPlaceInPriceList(prev);
}

LNode *FindPlaceToDeleteByCode(List *list, int code)
{
    LNode *curr = list->head, *prev = NULL;

    while(curr && (curr->apartment->code != code))
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

void PrintData(Apt *apt) // printing the apartment details
{
    printf("Apt details:\n");
    printf("Code: %d\n", apt->code);
    printf("Address: %s\n", apt->address);
    printf("Number of rooms: %d\n", apt->num_of_rooms);
    printf("Price: %d\n", apt->price);
    printf("Entry date: %d.%d.%d\n", apt->day, apt->month, apt->year);
    printf("Database entry date: %d\n", (int)apt->Database_entry_date);
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
        exit(MEM_ALLOC_ERR);
    }
    return new_arr;
}

void DeleteFromBeginningOfPList(List *list)
{
    while(list->head) {
        list->head = list->head->next;
        if (list->head == NULL) {
            free(list->tail);
            list->tail = NULL;
        } else {
            free(list->head->prev);
            list->head->prev = NULL;
        }
    }
}
