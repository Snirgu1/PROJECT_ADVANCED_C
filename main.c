#include "main_commands.h"
int main()
{
    List lst, lstPrice;
    InitializeList(&lst);
    InitializeList(&lstPrice);

    char *short_term_history[N];
    InitializeSHistory(short_term_history);
    CList history;
    history.head = history.tail = NULL;


    char* temp;
    printf("Please enter one of the following commands:\nadd-apt, find-apt, buy-apt, delete-apt or exit\n");
    printf("For reconstruction commands, please enter:\n!!, !num, history, short_history or !num^str1^str2\n");


    printf("Please enter one of the following commands:\nadd-apt, find-apt, buy-apt, delete-apt or exit\n");
    printf("For reconstruction commands, please enter:\n!!, !num, history, short_history or !num^str1^str2\n");

    temp = "add-apt \"Hasavyonim 23 Ramat Ono\" 2000000 4 01 01 21";

    checkCommand(temp, &lst, &lstPrice);

    temp = "add-apt \"Rothschild 67 Rishon Le Zion\" 1700000 3 03 10 20";
    checkCommand(temp, &lst, &lstPrice);

    temp = "add-apt \"Ben Gurion 25 Herzliya\" 2200000 5 01 08 20";
    checkCommand(temp, &lst, &lstPrice);

    temp = "add-apt \"Gordon 85 Holon\" 1500000 3 15 06 21";
    checkCommand(temp, &lst, &lstPrice);

    Apt* apt1 = CreApt(temp);
    apt1->code = 1;
    n1 = CreateLnode(apt1);
    lst.head = n1;


    temp = "add-apt \"Dizengoff 180 Tel Aviv\" 2000000 4 28 09 20";
    //temp = "add-apt \"Hasavyonim 23 Ramat Ono\" 2000000 4 01 01 21";
    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);
    temp = "add-apt \"Rothschild 67 Rishon Le Zion\" 1700000 3 03 10 20";

    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);
    temp = "add-apt \"Ben Gurion 25 Herzliya\" 2200000 5 01 08 20";
    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);
    temp = "add-apt \"Gordon 85 Holon\" 1500000 3 15 06 21";
    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);
    temp = "find-apt -MinNumRooms 3 -MaxNumRooms 5 -MaxPrice 1750000 -s";
    //temp = "find-apt -Date 01102022 -MinNumRooms 3 -MaxNumRooms 5 -MaxPrice 1750000 -sr";
    printf("\n%s\n", temp);
    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);
    temp = "find-apt -MinNumRooms 4 -sr";
    printf("\n%s\n", temp);
    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);
    temp = "find-apt -MaxNumRooms 5 -s";
    printf("\n%s\n", temp);
    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);
    temp = "buy-apt 2";
    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);
   //temp = "delete-apt -Enter 9";
    temp = "history";
    printf("\n%s\n", temp);
    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);
    temp = "!5^5^6";
    printf("\n%s\n", temp);
    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);
    temp = "!3^Ben Gurion^David Ben Gurion";
    printf("\n%s\n", temp);
    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);
    temp = "short_history";
    printf("\n%s\n", temp);
    checkCommand(temp, &lst, &lstPrice, short_term_history, &history);
    temp = "!6";
    printf("\n%s\n", temp);
    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);
    temp = "!!";
    printf("\n%s\n", temp);
    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);
    temp = "find-apt -Date 01102020 -sr";
    printf("\n%s\n", temp);
    checkCommand(temp, &lst, &lstPrice,short_term_history, &history);

    ClearCList(&history);
    ClearList(&lst);
    DeleteFromBeginningOfPList(&lstPrice); // the apt is already deallocated so only deallocating the node

    Apt* Apt2 = CreApt(temp);
    Apt2->code = 2;
    n2 = CreateLnode(Apt2);
    n1->next = n2 ;


    n2->prev = n1 ;

    temp = "add-apt \"Ben Gurion 25 Herzliya\" 2200000 5 01 08 20";
    Apt* apt3 = CreApt(temp);
    apt3->code = 3;
    n3 = CreateLnode(apt3);
    n2->next = n3 ;
    n3->prev = n2 ;

    temp = "add-apt \"Gordon 85 Holon\" 1500000 3 15 06 21";
    Apt* apt4 = CreApt(temp);
    apt4->code = 4;
    n4 = CreateLnode(apt4);
    n3->next = n4 ;
    n4->prev = n3 ;

    temp = "find-apt -MinNumRooms 3 -MaxNumRooms 5 -MaxPrice 1750000 -s";
    find(&lst,temp);

    ClearList(&lst);
    DeleteFromBeginningOfPList(&lstPrice);

    return 0;
}
