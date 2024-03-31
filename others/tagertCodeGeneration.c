#include <stdio.h>
#include <string.h>

typedef struct
{
    char result[10];
    char op[5];
    char arg1[10];
    char arg2[10];
} TAC;

int main()
{
    TAC tac[10];
    int numTAC = 0;
    int i;

    strcpy(tac[0].result, "t1");
    strcpy(tac[0].op, "=");
    strcpy(tac[0].arg1, "a");
    strcpy(tac[0].arg2, "b");

    strcpy(tac[1].result, "t2");
    strcpy(tac[1].op, "+");
    strcpy(tac[1].arg1, "t1");
    strcpy(tac[1].arg2, "c");

    numTAC = 2;

    // Print intermediate code
    printf("Intermediate Code:\n");
    for (i = 0; i < numTAC; i++)
    {
        printf("%s = %s %s %s\n", tac[i].result, tac[i].arg1, tac[i].op, tac[i].arg2);
    }

    printf("\nGenerated Target Code (Assembly Code):\n");

    for (i = 0; i < numTAC; i++)
    {
        if (strcmp(tac[i].op, "=") == 0)
        {
            printf("MOV %s, %s\n", tac[i].result, tac[i].arg1);
        }
        else if (strcmp(tac[i].op, "+") == 0)
        {
            printf("ADD %s, %s, %s\n", tac[i].result, tac[i].arg1, tac[i].arg2);
        }
    }

    return 0;
}
