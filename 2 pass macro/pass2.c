#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ala_line_counter = 0;

void printFile(char *filename, char *printName)
{
    char temp[100]; // Increased buffer size for readability
    printf("\n\n%s:\n", printName);
    FILE *fl = fopen(filename, "r");
    if (fl == NULL)
    {
        printf("Error opening file %s\n", filename);
        return;
    }
    while (fgets(temp, sizeof(temp), fl))
    {
        printf("\t%s", temp);
    }
    fclose(fl);
}

int main()
{
    int mnt_match_counter = 0;
    int mntc_counter = 0;
    FILE *fl, *f2, *f3, *f4, *f5, *f6;
    char mne[20], name[20], mnel[20], opnd1[20], arg[20];
    fl = fopen("input.txt", "r");
    f2 = fopen("MNT.txt", "r");
    f3 = fopen("MDT.txt", "r");
    f4 = fopen("MNTC.txt", "r");
    f5 = fopen("output.txt", "w");
    f6 = fopen("ALAPASS2.txt", "w+");

    printFile("input.txt", "INPUT PROGRAM");

    fgets(arg, sizeof(arg), f4);
    mntc_counter = atoi(arg);

    while (fgets(mne, sizeof(mne), fl))
    {
        mne[strcspn(mne, "\n")] = 0;
        if (strcmp(mne, "MACRO") == 0)
        {
            // Process MACRO definition
            while (strcmp(mne, "MEND") != 0)
            {
                fprintf(f5, "%s\n", mne);
                fgets(mne, sizeof(mne), fl);
                mne[strcspn(mne, "\n")] = 0;
            }
            fprintf(f5, "%s\n", mne); // Include MEND in output
        }
        else if (strcmp(mne, "END") == 0)
        {
            fprintf(f5, "%s\n", mne);
        }
        else
        {
            // Process other instructions
            fgets(name, sizeof(name), f2);
            name[strcspn(name, "\n")] = 0;
            char *mnt_part1 = strtok(name, " ");
            char *mnt_part2 = strtok(NULL, " ");
            char *mnt_part3 = strtok(NULL, " ");
            int mdt_index_in_mnt = atoi(mnt_part3);

            if (strcmp(mne, mnt_part2) == 0)
            {
                fprintf(f6, "%d %s\n", ala_line_counter, mne);
                ala_line_counter++;

                while (fgets(mnel, sizeof(mnel), f3))
                {
                    mnel[strcspn(mnel, "\n")] = 0;
                    char *mdt_part1 = strtok(mnel, " ");
                    int mdt_index = atoi(mdt_part1);
                    if (mdt_index == mdt_index_in_mnt)
                    {
                        fgets(opnd1, sizeof(opnd1), f3);
                        opnd1[strcspn(opnd1, "\n")] = 0;
                        char *macro_definition = strtok(opnd1, " ");
                        if (strcmp(macro_definition, "MEND") == 0)
                        {
                            fprintf(f5, "%s %s\n", mne, macro_definition);
                            fseek(f2, SEEK_SET, 0);
                            break;
                        }
                        else
                        {
                            fprintf(f5, "%s %s %s\n", mne, mdt_part1, macro_definition);
                        }
                    }
                }
            }
        }
    }

    fclose(fl);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    fclose(f6);

    printf("\n\nOUTPUT:");
    printFile("ALAPASS2.txt", "ALA");
    printFile("output.txt", "OUTPUT FINAL PROGRAM");

    printf("\nPASS 2 is successful\n");

    return 0;
}
