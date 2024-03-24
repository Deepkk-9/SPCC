#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char op[10];
    char arg1[10];
    char arg2[10];
    char result[10];
} Quadruple;

Quadruple quad[20]; // Assuming a maximum of 20 quadruples
int quadlen = 0;

int addr = 100;

void generateQuadruple(char *op, char *arg1, char *arg2, char *result)
{
    strcpy(quad[quadlen].op, op);
    strcpy(quad[quadlen].arg1, arg1);
    strcpy(quad[quadlen].arg2, arg2);
    strcpy(quad[quadlen].result, result);
    quadlen++;
}

void printQuadruple()
{
    printf("\nQuadruple Table:\n");
    printf("Op\tArg1\tArg2\tResult\n");
    for (int i = 0; i < quadlen; i++)
    {
        printf("%s\t%s\t%s\t%s\n", quad[i].op, quad[i].arg1, quad[i].arg2, quad[i].result);
    }
}

void pm(char *exp, int l, int i)
{
    char exp1[10];
    strncpy(exp1, exp, l - i - 1);
    exp1[l - i - 1] = '\0';

    printf("Three address code:\ntemp=%s\ntemp1=%c%c temp\n", exp1, exp[l - i - 2], exp[l - i - 1]);

    char op[10], arg1[10], arg2[10], result[10];
    strcpy(op, "temp=");
    strcpy(arg1, exp1);
    sprintf(arg2, "%c%c", exp[l - i - 2], exp[l - i - 1]);
    strcpy(result, "temp1");

    generateQuadruple(op, arg1, arg2, result);
}

void divide(char *exp, int l, int i)
{
    char exp1[10];
    strncpy(exp1, exp, i + 2);
    exp1[i + 2] = '\0';

    printf("Three address code:\ntemp=%s\ntemp1=temp%c%c\n", exp1, exp[i + 2], exp[i + 3]);

    char op[10], arg1[10], arg2[10], result[10];
    strcpy(op, "temp=");
    strcpy(arg1, exp1);
    sprintf(arg2, "temp%c%c", exp[i + 2], exp[i + 3]);
    strcpy(result, "");

    generateQuadruple(op, arg1, arg2, result);
}

void plus(char *exp, int l, int i)
{
    char exp1[10];
    strncpy(exp1, exp, i + 2);
    exp1[i + 2] = '\0';

    printf("Three address code:\ntemp=%s\ntemp1=temp%c%c\n", exp1, exp[i + 2], exp[i + 3]);

    char op[10], arg1[10], arg2[10], result[10];
    strcpy(op, "temp=");
    strcpy(arg1, exp1);
    sprintf(arg2, "temp%c%c", exp[i + 2], exp[i + 3]);
    strcpy(result, "");

    generateQuadruple(op, arg1, arg2, result);
}

int main()
{
    int ch, l, i;
    char exp[10];

    while (1)
    {
        printf("\n1. Assignment\n2. Arithmetic\n3. Relational\n4. Print Quadruple Table\n5. Exit\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("\nEnter the expression with assignment operator: ");
            scanf("%s", exp);
            l = strlen(exp);
            i = 0;
            while (exp[i] != '=')
                i++;

            char exp1[10], exp2[10];
            strncpy(exp1, exp, i);
            exp1[i] = '\0';
            strcpy(exp2, exp + i + 1);

            printf("Three address code:\ntemp=%s\n%s=temp\n", exp2, exp1);

            char op[10], arg1[10], arg2[10], result[10];
            strcpy(op, "temp=");
            strcpy(arg1, exp2);
            strcpy(arg2, "");
            strcpy(result, exp1);

            generateQuadruple(op, arg1, arg2, result);
            break;

        case 2:
            printf("\nEnter the expression with arithmetic operator: ");
            scanf("%s", exp);
            l = strlen(exp);

            for (i = 0; i < l; i++)
            {
                if (exp[i] == '+' || exp[i] == '-')
                {
                    if (exp[i + 2] == '/' || exp[i + 2] == '*')
                    {
                        pm(exp, l, i);
                        break;
                    }
                    else
                    {
                        plus(exp, l, i);
                        break;
                    }
                }
                else if (exp[i] == '/' || exp[i] == '*')
                {
                    divide(exp, l, i);
                    break;
                }
            }
            break;

        case 3:
            printf("\nEnter the expression with relational operator: ");
            char id1[5], rel_op[5], id2[5]; // Renamed 'op' to 'rel_op'
            scanf("%s %s %s", id1, rel_op, id2);

            if (strcmp(rel_op, "<") == 0 || strcmp(rel_op, ">") == 0 || strcmp(rel_op, "<=") == 0 ||
                strcmp(rel_op, ">=") == 0 || strcmp(rel_op, "==") == 0 || strcmp(rel_op, "!=") == 0)
            {
                printf("\n%d\tif %s %s %s goto %d", addr, id1, rel_op, id2, addr + 3);
                addr++;
                printf("\n%d\tT:=0", addr);
                addr++;
                printf("\n%d\tgoto %d", addr, addr + 2);
                addr++;
                printf("\n%d\tT:=1\n", addr);

                // Generate quadruples for relational expression
                char temp1[10], temp2[10], temp3[10], temp4[10];
                sprintf(temp1, "%d", addr - 3);
                sprintf(temp2, "%d", addr + 3);
                sprintf(temp3, "%d", addr + 2);
                sprintf(temp4, "%d", addr);

                generateQuadruple(id1, rel_op, id2, temp1);
                generateQuadruple("goto", "", "", temp2);
                generateQuadruple("=", "T:=0", "", temp3);
                generateQuadruple("goto", "", "", temp4);
            }
            else
            {
                printf("Expression is incorrect");
            }
            break;

        case 4:
            printQuadruple();
            break;

        case 5:
            exit(0);
        }
    }

    return 0;
}
