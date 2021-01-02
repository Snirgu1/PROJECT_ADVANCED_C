#include "main_commands.h"

int main( )
{
    List lst, lstPrice;
    CList history;
    char *short_term_history[N];

    InitializeDataBase(&lst,&lstPrice,short_term_history,&history);          /* initialize required Lists and array */
    ReadBinFile("DB_Binfile.bin",&lst,&lstPrice);                      /* reading Bin file and set info to DB  */
//    TestProject(&lst,&lstPrice,short_term_history,&history);                  /* Project tests */
    getHistoryFromFile(short_term_history,&history);
    TestProjectAfterFiles(&lst,&lstPrice,short_term_history,&history);       /* Project tests part two - after we got files filled  */
    WriteHistoryToFile(&history,short_term_history);                         /* writing history to txt file */
    WriteDatabaseToBinFile(&lst);                                            /* writing apartments DB to Bin file */
    ClearCList(&history);
    ClearList(&lst);
    DeleteFromBeginningOfPList(&lstPrice); // the apt is already deallocated so only deallocating the node
    return 0;
}

