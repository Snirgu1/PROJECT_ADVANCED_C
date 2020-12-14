#include "main_commands.h"

int main()
{
    List lst, lstPrice;
    InitializeList(&lst);
    InitializeList(&lstPrice);
    char* shortHistory[7];
    InitializeSHistory(shortHistory);
    CList history;
    //InitializeList(&history);
    char* temp;
    printf("Please enter one of the following commands:\nadd-apt, find-apt, buy-apt, delete-apt or exit\n");
    printf("For reconstruction commands, please enter:\n!!, !num, history, short_history or !num^str1^str2\n");

    temp = "add-apt \"Hasavyonim 23 Ramat Ono\" 2000000 4 01 01 21";
    //recordHistory(temp);
    checkCommand(temp, &lst, &lstPrice);

    temp = "add-apt \"Rothschild 67 Rishon Le Zion\" 1700000 3 03 10 20";
    checkCommand(temp, &lst, &lstPrice);

    temp = "add-apt \"Ben Gurion 25 Herzliya\" 2200000 5 01 08 20";
    checkCommand(temp, &lst, &lstPrice);

    temp = "add-apt \"Gordon 85 Holon\" 1500000 3 15 06 21";
    checkCommand(temp, &lst, &lstPrice);

//    for(curr = lst.head ; curr != NULL ; curr=  curr->next )
//    {
//        printf("%d\n",curr->apartment->price);
//    }
    PrintList(&lst);
    printf("\n");
    PrintList(&lstPrice);
    printf("\n\n");

    temp = "find-apt -MinNumRooms 3 -MaxNumRooms 5 -MaxPrice 1750000 -s";
    checkCommand(temp, &lst, &lstPrice);
    temp = "buy 2";
    checkCommand(temp, &lst, &lstPrice);

    PrintList(&lst);
    printf("\n");
    PrintList(&lstPrice);
    ClearList(&lst);
    DeleteFromBeginningOfPList(&lstPrice); // the apt is already deallocated so only deallocating the node

    return 0;
}


