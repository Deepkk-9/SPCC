#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_CODE_LENGTH 10000
#define MAX_LINE_LENGTH 1000

void remove_code_after_return(char *code)
{
    char *return_pos = strstr(code, "return");
    if (return_pos != NULL)
    {
        char *newline_pos = strchr(return_pos, '\n');
        if (newline_pos != NULL)
        {
            *newline_pos = '\0';
        }
    }
}
int main()
{
    char code[MAX_CODE_LENGTH];
    char line[MAX_LINE_LENGTH];
    printf("Enter the code snippet representing a function (press Ctrl+Z to finish):\n");
    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL)
    {
        strcat(code, line);
    }
    printf("\nOriginal Code:\n%s\n", code);
    remove_code_after_return(code);
    printf("\nCode After Removing Code After Return Statement:\n%s\n", code);
    return 0;
}
