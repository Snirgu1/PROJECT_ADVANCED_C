#include "main_commands.h"
#include "Reconstraction.h"


void Test1(List* lst,List* lstPrice,char* short_term_history[] ,CList *history)
{
    printf("Please enter one of the following commands:\nadd-apt, find-apt, buy-apt, delete-apt or exit\n");
    printf("For reconstruction commands, please enter:\n!!, !num, history, short_history or !num^str1^str2\n");
    char* temp = NULL;

    temp = "add-apt \"Dizengoff 180 Tel Aviv\" 2000000 4 28 09 20";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "add-apt \"Rothschild 67 Rishon Le Zion\" 1700000 3 03 10 20";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "add-apt \"Ben Gurion 25 Herzliya\" 2200000 5 01 08 20";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "add-apt \"Gordon 85 Holon\" 1500000 3 15 06 21";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "find-apt -MinNumRooms 3 -MaxNumRooms 5 -MaxPrice 1750000 -s";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "find-apt -MinNumRooms 4 -sr";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "find-apt -MaxNumRooms 5 -s";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "buy-apt 2";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "history";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "!5^5^6";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "!3^Ben Gurion^David Ben Gurion";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "short_history";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "!6";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "!!";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "find-apt -Date 01102020 -sr";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
    temp = "exit";
    printf(">> %s\n",temp);
    checkCommand(temp, lst, lstPrice,short_term_history, history);
}

void Test2(List* lst,List* lstPrice,char* short_term_history[] ,CList *history)
{
    printf("Please enter one of the following commands:\nadd-apt, find-apt, buy-apt, delete-apt or exit\n");
    printf("For reconstruction commands, please enter:\n!!, !num, history, short_history or !num^str1^str2\n");
    char* temp = NULL;
    temp = "history";
    printf(">> %s\n",temp);
    checkCommand(temp,lst,lstPrice,short_term_history,history);
    temp = "add-apt \"Moshe Dayan 4 Eilat\" 1300000 4 27 08 20";
    printf(">> %s\n",temp);
    checkCommand(temp,lst,lstPrice,short_term_history,history);
    temp = "find-apt -MaxPrice 2250000 -sr";
    printf(">> %s\n",temp);
    checkCommand(temp,lst,lstPrice,short_term_history,history);
    temp = "short_history";
    printf(">> %s\n",temp);
    checkCommand(temp,lst,lstPrice,short_term_history,history);
    temp = "history";
    printf(">> %s\n",temp);
    checkCommand(temp,lst,lstPrice,short_term_history,history);
    temp = "exit";
    printf(">> %s\n",temp);
    checkCommand(temp,lst,lstPrice,short_term_history,history);
}

/* comparing the first letter of the line to decide which command to active */
void checkCommand(char* line, List* lstByCode, List* lstByPrice, char** shortHistory, CList* history) // checking first letter of the line to decide which command
{
    if(line[0] == 'a') {
        addApt(line + 9, lstByCode, lstByPrice);
        recordHistory(line, shortHistory, history);
    }
    else if(line[0] == 'f') {
        find(lstByPrice, lstByCode, line); // need to check which list to send
        recordHistory(line, shortHistory, history);
    }
    else if(line[0] == 'b') {
        buyApt(line, lstByCode, lstByPrice);
        recordHistory(line, shortHistory, history);
    }
    else if(line[0] == 'd') {
        deleteApt(line, lstByPrice, lstByCode);
        recordHistory(line, shortHistory, history);
    }
    else if(line[0] == 'e')
    {
        exitProg(history,shortHistory,lstByCode,lstByPrice);
    }
    else if(line[0] == 'h')
    {
        PrintCList(history);
        PrintShortHArray(shortHistory, history);
    }
    else if(line[0] == 's')
        PrintShortHArray(shortHistory, history);
    else
        checkReconstraction(line+1, lstByCode, lstByPrice,shortHistory, history);
}

/* exit the program */
void exitProg(CList *history,char** shortHistory,List* lstByCode,List* lstByPrice)
{
    WriteHistoryToFile(history,shortHistory);                                         /* writing history to txt file */
    WriteDatabaseToBinFile(lstByCode);                                                /* writing apartments DB to Bin file */
    ClearDB(history, shortHistory,lstByCode,lstByPrice);
    printf("Good Bye!\n");
}

/* ========================================== FIND AND DELETE FUNCTIONS ==========================================*/

BOOL isEarlier(short int apt_year,short int apt_month ,short int apt_day, Find_keys* keys)
{
    if(apt_year < keys->year)                /* in case of earlier year */
        return TRUE;
    else if( apt_year > keys->year)          /*  in case of later year */
        return FALSE;
    else                                     /* in case of equal year */
    {
        if(apt_month < keys->month )         /* in case of equal year and earlier month  */
            return TRUE;
        else if (apt_month > keys->month )   /* in case of equal year and bigger month  */
            return FALSE;
        else                                 /* in case of equal year and month */
        {
            if(apt_day <= keys->day)         /* in case of earlier day and equal year and month */
                return TRUE;
            else return FALSE;
        }
    }
}

BOOL checkDataBaseEntryDate(time_t Database_entry_date, short int days_ago)
{
    time_t current_time_sec;
    current_time_sec = time(NULL);
    int current_time_days = (int)(current_time_sec/3600)/(24);               /* num of days since 1.1.1970 to current time*/
    int dataBase_entry_date_days = (int)(Database_entry_date/3600)/(24);     /* num of days since 1.1.1970 to Database entry date */
    return (current_time_days - dataBase_entry_date_days <= days_ago) ? TRUE : FALSE;
}

BOOL checkAptMatch(Apt* apt, Find_keys* keys)
{

    if( (apt->price >= keys->minP) && (apt->price <= keys->maxP) ) {          /* check price */
        if( (apt->num_of_rooms >= keys->minR) && (apt->num_of_rooms <= keys->maxR) )    /* check room number */
        {
            if(keys->year != INITIAL)
            {
                if (isEarlier(apt->year,apt->month,apt->day,keys) == TRUE )                     /* check enter to apt date */
                {
                    if(checkDataBaseEntryDate(apt->Database_entry_date,keys->lastXdays_enter) == TRUE)  /* check Database Entry date*/
                        return TRUE;
                }
            }
            else
            {
                if (checkDataBaseEntryDate(apt->Database_entry_date, keys->lastXdays_enter) == TRUE)  /* check Database Entry date*/
                    return TRUE;
            }
        }
    }
    return FALSE ;
}

BOOL InTimeRange(Apt* apt,int days_ago)
{
    time_t current = time(&current);
    int seconds_in_day = (3600*24);
    int Total_seconds_InDaysRange = days_ago*(seconds_in_day);
    double seconds_diff = difftime(current,apt->Database_entry_date);
    if ( seconds_diff <= Total_seconds_InDaysRange  )
        return TRUE;
    else
        return FALSE;
}

void collectDate(const char* date_str,Find_keys* keys)
{
    char temp[N];
    int i = 0 ;
    temp[0] = date_str[i++];
    temp[1] = date_str[i++];
    keys->day = atoi(temp) ;
    temp[0] = date_str[i++];
    temp[1] = date_str[i++];
    keys->month = atoi(temp);
    i += 2;
    temp[0] = date_str[i++];
    temp[1] = date_str[i];
    keys->year = atoi(temp);
}

void collectKeysSearch(char* line,Find_keys *keys)
{
    line = line + 9;
    char* temp = strdup(line);
    char delim[NUM_OF_DELIM] = {' ','-'};
    char* findByCommands[NUM_OF_FIND_COMMANDS] = {"MinNumRooms","MaxNumRooms","MaxPrice","MinPrice","Date","Enter","s","sr"};
    char* token = NULL;

    keys->lastXdays_enter = keys -> minP = keys->minR  = keys->order = INITIAL;
    keys->year = keys->month = keys->day = INITIAL;
    keys->maxR = MAXROOMS ;
    keys->maxP = (int)MAX_INIT ; /* need to fix the MAX INIT val */

    token = strtok(temp,delim);
    while(token)
    {
        if(strcmp(token,findByCommands[0]) == 0){            /* find by MinNumRooms */
            token = strtok(NULL,delim);
            keys->minR  = atoi(token);
        }
        else if(strcmp(token,findByCommands[1]) == 0){        /* find by MaxNumRooms */
            token = strtok(NULL,delim);
            keys->maxR = atoi(token);
        }
        else if(strcmp(token,findByCommands[2]) == 0){        /* find by MaxPrice */
            token = strtok(NULL,delim);
            keys->maxP = atoi(token);
        }
        else if(strcmp(token,findByCommands[3]) == 0){        /* find by MinPrice */
            token = strtok(NULL,delim);
            keys->minP = atoi(token);
        }
        else if(strcmp(token,findByCommands[4]) == 0){        /* find by Entry date in to apartment  */
            token = strtok(NULL,delim);
            collectDate(token,keys);
        }
        else if(strcmp(token,findByCommands[5]) == 0){        /* find by database entry date */
            token = strtok(NULL,delim);
            keys->lastXdays_enter = atoi(token);
        }
        else if(strcmp(token,findByCommands[6]) == 0){      /* find all apartments - low to high*/
            keys->order = INCREASE ;
        }
        else if(strcmp(token,findByCommands[7]) == 0){      /* find all apartments - high to low*/
            keys->order = DECREASE ;
        }
        token = strtok(NULL,delim);
    }
    free(temp);
}

void findAndPrint(List* price_lst,List* code_lst,Find_keys* keys)
{
    LNode* curr;
    if( keys->order == DECREASE)
    {
        for ( curr = price_lst->tail ; curr != NULL ; curr = curr->prev )
        {
            if(checkAptMatch(curr->apartment, keys) == TRUE)
            {
                PrintData(curr->apartment);
            }
        }
    }
    else
    {
        for( curr = price_lst->head ; curr != NULL ; curr = curr->next )
        {
            if ( checkAptMatch(curr->apartment,keys) == TRUE )
            {
                PrintData(curr->apartment);
            }
        }
    }
}

void find(List* price_lst, List* code_lst, char* line)
{
    Find_keys keys;    /* struct to represent the required info to find the required apartments */
    collectKeysSearch(line, &keys);  /* collect search details from command */
    findAndPrint(price_lst,code_lst,&keys);
}

int collectDaysRange(char* line)
{
    return atoi(line+18);
}

void deleteApt(char *line  ,List *lstByPrice, List *lstByCode)
{
    int days_ago = collectDaysRange(line);
    LNode *curr = lstByCode->tail;
    if(!curr)
        return;
    while(curr != NULL)
    {
        if(InTimeRange(curr->apartment,days_ago))
        {
            DeleteFromList(lstByCode, lstByPrice, curr->apartment->code);
            curr = lstByCode->tail;
        }
        else curr = curr->prev;
    }
}

/* ========================================== ADD AND BUY FUNCTIONS ==========================================*/

/* creates new apartment and adding it to both lists */
void addApt(char* line, List* lstByCode, List* lstByPrice)
{
    int currCode = 0;
    if(lstByCode->tail != NULL)
        currCode = lstByCode->tail->apartment->code;
    Apt *apt1 = getAptParameters(line, currCode);
    if(lstByCode->head == NULL)
        AddToEmptyList(lstByCode, AllocateLNode(apt1));
    else
        AddToEndOfList(lstByCode, AllocateLNode(apt1));
    AddToListByPrice(lstByPrice, apt1); // adding the apartment to the list sorted by price
}

void buyApt(char* line, List* lstByCode, List* lstByPrice)
{
    int code = atoi(line+8);
    DeleteFromList(lstByCode, lstByPrice, code);
}