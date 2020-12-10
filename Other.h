#ifndef PROJECT_ADVANCED_C_OTHER_H
#define PROJECT_ADVANCED_C_OTHER_H
#include "DataBase.h"

/* get line function */
char* get_line()
{
    char ch = ' ' ;
    int l_size = 0, p_size = 2;
    char* line = (char*)malloc(sizeof(char)*p_size);
    while( ch != '\n')
    {
        scanf("%c",&ch);
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
void AllocError();

#endif
