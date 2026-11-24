
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "macro.h"

mll *headptr = NULL;

void macro()
{
    FILE *fp = fopen("temp", "r");

    char s[100], *t;

    if(fp == NULL)
        return;

    while(fgets(s, 100, fp))
    {
        t = s;

        while(isspace((unsigned char)*t))
            t++;

        if(strncmp(t, "#define", 7) == 0 &&
           isspace((unsigned char)t[7]))
        {
            mll *new = malloc(sizeof(mll));

            if(new == NULL)
                break;

            new->count = 0;
            new->is_function = 0;
            new->next = NULL;

            t += 7;

            while(isspace((unsigned char)*t))
                t++;

            int i = 0;

            while(*t && !isspace((unsigned char)*t) &&
                  *t != '(' && i < 49)
            {
                new->mname[i++] = *t++;
            }

            new->mname[i] = '\0';

            /* Read function-like macro arguments */

            if(*t == '(')
            {
                new->is_function = 1;

                t++;

                while(*t && *t != ')' && new->count < 5)
                {
                    while(isspace((unsigned char)*t) ||
                          *t == ',')
                        t++;

                    if(*t == ')')
                        break;

                    i = 0;

                    while((isalnum((unsigned char)*t) ||
                           *t == '_') && i < 49)
                    {
                        new->args[new->count][i++] = *t++;
                    }

                    new->args[new->count][i] = '\0';

                    if(i > 0)
                        new->count++;
                    else
                        break;
                }

                while(*t && *t != ')')
                    t++;

                if(*t == ')')
                    t++;
            }

            while(*t == ' ' || *t == '\t')
                t++;

            i = 0;

            while(*t && *t != '\n' && i < 49)
                new->mbody[i++] = *t++;

            new->mbody[i] = '\0';

            if(headptr == NULL)
                headptr = new;

            else
            {
                mll *last = headptr;

                while(last->next)
                    last = last->next;

                last->next = new;
            }
        }
    }

    fclose(fp);
}

