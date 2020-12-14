#include "main_commands.h"
/* updated snir 10101*/
int main()
{
    printf("Please enter ....\n");
    List lst; lst.head = lst.tail = NULL ;
    LNode*n1,*n2,*n3,*n4,*curr;
    char* temp;

    temp = "add-apt \"Hasavyonim 23 Ramat Ono\" 2000000 4 01 01 21";
    Apt* apt1 = CreApt(temp);
    apt1->code = 1;
    n1 = CreateLnode(apt1);
    lst.head = n1;

    temp = "add-apt \"Rothschild 67 Rishon Le Zion\" 1700000 3 03 10 20";
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

    lst.tail = n4;
//    for(curr = lst.head ; curr != NULL ; curr=  curr->next )
//    {
//        printf("%d\n",curr->apartment->price);
/*bla bla bla */
//    }
    temp ="find-apt -MinNumRooms 3 -MaxNumRooms 5 -MaxPrice 1750000 -s";
    find(&lst,temp);
    return 0;
}


