#include <stdio.h>
#include <string.h>
#include <ctype.h>

void removeElement(int index, char words[20][20], int *size)
{
    int i;
    for (i = index; i < *size; i++)
    {
        strcpy(words[i], words[i + 1]);
    }
    (*size)--;
}
void main()
{

    // declarations
    char input[100], words[20][20], word[20];
    int freq[20];
    int i, j;
    int wordCounter = 0, size;
    printf("Enter a Sentence: ");
    scanf("%[^\n]", &input);

    // tokenizing the sentence
    char *token = strtok(input, " ");
    while (token != NULL)
    {
        strcpy(words[wordCounter], token);
        wordCounter++;
        token = strtok(NULL, " ");
    }
    // calculating the frequency
    for (i = 0; i < wordCounter; i++)
    {

        strcpy(word, words[i]);
        freq[i] = 1;

        for (j = i + 1; j < wordCounter; j++)
        {
            if (strcmp(word, words[j]) == 0)
            {
                freq[i]++;
                removeElement(j, words, &wordCounter);
                j--; // necessary as the elements shift by 1
            }
        }
    }
    printf("Word\t\tFrequency\n");
    printf("----\t\t---------\n");

    for (i = 0; i < wordCounter; i++)
    {
        printf("%s\t\t%d\n", words[i], freq[i]);
    }
    printf("WordCounter: %d\n", wordCounter);
}
