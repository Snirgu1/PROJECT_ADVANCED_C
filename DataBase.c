#include "main_commands.h"
static int commandCounter = 1;
// to follow the last apt code

void InitializeDataBase(List *lst,List* lstPrice,char** short_term_history,CList* history)
{
    InitializeList(lst);
    InitializeList(lstPrice);
    InitializeSHistory(short_term_history);
    InitializeClist(history);
}

/* allocating new apartment and initializing the parameters by the line */
Apt* getAptParameters(char* line, int currCode)
{
    Apt* res = NULL;
    const char delimA[2] = "\"";
    char* temp = strdup(line);
    char *token = strtok(temp, delimA);
    char *address = (char*)check_malloc(sizeof(char)*strlen(token));
    strcpy(address,token);

    const char delimB[2] = " ";
    int price = atoi(strtok(NULL,delimB));
    Sint num_of_rooms = atoi(strtok(NULL,delimB));
    Sint day = atoi(strtok(NULL,delimB));
    Sint month = atoi(strtok(NULL,delimB));
    Sint year = atoi(strtok(NULL,delimB));
    time_t DB_entry_date = time(&DB_entry_date);
    res = AllocateApt(currCode+1, strlen(address), day, month, year, num_of_rooms, price, address, DB_entry_date);
    free(temp);
    return res;
}

/* allocate new apt */
Apt *AllocateApt (Sint code, Sint len, Sint day, Sint month, Sint year, Sint num_of_rooms, int price, char* address, time_t EntryToDB)
{
    Apt* res = (Apt*)check_malloc(sizeof(Apt));
    res->code = code;
    res->address = (char*)check_malloc(len);
    res->address = address;
    res->year = year;
    res->month = month;
    res->day = day;
    res->num_of_rooms = num_of_rooms;
    res->Database_entry_date = EntryToDB;
    res->price = price;

    return res;
}

/* allocating new Lnode and initializing it to the new apt */
LNode *AllocateLNode(Apt *apt)
{
    LNode *node = (LNode*)check_malloc(sizeof(LNode));
    node->apartment = apt;
    node->next = node->prev = NULL;

    return node;
}

/* allocation command list node ( for Command List - Maagar B )*/
CLnode* AllocateCLnode(char* command)
{
    CLnode *res = (CLnode*)check_malloc(sizeof(CLnode));
    res->next = NULL;
    res->command = command;
    res->commandNum = commandCounter;
    commandCounter++;

    return res;

}

/* finding correct place to add node by it's price */
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

/* initializing list */
void InitializeList(List* list)
{
    list->head = list->tail = NULL;
}

/* add to list functions */
void AddToEmptyList (List *list,CList *Clist, LNode *node, CLnode *Cnode)
{
    if(list != NULL)
        list->head = list->tail = node;
    if(Clist != NULL)
        Clist->head = Clist->tail = Cnode;
}
void AddToBeginningOfList (List *list, LNode *node)
{
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
}
void AddToEndOfList(List *list, LNode *node, CList *Clist, CLnode *Cnode)
{
    if(Clist == NULL) {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    else if(list == NULL)
    {
        Clist->tail->next = Cnode;
        Clist->tail = Cnode;
    }
}
void AddToInnerPlaceInList (LNode *prev, LNode *node)
{
    node->prev = prev;
    node->next = prev->next;
    prev->next = node;
    node->next->prev = node;
}
void AddToListByPrice (List *list, Apt* apt)
{
    LNode *prev;
    LNode* node = AllocateLNode(apt);

    if(list->head == NULL)
        AddToEmptyList(list,NULL, node, NULL);
    else{
        prev = FindPlaceToInsertByPrice(list, apt);
        if(prev == NULL)
            AddToBeginningOfList(list, node);
        else if (prev == list->tail)
            AddToEndOfList(list, node, NULL, NULL);
        else
            AddToInnerPlaceInList(prev, node);
    }
}

/* delete from list functions */
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
void DeleteFromInnerPlaceInList(LNode *prev, int flag)
{
    LNode *node = prev->next;

    prev->next = node->next;
    node->next->prev = prev;
    if(flag == CODELIST)
        DeallocateListNode(node);
    else if(flag == PRICELIST)
        free(node);
}
void DeallocateListNode(LNode *node)
{
    free(node->apartment);
    free(node);
}
void DeleteFromBeginningOfList(List *list, int flag)
{
    list->head = list->head->next;
    if(list->head == NULL)
    {
        if(flag == CODELIST)
            DeallocateListNode(list->tail);
        else if(flag == PRICELIST)
            free(list->tail);
        list->tail = NULL;
    }
    else
    {
        if(flag == CODELIST)
            DeallocateListNode(list->head->prev);
        else if(flag == PRICELIST)
            free(list->head->prev);
        list->head->prev = NULL;
    }
}
void DeleteFromEndOfList(List *list, int flag)
{
    if(list->tail == list->head) //assume list is not empty
    {
        if(flag == CODELIST)
            DeallocateListNode(list->tail);
        else if(flag == PRICELIST)
            free(list->tail);
        list->tail = list->head = NULL;
        return;
    }
    list->tail = list->tail->prev;
    if(flag == CODELIST)
        DeallocateListNode(list->tail->next);
    else if(flag == PRICELIST)
        free(list->tail->next);
    list->tail->next = NULL;
}
void DeleteFromList (List *list, List *listByPrice, int code)
{
    LNode *prevC, *prevP;
    if(list->head == NULL)
        printf("List is empty, cannot delete!\n");
    else
    {
        prevC = FindPlaceToDeleteByCode(list, code);
        prevP = FindPlaceToDeleteByCode(listByPrice, code);
        if(prevC == list->tail)
        {
            printf("not found!\n");
            return;
        }
        if(prevC == NULL)
            DeleteFromBeginningOfList(list, CODELIST);
        else if(prevC->next == list->tail)
            DeleteFromEndOfList(list, CODELIST);
        else
            DeleteFromInnerPlaceInList(prevC, CODELIST);
        DeleteFromPriceList(listByPrice, prevP);
    }
}
void DeleteFromPriceList(List *list, LNode *prev)
{
    if(prev == NULL)
        DeleteFromBeginningOfList(list, PRICELIST);
    else if(prev->next == list->tail)
        DeleteFromEndOfList(list, PRICELIST);
    else
        DeleteFromInnerPlaceInList(prev, PRICELIST);
}

/* Add to Command List functions */
void AddToCList(CList *list, char* command)
{
    CLnode *cell = AllocateCLnode(command);
    if(list->head == NULL)
        AddToEmptyList(NULL, list, NULL, cell);
    else
        AddToEndOfList(NULL, NULL, list, cell);
}

/* delete from Command List functions */
void DeleteFromBeginningOfCList(CList *list)
{
    CLnode *cell = list->head;

    list->head = list->head->next;
    DeallocateCListcell(cell);
    if(list->head == NULL)
        list->tail = NULL;
}
void DeallocateCListcell(CLnode *cell)
{
    free(cell->command);
    free(cell);
}

/* printing functions */
void PrintCList(CList *list)
{
    CLnode *curr = list->head;
    while(curr)
    {
        printf("%d: %s\n",curr->commandNum, curr->command);
        curr = curr->next;
    }
}
void PrintShortHArray(char **array, CList *list)
{
    int i, cmd_ind = 0;
    if(list->head == NULL)
        cmd_ind = 1 ;
    else
        cmd_ind = ( list->tail->commandNum) + 1;

    for(i = 0; i < N ; i++)
    {
        printf("%d: %s\n", cmd_ind++, array[i]);
    }
}
void PrintData(Apt *apt) // printing the apartment details
{
    struct tm tm = *localtime(&apt->Database_entry_date);
    printf("Apt details:\n");
    printf("Code: %d\n", apt->code);
    printf("Address: %s\n", apt->address);
    printf("Number of rooms: %d\n", apt->num_of_rooms);
    printf("Price: %d\n", apt->price);
    printf("Entry date: %d.%d.%d\n", apt->day, apt->month, apt->year);
    printf("Database entry date: %d.%d.%d\n",tm.tm_mday ,tm.tm_mon + 1,tm.tm_year + 1900);
}

/* initializing Command list */
void InitializeClist(CList* Clst)
{
    Clst->head = Clst->tail = NULL;
}

/* Clear List functions */
void ClearList(List *list)
{
    while(list->head)
        DeleteFromBeginningOfList(list, CODELIST);
}
void ClearCList(CList *list)
{
    while(list->head)
        DeleteFromBeginningOfCList(list);
}
void ClearShortTermHistory(char *short_term_history[N])
{
    int i;
    for(i = 0; i < N; i++)
    {
        free(short_term_history[i]);
    }
}
void ClearDB(CList *history, char *short_term_history[N], List *lst, List *lstPrice)
{
    ClearCList(history);
    ClearShortTermHistory(short_term_history);
    ClearList(lst);
    DeleteFromBeginningOfList(lstPrice, PRICELIST);// the apt is already deallocated so only deallocating the node
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
void check_file (FILE *file)
{
    if(!file)
    {
        printf("error - open file to use has failed\n");
        exit(FILE_ERROR);
    }
}