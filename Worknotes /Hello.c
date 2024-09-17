#include "main.h"

int main(int argc, char* argv[])
{
    //checking if file name is passed and nothing more is passed via command line
    if(argc < 2 || argc > 2)
    {
        printf("ERROR: Incorrect way of passing CLA.\n");
        printf("Usage: ./a.out <.cpp file_name>\n");
        return FAILURE;
    }
    //if filename is passed via CLA
    else
    {
        //opening file in read mode
        FILE *fptr = fopen(argv[1], "r");

        //if file not exist
        if(fptr == NULL)
        {
            printf("ERROR: file %s not exist, please pass correct file name.\n", argv[1]);
            return FAILURE;
        }

        //function to check if file has content in it
        if(file_Validation(argv[1], fptr) == SUCCESS)
        {
            //creating structure variable
            Info info;
            extract_data(&info, fptr);

            printf("\nTokens generated.\n");
            fclose(fptr);
        }
        else
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}
