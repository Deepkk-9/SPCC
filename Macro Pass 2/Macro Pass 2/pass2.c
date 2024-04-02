#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ala_line_counter = 0;

void printFile(char *filename, char *printName)
{
    char temp[20]; // Increased buffer size for readability
    printf("\n\n%s:\n", printName);
    FILE *f1 = fopen(filename, "r");
    if (f1 == NULL)
    {
        printf("Error opening file %s\n", filename);
        return;
    }
    while (fgets(temp, sizeof(temp), f1))
    {
        printf("\t%s", temp);
    }
    fclose(f1);
}

int main()
{
    int mnt_match_counter = 0;
    int mntc_counter = 0;
    FILE *f1, *f2, *f3, *f4, *f5, *f6;
    char mne[20], name[20], mnel[20], opnd1[20], arg[20];
    f1 = fopen("input.txt", "r");
    f2 = fopen("MNT.txt", "r");
    f3 = fopen("MDT.txt", "r");
    f4 = fopen("MNTC.txt", "r");
    f5 = fopen("output.txt", "w");
    f6 = fopen("ALAPASS2.txt", "w+");

    printFile("input.txt", "INPUT PROGRAM");

    fgets(arg, sizeof(arg), f4);
    mntc_counter = atoi(arg);

    while (fgets(mne, sizeof(mne), f1))
    {
        mnt_match_counter = 0;
        mne[strcspn(mne, "\n")] = 0;
        if (strcmp(mne, "MACRO") == 0)
        {
            // Process MACRO definition
            while (strcmp(mne, "MEND") != 0)
            {
                fprintf(f5, "%s\n", mne);
                fgets(mne, sizeof(mne), f1);
                mne[strcspn(mne, "\n")] = 0;
            }
        }
        else if (strcmp(mne, "END") == 0)
        {
            fprintf(f5, "%s\n", mne);
        }
        else
        {
            // Process other instructions

            char *token_part1 = strtok(mne, " ");
            char *token_part2 = strtok(NULL, " ");

            while (fgets(name, sizeof(name), f2))
            {
                name[strcspn(name, "\n")] == 0;

                char *mnt_part1 = strtok(name, " ");
                char *mnt_part2 = strtok(NULL, " ");
                char *mnt_part3 = strtok(NULL, " ");
                int mdt_index_in_mnt = atoi(mnt_part3);

                if (strcmp(token_part1, mnt_part2) == 0)
                {
                    fprintf(f6, "%d %s\n", ala_line_counter, token_part2);
                    ala_line_counter++;

                    while (fgets(mnel, sizeof(mnel), f3))
                    {
                        mnel[strcspn(mnel, "\n")] = 0;
                        char *mdt_part1 = strtok(mnel, " ");
                        char *mdt_part2 = strtok(NULL, " ");
                        int mdt_index = atoi(mdt_part1);
                        if (mdt_index == mdt_index_in_mnt)
                        {
                            while (fgets(opnd1, sizeof(opnd1), f3))
                            {
                                opnd1[strcspn(opnd1, "\n")] == 0;
                                char *macro_definition1 = strtok(opnd1, " ");
                                char *macro_definition2 = strtok(NULL, " ");
                                char *macro_definition3 = strtok(NULL, " ");

                                if (strcmp(macro_definition2, "MEND") != 0)
                                {
                                    fprintf(f5, "%s %s\n", macro_definition2, token_part2);
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                    }
                    fseek(f3, SEEK_SET, 0);
                    break;
                }
                else
                {
                    mnt_match_counter++;
                }
            }

            if (mnt_match_counter == mntc_counter)
            {
                fprintf(f5, "%s %s\n", token_part1, token_part2);
            }

            fseek(f2, SEEK_SET, 0);
        }
    }

    fclose(f1);
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
