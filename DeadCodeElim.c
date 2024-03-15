#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_SIZE 100

typedef struct
{
    char op;
    char arg1[10];
    char arg2[10];
    char result[10];
} Quadruple;

Quadruple quadTable[MAX_EXPR_SIZE];
int quadCount = 0;

void addQuad(char op, char arg1[], char arg2[], char result[])
{
    quadTable[quadCount].op = op;
    strcpy(quadTable[quadCount].arg1, arg1);
    strcpy(quadTable[quadCount].arg2, arg2);
    strcpy(quadTable[quadCount].result, result);
    quadCount++;
}

void generateTAC(char expr[])
{
    char tempResult[10];
    int tempCount = 1;

    for (int i = 0; expr[i] != '\0'; i++)
    {
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/')
        {
            sprintf(tempResult, "t%d", tempCount++);
            addQuad(expr[i], &(expr[i - 1]), &(expr[i + 1]), tempResult);
            expr[i + 1] = tempResult[1]; // Update expression with the temporary result
        }
    }

    // Add the last assignment quad for the final result
    addQuad('=', &(expr[strlen(expr) - 1]), NULL, "result");
}

void printQuadrupleTable()
{
    printf("\nQuadruple Table:\n");
    printf("--------------------------------------------------\n");
    printf("| Quad |   OP   |  Arg1  |  Arg2  |  Result  |\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < quadCount; i++)
    {
        printf("|  %-3d |   %-3c  |  %-4s  |  %-4s  |  %-6s  |\n", i + 1,
               quadTable[i].op, quadTable[i].arg1,
               quadTable[i].arg2, quadTable[i].result);
    }
    printf("--------------------------------------------------\n");
}

int main()
{
    char expression[MAX_EXPR_SIZE];

    printf("Enter an arithmetic expression (e.g., a + b * c - d):\n");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0'; // Remove newline character

    generateTAC(expression);
    printf("\nThree-Address Code (TAC):\n");
    printf("%s\n", expression);
    printQuadrupleTable();

    return 0;
}
