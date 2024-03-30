#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mnt_line_counter = 0;
int mdt_line_counter = 0;

void printFile(char *filename, char *printName)
{
    char temp[20];
    printf("\n\n%s:\n", printName);
    FILE *f1 = fopen(filename, "r");
    while (fgets(temp, sizeof(temp), f1))
    {
        printf("\t%s", temp);
    }
    fclose(f1);
}

int main()
{
    FILE *f1, *f2, *f3;
    char mne[20], opnd[20], la[20];
    f1 = fopen("input.txt", "r");
    f2 = fopen("MNT.txt", "w+");
    f3 = fopen("MDT.txt", "w+");

    printFile("input.txt", "INPUT PROGRAM");

    while (fgets(mne, sizeof(mne), f1))
    {
        mne[strcspn(mne, "\n")] = 0;
        if (strcmp(mne, "MACRO") == 0)
        {
            fgets(la, sizeof(la), f1);
            la[strcspn(la, "\n")] = 0;
            char *token = strtok(la, " ");
            fprintf(f2, "%d %s %d\n", mnt_line_counter, token, mdt_line_counter);
            fprintf(f3, "%d %s\n", mdt_line_counter, token);

            mnt_line_counter++;
            mdt_line_counter++;
            fgets(mne, sizeof(mne), f1);
            mne[strcspn(mne, "\n")] = 0;
            while (strcmp(mne, "MEND") != 0)
            {
                fprintf(f3, "%d %s\n", mdt_line_counter, mne);
                mdt_line_counter++;
                fgets(mne, sizeof(mne), f1);
                mne[strcspn(mne, "\n")] = 0;
            }
            fprintf(f3, "%d %s\n", mdt_line_counter, mne);
            mdt_line_counter++;
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
    printFile("MNT.txt", "Macro Name Table");

    return 0;
}
