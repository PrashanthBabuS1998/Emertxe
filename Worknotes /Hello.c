#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct str_Info
{
    char buf_str[20];
}Info;

int file_Validation(char* str, FILE *fptr);
int extract_data(Info *info,FILE *fptr);
int group_identifiers(char* str);

#endif
