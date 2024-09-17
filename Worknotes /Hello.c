#include "main.h"
extern int invalid_id_flag;

//function to extract each line from a file
int extract_data(Info *info,FILE *fptr)
{
    int i = 0;
    char ch;

    while(ch != EOF)
    {
        //reset index to 0
        i = 0;

        //extracting a character at a time
        ch = fgetc(fptr);

        //if ch is newline skip the iteration
        if(ch == '\n')
        {
            continue;
        }

        //start storing the characters in the variables until newline is reached
        while(ch != '\n' && ch != EOF)
        {
            info -> buf_str[i++] = ch;
            ch = fgetc(fptr);    
        }
        //padding null value at the end
        info -> buf_str[i] = '\0';
        //printf("%s\n", info->buf_str);

        //calling functions to group it the variables
        if(invalid_id_flag != 1)
        {
            group_identifiers(info -> buf_str);
        }
        else
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}
