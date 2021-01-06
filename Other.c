#include "Other.h"
#include "DataBase.h"


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
        return;
    }
}
