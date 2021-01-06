#include "main_commands.h"

int main( )
{
    List lst,lstPrice;
    CList history;
    char *short_term_history[N];
    char ans;

    InitializeDataBase(&lst,&lstPrice,short_term_history,&history);                /* Initialize required Lists and array */
    ReadBinFile("DB_Binfile.bin",&lst,&lstPrice);                           /* Read bin file and set info from it to DB */
    getHistoryFromFile(short_term_history,&history);                              /* Read txt file and set project History from it */

    printf("\nFIRST TIME RUNING PROJECT ?\nPRESS Y / N  FOR ANSWER ?\n");
    scanf("%c",&ans);
    if(ans == 'Y' || ans == 'y' )
        Test1(&lst,&lstPrice,short_term_history,&history);                    /* Test part one - first run */
    else
        Test2(&lst,&lstPrice,short_term_history,&history);                    /* Test part two - after first run */

    printf("Press any key to continue...\n");
    scanf(" %c",&ans);
    return 0;
}
