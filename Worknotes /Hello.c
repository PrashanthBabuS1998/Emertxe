#include "main.h"

int file_Validation(char* str, FILE *fptr)
{
    //seek to end of file
    fseek(fptr, 0, SEEK_END);

    //if ftell is 0, which means file is empty
    if(ftell == 0)
    {
        printf("File is empty.\n");
        return FAILURE;
    }
    else
    {
        fseek(fptr, 0, SEEK_SET);
        return SUCCESS;
    }
}
