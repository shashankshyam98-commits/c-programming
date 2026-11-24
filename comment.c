
#include<stdio.h>

void comment(char *output)
{
    FILE *fp = fopen("temp1", "r");
    FILE *qp = fopen(output, "w");

    int ch, next;
    int str = 0, chr = 0, escape = 0;

    if(fp == NULL || qp == NULL)
    {
        printf("File opening error\n");

        if(fp != NULL)
            fclose(fp);

        if(qp != NULL)
            fclose(qp);

        return;
    }

    while((ch = fgetc(fp)) != EOF)
    {
        /* Inside string */

        if(str)
        {
            fputc(ch, qp);

            if(escape)
                escape = 0;

            else if(ch == '\\')
                escape = 1;

            else if(ch == '"')
                str = 0;
        }

        /* Inside character constant */

        else if(chr)
        {
            fputc(ch, qp);

            if(escape)
                escape = 0;

            else if(ch == '\\')
                escape = 1;

            else if(ch == '\'')
                chr = 0;
        }

        /* Starting string */

        else if(ch == '"')
        {
            str = 1;
            fputc(ch, qp);
        }

        /* Starting character constant */

        else if(ch == '\'')
        {
            chr = 1;
            fputc(ch, qp);
        }

        /* Comment checking */

        else if(ch == '/')
        {
            next = fgetc(fp);

            /* Single-line comment */

            if(next == '/')
            {
                while((ch = fgetc(fp)) != '\n' && ch != EOF);

                if(ch == '\n')
                    fputc('\n', qp);
            }

            /* Multiline comment */

            else if(next == '*')
            {
                while((ch = fgetc(fp)) != EOF)
                {
                    if(ch == '\n')
                        fputc('\n', qp);

                    if(ch == '*')
                    {
                        next = fgetc(fp);

                        if(next == '/')
                            break;

                        if(next == '\n')
                            fputc('\n', qp);

                        if(next == EOF)
                            break;
                    }
                }
            }

            else
            {
                fputc('/', qp);

                if(next != EOF)
                    fputc(next, qp);
            }
        }

        else
        {
            fputc(ch, qp);
        }
    }

    fclose(fp);
    fclose(qp);
}

