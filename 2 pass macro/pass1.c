#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mnt_line_counter = 0;
int mdt_line_counter = 0;
int ala_line_counter = 0;

void printFile(char *filename, char *printName)
{
    char temp[20];
    printf("\n\n%s:\n", printName);
    FILE *fl = fopen(filename, "r");
    while (fgets(temp, sizeof(temp), fl))
    {
        printf("\t%s", temp);
    }
    fclose(fl);
}

int main()
{
    FILE *fl, *f2, *f3, *f4, *f5, *f6;
    char mne[20], opnd[20], la[20];
    fl = fopen("input.txt", "r");
    f2 = fopen("MNTC.txt", "w");
    f3 = fopen("MDTC.txt", "w");
    f4 = fopen("MNT.txt", "w");
    f5 = fopen("MDT.txt", "w");
    f6 = fopen("ALA.txt", "w");

    printf("PASS I of two pass macro processor:\n");
    printFile("input.txt", "INPUT PROGRAM");

    while (fgets(mne, sizeof(mne), fl))
    {
        mne[strcspn(mne, "\n")] = 0;
        if (strcmp(mne, "MACRO") == 0)
        {
            fgets(la, sizeof(la), fl);
            la[strcspn(la, "\n")] = 0;
            char *token = strtok(la, " ");
            fprintf(f5, "%d %s\n", mdt_line_counter, token);
            fprintf(f4, "%d %s %d\n", mnt_line_counter, token, mdt_line_counter);
            mnt_line_counter++;
            mdt_line_counter++;
            char *args = strtok(NULL, " ");
            fprintf(f6, "%d %s\n", ala_line_counter, args);
            ala_line_counter++;
            fgets(mne, sizeof(mne), fl);
            mne[strcspn(mne, "\n")] = 0;
            while (strcmp(mne, "MEND") != 0)
            {
                fprintf(f5, "%d %s\n", mdt_line_counter, mne);
                mdt_line_counter++;
                fgets(mne, sizeof(mne), fl);
                mne[strcspn(mne, "\n")] = 0;
            }
            fprintf(f5, "%d %s\n", mdt_line_counter, mne);
            mdt_line_counter++;
        }
    }

    fprintf(f2, "%d\n", mnt_line_counter);
    fprintf(f3, "%d\n", mdt_line_counter);

    fclose(fl);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    fclose(f6);

    printf("\n\nOUTPUT DATABASES:");
    printFile("MNTC.txt", "MNTC");
    printFile("MDTC.txt", "MDTC");
    printFile("MNT.txt", "MNT");
    printFile("MDT.txt", "MDT");
    printFile("ALA.txt", "ALA");

    printf("\n\nPASS I is successfully completed\n");

    return 0;
}
