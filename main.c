
#include<stdio.h>
#include<string.h>

void header(char *);
void macro(void);
void replace(void);
void comment(char *);

int main(int argc, char **argv)
{
    char output[1024];
    int i;

    if(argc != 2)
    {
        printf("Usage: ./preprocessor filename.c\n");
        return 0;
    }

    if(strlen(argv[1]) >= sizeof(output))
    {
        printf("Filename is too long\n");
        return 0;
    }

    strcpy(output, argv[1]);

    i = strlen(output);

    if(i < 3 || strcmp(output + i - 2, ".c") != 0)
    {
        printf("Input file must have .c extension\n");
        return 0;
    }


    strcpy(output + i - 2, ".i");

    header(argv[1]);

    macro();

    replace();

    comment(output);

    printf("Preprocessing completed: %s\n", output);

    return 0;
}

