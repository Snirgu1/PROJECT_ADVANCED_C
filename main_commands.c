#include "main_commands.h"

 void checkCommand(char* line, List* lstByCode, List* lstByPrice)
 {
    if(line[0] == 'a')
        addApt(line, lstByCode, lstByPrice);
    else if(line[0] == 'f')
        find(lstByCode, line); // need to check which list to send
        /*
    else if(line[0] == 'b')
        buyApt(line);
    else if(line[0] == 'd')
        deleteApt(line);
    else
        exitProg;
         */
 }

 /* ========================================== FIND AND DELETE FUNCTIONS ==========================================*/

 void find(List* apartment, char* line)
 {
     line = line + 9;
     /* variables */
     char* findByCommands[NUM_OF_FIND_COMMANDS] = {"MinNumRooms","MaxNumRooms","MaxPrice","MinPrice","Date","Enter","s","sr"};
     char delim[NUM_OF_DELIM] = {' ','-'};
     char* temp = strdup(line);
     char* token;
     int minR,maxR,maxP,minP,lastXdays_enter,order;
     order = minR = maxP = lastXdays_enter = INITIAL;
     token = strtok(temp,delim);

     while(token)
     {
         if(!strcmp(token,findByCommands[0])){            /* find by MinNumRooms */
             token = strtok(NULL,delim);
             minR = atoi(token);
             printf("min room is : %d\n",minR);
         }
         else if(!strcmp(token,findByCommands[1])){        /* find by MaxNumRooms */
             token = strtok(NULL,delim);
             maxR = atoi(token);
             printf("max room is : %d\n",maxR);
         }
         else if(!strcmp(token,findByCommands[2])){        /* find by MaxPrice */
             token = strtok(NULL,delim);
             maxP = atoi(token);
             printf("max price is : %d\n",maxP);
         }
         else if(!strcmp(token,findByCommands[3])){        /* find by MinPrice */
             token = strtok(NULL,delim);
             minP = atoi(token);
             printf("min price is : %d\n",minP);
         }
         else if(!strcmp(token,findByCommands[4])){        /* find by Entry date in to apartment  */
             token = strtok(NULL,delim);
             printf("entry date is : %s\n",token);
         }
         else if(!strcmp(token,findByCommands[5])){        /* find by database entry date */
             token = strtok(NULL,delim);
             lastXdays_enter = atoi(token);
             printf("Please show the apt's enterd in the last %d days : \n",lastXdays_enter);
         }
         else if(strcmp(token,findByCommands[6]) == 0){      /* find all apartments - low to high*/
             order = INCREASE ;
             printf("s - sort from low to high \n");
         }
         else if(strcmp(token,findByCommands[7]) == 0){      /* find all apartments - high to low*/
             order = DECREASE ;
             printf("sr - sort from high to low \n");
         }
         token = strtok(NULL,delim);
     }
 }
 void printApt(Apt* apt)
{
    printf("--- apt code --- : %d\n",apt->code);
    printf("address : %s\n",apt->address);
    printf("price : %d\n",apt->price);
    printf("num_of_rooms : %d\n",apt->num_of_rooms);
    printf("entry date is : %d/%d/%d \n\n",apt->day,apt->month,apt->year);
}

/* ========================================== ADD AND BUY FUNCTIONS ==========================================*/
/*
LNode* CreateLnode(Apt* apt)
{
    LNode* res = (LNode*)malloc(sizeof(LNode));
    if(!res)
        exit(MEM_ALLOC_ERR);
    res->prev = NULL;
    res->next = NULL;
    res->apartment = apt;
    return res;
}
*/
/* TEST ONLY _ NOT EFFICIENT !!! */
Apt* CreApt(char* line)
{
    static int code = 1;
    Apt* res = (Apt*)malloc(sizeof(Apt));
    int i = 9, wi = 0 ;
    char ch = line[i++];
    char* address = (char*)malloc(sizeof(char)*100);
    char* temp_price = (char*)malloc(sizeof(char)*100);
    char* temp = (char*)malloc(sizeof(char)*100);

    /* get address */
    while( ch != '\"')
    {
        address[wi++] = ch;
        ch = line[i++];
    }
    address[wi] = '\0';
    res->address = address ;
    /* get price */
    int pwi = 0 ;
    ch = line[++i];
    while( ch != ' ')
    {
        ch = line[i++];
        temp_price[pwi++] = ch;
    }
    res->price = atoi(temp_price);

    /* get number of rooms (MAX 9) - need to fix  */
    ch = line[i++];
    temp[0] = ch;
    ch = line[i++];
    temp[1] = ch;
    res->num_of_rooms = atoi(temp);
    /* get day */
    ch = line[i++] ;
    temp[0] = ch ;
    ch = line[i] ;
    temp[1] = ch ;
    res->day= atoi(temp);
    /* get month */
    i+= 2 ;
    ch = line[i++];
    temp[0] = ch;
    ch = line[i];
    temp[1] = ch;
    res->month= atoi(temp);
    /* get year*/
    i+= 2 ;
    ch = line[i++];
    temp[0] = ch;
    ch = line[i];
    temp[1] = ch;
    res->year= atoi(temp);

    res->code = code;
    code++;
    res->Database_entry_date = 0;

    return res;
}

void addApt(char* line, List* lstByCode, List* lstByPrice)
{
    Apt *apt1 = CreApt(line);
    AddToListByCode(lstByCode, apt1);
    AddToListByPrice(lstByPrice, apt1);
}
