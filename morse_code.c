/* This program converts Morse code to English and English to Morse code */
/* Implemented in C language with file handling */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *morseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.",
    "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
    ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

void morseCodeConverter();
void convertToMorseCode();    
void convertToEnglishText();
void convertToEnglishWord(char *morse, char *output);

int main() 
{ 
    morseCodeConverter();
    return 0; 
}

void morseCodeConverter()
{
    int input;
    printf("\t\t\t\tMorse Code Converter\n\n");
    printf("Press 1 to convert English text into Morse code\n");
    printf("Press 2 to convert Morse code into English text\n");
    scanf("%d", &input);
    getchar(); // to clear buffer
    
    if (input == 2)
    {
        convertToEnglishText();
    }
    else if (input == 1)
    {
        convertToMorseCode();
    }
    else
    {
        printf("Invalid Input!\n");
    }
}

void convertToMorseCode()
{
    char text[1000];
    FILE *inputFile, *outputFile;
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");
    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    
    fgets(text, sizeof(text), inputFile);
    fclose(inputFile);
    
    printf("Morse Code: ");
    fprintf(outputFile, "Morse Code: ");
    for (int i = 0; text[i] != '\0'; ++i)
    {
        if (text[i] != ' ' && isalpha(text[i]))
        {
            printf("%s ", morseCode[toupper(text[i]) - 'A']);
            fprintf(outputFile, "%s ", morseCode[toupper(text[i]) - 'A']);
        }
        else if (text[i] == ' ')
        {
            printf("  ");
            fprintf(outputFile, "  ");
        }
    }
    printf("\n");
    fprintf(outputFile, "\n");
    fclose(outputFile);
    printf("Morse code has been written to output.txt\n");
}

void convertToEnglishText()
{
    char text[1000], word[100], output[1000] = "";
    int start = 0, i, j;
    FILE *inputFile, *outputFile;
    
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");
    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    
    fgets(text, sizeof(text), inputFile);
    fclose(inputFile);
    
    int len = strlen(text);
    for (i = 0, j = 0; i <= len; ++i)
    {
        if (text[i] == ' ' || text[i] == '\0')
        {
            word[j] = '\0';
            if (strlen(word) > 0)
            {
                char letter[2];
                convertToEnglishWord(word, letter);
                strcat(output, letter);
            }
            if (text[i] == ' ' && text[i + 1] == ' ' && text[i + 2] == ' ')
            {
                strcat(output, " ");
                i += 2;
            }
            j = 0;
        }
        else
        {
            word[j++] = text[i];
        }
    }
    printf("English Text: \"%s\"\n", output);
    fprintf(outputFile, "English Text: \"%s\"\n", output);
    fclose(outputFile);
    printf("English text has been written to output.txt\n");
}

void convertToEnglishWord(char *morse, char *output)
{
    for (int i = 0; i < 26; i++)
    {
        if (strcmp(morse, morseCode[i]) == 0)
        {
            output[0] = 'A' + i;
            output[1] = '\0';
            return;
        }
    }
    output[0] = '?'; // If not found
    output[1] = '\0';
}

