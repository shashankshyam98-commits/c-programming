#include<stdio.h>
#ifndef MACRO_H
#define MACRO_H

typedef struct macro
{
    char mname[50];
    char mbody[50];
    char args[5][50];
    int count;
    int is_function;
    struct macro *next;
} mll;

extern mll *headptr;

void macro(void);
void replace(void);
void replace_args(char *, char [5][50],
                  char [5][50], int, FILE *);

#endif

