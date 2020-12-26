#include "FilesOp.h"

void WriteHistoryToFile(CList* lst_history, char* shortHistory[])
{
    FILE *f = fopen("HistoryDoc.txt","w");
    if(!f)
    {
        fprintf(stderr,"open txt file \"HistoryDoc.txt\" failed\n");
        exit(FILE_ERROR);
    }
    if(lst_history->head == NULL )    /* if database B (Cmd LIST) is empty , write only database A (shortTerm) to file */
    {
        WriteCmdArrToFile(f,shortHistory,1);
    }
    else                            /* there is more than 7 commands, write the arr and the Clist */
    {
        WriteCListToFile(f,lst_history);
        WriteCmdArrToFile(f,shortHistory,lst_history->tail->commandNum + 1);
    }
    fclose(f);
}
void WriteCListToFile(FILE* f,CList *lst_history)
{
    CLnode *curr = lst_history->head ;
    while(curr != NULL)
    {
        fprintf(f,"%d: %s\n",curr->commandNum, curr->command);
        curr = curr->next;
    }
}
void WriteCmdArrToFile(FILE* f,char* shortHistory[],int start_ind)
{
    int  i = 0 ;
    int curr_cmd_ind = start_ind ;
    while( shortHistory[i] != NULL  && i < 7)
    {
        fprintf(f,"%d: %s\n",curr_cmd_ind,shortHistory[i]);
        curr_cmd_ind++;
        i++;
    }
}

/* get history from txt file in start of project */
void getHistoryFromFile(char* short_term_history[] ,CList* history)
{
    int i = 0 ,j = 0 ,num = 0;
    int offset  ;
    char* temp ,tokTemp;
    char* token;

    FILE *f = fopen("HistoryDoc.txt","r");
    if(!f)
    {
        fprintf(stderr,"using file error, exiting..\n");
        exit(FILE_ERROR);
    }

    while( !feof(f) )
    {
        temp = get_line(f);
    }
    fclose(f);
}

/* get line from txt file */
char* get_line(FILE* f)
{
    char ch = ' ';
    int l_size = 0, p_size = 2;
    char* line = (char*)malloc(sizeof(char)*p_size);
    while( ch != '\n')
    {
        ch = (char)fgetc(f);
        line[l_size] = ch;
        l_size++;
        if(l_size == p_size)
        {
            p_size *= 2;
            line = (char*)realloc(line,p_size);
        }
    }
    line = (char*)realloc(line,l_size+1);
    line[l_size] = '\0';
    return line;
}

/* writing apartments DB to bin file  */
void WriteDatabaseToBinFile(List* lst)
{
    LNode *curr ;
    FILE * f = fopen("DB_Binfile.bin","wb");
    if(!f)
    {
        fprintf(stderr,"error openeing file, exiting...\n");
        exit(FILE_ERROR);
    }


    int num_of_apts = getSize(lst);

    fwrite(&num_of_apts, sizeof(int),1, f);

    for( curr = lst->head ;  curr != NULL ; curr = curr->next )
    {
        WriteApt(f,curr);
    }
    fclose(f);
}

/* how many apartments in DB at the moment*/
int getSize(List *lst)
{
    int i = 0 ;
    LNode *curr = lst->head;
    while(curr)
    {
        if( curr->apartment != NULL )
            i++;
        curr = curr->next ;
    }
    return i;
}

/* writing apartment's details to BinFile */
void WriteApt(FILE* f,LNode* curr)
{
    BYTE *RoomsAndDate;
    Sint len = (Sint)strlen(curr->apartment->address);
    fwrite(&curr->apartment->code,sizeof(Sint),1,f);
    fwrite(&len,sizeof(Sint),1,f);
    fwrite(curr->apartment->address,sizeof(char),len,f);
    fwrite(&curr->apartment->price,sizeof(int),1,f);
    fwrite(&curr->apartment->Database_entry_date,sizeof(time_t),1,f);
    RoomsAndDate = CollectRoomsAndDate(curr->apartment);
    fwrite(RoomsAndDate,sizeof(BYTE),3,f);
    free(RoomsAndDate);
}

/* collect num of rooms and date - 3 Bytes total */
BYTE* CollectRoomsAndDate(Apt* apt)
{
    BYTE* res = (BYTE*)check_malloc(sizeof (BYTE)*3);
    BYTE CurrByte = 0;
    Sint numOfRooms = apt->num_of_rooms;
    CurrByte = ExtractRooms(numOfRooms);        /* collecting first 4 bits */
    ExtractDate(res,&CurrByte,apt);
    return res;
}

/* collect the num of rooms (4 bits total) */
BYTE ExtractRooms(Sint numOfRooms)
{
    BYTE Mask = 0x0F; /* 00001111*/
    BYTE res ;
    res = Mask & numOfRooms ;
    res <<= 4;
    return res;
}

/*  collect apt entry date */
void ExtractDate(BYTE* res,BYTE* currByte,Apt* apt)
{
    CollectDay(res,currByte,apt->year);
    CollectMonth(currByte,apt->month);
    CollectYear(res,currByte,apt->year);
}

/* collect apt entry day of date */
void CollectDay(BYTE* res, BYTE* currByte,Sint day)
{
    int wi = 7,ri = 0 ;                /* wi -bit location to write in currByte,  ri - bit location to read from day */
    *currByte |= (day >> 1) ;
    res[0] = *currByte ;
    *currByte = 0 ;
    if( isBitISet(day,ri) == TRUE )
        setBit(currByte,wi);
}

/* collect apt entry month of date */
void CollectMonth(BYTE* currByte,Sint month)
{
    int ri = 3, wi = 6;     /* wi -bit location to write in currByte,  ri - bit location to read from month */
    while(ri >= 0)
    {
        if( isBitISet(month,ri) == TRUE )
            setBit(currByte,wi);
        ri--; wi--;
    }
}

/* collect apt entry year of date */
void CollectYear(BYTE* res,BYTE* currByte,Sint year)
{
    int ri = 6 , wi = 2;        /* wi -bit location to write in currByte,  ri - bit location to read from year */
    BYTE MASK = 0x0F;
    while(wi >= 0 )
    {
        if( isBitISet(year,ri) == TRUE )
            setBit(currByte,wi);
        wi--; ri--;
    }
    res[1] = *currByte;
    *currByte = 0 ;
    MASK = year & MASK ;
    *currByte = MASK << 4 ;
    res[2] = *currByte;
}

/* set Bit I */
void setBit(BYTE* currByte,int i)
{
    BYTE mask = 1 << i;
    *currByte |= mask;
}

/* check if Bit I set */
BOOL isBitISet(BYTE ch, int i)
{
    BYTE mask = 1 << i;
    if( (mask & ch) == 0)
        return FALSE;
    else
        return TRUE;
}

void readBinFile(char* fname) /* TEST ONLY - NOT NEEDED*/
{
    FILE* f = fopen(fname, "rb");
    int num_of_apts = 0,  price ,i = 0 ;
    Sint code, len ,day ,month,year , num_of_rooms ;
    time_t EntryToDB ;
    char* address  = NULL ;
    printf("\nSTART READING FROM BIN FILE\n");
    fread(&num_of_apts,sizeof(int),1,f);
    printf("Num of apartments :%d\n\n", num_of_apts);

    while( i  < num_of_apts )
    {
        fread(&code,sizeof(Sint),1,f);
        printf("code : %d\n", code);

        fread(&len,sizeof(Sint),1,f);
        printf("len : %d\n", len);

        address =(char*)check_malloc(sizeof(char)*len);
        fread(address,sizeof(BYTE),len,f);
        address[len] = '\0';
        printf("address : %s\n", address);

        fread(&price,sizeof(int),1,f);
        printf("price : %d\n", price);

        fread(&EntryToDB,sizeof(time_t),1,f);
        printf("EntryToDB : %ld\n\n", EntryToDB);

        fseek(f,3,SEEK_CUR);
        i++;
    }
}
/* day -  00000000 000XXXXX */
/* month -  00000000 0000XXXX */
/* year -  00000000 0XXXXXXX */
