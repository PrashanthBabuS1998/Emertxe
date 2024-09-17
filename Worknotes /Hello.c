#include "main.h"

static char kw_data[][10] = {"const", "volatile", "extern", "auto", "register", "static", "signed",
 "unsigned", "short", "long", "double", "char", "int", "float", "struct", "class", "union", "enum",
  "void", "typedef"};

static char kw_nondata[][10] = {"goto", "return", "continue", "break", "if", "else", "for", "while", 
"do", "switch", "case", "default", "sizeof"};

static char operators[] = {'/', '%', '+', '-', '*', '=', '<', '>', '~', '&', ',', '!', '^', '|'};

static char symbols[] = {'(', ')', '{', '}', '[', ']', ':', ';'};

int comment_flag = 0;
int keyword_flag = 0;
int invalid_id_flag;

//function to check if character is symbol/operator or not 
int is_symbol_or_operator(char ch)
{
        int j = 0;
        for(j = 0; j < sizeof(symbols) / sizeof(symbols[0]); j++)
        {
            if(ch == symbols[j])
            {
                return SUCCESS;
            }
        }

        for(j = 0; j < sizeof(operators) / sizeof(operators[0]); j++)
        {
            if(ch == operators[j])
            {
                return SUCCESS;
            }
        }
        return FAILURE;
}


int group_identifiers(char* str)
{
    //printf("%ld\n", sizeof(kw_nondata));
    //printf("str = %s\n", str);
    int i = 0;
    int j = 0;
    int k = 0;
    keyword_flag = 0;
    invalid_id_flag = 0;
    char ch;
    char buffer_str[20];

    while(str[i] != '\0')
    {
        //printf("str1 = %c str2 = %c\n", str[i], str[i+1]);
        ch = str[i++];

        //printf("ch = %c %d\n", ch, ch);
        //logic to detect preprocessor dircetive
        if(ch == '#')
        {
            printf("%s : preprocessor directive\n", str);
            break;
        }

        //logic to extract comments
        //if comment flag is set print lines until end comment "*/" is detected
        if(comment_flag == 1)
        {
            //printf("%s\n", str);
            while(ch != '/' && ch != '\0')
            {
                ch = str[i];
                //if "*/ " is detected unset comment flag
                if(str[i-1] == '*' && ch == '/')
                {
                    comment_flag = 0;
                   // printf("------------------------------------------------\n");
                }
                i++;
            }
            break;
        }

        //if double backslash or backslash and star is detected
        if(ch == '/' && (str[i] == '/' || str[i] == '*'))
        {
            ch = str[i];
            //if comment is single line print comment
            if(ch == '/')
            {
               // printf("%s : Comment\n", str);
                break;
            }
            //if comment is multiline set comment flag and print current line comment
            else if(ch == '*')
            {
                comment_flag  = 1;
               // printf("------------------------------------------------\n");
               // printf("Multiline comment : \n");
                // printf("%s\n", str);
                break;
            }
        }

        //to extract variables
        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            keyword_flag = 0;
            k = 0;

            //extract until space is encountered
            while(ch != ' ')
            {
                //if character is not symbol or operator add to buffer string else come out of loop
                if(is_symbol_or_operator(ch) == FAILURE)
                {
                    buffer_str[k++] = ch;
                    ch = str[i++];
                }
                else
                {
                    break;
                }
            }
            buffer_str[k] = '\0';

            //check if extracted token is keyword, if yes print it
            for(j = 0; j < 20; j++)
            {
                if(strcmp(buffer_str,kw_data[j]) == 0)
                {
                    keyword_flag = 1;
                    printf("%-20s : Keyword (datatype)\n", kw_data[j]);
                }
            }

            for(j = 0; j < 13; j++)
            {
                if(strcmp(buffer_str,kw_nondata[j]) == 0)
                {
                    keyword_flag = 1;
                    printf("%-20s : Keyword (non-datatype)\n", kw_nondata[j]);
                }
            }

            //if extracted keyword is not keyword, print it as identifier
            if(keyword_flag == 0)
            {
                printf("%-20s : Identifier\n",buffer_str);
            }
        }
        //extracting literal and printing it
        else if(ch == '"')
        {
            k = 0;
            buffer_str[k++] = ch;

            ch = str[i++];
            while(ch != '"')
            {
                    buffer_str[k++] = ch;
                    ch = str[i++];
            }
            buffer_str[k++] = ch;
            buffer_str[k] = '\0';
            printf("%-20s : Literal\n", buffer_str);
        } 
            //extracting constant values and printing it
        else if(ch >= '0' && ch <= '9')
        {
            k = 0;
            buffer_str[k++] = ch;

            ch = str[i++];
            while((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')|| ch == '.')
            {
                    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
                    {
                        invalid_id_flag = 1;
                    }
                    buffer_str[k++] = ch;
                    ch = str[i++];
            }
            //buffer_str[k++] = ch;
            buffer_str[k] = '\0';

            //print error if token is invalid
            if(invalid_id_flag == 1)
            {
                printf("\nTokens can't be generated\n\n");
                return FAILURE;
            }
            printf("%-20s : Constant\n", buffer_str);
        }

        //to extract symbols
        for(j = 0; j < sizeof(symbols) / sizeof(symbols[0]); j++)
            {
                if(ch == symbols[j])
                {
                    printf("%-20c : Special Character\n", ch);
                }
            }

        //to extract operators
        for(j = 0; j < sizeof(operators) / sizeof(operators[0]); j++)
            {
                if(ch == operators[j])
                {
                    if(ch == '<' || ch == '>')
                    {
                        if(str[i] == '=')
                        {
                            printf("%c%-19c : Operator\n", ch, str[i]);
                            i++;
                        }
                        else
                        {
                            printf("%-20c : Operator\n", ch);
                        }
                    }
                    else
                    {
                        printf("%-20c : Operator\n", ch);
                    }
                }
            }

    }

    return SUCCESS;
}
