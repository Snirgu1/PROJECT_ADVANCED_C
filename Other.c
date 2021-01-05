//
// Created by idanm on 12/19/2020.
//

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
        fprintf(stderr,"error openeing file, exiting...\n");
        exit(FILE_ERROR);
    }
}

char *inputString(FILE* fp, size_t size) /* func from stackoverflow NEVER used */
{
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof (*str) * size);
    if(!str)
        return str;
    while(EOF!=(ch = fgetc(fp)) && ch != '\n')
    {
        str[len++] = ch;
        if(len == size)
        {
            str = realloc(str, sizeof (*str) * (size+=16));
            if(!str)
                return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(*str)*len);
}
