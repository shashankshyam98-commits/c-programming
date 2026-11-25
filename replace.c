
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "macro.h"


void replace_args(char *body, char args[5][50],
                  char values[5][50], int count, FILE *qp)
{
    char *p = body;
    char word[50];
    int i, j;

    while(*p)
    {
        if(isalpha((unsigned char)*p) || *p == '_')
        {
            i = 0;

            while(isalnum((unsigned char)*p) || *p == '_')
            {
                if(i < 49)
                    word[i++] = *p;

                p++;
            }

            word[i] = '\0';

            for(j = 0; j < count; j++)
            {
                if(strcmp(word, args[j]) == 0)
                    break;
            }

            if(j < count)
                fprintf(qp, "%s", values[j]);

            else
                fprintf(qp, "%s", word);
        }

        else
        {
            fputc(*p, qp);
            p++;
        }
    }
}


void replace()
{
    FILE *fp = fopen("temp", "r");
    FILE *qp = fopen("temp1", "w");

    char s[200], word[100];
    char values[5][50];

    char *p;
    int i, j, depth;

    if(fp == NULL || qp == NULL)
    {
        printf("File opening error\n");

        if(fp != NULL)
            fclose(fp);

        if(qp != NULL)
            fclose(qp);

        return;
    }

    while(fgets(s, 200, fp))
    {
        p = s;

        

        char *q = s;

        while(isspace((unsigned char)*q))
            q++;

        if(strncmp(q, "#define", 7) == 0 &&
           isspace((unsigned char)q[7]))
            continue;

        while(*p)
        {
            if(isalpha((unsigned char)*p) || *p == '_')
            {
                i = 0;

                while(isalnum((unsigned char)*p) || *p == '_')
                {
                    if(i < 99)
                        word[i++] = *p;

                    p++;
                }

                word[i] = '\0';

                mll *temp = headptr;

                while(temp)
                {
                    if(strcmp(word, temp->mname) == 0)
                        break;

                    temp = temp->next;
                }

                if(temp)
                {
                    

                    if(temp->is_function)
                    {
                        if(*p == '(')
                        {
                            p++;

                            for(j = 0; j < temp->count; j++)
                            {
                                i = 0;
                                depth = 0;

                                while(isspace((unsigned char)*p))
                                    p++;

                                while(*p &&
                                      !(*p == ',' && depth == 0) &&
                                      !(*p == ')' && depth == 0))
                                {
                                    if(*p == '(')
                                        depth++;

                                    if(*p == ')')
                                        depth--;

                                    if(i < 49)
                                        values[j][i++] = *p;

                                    p++;
                                }

                                values[j][i] = '\0';

                              

                                int k = 0;

                                while(isspace((unsigned char)values[j][k]))
                                    k++;

                                if(k > 0)
                                    memmove(values[j],
                                            values[j] + k,
                                            strlen(values[j] + k) + 1);

                                /* Remove trailing spaces */

                                i = strlen(values[j]);

                                while(i > 0 &&
                                      isspace((unsigned char)values[j][i-1]))
                                    values[j][--i] = '\0';

                                if(*p == ',')
                                    p++;
                            }

                            if(*p == ')')
                                p++;

                            replace_args(temp->mbody,
                                         temp->args,
                                         values,
                                         temp->count,
                                         qp);
                        }

                        else
                        {
                            fprintf(qp, "%s", word);
                        }
                    }

                    /* Object-like macro */

                    else
                    {
                        fprintf(qp, "%s", temp->mbody);
                    }
                }

                else
                {
                    fprintf(qp, "%s", word);
                }
            }

            else
            {
                fputc(*p, qp);
                p++;
            }
        }
    }

    fclose(fp);
    fclose(qp);
}

