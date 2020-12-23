#include "main_commands.h"

int main() {

    List lst, lstPrice;
    CList history;
    char *short_term_history[N];

    InitializeDataBase(&lst,&lstPrice,short_term_history,&history); /* initialize required Lists and array */
    TestProject(&lst,&lstPrice,short_term_history,&history);      /* Project tests */
    WriteHistoryToFile(&history,short_term_history);            /* writing history to txt file */
    ClearCList(&history);
    ClearList(&lst);
    DeleteFromBeginningOfPList(&lstPrice); // the apt is already deallocated so only deallocating the node
    return 0;
}

