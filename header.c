
#include<stdio.h>
#include<string.h>

void header(char *p)
{
    FILE *fp = fopen(p, "r");
    FILE *qp = fopen("temp", "w");

    char s[100], *t;

    if(fp == NULL || qp == NULL)
    {
        printf("File opening error\n");

        if(fp != NULL)
            fclose(fp);

        if(qp != NULL)
            fclose(qp);

        return;
    }

    while(fgets(s, 100, fp))
    {
        t = strstr(s, "#include");

        if(t != NULL &&
           (t[8] == '"' || t[8] == '<'))
        {
            if(t[8] == '"')
            {
                int i = 0;
                char hname[100];

                t = t + 9;

                while(*t && *t != '"' && i < 99)
                    hname[i++] = *t++;

                hname[i] = '\0';

                FILE *h = fopen(hname, "r");

                if(h == NULL)
                {
                    printf("%s file is not present in pwd\n", hname);
                    continue;
                }

                char ch;

                while((ch = fgetc(h)) != EOF)
                    fputc(ch, qp);

                fclose(h);
            }

            else if(t[8] == '<')
            {
                int i = 0;
                char hname[100], path[200];

                t = t + 9;

                while(*t && *t != '>' && i < 99)
                    hname[i++] = *t++;

                hname[i] = '\0';

                sprintf(path, "/usr/include/%s", hname);

                FILE *tp = fopen(path, "r");

                if(tp == NULL)
                {
                    printf("No predefined headerfile found\n");
                    continue;
                }

                char ch;

                while((ch = fgetc(tp)) != EOF)
                    fputc(ch, qp);

                fclose(tp);
            }
        }

        else
        {
            fputs(s, qp);
        }
    }

    fclose(fp);
    fclose(qp);
}

